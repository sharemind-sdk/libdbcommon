/*
 * This file is a part of the Sharemind framework.
 * Copyright (C) Cybernetica AS
 *
 * All rights are reserved. Reproduction in whole or part is prohibited
 * without the written consent of the copyright owner. The usage of this
 * code is subject to the appropriate license agreement.
 */


#ifndef SHAREMIND_DBCOMMON_LASTERROR_H
#define SHAREMIND_DBCOMMON_LASTERROR_H

#include <string>


namespace sharemind {

namespace moduleLoader {

/**
  The LastError class provides a simple single error reporting functionality
  using std::string.
*/
class LastError {

public: /* Methods: */

    inline LastError()
        : m_lastError(m_errorStringNone)
        , m_lastErrorIsDynamic(false)
    {}

    inline ~LastError() {
        if (m_lastErrorIsDynamic)
            delete m_lastError;
        m_lastErrorIsDynamic = false; /* Just in case */
    }

    /** \returns whether an error is set. */
    inline bool hasError() const { return m_lastError != m_errorStringNone; }

    /** Clears any errors, if set. */
    inline void clearError() { resetErrorToStaticString(m_errorStringNone); }

    /** \returns the last error string or otherwise an empty string. */
    inline const std::string & lastError() const { return *m_lastError; }

protected: /* Methods: */

    /**
      Alias for resetErrorToDynamicString().
      \param[in] newErrorStr The new error string.
    */
    inline void resetError(const std::string & newErrorStr) {
        resetErrorToDynamicString(newErrorStr);
    }

    /**
      Sets the error string to a copy of newErrorStr.
      \param[in] newErrorStr The new error string.
    */
    inline void resetErrorToDynamicString(const std::string & newErrorStr) {
        if (m_lastErrorIsDynamic) {
            delete m_lastError;
            m_lastError = new std::string(newErrorStr);
        } else {
            m_lastError = new std::string(newErrorStr);
            m_lastErrorIsDynamic = true;
        }
    }

    /**
      \brief Sets the error string to newErrorStr without making a copy of it.

      \note This method is more effective in out-of-memory situatsions where new
      memory allocation could fail.

      \param[in] newErrorStr The new error string.
      \warning Because no copy is made, it is expected that the string at
               address newErrorStr remains a valid string until clearError() is
               called or LastError is destroyed.
    */
    inline void resetErrorToStaticString(const std::string * newErrorStr) {
        if (m_lastErrorIsDynamic)
            delete m_lastError;
        m_lastErrorIsDynamic = false;
        m_lastError = newErrorStr;
    }

private: /* Fields: */

    const std::string * m_lastError;
    bool m_lastErrorIsDynamic;

private: /* Static fields: */

    static const std::string * const m_errorStringNone;

}; /* class LastError { */

} /* namespace moduleLoader { */

} /* namespace sharemind { */

#endif /* SHAREMIND_DBCOMMON_LASTERROR_H */
