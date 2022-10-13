#pragma once
#include "afxdialogex.h"
#include "CDoublePoint.h"

#define MAX_POINT 150
// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CDoublePoint cCenterOfGravity;	//원의 무게중심
	CImage m_image;
	CWnd* m_pParent;	//부모윈도우
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDLGIMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSendData();
	void InitImageDC(int nWidth, int nHeight, int nBpp);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

private :
	void drawData(CDC* pDC);
};
