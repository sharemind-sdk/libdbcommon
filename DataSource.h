 /*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_DBCOMMON_DATASOURCE_H
#define SHAREMIND_DBCOMMON_DATASOURCE_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <string>

#include "datasourceapi.h"


#ifdef __cplusplus
extern "C" {
#endif

const char * DataSource_name(DataSource * src) __attribute__ ((nonnull(1)));
const char * DataSource_module(DataSource * src) __attribute__ ((nonnull(1)));
const char * DataSource_conf(DataSource * src) __attribute__ ((nonnull(1)));

#ifdef __cplusplus
} /* extern "C" { */
#endif

namespace sharemind  {

class DataSource {
private: /* Types: */

    typedef ::DataSource DataSourceWrapper;

public: /* Methods: */

    DataSource(const std::string & name, const std::string & module, const std::string & conf);

    inline std::string & name() { return m_name; }
    inline const std::string & name() const { return m_name; }

    inline std::string & module() { return m_module; }
    inline const std::string & module() const { return m_module; }

    inline std::string & conf() { return m_conf; }
    inline const std::string & conf() const { return m_conf; }

    inline DataSourceWrapper * getWrapper() { return &m_wrapper; }
    inline const DataSourceWrapper * getWrapper() const { return &m_wrapper; }

private: /* Fields: */

    DataSourceWrapper m_wrapper;

    std::string m_name;
    std::string m_module;
    std::string m_conf;

}; /* class DataSource { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_DATASOURCE_H */
