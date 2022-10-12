// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
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
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

#include "MfcStartDlg.h"
void CDlgImage::OnBnClickedBtnSendData()
{
	CMfcStartDlg* pDlg = (CMfcStartDlg*)m_pParent;
	pDlg->CallFunction(123);
}
