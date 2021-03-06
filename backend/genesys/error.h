/* sane - Scanner Access Now Easy.

   Copyright (C) 2019 Povilas Kanapickas <povilas@radix.lt>

   This file is part of the SANE package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef BACKEND_GENESYS_ERROR_H
#define BACKEND_GENESYS_ERROR_H

#include "../include/sane/config.h"
#include "../include/sane/sane.h"
#include "../include/sane/sanei_backend.h"

#include <stdexcept>
#include <cstdarg>
#include <cstring>
#include <string>
#include <new>

#define DBG_error0      0	/* errors/warnings printed even with devuglevel 0 */
#define DBG_error       1	/* fatal errors */
#define DBG_init        2	/* initialization and scanning time messages */
#define DBG_warn        3	/* warnings and non-fatal errors */
#define DBG_info        4	/* informational messages */
#define DBG_proc        5	/* starting/finishing functions */
#define DBG_io          6	/* io functions */
#define DBG_io2         7	/* io functions that are called very often */
#define DBG_data        8	/* log image data */

namespace genesys {

class SaneException : public std::exception {
public:
    SaneException(SANE_Status status);
    SaneException(SANE_Status status, const char* format, ...)
    #ifdef __GNUC__
        __attribute__((format(printf, 3, 4)))
    #endif
    ;

    SaneException(const char* format, ...)
    #ifdef __GNUC__
        __attribute__((format(printf, 2, 3)))
    #endif
    ;

    SANE_Status status() const;
    const char* what() const noexcept override;

private:

    void set_msg();
    void set_msg(const char* format, std::va_list vlist);

    std::string msg_;
    SANE_Status status_;
};

// call a function and throw an exception on error
#define TIE(function)                                                                              \
    do {                                                                                           \
        SANE_Status tmp_status = function;                                                         \
        if (tmp_status != SANE_STATUS_GOOD) {                                                      \
            throw ::genesys::SaneException(tmp_status);                                            \
        }                                                                                          \
    } while (false)

class DebugMessageHelper {
public:
    static constexpr unsigned MAX_BUF_SIZE = 120;

    DebugMessageHelper(const char* func);
    DebugMessageHelper(const char* func, const char* format, ...)
    #ifdef __GNUC__
        __attribute__((format(printf, 3, 4)))
    #endif
    ;

    ~DebugMessageHelper();

    void status(const char* msg) { vstatus("%s", msg); }
    void vstatus(const char* format, ...)
    #ifdef __GNUC__
        __attribute__((format(printf, 2, 3)))
    #endif
    ;

    void clear() { msg_[0] = '\n'; }

    void log(unsigned level, const char* msg);
    void vlog(unsigned level, const char* format, ...)
    #ifdef __GNUC__
        __attribute__((format(printf, 3, 4)))
    #endif
    ;

private:
    const char* func_ = nullptr;
    char msg_[MAX_BUF_SIZE];
    unsigned num_exceptions_on_enter_ = 0;
};

#if defined(__GNUC__) || defined(__clang__)
#define GENESYS_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define GENESYS_CURRENT_FUNCTION __FUNCSIG__
#else
#define GENESYS_CURRENT_FUNCTION __func__
#endif

#define DBG_HELPER(var) DebugMessageHelper var(GENESYS_CURRENT_FUNCTION)
#define DBG_HELPER_ARGS(var, ...) DebugMessageHelper var(GENESYS_CURRENT_FUNCTION, __VA_ARGS__)

bool dbg_log_image_data();

template<class F>
SANE_Status wrap_exceptions_to_status_code(const char* func, F&& function)
{
    try {
        function();
        return SANE_STATUS_GOOD;
    } catch (const SaneException& exc) {
        DBG(DBG_error, "%s: got error: %s\n", func, exc.what());
        return exc.status();
    } catch (const std::bad_alloc& exc) {
        (void) exc;
        DBG(DBG_error, "%s: failed to allocate memory\n", func);
        return SANE_STATUS_NO_MEM;
    } catch (const std::exception& exc) {
        DBG(DBG_error, "%s: got uncaught exception: %s\n", func, exc.what());
        return SANE_STATUS_INVAL;
    } catch (...) {
        DBG(DBG_error, "%s: got unknown uncaught exception\n", func);
        return SANE_STATUS_INVAL;
    }
}

template<class F>
SANE_Status wrap_exceptions_to_status_code_return(const char* func, F&& function)
{
    try {
        return function();
    } catch (const SaneException& exc) {
        DBG(DBG_error, "%s: got error: %s\n", func, exc.what());
        return exc.status();
    } catch (const std::bad_alloc& exc) {
        (void) exc;
        DBG(DBG_error, "%s: failed to allocate memory\n", func);
        return SANE_STATUS_NO_MEM;
    } catch (const std::exception& exc) {
        DBG(DBG_error, "%s: got uncaught exception: %s\n", func, exc.what());
        return SANE_STATUS_INVAL;
    } catch (...) {
        DBG(DBG_error, "%s: got unknown uncaught exception\n", func);
        return SANE_STATUS_INVAL;
    }
}

template<class F>
void catch_all_exceptions(const char* func, F&& function)
{
    try {
        function();
    } catch (const SaneException& exc) {
        DBG(DBG_error, "%s: got exception: %s\n", func, exc.what());
    } catch (const std::bad_alloc& exc) {
        DBG(DBG_error, "%s: got exception: could not allocate memory: %s\n", func, exc.what());
    } catch (const std::exception& exc) {
        DBG(DBG_error, "%s: got uncaught exception: %s\n", func, exc.what());
    } catch (...) {
        DBG(DBG_error, "%s: got unknown uncaught exception\n", func);
    }
}

inline void wrap_status_code_to_exception(SANE_Status status)
{
    if (status == SANE_STATUS_GOOD)
        return;
    throw SaneException(status);
}

} // namespace genesys

#endif // BACKEND_GENESYS_ERROR_H
