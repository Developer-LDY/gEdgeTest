
// gEdgeTestDlg.h : 헤더 파일
//

#pragma once
#define __G_DEBUG__
#include "afxwin.h"

#include "gEdge.h"
#include "gLogger.h"
#include "gImage.h"


// CgEdgeTestDlg 대화 상자
class CgEdgeTestDlg : public CDialogEx
{
// 생성입니다.
private:
	gEdge m_edge;
	gLogger m_logger;
public:
	CgEdgeTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEDGETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	afx_msg void OnBnClickedBtnGetEdge();
	gImage m_imgDisplay;
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnWeight();
};
