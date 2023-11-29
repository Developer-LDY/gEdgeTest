// Process.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "gEdgeTest.h"
#include "Process.h"
#include "gedge.h"
#include <iostream>
#include <gLogger.h>


// CProcess
double dBeforeT, dBeforeA, dBeforeB;
CPoint ptCrossPointForCopy;
int nEdgeCountForCopy = 0;


CProcess::CProcess(unsigned char* fm, int nWidth, int nHeight, int nPitch)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nPitch = nPitch;
	m_fm = fm;
}

CProcess::CProcess() {

}


CProcess::~CProcess()
{
}

void CProcess::EdgeDrawCountInit() {
	nEdgeCountForCopy = 0;
}

// CProcess 멤버 함수
CPoint *CProcess::getWeightCenter(CRect rect) {

	CPoint *cpResults = new CPoint[2];

	CPoint ptBeforeBinarization;
	CPoint ptAfterBinarization;
	int nTh = 100;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;


	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (m_fm[j*m_nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	if (nCount == 0) { // division by zero 회피
		MessageBox(NULL,_T("threshold 확인"), _T("Title"), MB_ICONERROR);
	}
	else {
		ptBeforeBinarization.x = nSumX / nCount;
		ptBeforeBinarization.y = nSumY / nCount;

		nSumX = 0;
		nSumY = 0;
		nCount = 0;
	}

	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (m_fm[j*m_nPitch + i] > nTh)
				m_fm[j*m_nPitch + i] = 0xff;
			else
				m_fm[j*m_nPitch + i] = 0x00;

			nSumX += i;
			nSumY += j;
			nCount++;

		}
	}

	ptAfterBinarization.x = nSumX / nCount;
	ptAfterBinarization.y = nSumY / nCount;
	//std::cout << "test" << std::endl;
	//std::cout << ptBeforeBinarization.x << "_" << ptBeforeBinarization.y << " / " << 
	//	ptAfterBinarization.x << "_" << ptAfterBinarization.y << std::endl;
	cpResults[0] = ptBeforeBinarization;
	cpResults[1] = ptAfterBinarization;

	return cpResults;
}

void CProcess::getEdge(CRect rect, double *t, double *a, double *b) {

	gEdge edge;

	int* pDataHorizon = new int[rect.Height()];
	double *pX_Horizon = new double[rect.Width()];
	double *pY_Horizon = new double[rect.Width()];

	int* pDataVertical = new int[rect.Width()];
	double *pX_Vertical = new double[rect.Height()];
	double *pY_Vertical = new double[rect.Height()];

	double dEdge;
	int nSlope;

	int nWhiteBlackDir;
	bool bVertical;

	memset(pDataHorizon, 0, rect.Height());
	memset(pDataVertical, 0, rect.Width());

	if (m_fm[rect.top*m_nPitch + rect.left] >= m_fm[rect.bottom*m_nPitch + rect.right]) {
		nWhiteBlackDir = 0;
		//std::cout << "W2B" << std::endl;
	}
	else {
		nWhiteBlackDir = 1;
		//std::cout << "B2W" << std::endl;
	}

	//std::cout << (int)m_fm[rect.top*m_nPitch + rect.left] << "_" << (int)m_fm[rect.bottom*m_nPitch + rect.left] << std::endl;

	if ((m_fm[rect.top*m_nPitch + rect.left] > 50 && m_fm[rect.bottom*m_nPitch + rect.left] > 50) ||
		(m_fm[rect.top*m_nPitch + rect.left] < 50 && m_fm[rect.bottom*m_nPitch + rect.left] < 50)) {

		bVertical = true;
		//std::cout << rect.left << "__" << rect.right << "__" << rect.top << "__" << rect.bottom << "__" << nWhiteBlackDir << "_" << "Vertical" << std::endl;

		for (int i = rect.top; i < rect.bottom; i++) {
			for (int j = rect.left; j < rect.right; j++) {
				pDataVertical[j - rect.left] = m_fm[i * m_nPitch + j];
				//std::cout << j - rect.left << "--" << pDataVertical[j - rect.left] << "__" << i * m_nPitch + j << std::endl;
			}

			edge.LineFindEdge(gEdge::ABS, rect.Width(), pDataVertical, &dEdge, &nSlope, &nWhiteBlackDir);

			pX_Vertical[i - rect.top] = dEdge + rect.left;
			pY_Vertical[i - rect.top] = i;

			edge.LineFitting(rect.Height(), pX_Vertical, pY_Vertical, rect.Height()*0.5, 0.1, t, a, b);
		}

	}
	else {

		bVertical = false;
		//std::cout << rect.left << "__" << rect.right << "__" << rect.top << "__" << rect.bottom << "__" << nWhiteBlackDir << "_" << "Horizon" << std::endl;

		for (int i = rect.left; i < rect.right; i++) {
			for (int j = rect.top; j < rect.bottom; j++) {
				pDataHorizon[j - rect.top] = m_fm[j*m_nPitch + i];
				//std::cout << j - rect.top << "--" << pDataHorizon[j - rect.top] << "__" << j*m_nPitch + i << std::endl;
			}

			edge.LineFindEdge(gEdge::ABS, rect.Height(), pDataHorizon, &dEdge, &nSlope, &nWhiteBlackDir);

			pX_Horizon[i - rect.left] = i;
			pY_Horizon[i - rect.left] = dEdge + rect.top;

			edge.LineFitting(rect.Width(), pX_Horizon, pY_Horizon, rect.Width()*0.2, 0.1, t, a, b);
		}
	}

	nEdgeDrawCount = &++nEdgeCountForCopy;
	std::cout << fmt::format("edge 카운트 {}", *nEdgeDrawCount) << std::endl;

	if (*nEdgeDrawCount == 1) {
		dBeforeT = *t;
		dBeforeA = *a;
		dBeforeB = *b;
		std::cout << *t << "_" << *a << "_" << *b << "_" << std::endl;
	}
	else {
		std::cout << fmt::format("dBeforeT {} dBeforeA {} dBeforeB {} ////", dBeforeT, dBeforeA, dBeforeB) << std::endl;

		edge.FindCrossPoint(*t, *a, *b, dBeforeT, dBeforeA, dBeforeB, &dCrossPointResultX, &dCrossPointResultY);

		std::cout << fmt::format("CrossPoint -  {}, {}", dCrossPointResultX, dCrossPointResultY) << std::endl;

		ptCrossPointForCopy = { (int)dCrossPointResultX ,(int)dCrossPointResultY };

		ptCrossPoint = &ptCrossPointForCopy;

	}

	delete pY_Vertical;
	delete pX_Vertical;
	delete pDataVertical;
	delete pY_Horizon;
	delete pX_Horizon;
	delete pDataHorizon;

}


