/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "Modules.h"

#include <stdint.h>
#include "ModuleLoader.h"


namespace sharemind {

namespace moduleLoader {

SharemindModuleApiError Modules::push_back(const std::string & filename, const std::string & config) {
    if (m_mods.size() >= SIZE_MAX)
        return SHAREMIND_MODULE_API_OUT_OF_MEMORY;

    SharemindModule * const m = SharemindModule_new(m_loader->m_modapi,
                                                    filename.c_str(),
                                                    config.c_str());
    if (!m) {
        resetError(SharemindModuleApi_get_last_error_string(m_loader->m_modapi));
        return SharemindModuleApi_get_last_error(m_loader->m_modapi);
    }

    SharemindModuleApiError e = SharemindModule_mod_init(m);
    if (e != SHAREMIND_MODULE_API_OK) {
        SharemindModule_free(m);
        return e;
    }

    try {
        m_mods.push_back(m);
    } catch (const std::bad_alloc &) {
        SharemindModule_free(m);
        return SHAREMIND_MODULE_API_OUT_OF_MEMORY;
    }

    return SHAREMIND_MODULE_API_OK;
}

} /* namespace moduleLoader { */

} /* namespace sharemind { */
