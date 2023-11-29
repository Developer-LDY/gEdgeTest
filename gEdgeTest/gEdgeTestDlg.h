
// gEdgeTestDlg.h : ��� ����
//

#pragma once
#define __G_DEBUG__
#include "afxwin.h"

#include "gEdge.h"
#include "gLogger.h"
#include "gImage.h"


// CgEdgeTestDlg ��ȭ ����
class CgEdgeTestDlg : public CDialogEx
{
// �����Դϴ�.
private:
	gEdge m_edge;
	gLogger m_logger;
public:
	CgEdgeTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEDGETEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
