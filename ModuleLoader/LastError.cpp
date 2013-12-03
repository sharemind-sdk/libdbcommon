/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#include "LastError.h"


namespace {
const std::string noErrorString;
} /* namespace { */

const std::string * const sharemind::moduleLoader::LastError::m_errorStringNone = &noErrorString;
