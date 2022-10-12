
// MfcStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcStart.h"
#include "MfcStartDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
//#pragma commment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMfcStartDlg 대화 상자



CMfcStartDlg::CMfcStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
	, m_nNum1(0), m_nNum2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_nNum1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_nNum2);
}

// 메세지맵 (이벤트를 정의)
BEGIN_MESSAGE_MAP(CMfcStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, &CMfcStartDlg::OnBnClickedBtnTest)
	ON_EN_CHANGE(IDC_EDIT_NUM1, &CMfcStartDlg::OnEnChangeEditNum1)
	ON_EN_CHANGE(IDC_EDIT_NUM2, &CMfcStartDlg::OnEnChangeEditNum2)
	ON_BN_CLICKED(IDC_BNT_IMAGE, &CMfcStartDlg::OnBnClickedBntImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMfcStartDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMfcStartDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMfcStartDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_ONOFF, &CMfcStartDlg::OnBnClickedBtnOnoff)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MODAL, &CMfcStartDlg::OnBnClickedBtnModal)
END_MESSAGE_MAP()


// CMfcStartDlg 메시지 처리기

BOOL CMfcStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATIC_RESULT, _T("0"));
	m_pDlgImage = new CDlgImage;	//메모리 해제 필요
	m_pDlgImage->Create(IDD_CDLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMfcStartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMfcStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMfcStartDlg::OnBnClickedBtnTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	
	int m_nResult = m_nNum1 + m_nNum2;
	SetDlgItemText(IDC_STATIC_RESULT, _T(""));
	CString m_strResult;
	m_strResult.Format(_T("%d"), m_nResult);

	/*namespace 사용방법
	std::cout << m_nNum << std::endl;*/
	cout << m_nNum1 << "+" << m_nNum2 << "=" << m_nResult << endl;
	SetDlgItemText(IDC_STATIC_RESULT, m_strResult);
	UpdateData(false);

	//AfxMessageBox(_T("hello windows"));
}

void CMfcStartDlg::OnEnChangeEditNum()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMfcStartDlg::OnEnChangeEditNum2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMfcStartDlg::OnEnChangeEditNum1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMfcStartDlg::OnBnClickedBntImage()
{

	InitImageDC(320, 240, 8);	
	DrawBackground();

	//최초 이미지 드로우
	CClientDC dc(this);
	UpdateDisplay();
}

void CMfcStartDlg::InitImageDC(int nWidth, int nHeight, int nBpp)
{
	//이미지 생성
	if (m_image == NULL)
		m_image.Create(nWidth, nHeight, nBpp);
	//8bit 이미지에 대한 흑백설정
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		m_image.SetColorTable(0, 256, rgb);
	}
}

void CMfcStartDlg::DrawBackground()
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();	//비트맵에 지정된 실제 비트값에 대한 포인터
	//배경 그라디언트
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight(); 
	int nPitch = m_image.GetPitch();
	//memset(fm, 0xff, nWidth * nHeight);
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			fm[j * nPitch + i] = j;
		}
	}
}

CString g_strFileImage = _T("./image.bmp");
void CMfcStartDlg::OnBnClickedBtnSave()
{
	m_image.Save(g_strFileImage);
}


void CMfcStartDlg::OnBnClickedBtnLoad()
{
	if (m_image != NULL)
		m_image.Destroy();
	m_image.Load(g_strFileImage);

	UpdateDisplay();
}

void CMfcStartDlg::UpdateDisplay()
{
	//이미지 드로우
	CClientDC dc(this);
	m_image.Draw(dc, 10, 240 / 2);
}

void CMfcStartDlg::MoveRect()
{
	static int nSttX = 0;
	static int nSttY = 0;
	if (m_image == NULL)
		return;
	int nBoxColor = 255;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nBpp = m_image.GetPitch();

	//이미지 생성
	if (m_image == NULL)
		m_image.Create(nWidth, nHeight, nBpp);
	//8bit 이미지에 대한 흑백설정
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	
	int nPitch = m_image.GetPitch();	//이미지의 개별 픽셀을 찾는 데 사용
	unsigned char* fm = (unsigned char*)m_image.GetBits();	//비트맵에 지정된 실제 비트값에 대한 포인터

	//memset(fm, 0xff, nWidth * nHeight);
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{
			fm[j * nPitch + i] = j;
		}
	}
	//이미지에 box그림그리기
	for (int j = 5+ nSttY; j < nSttY+50; j++)
	{
		for (int i = 5+ nSttX; i < nSttX+30; i++) {
			if(ValidImgPos(i, j))
				fm[j * nPitch + i] = nBoxColor;
		}
	}
	nSttX++;
	nSttY++;
	UpdateDisplay();
}
void CMfcStartDlg::MoveCircle()
{
	static int nCenterX = 320;
	static int nCenterY = 0;

	if (m_image == NULL)
		return;
	int nBoxColor = 255;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nBpp = m_image.GetPitch();

	int nPitch = m_image.GetPitch();	//이미지의 개별 픽셀을 찾는 데 사용
	unsigned char* fm = (unsigned char*)m_image.GetBits();	//비트맵에 지정된 실제 비트값에 대한 포인터

	//동그라미 출력  (x - a)2 + (y - b)2 = r2
	int r = 30;
	for (int j = -r; j < +r; j++)
	{
		for (int i = -r; i < +r; i++)
		{
			int nPx = nCenterX + i;
			int nPy = nCenterY + j;
			//if(pow(nPx-nCenterX,2)+pow(nPy-nCenterY,2) < pow(r, 2))
			if (ValidInCirclePos(nCenterX, nCenterY, nPx, nPy, r))
			{
				fm[(nCenterY + j) * nPitch + (nCenterX + i)] = 150;
			}

		}
	}
	
	nCenterX--;
	nCenterY++;
	UpdateDisplay();
}

void CMfcStartDlg::OnBnClickedBtnAction()
{
	for (size_t i = 0; i < 100; i++)
	{
		MoveRect();
		MoveCircle();
		//딜레이 Sleep 함수 사용
		Sleep(10);
	}
}

BOOL CMfcStartDlg::ValidImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

BOOL CMfcStartDlg::ValidInCirclePos(int x, int y, int p1, int p2, int r) {
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	//밖으로 나갔을 때 처리
	if (p1 < 0 || p2 < 0 || p1 >= nWidth || p2 >= nHeight)
		return false;
	
	if (pow(p1 - x, 2) + pow(p2 - y, 2) < pow(r, 2))
		return true;
	return false;
}

void CMfcStartDlg::OnBnClickedBtnOnoff()
{
	//버튼 이미지 토글
	static bool bOn = false;
	if (bOn) {
		m_pBtnOnOff->LoadBitmaps(IDB_ON);
	}
	else {
		m_pBtnOnOff->LoadBitmaps(IDB_OFF);
	}
	bOn = !bOn;
}


BOOL CMfcStartDlg::OnEraseBkgnd(CDC* pDC)
{
	//클라이언트DC를 얻어와, 색칠하는 방법
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, RGB(25, 32, 40));
	return TRUE;


	//비트맵 이미지로 배경을 처리하는 방법
	/*CPngImage image; 
	image.Load(IDB_BASE, nullptr);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&image);

	pDC->BitBlt(0,0, 800, 800, &dc, 0,0, SRCCOPY);
	dc.SelectObject(pOldBitmap);
	return TRUE;*/

	
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CMfcStartDlg::initButtons()
{
	//bitmap버튼 추가
	CRect rect(0, 0, 200, 50);
	GetDlgItem(IDC_BTN_ONOFF)->GetClientRect(&rect);
	m_pBtnOnOff = new CBitmapButton;	//메모리 할당 시 해제 필 
	m_pBtnOnOff->Create(NULL, WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, rect, this, IDC_BTN_ONOFF);
	m_pBtnOnOff->LoadBitmaps(IDB_ON, IDB_OFF);
	m_pBtnOnOff->SizeToContent();
}

void CMfcStartDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//메모리 해제
	if (m_pBtnOnOff != NULL)
		delete m_pBtnOnOff;
	if (m_pDlgImage != NULL)
		delete m_pDlgImage;
}


void CMfcStartDlg::OnBnClickedBtnModal()
{
	m_pDlgImage->ShowWindow(SW_SHOW);
}


//모달간 데이터 전송 코드
void CMfcStartDlg::CallFunction(int n)
{
	int nData = n;
	cout << "modal called data : " << nData << endl;
}
