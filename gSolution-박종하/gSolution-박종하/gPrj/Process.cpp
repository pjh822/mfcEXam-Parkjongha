// Process.cpp: 구현 파일
//

#include "stdafx.h"
#include "gPrj.h"
#include "Process.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

int CProcess::getStarInfo(CImage* pImage, int nTh)
{
    unsigned char* fm = (unsigned char*)pImage->GetBits();
    int nWidth = pImage->GetWidth();
    int nHeight = pImage->GetHeight();
    int nPitch = pImage->GetPitch();

    int nSum = 0;
    for (int k = 0; k < nWidth * nHeight; k++) {
        if (fm[k] > 100)
            nSum++;
    }

    return nSum;
}
