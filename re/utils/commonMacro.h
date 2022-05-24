//
// Created by william on 2022/5/22.
//

#ifndef SIMPLERENDERENGINE_COMMONMACRO_H
#define SIMPLERENDERENGINE_COMMONMACRO_H

#include "logger.h"

#include <chrono>
#include <string>
#include <thread>

#define LOG_HELPER(level, ...) \
    Logger::getInstance().log(level, "[in File:" + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " in func:" + std::string(__FUNCTION__) + "]:" + __VA_ARGS__)

#define LOG_DEBUG(...) LOG_HELPER(Logger::Level::Debug, __VA_ARGS__)
#define LOG_INFO(...) LOG_HELPER(Logger::Level::Info, __VA_ARGS__)
#define LOG_WARN(...) LOG_HELPER(Logger::Level::Warn, __VA_ARGS__)
#define LOG_ERROR(...) LOG_HELPER(Logger::Level::Error, __VA_ARGS__)
#define LOG_FATAL(...) LOG_HELPER(Logger::Level::Fatal, __VA_ARGS__)

/// 安卓平台下导出动态库
#ifdef __cplusplus
    #define EXPORT extern "C" __attribute__((visibility("default")))
#else
    #define EXPORT extern __attribute__((visibility("default")))
#endif
/// __attribute__((visibility("default")))  // 默认，设置为：default之后就可以让外面的类看见了。
/// __attribute__((visibility("hideen")))  // 隐藏

#if defined(NDEBUG) && defined(__GNUC__)
    #define ASSERT_ONLY __attribute__((unused))
#else
    #define ASSERT_ONLY
#endif

#ifdef NDEBUG
    #define ASSERT(statement)
#else
    #define ASSERT(statement) assert(statement)
#endif

#define GET_CURRENT(__VA_ARGS__) (std::string(CURRENT_PROJECT_DIR) + __VA_ARGS__).c_str()

#define TO_STRING(s) #s
#define CONNECTION(x, y) x##y

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))
#define VECTOR_SIZE(x) (sizeof(x[0]) * x.size())

#define ENUM_ALIAS(name, member) \
    constexpr auto name##_##member = name::member

#define NO_REF_TYPE(t) std::remove_reference<decltype(*t)>::type
#define MAKE_SHARED(t, ...) std::make_shared<typename NO_REF_TYPE(t)>(__VA_ARGS__)
#define MAKE_UNIQUE(t, ...) std::make_unique<typename NO_REF_TYPE(t)>(__VA_ARGS__)

/// math macros
#define MATH_PI 3.1415926f
#define TWO_MATH_PI (MATH_PI * 2.0f)
#define MATH_DEG_TO_RAD(x) ((x)*0.0174532925f)
#define MATH_PIOVER2 1.57079632679489661923f
#define MATH_EPSILON 0.000001f

#endif //SIMPLERENDERENGINE_COMMONMACRO_H