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
struct DataSourceManager_;
typedef DataSourceManager_ DataSourceManager;
struct DataSource_;
typedef DataSource_ DataSource;

/*******************************************************************************
    DataSourceManager
*******************************************************************************/

struct DataSourceManager_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    DataSource * (*get_source)(DataSourceManager * mgr, const char * name);
};

/*******************************************************************************
    DataSource
*******************************************************************************/

struct DataSource_ {
    SHAREMIND_ICONST void * SHAREMIND_ICONST internal;

    const char * (* name)(DataSource * src);
    const char * (* module)(DataSource * src);
    const char * (* conf)(DataSource * src);
};

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_DBCOMMON_DATASOURCEAPI_H */

