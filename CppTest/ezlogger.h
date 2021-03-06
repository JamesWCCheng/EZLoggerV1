﻿#ifndef __EZLOGGER_H__
#define __EZLOGGER_H__
#include <stdio.h>
#include <utility>
#include <string>
#include <stdint.h>
#include <cinttypes>

#ifndef GECKO // GECKO
#define printf_stderr printf

#define EZ_NONE ""
#define EZ_RED ""
#define EZ_LIGHT_RED ""
#define EZ_GREEN ""
#define EZ_LIGHT_GREEN ""
#define EZ_BLUE ""
#define EZ_LIGHT_BLUE ""
#define EZ_DARY_GRAY ""
#define EZ_CYAN ""
#define EZ_LIGHT_CYAN ""
#define EZ_PURPLE ""
#define EZ_LIGHT_PURPLE ""
#define EZ_BROWN ""
#define EZ_YELLOW ""
#define EZ_LIGHT_GRAY ""
#define EZ_WHITE ""
#endif
static const char* EZ_TAG = "EZLOG";
#define _(x) std::make_pair(x, #x)

#ifdef GECKO // GECKO
#define EZ_NONE "\033[m"
#define EZ_RED "\033[0;32;31m"
#define EZ_LIGHT_RED "\033[1;31m"
#define EZ_GREEN "\033[0;32;32m"
#define EZ_LIGHT_GREEN "\033[1;32m"
#define EZ_BLUE "\033[0;32;34m"
#define EZ_LIGHT_BLUE "\033[1;34m"
#define EZ_DARY_GRAY "\033[1;30m"
#define EZ_CYAN "\033[0;36m"
#define EZ_LIGHT_CYAN "\033[1;36m"
#define EZ_PURPLE "\033[0;35m"
#define EZ_LIGHT_PURPLE "\033[1;35m"
#define EZ_BROWN "\033[0;33m"
#define EZ_YELLOW "\033[1;33m"
#define EZ_LIGHT_GRAY "\033[0;37m"
#define EZ_WHITE "\033[1;37m"

#include "nsLiteralString.h"
#include "nsStringFwd.h"
#include "nsString.h"
#include "nsError.h" // For nsresult
#include "nsDebug.h" //For printf_stderr

#ifdef NS_WARNING_COLOR
#undef NS_WARNING
#define NS_WARNING(str)                                       \
    NS_DebugBreak(NS_DEBUG_WARNING, EZ_LIGHT_RED str "\033[m", nullptr, __FILE__, __LINE__)
#endif

#ifdef MOZ_LOG_886
#undef MOZ_LOG
#define REAL_LOG(X) printf_stderr(EZ_LIGHT_BLUE X "\033[m")
#define MOZ_LOG(_module,_level, arg) REAL_LOG arg
#endif

/*
nsString foo = NS_LITERAL_STRING
nsCString bar = NS_LITERAL_CSTRING

*/
namespace {
  // For nsAutoString
  void printInternal(const nsAutoString& aAutoStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName, NS_ConvertUTF16toUTF8(aAutoStr).get());
  }

  // For nsAutoCString
  void printInternal(const nsAutoCString& aAutoCStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName, aAutoCStr.get());
  }

  // For nsACString
  void printInternal(const nsACString& aACStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName, nsPromiseFlatCString(aACStr).get());
  }

  // For nsAString
  void printInternal(const nsAString& aAStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName,
      NS_ConvertUTF16toUTF8(nsPromiseFlatString(aAStr).get()).get());
  }

  void printInternal(nsresult aRes, const char* const aObjName)
  {
    printf_stderr("%s = %x", aObjName, static_cast<uint32_t>(aRes));
  }
}
#endif
namespace {
  // For std string
  void printInternal(std::string aStdStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName, aStdStr.c_str());
  }
  // For pointer
  void printInternal(void* aPtr, const char* const aObjName)
  {
    printf_stderr("%s = %p", aObjName, aPtr);
  }
  // For c style string
  void printInternal(const char* aStr, const char* const aObjName)
  {
    printf_stderr("%s = %s", aObjName, aStr);
  }
  // For float
  void printInternal(float aVal, const char* const aObjName)
  {
    printf_stderr("%s = %f", aObjName, aVal);
  }
  // For double
  void printInternal(double aVal, const char* const aObjName)
  {
    printf_stderr("%s = %lf", aObjName, aVal);
  }
  // For bool
  void printInternal(bool aVal, const char* const aObjName)
  {
    printf_stderr("%s = %d", aObjName, aVal);
  }
  // For int32_t
  void printInternal(int32_t aVal, const char* const aObjName)
  {
    printf_stderr("%s = %d", aObjName, aVal);
  }
  // For uint32_t
  void printInternal(uint32_t aVal, const char* const aObjName)
  {
    printf_stderr("%s = %u", aObjName, aVal);
  }
  // For uint64_t
  void printInternal(uint64_t aVal, const char* const aObjName)
  {
    printf_stderr("%s =%" PRIu64, aObjName, aVal);
  }
  // For int64_t
  void printInternal(int64_t aVal, const char* const aObjName)
  {
    printf_stderr("%s = %" PRId64, aObjName, aVal);
  }


  void ezPrint() {
    printf_stderr(EZ_NONE"\n");
  }

  template<class Type>
  void ezPrint(
    const std::pair<Type, const char *> &arg) {
    printInternal(arg.first, arg.second);
    ezPrint();
  }

  template<class Type, class... Types>
  void ezPrint(
    const std::pair<Type, const char *> &arg,
    const std::pair<Types, const char *> &... args) {
    // first is the real object, second is the object variable name.
    printInternal(arg.first, arg.second);
    printf_stderr(", ");
    ezPrint(args...);
  }

  template<class... Types>
  void PInternal(const char* aColor, const char* aFileName, const int aLineNum, Types&&...  args)
  {
    printf_stderr("[%s] %s%s(%d) ", EZ_TAG, aColor, aFileName, aLineNum);
    ezPrint(std::forward<Types>(args)...);
  }
} //namespace
#define P(...) PInternal("", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PR(...) PInternal(EZ_LIGHT_RED, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PG(...) PInternal(EZ_LIGHT_GREEN, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PB(...) PInternal(EZ_LIGHT_BLUE, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PX(EZ_COLOR, ...) PInternal(EZ_COLOR, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define P0(...) PInternal("", __FUNCTION__, __LINE__)
#define PR0(...) PInternal(EZ_LIGHT_RED, __FUNCTION__, __LINE__)
#define PG0(...) PInternal(EZ_LIGHT_GREEN, __FUNCTION__, __LINE__)
#define PB0(...) PInternal(EZ_LIGHT_BLUE, __FUNCTION__, __LINE__)
#define PX0(EZ_COLOR, ...) PInternal(EZ_COLOR, __FUNCTION__, __LINE__)

#endif