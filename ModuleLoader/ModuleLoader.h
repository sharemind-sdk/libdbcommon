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

#include <cassert>
#include <map>
#include <set>
#include <string>
#include <boost/ptr_container/ptr_map.hpp>
#include <sharemind/libvm/libvm.h>

#include "LastError.h"


namespace sharemind {

namespace moduleLoader {

class Modules;

class ModuleLoader: public LastError {

    friend class Modules;

private: /* Types: */

    typedef boost::ptr_map<std::string, SharemindSyscallBinding> SyscallMap;
    typedef std::map<std::string, SyscallMap> ModuleSyscallMap;

public: /* Methods: */

    ModuleLoader(const std::set<std::string> & signatures);
    ~ModuleLoader();

    SharemindModule * addModule(const std::string & filename, const std::string & config = std::string());

    inline bool hasModule(const std::string & module) const {
        return m_moduleSyscallMap.find(module) != m_moduleSyscallMap.end();
    }

    const SharemindSyscallBinding * getSyscall(const std::string & module, const std::string & signature) const;

    inline bool setModuleFacility(const char * name, void * facility, void * context = NULL) {
        assert(name);
        return SharemindModuleApi_set_module_facility(m_modapi, name, facility, context);
    }

    inline const SharemindFacility * getModuleFacility(const char * name) {
        assert(name);
        return SharemindModuleApi_get_module_facility(m_modapi, name);
    }

private: /* Fields: */

    SharemindModuleApi * m_modapi;
    Modules * m_modules;
    ModuleSyscallMap m_moduleSyscallMap;

    std::set<std::string> m_reqSignatures;

}; /* class ModuleLoader { */

} /* namespace moduleLoader { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_LOADER_H */
