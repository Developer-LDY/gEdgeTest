
// gEdgeTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gEdgeTest.h"
#include "gEdgeTestDlg.h"
#include "afxdialogex.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
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


// CgEdgeTestDlg 대화 상자



CgEdgeTestDlg::CgEdgeTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GEDGETEST_DIALOG, pParent),
	m_logger("main",".\\log")

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgEdgeTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_DISPLAY, m_imgDisplay);
}

BEGIN_MESSAGE_MAP(CgEdgeTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GET_EDGE, &CgEdgeTestDlg::OnBnClickedBtnGetEdge)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CgEdgeTestDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_WEIGHT, &CgEdgeTestDlg::OnBnClickedBtnWeight)
END_MESSAGE_MAP()


// CgEdgeTestDlg 메시지 처리기

BOOL CgEdgeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	m_logger.setConsoleLevel(G_LOGGER_LEVEL_TRACE);
	ScopeLog(&m_logger);
	m_imgDisplay.gSetUseRoi();


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgEdgeTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgEdgeTestDlg::OnPaint()
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
HCURSOR CgEdgeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgEdgeTestDlg::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog fDlg(true);
	if (fDlg.DoModal() == IDOK)
		m_imgDisplay.gLoad(fDlg.GetPathName());

	CProcess process;
	process.EdgeDrawCountInit();

}

void CgEdgeTestDlg::OnBnClickedBtnGetEdge()
{
	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeight();
	int nPitch = m_imgDisplay.gGetPitch();
	unsigned char* fm = m_imgDisplay.gGetImgPtr();

	CProcess process(fm, nWidth, nHeight, nPitch);
	double t, a, b;
	process.getEdge(m_imgDisplay.gGetRoi(), &t, &a, &b);

	CPoint p1, p2;
	p1.x = 0;
	p2.x = nWidth;
	p1.y = (a*p1.x + b) / t;
	p2.y = (a*p2.x + b) / t;

	m_imgDisplay.gDrawLine(p1,p2);

	m_logger.debug("{} 엣지 카운트", *process.nEdgeDrawCount);
	if (*process.nEdgeDrawCount == 2) {

		*process.nEdgeDrawCount = 0;

		m_logger.debug("{} x좌표 {} y좌표", process.ptCrossPoint->x, process.ptCrossPoint->y);
		m_imgDisplay.gDrawCircle({ process.ptCrossPoint->x - 10,process.ptCrossPoint->y - 10,
									process.ptCrossPoint->x + 10,process.ptCrossPoint->y + 10 },
									0, 0, COLOR_RED, 5);
	}

	m_imgDisplay.UpdateDisplay();
}


void CgEdgeTestDlg::OnBnClickedBtnWeight()
{
	int nWidth = m_imgDisplay.gGetWidth();
	int nHeight = m_imgDisplay.gGetHeight();
	int nPitch = m_imgDisplay.gGetPitch();
	unsigned char* fm = m_imgDisplay.gGetImgPtr();

	CProcess process(fm, nWidth, nHeight, nPitch);
	CPoint *ptResults;
	ptResults = process.getWeightCenter(m_imgDisplay.gGetRoi());

	int nCircleSize = 10;

	m_imgDisplay.gDrawCircle({ ptResults[0].x - nCircleSize,ptResults[0].y - nCircleSize,
					ptResults[0].x + nCircleSize,ptResults[0].y + nCircleSize }, 0, 0, RGB(255, 0, 0), 5);
	m_imgDisplay.gDrawCircle({ ptResults[1].x - nCircleSize,ptResults[1].y - nCircleSize,
					ptResults[1].x + nCircleSize,ptResults[1].y + nCircleSize }, 0, 0, RGB(0, 255, 0), 5);

	m_logger.debug("{}, {} / {}, {}", ptResults[0].x, ptResults[0].y, ptResults[1].x, ptResults[1].y);

	m_imgDisplay.UpdateDisplay();
}
