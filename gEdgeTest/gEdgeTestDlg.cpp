
// gEdgeTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "gEdgeTest.h"
#include "gEdgeTestDlg.h"
#include "afxdialogex.h"
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CgEdgeTestDlg ��ȭ ����



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


// CgEdgeTestDlg �޽��� ó����

BOOL CgEdgeTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_logger.setConsoleLevel(G_LOGGER_LEVEL_TRACE);
	ScopeLog(&m_logger);
	m_imgDisplay.gSetUseRoi();


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CgEdgeTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CgEdgeTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgEdgeTestDlg::OnBnClickedBtnLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	m_logger.debug("{} ���� ī��Ʈ", *process.nEdgeDrawCount);
	if (*process.nEdgeDrawCount == 2) {

		*process.nEdgeDrawCount = 0;

		m_logger.debug("{} x��ǥ {} y��ǥ", process.ptCrossPoint->x, process.ptCrossPoint->y);
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
