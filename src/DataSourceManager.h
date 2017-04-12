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

#ifndef SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H
#define SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H

#ifndef SHAREMIND_INTERNAL_
#error SHAREMIND_INTERNAL_ not defined
#endif

#include <map>
#include <memory>
#include <string>
#include "DataSource.h"
#include "datasourceapi.h"


namespace sharemind  {

class DataSourceManager {

private: /* Types: */

    typedef SharemindDataSourceManager DataSourceManagerWrapper;

public: /* Methods: */

    DataSourceManager();

    bool addDataSource(const std::string & name, const std::string & dbModule, const std::string & config);
    DataSource * getDataSource(const std::string & name);
    bool hasDataSource(const std::string & name) const;

    inline DataSourceManagerWrapper * getWrapper() { return &m_wrapper; }
    inline const DataSourceManagerWrapper * getWrapper() const { return &m_wrapper; }

private: /* Fields: */

    DataSourceManagerWrapper m_wrapper;

    std::map<std::string, std::unique_ptr<DataSource> > m_dataSources;

}; /* class DataSourceManager { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H */
