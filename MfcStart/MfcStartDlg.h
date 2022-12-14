
// MfcStartDlg.h: 헤더 파일

#include "CDlgImage.h"
#include "CDoublePoint.h"

#pragma once


// CMfcStartDlg 대화 상자
class CMfcStartDlg : public CDialogEx
{
private :
	CImage m_image;
	BOOL ValidImgPos(int x, int y);
	BOOL ValidInCirclePos(int x, int y, int p1, int p2, int r, CImage* cImage);
// 생성입니다.
public:
	CMfcStartDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CDC m_MemDC;
	CDC m_cDC;
	
	CDlgImage* m_pDlgImage;
	CDlgImage* m_pDlgImageResult;

	CDlgImage* m_pDlgImageCircle;
	CDlgImage* m_pDlgImageCircleResult;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	CBitmapButton* m_pBtnOnOff;
	void initButtons();
	void InitCircleDlg();
	void DrawRandomCircle();
	void DrawCircleResult(CDoublePoint cCenterOfGravity);
	CDoublePoint FindCenterOfGravity(CImage* pImage, int nTh=100);
	void FindCircleOutLine();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTest();
	//변수 네이밍룰: (선언위치)_(자료형)(변수명)
	int m_nNum1;
	int m_nNum2;
	int m_nCircleSize;
	afx_msg void OnEnChangeEditNum();
	afx_msg void OnEnChangeEditNum2();
	afx_msg void OnEnChangeEditNum1();
	afx_msg void OnBnClickedBntImage();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	void UpdateDisplay();
	void MoveRect();
	void MoveCircle();
	void InitImageDC(int nWidth, int nHeight, int nBpp );
	afx_msg void OnBnClickedBtnAction();
	void DrawBackground();
	afx_msg void OnBnClickedBtnOnoff();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnModal();
	void CallFunction(int n);
	afx_msg void OnBnClickedModalTest();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnBnClickedBtnCircleMake();
};
