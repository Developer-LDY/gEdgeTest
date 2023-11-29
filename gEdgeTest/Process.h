#pragma once

// CProcess 명령 대상입니다.

class CProcess : public CObject
{

private:
	int m_nWidth;
	int m_nHeight;
	int m_nPitch;
	unsigned char* m_fm;
public:
	CProcess(unsigned char* fm, int nWidth, int nHeight, int nPitch);
	CProcess();
	virtual ~CProcess();

	void EdgeDrawCountInit();
	CPoint *getWeightCenter(CRect rect);
	void getEdge(CRect rect, double *t, double *a, double *b);

	double dCrossPointResultX, dCrossPointResultY;
	CPoint *ptCrossPoint;
	int *nEdgeDrawCount;
};




