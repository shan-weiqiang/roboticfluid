// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _FASTRTPS_CONFIG_H_
#define _FASTRTPS_CONFIG_H_

#define FASTRTPS_VERSION_MAJOR 2
#define FASTRTPS_VERSION_MINOR 11
#define FASTRTPS_VERSION_MICRO 3
#define FASTRTPS_VERSION_STR "2.11.3"

#define GEN_API_VER 1

// C++20 support defines
#ifndef HAVE_CXX20
#define HAVE_CXX20 0
#endif /* ifndef HAVE_CXX20 */

// C++17 support defines
#ifndef HAVE_CXX17
#define HAVE_CXX17 0
#endif /* ifndef HAVE_CXX17 */

// C++14 support defines
#ifndef HAVE_CXX14
#define HAVE_CXX14 0
#endif /* ifndef HAVE_CXX14 */

// C++1Y support defines
#ifndef HAVE_CXX1Y
#define HAVE_CXX1Y 0
#endif /* ifndef HAVE_CXX1Y */

// C++11 support defines
#ifndef HAVE_CXX11
#define HAVE_CXX11 1
#endif /* ifndef HAVE_CXX11 */

// Endianness defines
#ifndef FASTDDS_IS_BIG_ENDIAN_TARGET
#define FASTDDS_IS_BIG_ENDIAN_TARGET 0
#endif /* ifndef FASTDDS_IS_BIG_ENDIAN_TARGET */

// Security
#ifndef HAVE_SECURITY
#define HAVE_SECURITY 0
#endif /* ifndef HAVE_SECURITY */

//Sqlite3 support
#ifndef HAVE_SQLITE3
#define HAVE_SQLITE3 1
#endif /* ifndef HAVE_SQLITE3 */

// Using thirdparty shared_mutex
#define USE_THIRDPARTY_SHARED_MUTEX 1

// TLS support
#ifndef TLS_FOUND
#define TLS_FOUND 0
#endif /* ifndef TLS_FOUND */

// Strict real-time
#ifndef HAVE_STRICT_REALTIME
#define HAVE_STRICT_REALTIME 0
#endif /* ifndef HAVE_STRICT_REALTIME */

/* Log Macros */

// Enable compilation for eProsima Log Macros
#ifndef ENABLE_OLD_LOG_MACROS_
#define ENABLE_OLD_LOG_MACROS_ 1
#endif /* ifndef ENABLE_OLD_LOG_MACROS_ */

// Log Info
#ifndef FASTDDS_ENFORCE_LOG_INFO
/* #undef FASTDDS_ENFORCE_LOG_INFO */
#endif
#ifndef HAVE_LOG_NO_INFO
#define HAVE_LOG_NO_INFO 1
#endif /* ifndef HAVE_LOG_NO_INFO */

// Log Warning
#ifndef HAVE_LOG_NO_WARNING
#define HAVE_LOG_NO_WARNING 0
#endif /* ifndef HAVE_LOG_NO_WARNING */

// Log Error
#ifndef HAVE_LOG_NO_ERROR
#define HAVE_LOG_NO_ERROR 0
#endif /* ifndef HAVE_LOG_NO_ERROR */

// Statistics
/* #undef FASTDDS_STATISTICS */

// Deprecated macro
#if __cplusplus >= 201402L
#define FASTRTPS_DEPRECATED(msg) [[ deprecated(msg) ]]
#elif defined(__GNUC__) || defined(__clang__)
#define FASTRTPS_DEPRECATED(msg) __attribute__ ((deprecated(msg)))
#elif defined(_MSC_VER)
#define FASTRTPS_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#define FASTRTPS_DEPRECATED(msg)
#endif /* if __cplusplus >= 201402L */

// Deprecation with version
#define FASTDDS_DEPRECATED_UNTIL(major, entity_name, msg)                                                           \
    static_assert(FASTRTPS_VERSION_MAJOR < major, #entity_name " reached deprecation version " #major);             \
    FASTRTPS_DEPRECATED(#entity_name " has been deprecated and will be removed on major version " #major ". " msg)

#define FASTDDS_TODO_BEFORE(major, minor, msg)                                          \
    static_assert((FASTRTPS_VERSION_MAJOR < major) ||                                   \
            (FASTRTPS_VERSION_MAJOR == major && FASTRTPS_VERSION_MINOR < minor),  \
            "TODO before version " #major "." #minor " : " #msg);

#endif // _FASTRTPS_CONFIG_H_
