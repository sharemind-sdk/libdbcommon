 /*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H
#define SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <string>
#include <sharemind/common/ScopedObjectMap.h>

#include "datasourceapi.h"


namespace sharemind  {

class DataSource;

class DataSourceManager {
private: /* Types: */

    typedef SharemindDataSourceManager DataSourceManagerWrapper;
    typedef ScopedObjectMap<std::string, DataSource> DataSourceMap;

public: /* Methods: */

    DataSourceManager();

    bool addDataSource(const std::string & name, const std::string & dbModule, const std::string & config);
    DataSource * getDataSource(const std::string & name);
    bool hasDataSource(const std::string & name) const;

    inline DataSourceManagerWrapper * getWrapper() { return &m_wrapper; }
    inline const DataSourceManagerWrapper * getWrapper() const { return &m_wrapper; }

private: /* Fields: */

    DataSourceManagerWrapper m_wrapper;

    DataSourceMap m_dataSources;

}; /* class DataSourceManager { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_DATASOURCEMANAGER_H */
