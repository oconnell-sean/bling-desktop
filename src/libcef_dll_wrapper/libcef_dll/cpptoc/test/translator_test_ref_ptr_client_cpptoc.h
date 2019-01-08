// Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=68efb7154e628e7a9ce5370f85b24df8f9bb8e9b$
//

#ifndef CEF_LIBCEF_DLL_CPPTOC_TEST_TRANSLATOR_TEST_REF_PTR_CLIENT_CPPTOC_H_
#define CEF_LIBCEF_DLL_CPPTOC_TEST_TRANSLATOR_TEST_REF_PTR_CLIENT_CPPTOC_H_
#pragma once

#if !defined(WRAPPING_CEF_SHARED)
#error This file can be included wrapper-side only
#endif

#include "include/cef/capi/test/cef_translator_test_capi.h"
#include "include/cef/test/cef_translator_test.h"
#include "libcef_dll/cpptoc/cpptoc_ref_counted.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed wrapper-side only.
class CefTranslatorTestRefPtrClientCppToC
    : public CefCppToCRefCounted<CefTranslatorTestRefPtrClientCppToC,
                                 CefTranslatorTestRefPtrClient,
                                 cef_translator_test_ref_ptr_client_t> {
 public:
  CefTranslatorTestRefPtrClientCppToC();
};

#endif  // CEF_LIBCEF_DLL_CPPTOC_TEST_TRANSLATOR_TEST_REF_PTR_CLIENT_CPPTOC_H_