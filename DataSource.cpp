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

const char * DataSource_name(DataSource * src) {
    assert(src);
    assert(src->internal);

    return static_cast<sharemind::DataSource *>(src->internal)->name().c_str();
}

const char * DataSource_module(DataSource * src) {
    assert(src);
    assert(src->internal);

    return static_cast<sharemind::DataSource *>(src->internal)->module().c_str();
}

const char * DataSource_conf(DataSource * src) {
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
    m_wrapper.name = &DataSource_name;
    m_wrapper.module = &DataSource_module;
    m_wrapper.conf = &DataSource_conf;
}

} /* namespace sharemind { */
