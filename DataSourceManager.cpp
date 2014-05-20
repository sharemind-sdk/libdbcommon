 /*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include <cassert>

#define SHAREMIND_INTERNAL__
#include "DataSourceManager.h"

#include "DataSource.h"

#ifdef __cplusplus
extern "C" {
#endif

SharemindDataSource * SharemindDataSourceManager_get_source(SharemindDataSourceManager * mgr, const char * name) {
    assert(mgr);
    assert(mgr->internal);
    assert(name);

    try {
        sharemind::DataSourceManager * m = static_cast<sharemind::DataSourceManager *>(mgr->internal);

        sharemind::DataSource * src = m->getDataSource(name);
        if (!src)
            return nullptr;

        return src->getWrapper();
    } catch (...) {
        return nullptr;
    }
}

#ifdef __cplusplus
} /* extern "C" { */
#endif

namespace sharemind  {

DataSourceManager::DataSourceManager() {
    m_wrapper.internal = this;
    m_wrapper.get_source = &SharemindDataSourceManager_get_source;
}

bool DataSourceManager::addDataSource(const std::string & name, const std::string & dbModule, const std::string & config) {
    DataSource * const ds = new DataSource(name, dbModule, config);
    if (!m_dataSources.insert(const_cast<std::string &>(name), ds).second) {
        delete ds;
        return false;
    }

    return true;
}

DataSource * DataSourceManager::getDataSource(const std::string & name) {
    const DataSourceMap::iterator it = m_dataSources.find(name);
    if (it == m_dataSources.end())
        return nullptr;

    return it->second;
}

bool DataSourceManager::hasDataSource(const std::string & name) const {
    return m_dataSources.find(name) != m_dataSources.end();
}

} /* namespace sharemind { */
