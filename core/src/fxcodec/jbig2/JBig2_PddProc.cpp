// Copyright 2015 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "JBig2_PddProc.h"

#include "../../../../third_party/base/nonstd_unique_ptr.h"
#include "JBig2_GrdProc.h"
#include "JBig2_Image.h"
#include "JBig2_PatternDict.h"

CJBig2_PatternDict* CJBig2_PDDProc::decode_Arith(
    CJBig2_ArithDecoder* pArithDecoder,
    JBig2ArithCtx* gbContext,
    IFX_Pause* pPause) {
  FX_DWORD GRAY;
  CJBig2_Image* BHDC = nullptr;
  nonstd::unique_ptr<CJBig2_PatternDict> pDict(new CJBig2_PatternDict());
  pDict->NUMPATS = GRAYMAX + 1;
  pDict->HDPATS = FX_Alloc(CJBig2_Image*, pDict->NUMPATS);
  JBIG2_memset(pDict->HDPATS, 0, sizeof(CJBig2_Image*) * pDict->NUMPATS);

  nonstd::unique_ptr<CJBig2_GRDProc> pGRD(new CJBig2_GRDProc());
  pGRD->MMR = HDMMR;
  pGRD->GBW = (GRAYMAX + 1) * HDPW;
  pGRD->GBH = HDPH;
  pGRD->GBTEMPLATE = HDTEMPLATE;
  pGRD->TPGDON = 0;
  pGRD->USESKIP = 0;
  pGRD->GBAT[0] = -(int32_t)HDPW;
  pGRD->GBAT[1] = 0;
  if (pGRD->GBTEMPLATE == 0) {
    pGRD->GBAT[2] = -3;
    pGRD->GBAT[3] = -1;
    pGRD->GBAT[4] = 2;
    pGRD->GBAT[5] = -2;
    pGRD->GBAT[6] = -2;
    pGRD->GBAT[7] = -2;
  }
  FXCODEC_STATUS status =
      pGRD->Start_decode_Arith(&BHDC, pArithDecoder, gbContext, nullptr);
  while (status == FXCODEC_STATUS_DECODE_TOBECONTINUE) {
    pGRD->Continue_decode(pPause);
  }
  if (!BHDC)
    return nullptr;

  GRAY = 0;
  while (GRAY <= GRAYMAX) {
    pDict->HDPATS[GRAY] = BHDC->subImage(HDPW * GRAY, 0, HDPW, HDPH);
    GRAY = GRAY + 1;
  }
  delete BHDC;
  return pDict.release();
}

CJBig2_PatternDict* CJBig2_PDDProc::decode_MMR(CJBig2_BitStream* pStream,
                                               IFX_Pause* pPause) {
  FX_DWORD GRAY;
  CJBig2_Image* BHDC = nullptr;
  nonstd::unique_ptr<CJBig2_PatternDict> pDict(new CJBig2_PatternDict());
  pDict->NUMPATS = GRAYMAX + 1;
  pDict->HDPATS = FX_Alloc(CJBig2_Image*, pDict->NUMPATS);
  JBIG2_memset(pDict->HDPATS, 0, sizeof(CJBig2_Image*) * pDict->NUMPATS);

  nonstd::unique_ptr<CJBig2_GRDProc> pGRD(new CJBig2_GRDProc());
  pGRD->MMR = HDMMR;
  pGRD->GBW = (GRAYMAX + 1) * HDPW;
  pGRD->GBH = HDPH;
  FXCODEC_STATUS status = pGRD->Start_decode_MMR(&BHDC, pStream, nullptr);
  while (status == FXCODEC_STATUS_DECODE_TOBECONTINUE) {
    pGRD->Continue_decode(pPause);
  }
  if (!BHDC)
    return nullptr;

  GRAY = 0;
  while (GRAY <= GRAYMAX) {
    pDict->HDPATS[GRAY] = BHDC->subImage(HDPW * GRAY, 0, HDPW, HDPH);
    GRAY = GRAY + 1;
  }
  delete BHDC;
  return pDict.release();
}
