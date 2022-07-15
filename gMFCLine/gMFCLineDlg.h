
// gMFCLineDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "gImage.h"
//pixel data get
#include "gFindEdge.h"
//chart
#include "ChartViewer.h"
#include "chartdir.h"
#include "afxdialogex.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#define nHeight 1080
#define nWidth	1920
#define nBpp 8

#define CHART_WIDTH			540
#define CHART_HEIGHT		540
#define CHART_AREA_WIDTH	430
#define CHART_AREA_HEIGHT	370

//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// CgMFCLineDlg 대화 상자
class CgMFCLineDlg : public CDialogEx
{
// 생성입니다.
public:
	CgMFCLineDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMFCLINE_DIALOG };
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
private:

public:
	gImage m_gImage;
	DrawItem m_Item;
	CPoint m_nptImg[2];
	CButton* m_BTNStart;

	int nClickCnt = 0;
	int nPitch;

	void drawLine(int x1, int x2, int y1, int y2, double *dPX, double *dPY);

	//gChart
	DoubleArray m_dGrayData;
	DoubleArray m_dTimeStamps;
	CChartViewer m_ChartViewer;
	CViewPortControl m_ViewPortControl;
	CButton m_PointerStart;
	
	void drawLineChart(CChartViewer *viewer, const char **imageMap);
	void trackLineLegend(XYChart *c, int mouseX);	
	void OnMouseMovePlotArea();
	void loadData(int *GrayValue, int Len);
	void Process();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnStnClickedStaticgimage();
	afx_msg void OnBnClickedCheckStart();
};
