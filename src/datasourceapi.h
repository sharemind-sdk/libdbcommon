/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */

#ifndef SHAREMIND_DBCOMMON_DATASOURCEAPI_H
#define SHAREMIND_DBCOMMON_DATASOURCEAPI_H

#ifndef SHAREMIND_ICONST
#ifdef SHAREMIND_INTERNAL__
#define SHAREMIND_ICONST
#else
#define SHAREMIND_ICONST const
#endif
#endif /* SHAREMIND_ICONST */


#ifdef __cplusplus
extern "C" {
#endif

/** Forward declarations: */
struct SharemindDataSourceManager_;
typedef SharemindDataSourceManager_ SharemindDataSourceManager;
struct SharemindDataSource_;
typedef SharemindDataSource_ SharemindDataSource;

/*******************************************************************************
    SharemindDataSourceManager
*******************************************************************************/

struct SharemindDataSourceManager_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    SharemindDataSource * (*get_source)(SharemindDataSourceManager * mgr, const char * name);
};

/*******************************************************************************
    SharemindDataSource
*******************************************************************************/

struct SharemindDataSource_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    const char * (* name)(SharemindDataSource * src);
    const char * (* module)(SharemindDataSource * src);
    const char * (* conf)(SharemindDataSource * src);
};

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_DBCOMMON_DATASOURCEAPI_H */

