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

#ifndef SHAREMIND_DBCOMMON_DATASOURCE_H
#define SHAREMIND_DBCOMMON_DATASOURCE_H

#ifndef SHAREMIND_INTERNAL__
#error SHAREMIND_INTERNAL__ not defined
#endif

#include <string>

#include "datasourceapi.h"


namespace sharemind  {

class DataSource {
private: /* Types: */

    typedef SharemindDataSource DataSourceWrapper;

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
