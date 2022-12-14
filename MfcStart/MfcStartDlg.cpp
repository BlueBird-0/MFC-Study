
// MfcStartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcStart.h"
#include "MfcStartDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <tuple>
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
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMfcStartDlg 대화 상자



CMfcStartDlg::CMfcStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSTART_DIALOG, pParent)
	, m_nNum1(0), m_nNum2(0), m_nCircleSize(CIRCLE_SIZE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM1, m_nNum1);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_nNum2);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_SIZE, m_nCircleSize);
}

// 메세지맵 (이벤트를 정의)
BEGIN_MESSAGE_MAP(CMfcStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
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
	ON_BN_CLICKED(IDC_MODAL_TEST, &CMfcStartDlg::OnBnClickedModalTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CMfcStartDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CMfcStartDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CMfcStartDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_CIRCLE_MAKE, &CMfcStartDlg::OnBnClickedBtnCircleMake)
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
	MoveWindow(0, 0, 880, 950);

	SetDlgItemText(IDC_STATIC_RESULT, _T("0"));
	m_pDlgImage = new CDlgImage;	//메모리 해제 필요
	m_pDlgImage->Create(IDD_CDLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(10, 320, 320, 240);

	m_pDlgImageResult = new CDlgImage;	//메모리 해제 필요
	m_pDlgImageResult->Create(IDD_CDLGIMAGE, this);
	m_pDlgImageResult->ShowWindow(SW_SHOW);
	m_pDlgImageResult->MoveWindow(340, 320, 320, 240);
	
	//4-8과제 코드
	InitCircleDlg();
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
	m_image.Draw(dc, 10, 60);
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
			if (ValidInCirclePos(nCenterX, nCenterY, nPx, nPy, r, &m_image))
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
	for (size_t i = 0; i < MAX_POINT; i++)
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

BOOL CMfcStartDlg::ValidInCirclePos(int x, int y, int p1, int p2, int r, CImage* cImage) {
	int nWidth = cImage->GetWidth();
	int nHeight = cImage->GetHeight();
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
	if (m_pDlgImageResult != NULL)
		delete m_pDlgImageResult;
	if (m_pDlgImageCircle != NULL)
		delete m_pDlgImageCircle;
	if (m_pDlgImageCircleResult != NULL)
		delete m_pDlgImageCircleResult;
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


void CMfcStartDlg::OnBnClickedModalTest()
{	
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	for (int j = 0; j < MAX_POINT; j++)
	{
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		int bright = rand() % 0xff;
		fm[y * nPitch + x] = bright;

	}

	//count
	int nIndex = 0;
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] != 0) {
				//m_pDlgImageResult[m_pDlgImageResult->m_nDataCount].m_ptData
				m_pDlgImageResult->m_ptData[nIndex].x = i;
				m_pDlgImageResult->m_ptData[nIndex].y = j;
				m_pDlgImageResult->m_nDataCount = nIndex++;
			}
		}
	}

	m_pDlgImage->Invalidate();
	m_pDlgImageResult->Invalidate();
}

#include "CProcess.h"
#include <chrono>	//프로세스 시간 관리하기 위한 기능
void CMfcStartDlg::OnBnClickedBtnProcess()
{
	CProcess process;

	auto start = std::chrono::system_clock::now();	//auto : 지연선언

	int nRet = process.getStarInfo(&m_pDlgImage->m_image);

	auto end = std::chrono::system_clock::now();
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "process.getStarInfo : " << nRet << endl;
	cout << "처리시간 : " << millisec.count()<<"ms" << endl;
}


void CMfcStartDlg::OnBnClickedBtnMakePattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	CRect rect(50, 50, 70, 200);
	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			fm[j * nPitch + i] = rand()%0xff;
		}
	}
	m_pDlgImage->Invalidate();
}


void CMfcStartDlg::OnBnClickedBtnGetData()
{
	FindCenterOfGravity(&m_pDlgImage->m_image);
}

//nTh 보다 큰 값의 무게중심 구함
CDoublePoint CMfcStartDlg::FindCenterOfGravity(CImage* pImage, int nTh)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;	//double형변환
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;
	return CDoublePoint(dCenterX, dCenterY);
}


void CMfcStartDlg::InitCircleDlg() {
	//4-8 과제수행 코드
	m_pDlgImageCircle = new CDlgImage;	//메모리 해제 필요
	m_pDlgImageCircle->Create(IDD_CDLGIMAGE, this);
	m_pDlgImageCircle->ShowWindow(SW_SHOW);
	m_pDlgImageCircle->MoveWindow(30, 600, 320, 240);

	m_pDlgImageCircleResult = new CDlgImage;	//메모리 해제 필요
	m_pDlgImageCircleResult->Create(IDD_CDLGIMAGE, this);
	m_pDlgImageCircleResult->ShowWindow(SW_SHOW);
	m_pDlgImageCircleResult->MoveWindow(360, 600, 320, 240);
}

void CMfcStartDlg::OnBnClickedBtnCircleMake()
{
	DrawRandomCircle();
	CDoublePoint cCenterOfGravity = FindCenterOfGravity(&m_pDlgImageCircle->m_image);
	DrawCircleResult(cCenterOfGravity);
}

void CMfcStartDlg::DrawRandomCircle() {
	unsigned char* fm = (unsigned char*)m_pDlgImageCircle->m_image.GetBits();
	int nWidth = m_pDlgImageCircle->m_image.GetWidth();
	int nHeight = m_pDlgImageCircle->m_image.GetHeight();
	int nPitch = m_pDlgImageCircle->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	int nCenterX = rand() % nWidth;
	int nCenterY = rand() % nHeight;

	//'IDC_EDIT_CIRCLE_SIZE'값 가져오기
	UpdateData();
	int r = m_nCircleSize;
	//X, Y에 원 그리기(x - a)2 + (y - b)2 = r2
	for (int j = -r; j < +r; j++)
	{
		for (int i = -r; i < +r; i++)
		{
			int nPx = nCenterX + i;
			int nPy = nCenterY + j;
			if (ValidInCirclePos(nCenterX, nCenterY, nPx, nPy, r, &m_pDlgImageCircle->m_image))
			{
				fm[(nCenterY + j) * nPitch + (nCenterX + i)] = rand()%0xff;
			}
		}
	}
	m_pDlgImageCircle->Invalidate();
}


int out[240][320];	//필터적용할 output
void CMfcStartDlg::FindCircleOutLine()
{
	//윤곽선 필터로 사용할 변형 라플라시안 edge detection 사용
	int mask1[3][3] = {
		1, 1, 1,
		1, 150, 1,
		1, 1, 1
	};
	int sum;
	unsigned char* fm = (unsigned char*)m_pDlgImageCircle->m_image.GetBits();
	int nWidth = m_pDlgImageCircle->m_image.GetWidth();
	int nHeight = m_pDlgImageCircle->m_image.GetHeight();
	int nPitch = m_pDlgImageCircle->m_image.GetPitch();
	//패딩 없이 작업 
	for (int j = 1; j < nHeight-1; j++)
	{
		for (int i = 1; i < nWidth-1; i++)
		{
			sum =  0;
			for (int m = -1; m <= 1; m++)
			{
				for (int n = -1; n <= 1; n++)
				{
					sum += fm[(j+m)*nPitch+ (i+n)] * mask1[m + 1][n + 1];
				}
			}
			//출력
			out[j][i] = sum;
		}
	}
}

void CMfcStartDlg::DrawCircleResult(CDoublePoint cCenterOfGravity) {
	//무게중심 가운데 십자마크 그리기
	m_pDlgImageCircleResult->m_cCenterOfGravity = cCenterOfGravity;
	
	
	//원 외곽선 그리기
	FindCircleOutLine();
	int nWidth = m_pDlgImageCircleResult->m_image.GetWidth();
	int nHeight = m_pDlgImageCircleResult->m_image.GetHeight();
	
	int nCount = 0;
	for (int j = 0; j < nHeight; j++)
	{
		for (int i = 0; i < nWidth; i++)
		{	
			if (out[j][i] < 255 && out[j][i]!=0) {
				//fm[j * nPitch + i] = out[j][i];
				if (nCount < MAX_OUTLINE_POINT) {
					m_pDlgImageCircleResult->m_ptOutline[nCount].x = i;
					m_pDlgImageCircleResult->m_ptOutline[nCount].y = j;
					m_pDlgImageCircleResult->m_nOutlineCount = nCount++;
				}
			}
		}
	}

	m_pDlgImageCircleResult->Invalidate();
}