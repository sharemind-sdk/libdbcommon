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
