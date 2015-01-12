/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_DBCOMMON_LOADER_H
#define SHAREMIND_DBCOMMON_LOADER_H

#include <algorithm>
#include <cassert>
#include <cstring>
#include <LogHard/Logger.h>
#include <map>
#include <set>
#include <sharemind/libvm/libvm.h>
#include <sharemind/likely.h>
#include <sharemind/ScopedObjectMap.h>
#include <string>
#include <vector>


namespace sharemind {

namespace moduleLoader {

class ModuleLoader {

private: /* Types: */

    typedef std::set<std::string> StringSet;
    typedef ScopedObjectMap<std::string, SharemindSyscallWrapper> SyscallMap;
    typedef std::map<std::string, SyscallMap> ModuleSyscallMap;

public: /* Methods: */

    ModuleLoader(const std::set<std::string> & signatures,
                 const LogHard::Logger & logger)
        : m_reqSignatures(signatures)
        , m_logger(logger, "ModuleLoader:")
    {
        /// \todo Throw a better exception
        m_modApi = SharemindModuleApi_new(nullptr, nullptr, nullptr);
        if (unlikely(!m_modApi))
            throw std::bad_alloc();
    }

    ~ModuleLoader() {
        std::for_each(m_modules.begin(),
                      m_modules.end(),
                      &SharemindModule_free);
        m_modules.clear();
        SharemindModuleApi_free(m_modApi);
    }

    SharemindModule * addModule(const std::string & filename,
                                const std::string & config = std::string())
    {
        struct GracefulException {};
        SharemindModule * const m =
                SharemindModuleApi_newModule(m_modApi,
                                             filename.c_str(),
                                             config.c_str());
        if (unlikely(!m)) {
            m_logger.error()
                    << "Error while loading module \"" << filename << "\": "
                    << SharemindModuleApi_lastErrorString(m_modApi);
            return nullptr;
        }

        try {
            SharemindModuleApiError e = SharemindModule_init(m);
            if (unlikely(e != SHAREMIND_MODULE_API_OK)) {
                m_logger.error()
                        << "Error initializing module: Module returned "
                        << SharemindModuleApiError_toString(e);
                throw GracefulException();
            }

            const char * const moduleName = SharemindModule_name(m);
            assert(moduleName);
            if (unlikely(m_moduleSyscallMap.count(moduleName))) {
                m_logger.error() << "Module name \"" << moduleName
                                 << "\" is already provided by another module.";
                throw GracefulException();
            }

            /* Load system calls */
            const size_t numSyscalls = SharemindModule_numSyscalls(m);
            if (unlikely(numSyscalls != m_reqSignatures.size())) {
                m_logger.error() << "Invalid number of system calls in module!";
                throw GracefulException();
            }
            for (size_t i = 0u; i < numSyscalls; i++) {
                const SharemindSyscall * const sc =
                        SharemindModule_syscall(m, i);
                assert(sc);

                /* Check if system call signature is valid */
                const char * const scName = SharemindSyscall_signature(sc);
                assert(scName);
                if (unlikely(!m_reqSignatures.count(scName))) {
                    m_logger.error() << "The system call \"" << scName
                                     << "\" is not allowed.";
                    throw GracefulException();
                }
            }

            assert(!m_moduleSyscallMap.count(moduleName));
            SyscallMap & syscallMap = m_moduleSyscallMap[moduleName];
            try {
                for (size_t i = 0u; i < numSyscalls; i++) {
                    const SharemindSyscall * const sc =
                            SharemindModule_syscall(m, i);
                    assert(sc);
                    const char * const scName =
                            SharemindSyscall_signature(sc);
                    assert(scName);

                    SharemindSyscallWrapper * const scBinding =
                            new SharemindSyscallWrapper(
                                SharemindSyscall_wrapper(sc));
                    try {
                        #ifndef NDEBUG
                        std::pair<SyscallMap::iterator, bool> rv =
                        #endif
                                syscallMap.insert(scName, scBinding);
                        assert(rv.second);
                    } catch (...) {
                        delete scBinding;
                        throw;
                    }
                }
                m_modules.push_back(m);
                return m;
            } catch (...) {
                m_moduleSyscallMap.erase(moduleName);
                throw;
            }
        } catch (const std::exception & e) {
            m_logger.error() << "Error loading database module " << filename
                             << ": " << e.what();
            SharemindModule_free(m);
            return nullptr;
        } catch (const GracefulException &) {
            SharemindModule_free(m);
            return nullptr;
        }
    }

    inline bool hasModule(const std::string & module) const {
        return m_moduleSyscallMap.find(module) != m_moduleSyscallMap.end();
    }

    SharemindSyscallWrapper getSyscall(const std::string & module,
                                       const std::string & signature)
            const
    {
        ModuleSyscallMap::const_iterator msit = m_moduleSyscallMap.find(module);
        if (msit == m_moduleSyscallMap.end())
            return { nullptr, nullptr };

        const SyscallMap & syscallMap = msit->second;
        SyscallMap::const_iterator sit = syscallMap.find(signature);
        if (sit == syscallMap.end())
            return { nullptr, nullptr };

        return *(sit->second);
    }

    inline void setModuleFacility(const char * name,
                                  void * facility,
                                  void * context = nullptr)
    {
        assert(name);
        const auto r = SharemindModuleApi_setModuleFacility(m_modApi,
                                                            name,
                                                            facility,
                                                            context);
        if (r != SHAREMIND_MODULE_API_OK)
            throw std::bad_alloc(); /// \todo Throw a better exception
    }

    inline const SharemindFacility * moduleFacility(const char * name) {
        assert(name);
        return SharemindModuleApi_moduleFacility(m_modApi, name);
    }

private: /* Fields: */

    std::vector<SharemindModule *> m_modules;
    SharemindModuleApi * m_modApi;
    ModuleSyscallMap m_moduleSyscallMap;

    StringSet m_reqSignatures;

    const LogHard::Logger m_logger;

}; /* class ModuleLoader { */

} /* namespace moduleLoader { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_LOADER_H */