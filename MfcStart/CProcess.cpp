// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "MfcStart.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}

//nTh 값보다 큰 값을 전부 더해서 리턴
int CProcess::getStarInfo(CImage* pImage, int nTh) {
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	int nSum = 0;
	for (int i = 0; i < nWidth*nHeight; i++)
	{
		if (fm[i] > nTh)
		{
			nSum++;
		}
	}
	return nSum;
}


// CProcess 멤버 함수
