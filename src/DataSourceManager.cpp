/*
 * Copyright (C) 2015 Cybernetica
 *
 * Research/Commercial License Usage
 * Licensees holding a valid Research License or Commercial License
 * for the Software may use this file according to the written
 * agreement between you and Cybernetica.
 *
 * GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl-3.0.html.
 *
 * For further information, please contact us at sharemind@cyber.ee.
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
