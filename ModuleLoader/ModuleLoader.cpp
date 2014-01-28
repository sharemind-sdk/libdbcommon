/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#define SHAREMIND_INTERNAL__
#include "ModuleLoader.h"

#include <sharemind/likely.h>
#include <sstream>
#include <stdint.h>
#include "Modules.h"

namespace sharemind {

namespace moduleLoader {

namespace {
namespace Loader_ErrorString {
const std::string None = "No error.";
const std::string Oom = "Out of memory!";

// ModuleLoader::addModule() errors:
const std::string OomAfterFailedModuleLoad = "Out of memory after failing to load module!";
const std::string OomAfterDuplicateSyscall = "Out of memory after failing to load module because of duplicate system call!";
const std::string OomAfterDuplicateModuleName = "Out of memory after failing to load module because of duplicate module name!";
const std::string OomAfterInvalidSyscall = "Out of memory after failing to load module because of invalid system call!";
const std::string OomAfterMissingSyscall = "Out of memory after failing to load module because of missing system call!";
} // namespace Loader_ErrorString
} // anonymous namespace


ModuleLoader::ModuleLoader(const std::set<std::string> & signatures)
    : m_reqSignatures(signatures)
{
    m_modules = new Modules(this);
    try {
        m_modapi = SharemindModuleApi_new();
        if (!m_modapi)
            throw std::bad_alloc();
    } catch (...) {
        delete m_modules;
        throw;
    }
}

ModuleLoader::~ModuleLoader() {
    delete m_modules;
    SharemindModuleApi_free(m_modapi);
}

SharemindModule * ModuleLoader::addModule(const std::string & filename, const std::string & config) {
    const std::string * staticOomError = &Loader_ErrorString::Oom;
    try { // on OOM set error and return NULL, on graceful (bool) return NULL;

        SharemindModuleApiError mError = m_modules->push_back(filename, config);
        if (unlikely(mError != SHAREMIND_MODULE_API_OK)) {
            if (unlikely(mError == SHAREMIND_MODULE_API_OUT_OF_MEMORY)) {
                throw std::bad_alloc();
            } else {
                staticOomError = &Loader_ErrorString::OomAfterFailedModuleLoad;
                std::ostringstream oss;
                oss << "Code "
                    << SharemindModuleApiError_toString(mError)
                    << " while loading module from \""
                    << filename << "\":" << m_modules->lastError();
                resetError(oss.str());
                throw false; // Graceful
            }
        }

        try {
            SharemindModule & m = m_modules->back();

            SyscallMap syscallMap;

            const char * moduleName = SharemindModule_get_name(&m);

            /* Load system calls */
            size_t numSyscalls = SharemindModule_get_num_syscalls(&m);
            for (size_t i = 0u; i < numSyscalls; ++i) {
                const SharemindSyscall * sc = SharemindModule_get_syscall(&m, i);
                assert(sc);

                /* Check if system call signature is valid */
                const char * scName = SharemindSyscall_get_signature(sc);
                if (unlikely(!m_reqSignatures.count(scName))) {
                    staticOomError = &Loader_ErrorString::OomAfterInvalidSyscall;
                    std::ostringstream oss;
                    oss << "In module \"" << moduleName << "\", the system call \""
                        << scName << "\" is not an authorized signature.";
                    resetError(oss.str());
                    throw false; // Graceful
                }

                /* Allocate new binding */
                SharemindSyscallBinding * scBinding = new SharemindSyscallBinding;

                try {
                    scBinding->wrapper = SharemindSyscall_get_wrapper(sc);
                    scBinding->moduleHandle = SharemindModule_get_handle(&m);

                    /* Check for duplicate system call signatures */
                    std::string name(scName);
                    std::pair<SyscallMap::iterator, bool> rv = syscallMap.insert(name, scBinding);
                    if (unlikely(!rv.second)) {
                        staticOomError = &Loader_ErrorString::OomAfterDuplicateSyscall;
                        std::ostringstream oss;
                        oss << "In module \"" << moduleName << "\", the system call \""
                            << scName << "\" is provided twice in the same module.";
                        resetError(oss.str());
                        throw false; // Graceful
                    }
                } catch (...) {
                    delete scBinding;
                    throw;
                }
            }

            /* Check if we have all the required signatures */
            if (unlikely(syscallMap.size() != m_reqSignatures.size())) {
                staticOomError = &Loader_ErrorString::OomAfterMissingSyscall;
                std::ostringstream oss;
                oss << "Module \"" << moduleName << "\" is missing the following system calls: ";

                std::set<std::string>::const_iterator it;
                size_t count = 0;
                for (it = m_reqSignatures.begin();
                        it != m_reqSignatures.end();
                        ++it) {
                    if (!syscallMap.count(*it))
                        oss << (count++ ? ", " : "") << *it;
                }

                oss << ".";
                resetError(oss.str());
                throw false; // Graceful
            }

            /* Check for duplicate module names */
            std::pair<ModuleSyscallMap::iterator, bool> rv =
                m_moduleSyscallMap.insert(ModuleSyscallMap::value_type(moduleName, syscallMap));
            if (unlikely(!rv.second)) {
                staticOomError = &Loader_ErrorString::OomAfterDuplicateModuleName;
                std::ostringstream oss;
                oss << "Module name \"" << moduleName
                    << "\" is already provided by another module.";
                resetError(oss.str());
                throw false; // Graceful
            }
        } catch (...) {
            m_modules->pop_back();
            throw;
        }
    } catch (const std::bad_alloc &) {
        resetErrorToStaticString(staticOomError);
        return NULL;
    } catch (bool) { // graceful
        return NULL;
    }

    SharemindModule & m = m_modules->back();
    return &m;
}

const SharemindSyscallBinding * ModuleLoader::getSyscall(const std::string & module, const std::string & signature) const {
    ModuleSyscallMap::const_iterator msit = m_moduleSyscallMap.find(module);
    if (msit == m_moduleSyscallMap.end())
        return NULL;

    const SyscallMap & syscallMap = msit->second;
    SyscallMap::const_iterator sit = syscallMap.find(signature);
    if (sit == syscallMap.end())
        return NULL;

    return sit->second;
}

} /* namespace moduleLoader { */

} /* namespace sharemind { */
