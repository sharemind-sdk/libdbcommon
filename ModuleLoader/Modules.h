/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_DBCOMMON_MODULES_H
#define SHAREMIND_DBCOMMON_MODULES_H

#include <stdint.h>
#include <string>
#include <vector>
#include <sharemind/libmodapi/libmodapi.h>
#include "LastError.h"


namespace sharemind {

namespace moduleLoader {

class ModuleLoader;

class Modules : public LastError {

public: /* Methods: */

    inline Modules(ModuleLoader * moduleLoader)
        : m_loader(moduleLoader) {}

    inline ~Modules() {
        while (!m_mods.empty())
            pop_back();
    }

    SharemindModuleApiError push_back(const std::string & filename, const std::string & config = std::string());

    inline void pop_back() {
        SharemindModule_free(m_mods.back());
        m_mods.pop_back();
    }

    inline SharemindModule & back() const {
        return *(m_mods.back());
    }

private: /* Fields: */

    ModuleLoader * m_loader;
    std::vector<SharemindModule *> m_mods;

}; /* class ModuleLoader { */

} /* namespace moduleLoader { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_MODULES_H */
