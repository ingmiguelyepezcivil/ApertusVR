/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2016 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __Platform_H_
#define __Platform_H_

#include "OgreConfig.h"

namespace Ogre {
/* Initial platform/compiler-related stuff to set.
*/
#define OGRE_PLATFORM_WIN32 1
#define OGRE_PLATFORM_LINUX 2
#define OGRE_PLATFORM_APPLE 3
#define OGRE_PLATFORM_APPLE_IOS 4
#define OGRE_PLATFORM_ANDROID 5
#define OGRE_PLATFORM_NACL 6
#define OGRE_PLATFORM_WINRT 7
#define OGRE_PLATFORM_EMSCRIPTEN 8
    
#define OGRE_COMPILER_MSVC 1
#define OGRE_COMPILER_GNUC 2
#define OGRE_COMPILER_BORL 3
#define OGRE_COMPILER_WINSCW 4
#define OGRE_COMPILER_GCCE 5
#define OGRE_COMPILER_CLANG 6

#define OGRE_ENDIAN_LITTLE 1
#define OGRE_ENDIAN_BIG 2

#define OGRE_ARCHITECTURE_32 1
#define OGRE_ARCHITECTURE_64 2

#define OGRE_CPP_VER_UNDEFINED 0L
#define OGRE_CPP_VER_98 199711L
#define OGRE_CPP_VER_11 201103L
#define OGRE_CPP_VER_14 201402L


/* Finds the compiler type and version.
*/
#if (defined( __WIN32__ ) || defined( _WIN32 )) && defined(__ANDROID__) // We are using NVTegra
#   define OGRE_COMPILER OGRE_COMPILER_GNUC
#   define OGRE_COMP_VER 470
#elif defined( __GCCE__ )
#   define OGRE_COMPILER OGRE_COMPILER_GCCE
#   define OGRE_COMP_VER _MSC_VER
//# include <staticlibinit_gcce.h> // This is a GCCE toolchain workaround needed when compiling with GCCE 
#elif defined( __WINSCW__ )
#   define OGRE_COMPILER OGRE_COMPILER_WINSCW
#   define OGRE_COMP_VER _MSC_VER
#elif defined( _MSC_VER )
#   define OGRE_COMPILER OGRE_COMPILER_MSVC
#   define OGRE_COMP_VER _MSC_VER
#elif defined( __clang__ )
#   define OGRE_COMPILER OGRE_COMPILER_CLANG
#   define OGRE_COMP_VER (((__clang_major__)*100) + \
        (__clang_minor__*10) + \
        __clang_patchlevel__)
#elif defined( __GNUC__ )
#   define OGRE_COMPILER OGRE_COMPILER_GNUC
#   define OGRE_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)
#elif defined( __BORLANDC__ )
#   define OGRE_COMPILER OGRE_COMPILER_BORL
#   define OGRE_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

#define OGRE_COMPILER_MIN_VERSION(COMPILER, VERSION) (OGRE_COMPILER == (COMPILER) && OGRE_COMP_VER >= (VERSION))

/* Finds the c++ version.*/
#ifdef  __cplusplus
    #if __cplusplus >= OGRE_CPP_VER_14 
        #define OGRE_CPP_VER OGRE_CPP_VER_14
    #elif __cplusplus >= OGRE_CPP_VER_11
        #define OGRE_CPP_VER OGRE_CPP_VER_11
    #elif __cplusplus >= OGRE_CPP_VER_98
        #define OGRE_CPP_VER OGRE_CPP_VER_98
    #else
        #define OGRE_CPP_VER OGRE_CPP_VER_UNDEFINED
    #endif
#endif


/* define OGRE_OVERRIDE macro */
#if OGRE_CPP_VER >= OGRE_CPP_VER_11 || OGRE_COMPILER_MIN_VERSION(OGRE_COMPILER_MSVC, 1600)
    #define OGRE_OVERRIDE override
#else
    #define OGRE_OVERRIDE 
#endif

/* See if we can use __forceinline or if we need to use __inline instead */
#if OGRE_COMPILER_MIN_VERSION(OGRE_COMPILER_MSVC, 1200)
    #define OGRE_FORCE_INLINE __forceinline
#elif OGRE_COMPILER_MIN_VERSION(OGRE_COMPILER_GNUC, 340)
    #define OGRE_FORCE_INLINE inline __attribute__((always_inline))
#else
        #define OGRE_FORCE_INLINE __inline
#endif

/* define OGRE_NORETURN macro */
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#	define OGRE_NORETURN __declspec(noreturn)
#elif OGRE_COMPILER == OGRE_COMPILER_GNUC || OGRE_COMPILER == OGRE_COMPILER_CLANG
#	define OGRE_NORETURN __attribute__((noreturn))
#else
#	define OGRE_NORETURN
#endif

/* Finds the current platform */
#if (defined( __WIN32__ ) || defined( _WIN32 )) && !defined(__ANDROID__)
#   include <sdkddkver.h>
#   if defined(WINAPI_FAMILY)
#       include <winapifamily.h>
#       if WINAPI_FAMILY == WINAPI_FAMILY_APP|| WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#           define OGRE_PLATFORM OGRE_PLATFORM_WINRT
#       else
#           define OGRE_PLATFORM OGRE_PLATFORM_WIN32
#       endif
#   else
#       define OGRE_PLATFORM OGRE_PLATFORM_WIN32
#   endif
#   define __OGRE_WINRT_STORE     (OGRE_PLATFORM == OGRE_PLATFORM_WINRT && WINAPI_FAMILY == WINAPI_FAMILY_APP)        // WindowsStore 8.0 and 8.1
#   define __OGRE_WINRT_PHONE     (OGRE_PLATFORM == OGRE_PLATFORM_WINRT && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)  // WindowsPhone 8.0 and 8.1
#   define __OGRE_WINRT_PHONE_80  (OGRE_PLATFORM == OGRE_PLATFORM_WINRT && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP && _WIN32_WINNT <= _WIN32_WINNT_WIN8) // Windows Phone 8.0 often need special handling, while 8.1 is OK
#   if defined(_WIN32_WINNT_WIN8) && _WIN32_WINNT >= _WIN32_WINNT_WIN8 // i.e. this is modern SDK and we compile for OS with guaranteed support for DirectXMath
#       define __OGRE_HAVE_DIRECTXMATH 1
#   endif
#   ifndef _CRT_SECURE_NO_WARNINGS
#       define _CRT_SECURE_NO_WARNINGS
#   endif
#   ifndef _SCL_SECURE_NO_WARNINGS
#       define _SCL_SECURE_NO_WARNINGS
#   endif
#elif defined(__EMSCRIPTEN__)
#   define OGRE_PLATFORM OGRE_PLATFORM_EMSCRIPTEN
#elif defined( __APPLE_CC__)
    // Device                                                     Simulator
    // Both requiring OS version 6.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 60000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 60000
#       define OGRE_PLATFORM OGRE_PLATFORM_APPLE_IOS
#   else
#       define OGRE_PLATFORM OGRE_PLATFORM_APPLE
#   endif
#elif defined(__ANDROID__)
#   define OGRE_PLATFORM OGRE_PLATFORM_ANDROID
#elif defined( __native_client__ ) 
#   define OGRE_PLATFORM OGRE_PLATFORM_NACL
#   ifndef OGRE_STATIC_LIB
#       error OGRE must be built as static for NaCl (OGRE_STATIC=true in CMake)
#   endif
#   ifdef OGRE_BUILD_RENDERSYSTEM_D3D9
#       error D3D9 is not supported on NaCl (OGRE_BUILD_RENDERSYSTEM_D3D9 false in CMake)
#   endif
#   ifdef OGRE_BUILD_RENDERSYSTEM_GL
#       error OpenGL is not supported on NaCl (OGRE_BUILD_RENDERSYSTEM_GL=false in CMake)
#   endif
#   ifndef OGRE_BUILD_RENDERSYSTEM_GLES2
#       error GLES2 render system is required for NaCl (OGRE_BUILD_RENDERSYSTEM_GLES2=false in CMake)
#   endif
#else
#   define OGRE_PLATFORM OGRE_PLATFORM_LINUX
#endif

    /* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(__arm64__) || defined(__aarch64__) || defined(__mips64) || defined(__mips64_)
#   define OGRE_ARCH_TYPE OGRE_ARCHITECTURE_64
#else
#   define OGRE_ARCH_TYPE OGRE_ARCHITECTURE_32
#endif

// For generating compiler warnings - should work on any compiler
// As a side note, if you start your message with 'Warning: ', the MSVC
// IDE actually does catch a warning :)
#define OGRE_QUOTE_INPLACE(x) # x
#define OGRE_QUOTE(x) OGRE_QUOTE_INPLACE(x)
#define OGRE_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

/* define OGRE_DEPRECATED macro */
#if OGRE_CPP_VER >= OGRE_CPP_VER_14
#   define OGRE_DEPRECATED [[deprecated]]
#elif OGRE_COMPILER == OGRE_COMPILER_MSVC
#   define OGRE_DEPRECATED __declspec(deprecated)
#elif OGRE_COMPILER == OGRE_COMPILER_GNUC || OGRE_COMPILER == OGRE_COMPILER_CLANG
#   define OGRE_DEPRECATED __attribute__ ((deprecated))
#else
#   pragma message("WARNING: You need to implement OGRE_DEPRECATED for this compiler")
#   define OGRE_DEPRECATED
#endif

/* define OGRE_DEPRECATED_EX(msg) macro */
#if OGRE_CPP_VER >= OGRE_CPP_VER_14
    #define OGRE_DEPRECATED_EX(message) [[deprecated(message)]]
#elif OGRE_COMPILER == OGRE_COMPILER_MSVC
    #define OGRE_DEPRECATED_EX(message) __declspec(deprecated(message))
#elif OGRE_COMPILER == OGRE_COMPILER_GNUC || OGRE_COMPILER == OGRE_COMPILER_CLANG
#   define OGRE_DEPRECATED_EX(message) __attribute__ ((deprecated))
#else
#   define OGRE_DEPRECATED_EX(message)
#endif

//----------------------------------------------------------------------------
// Windows Settings
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#   if defined( OGRE_STATIC_LIB )
        // Linux compilers don't have symbol import/export directives.
#       define _OgreExport
#       define _OgrePrivate
#   else
#       if defined( OGRE_NONCLIENT_BUILD )
#           define _OgreExport __declspec( dllexport )
#       else
#           if defined( __MINGW32__ )
#               define _OgreExport
#           else
#               define _OgreExport __declspec( dllimport )
#           endif
#       endif
#       define _OgrePrivate
#   endif
// Win32 compilers use _DEBUG for specifying debug builds.
// for MinGW, we set DEBUG
#   if defined(_DEBUG) || defined(DEBUG)
#       define OGRE_DEBUG_MODE 1
#   else
#       define OGRE_DEBUG_MODE 0
#   endif

// Disable unicode support on MingW for GCC 3, poorly supported in stdlibc++
// STLPORT fixes this though so allow if found
// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLBOX_UNICODE__ in _mingw.h
// GCC 4 is also fine
#if defined(__MINGW32__)
# if OGRE_COMP_VER < 400
#  if !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__) || OGRE_COMP_VER > 345
#    define OGRE_UNICODE_SUPPORT 1
#   else
#    define OGRE_UNICODE_SUPPORT 0
#   endif
#  else
#   define OGRE_UNICODE_SUPPORT 1
#  endif
# else
#  define OGRE_UNICODE_SUPPORT 1
# endif
#else
#  define OGRE_UNICODE_SUPPORT 1
#endif

#endif // OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT

//----------------------------------------------------------------------------
// Linux/Apple/iOS/Android/NaCl/Emscripten Settings
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS || \
    OGRE_PLATFORM == OGRE_PLATFORM_ANDROID || OGRE_PLATFORM == OGRE_PLATFORM_NACL || OGRE_PLATFORM == OGRE_PLATFORM_EMSCRIPTEN

// Enable GCC symbol visibility
#   if defined( OGRE_GCC_VISIBILITY )
#       define _OgreExport  __attribute__ ((visibility("default")))
#       define _OgrePrivate __attribute__ ((visibility("hidden")))
#   else
#       define _OgreExport
#       define _OgrePrivate
#   endif

// A quick define to overcome different names for the same function
#   define stricmp strcasecmp

#   ifdef DEBUG
#       define OGRE_DEBUG_MODE 1
#   else
#       define OGRE_DEBUG_MODE 0
#   endif

// Always enable unicode support for the moment
// Perhaps disable in old versions of gcc if necessary
#define OGRE_UNICODE_SUPPORT 1

#endif

//----------------------------------------------------------------------------
// Android Settings
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
#   ifdef OGRE_UNICODE_SUPPORT
#       undef OGRE_UNICODE_SUPPORT
#   endif
#   define OGRE_UNICODE_SUPPORT 1
    // A quick define to overcome different names for the same function
#   define stricmp strcasecmp
#   ifdef DEBUG
#       define OGRE_DEBUG_MODE 1
#   else
#       define OGRE_DEBUG_MODE 0
#   endif
#   ifndef CLOCKS_PER_SEC
#       define CLOCKS_PER_SEC  1000
#   endif
#endif

#ifndef __OGRE_HAVE_DIRECTXMATH
#   define __OGRE_HAVE_DIRECTXMATH 0
#endif

//----------------------------------------------------------------------------
// Endian Settings
// check for BIG_ENDIAN config flag, set OGRE_ENDIAN correctly
#ifdef OGRE_CONFIG_BIG_ENDIAN
#    define OGRE_ENDIAN OGRE_ENDIAN_BIG
#else
#    define OGRE_ENDIAN OGRE_ENDIAN_LITTLE
#endif

//----------------------------------------------------------------------------
// Set the default locale for strings
#if OGRE_PLATFORM == OGRE_PLATFORM_ANDROID
//  Locales are not supported by the C lib you have to go through JNI.
#   define OGRE_DEFAULT_LOCALE ""
#else
#   define OGRE_DEFAULT_LOCALE "C"
#endif

//----------------------------------------------------------------------------
// Library suffixes
// "_d" for debug builds, nothing otherwise
#if OGRE_DEBUG_MODE
#   define OGRE_BUILD_SUFFIX "_d"
#else
#   define OGRE_BUILD_SUFFIX ""
#endif

#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#define DECL_MALLOC __declspec(restrict) __declspec(noalias)
#else
#define DECL_MALLOC __attribute__ ((malloc))
#endif

// Stack-alignment hackery.
//
// If macro __OGRE_SIMD_ALIGN_STACK defined, means there requests
// special code to ensure stack align to a 16-bytes boundary.
//
// Note:
//   This macro can only guarantee callee stack pointer (esp) align
// to a 16-bytes boundary, but not that for frame pointer (ebp).
// Because most compiler might use frame pointer to access to stack
// variables, so you need to wrap those alignment required functions
// with extra function call.
//
#if defined(__INTEL_COMPILER)
// For intel's compiler, simply calling alloca seems to do the right
// thing. The size of the allocated block seems to be irrelevant.
#define _OGRE_SIMD_ALIGN_STACK()   _alloca(16)
#define _OGRE_SIMD_ALIGN_ATTRIBUTE

#elif OGRE_CPU == OGRE_CPU_X86 && (OGRE_COMPILER == OGRE_COMPILER_GNUC || OGRE_COMPILER == OGRE_COMPILER_CLANG) && (OGRE_ARCH_TYPE != OGRE_ARCHITECTURE_64)
// mark functions with GCC attribute to force stack alignment to 16 bytes
#define _OGRE_SIMD_ALIGN_ATTRIBUTE __attribute__((force_align_arg_pointer))

#elif defined(_MSC_VER)
// Fortunately, MSVC will align the stack automatically
#define _OGRE_SIMD_ALIGN_ATTRIBUTE

#else
#define _OGRE_SIMD_ALIGN_ATTRIBUTE

#endif

// Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef signed char int8;
// define uint64 type
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
    typedef unsigned __int64 uint64;
    typedef __int64 int64;
#else
    typedef unsigned long long uint64;
    typedef long long int64;
#endif

// Disable these warnings (too much noise)
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#ifndef _CRT_SECURE_NO_WARNINGS
#   define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _SCL_SECURE_NO_WARNINGS
#   define _SCL_SECURE_NO_WARNINGS
#endif
// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4786)
// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4503)
// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)
// disable: "non dll-interface class used as base for dll-interface class"
// Happens when deriving from Singleton because bug in compiler ignores
// template export
#   pragma warning (disable : 4275)
// disable: "C++ Exception Specification ignored"
// This is because MSVC 6 did not implement all the C++ exception
// specifications in the ANSI C++ draft.
#   pragma warning( disable : 4290 )
// disable: "no suitable definition provided for explicit template
// instantiation request" Occurs in VC7 for no justifiable reason on all
// #includes of Singleton
#   pragma warning( disable: 4661)
// disable: deprecation warnings when using CRT calls in VC8
// These show up on all C runtime lib code in VC8, disable since they clutter
// the warnings with things we may not be able to do anything about (e.g.
// generated code from nvparse etc). I doubt very much that these calls
// will ever be actually removed from VC anyway, it would break too much code.
#   pragma warning( disable: 4996)
// disable: "conditional expression constant", always occurs on 
// OGRE_MUTEX_CONDITIONAL when no threading enabled
#   pragma warning (disable : 201)
// disable: "unreferenced formal parameter"
// Many versions of VC have bugs which generate this error in cases where they shouldn't
#   pragma warning (disable : 4100)
// disable: "behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized"
// We have this issue in OgreMemorySTLAlloc.h - so we see it over and over
#   pragma warning (disable : 4345)
#endif

}

#endif
