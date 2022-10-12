
// MfcStartDlg.h: 헤더 파일

#include "CDlgImage.h"

#pragma once


// CMfcStartDlg 대화 상자
class CMfcStartDlg : public CDialogEx
{
private :
	CImage m_image;
	BOOL ValidImgPos(int x, int y);
	BOOL ValidInCirclePos(int x, int y, int p1, int p2, int r);
// 생성입니다.
public:
	CMfcStartDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	
	CDlgImage* m_pDlgImage;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
	CBitmapButton* m_pBtnOnOff;
	void initButtons();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTest();
	//변수 네이밍룰: (선언위치)_(자료형)(변수명)
	int m_nNum1;
	int m_nNum2;
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
};
