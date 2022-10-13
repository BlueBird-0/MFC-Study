// CDlgImage.cpp: 구현 파일
//

#include "pch.h"	//이전버전의 stdafx.h
#include "MfcStart.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDLGIMAGE, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, &CDlgImage::OnBnClickedBtnSendData)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

#include "MfcStartDlg.h"
void CDlgImage::OnBnClickedBtnSendData()
{
	CMfcStartDlg* pDlg = (CMfcStartDlg*)m_pParent;
	pDlg->CallFunction(123);
}


//다이얼로그 생성시 항상 call되는 함수
BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InitImageDC(320, 240, 8);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::InitImageDC(int nWidth, int nHeight, int nBpp)
{
	//이미지 생성
	//if (m_image == NULL)
	m_image.Create(nWidth, -nHeight, nBpp);
	//8bit 이미지에 대한 흑백설정
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image) {
		m_image.Draw(dc, 0, 0, 320, 240);
	}

	drawData(&dc);
}

void CDlgImage::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen; 
	pen.CreatePen(PS_SOLID, 1, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);	//기존 펜 저장
	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(5, 5);
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);	//기존 펜 불러오기
}