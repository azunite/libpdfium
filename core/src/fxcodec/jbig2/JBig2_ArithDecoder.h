// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_SRC_FXCODEC_JBIG2_JBIG2_ARITHDECODER_H_
#define CORE_SRC_FXCODEC_JBIG2_JBIG2_ARITHDECODER_H_

class CJBig2_BitStream;

struct JBig2ArithCtx {
  unsigned int MPS;
  unsigned int I;
};

class CJBig2_ArithDecoder {
 public:
  explicit CJBig2_ArithDecoder(CJBig2_BitStream* pStream);

  ~CJBig2_ArithDecoder();

  int DECODE(JBig2ArithCtx* pCX);

 private:
  void INITDEC();
  void BYTEIN();

  unsigned char B;
  unsigned int C;
  unsigned int A;
  unsigned int CT;
  CJBig2_BitStream* m_pStream;
};

#endif  // CORE_SRC_FXCODEC_JBIG2_JBIG2_ARITHDECODER_H_
