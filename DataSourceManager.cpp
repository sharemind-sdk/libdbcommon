 /*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#define SHAREMIND_INTERNAL__

#include "DataSourceManager.h"

#include <cassert>
#include "DataSource.h"


extern "C" {

SharemindDataSource * SharemindDataSourceManager_get_source(
        SharemindDataSourceManager * mgr,
        const char * name)
{
    assert(mgr);
    assert(mgr->internal);
    assert(name);

    try {
        sharemind::DataSourceManager & m =
                *static_cast<sharemind::DataSourceManager *>(mgr->internal);
        sharemind::DataSource * const src = m.getDataSource(name);
        return src ? src->getWrapper() : nullptr;
    } catch (...) {
        return nullptr;
    }
}

} /* extern "C" { */


namespace sharemind  {

DataSourceManager::DataSourceManager()
    : m_wrapper{this,  &SharemindDataSourceManager_get_source}
{}

bool DataSourceManager::addDataSource(const std::string & name,
                                      const std::string & dbModule,
                                      const std::string & config)
{
    DataSource * const ds = new DataSource(name, dbModule, config);
    try {
        return m_dataSources.insert(name, ds).second
               || (delete ds, false);
    } catch (...) {
        delete ds;
        throw;
    }
}

DataSource * DataSourceManager::getDataSource(const std::string & name) {
    const DataSourceMap::iterator it = m_dataSources.find(name);
    return (it != m_dataSources.end()) ? it->second : nullptr;
}

bool DataSourceManager::hasDataSource(const std::string & name) const
{ return m_dataSources.find(name) != m_dataSources.end(); }

} /* namespace sharemind { */
