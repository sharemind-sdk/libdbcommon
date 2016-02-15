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

#include <cassert>

#define SHAREMIND_INTERNAL_
#include "DataSource.h"


#ifdef __cplusplus
extern "C" {
#endif

const char * SharemindDataSource_name(SharemindDataSource * src) {
    assert(src);
    assert(src->internal);

    return static_cast<sharemind::DataSource *>(src->internal)->name().c_str();
}

const char * SharemindDataSource_module(SharemindDataSource * src) {
    assert(src);
    assert(src->internal);

    return static_cast<sharemind::DataSource *>(src->internal)->module().c_str();
}

const char * SharemindDataSource_conf(SharemindDataSource * src) {
    assert(src);
    assert(src->internal);

    return static_cast<sharemind::DataSource *>(src->internal)->conf().c_str();
}

#ifdef __cplusplus
} /* extern "C" { */
#endif

namespace sharemind {

DataSource::DataSource(const std::string & name, const std::string & module, const std::string & conf)
    : m_name(name)
    , m_module(module)
    , m_conf(conf)
{
    m_wrapper.internal = this;
    m_wrapper.name = &SharemindDataSource_name;
    m_wrapper.module = &SharemindDataSource_module;
    m_wrapper.conf = &SharemindDataSource_conf;
}

} /* namespace sharemind { */
