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

#ifndef SHAREMIND_DBCOMMON_DATASOURCEAPI_H
#define SHAREMIND_DBCOMMON_DATASOURCEAPI_H

#ifndef SHAREMIND_ICONST
#ifdef SHAREMIND_INTERNAL_
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
    SharemindDataSource * (*get_source)(SharemindDataSourceManager * mgr, const char * name);
};

/*******************************************************************************
    SharemindDataSource
*******************************************************************************/

struct SharemindDataSource_ {
    const char * (* name)(SharemindDataSource * src);
    const char * (* module)(SharemindDataSource * src);
    const char * (* conf)(SharemindDataSource * src);
};

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* SHAREMIND_DBCOMMON_DATASOURCEAPI_H */

