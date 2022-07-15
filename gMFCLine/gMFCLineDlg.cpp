
// gMFCLineDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gMFCLine.h"
#include "gMFCLineDlg.h"
#include "afxdialogex.h"

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
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()


// CgMFCLineDlg 대화 상자



CgMFCLineDlg::CgMFCLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GMFCLINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgMFCLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_gImage, m_gImage);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
	DDX_Control(pDX, IDC_CHECK_START, m_PointerStart);
}

BEGIN_MESSAGE_MAP(CgMFCLineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CgMFCLineDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CgMFCLineDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CgMFCLineDlg::OnBnClickedBtnClear)
	ON_STN_CLICKED(IDC_STATIC_gImage, &CgMFCLineDlg::OnStnClickedStaticgimage)
	ON_BN_CLICKED(IDC_CHECK_START, &CgMFCLineDlg::OnBnClickedCheckStart)
	ON_STN_CLICKED(IDC_ChartViewer, &CgMFCLineDlg::OnStnClickedStaticgimage)
	ON_CONTROL(CVN_MouseMovePlotArea,IDC_ChartViewer, OnMouseMovePlotArea)
END_MESSAGE_MAP()


// CgMFCLineDlg 메시지 처리기
BOOL CgMFCLineDlg::OnInitDialog()
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

	m_gImage.gCreate(nWidth, nHeight, nBpp);
	SetTimer(0, 100, NULL);	// ontimer 주기 설정

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgMFCLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgMFCLineDlg::OnPaint()
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
HCURSOR CgMFCLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgMFCLineDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPoint ptMouse, ptImg;
	int nGray = m_gImage.gGetPixelInfo(ptMouse, ptImg);
	CString str;

	str.Format(_T("[Pixel Pos] (Gray Level)\n[%04d, %04d] (%03d)\n[Mouse Pos]\n[%04d, %04d]"), 
		ptImg.x, ptImg.y, nGray,ptMouse.x,ptMouse.y);
	SetDlgItemText(IDC_STATIC_INFO, str);

	CDialogEx::OnTimer(nIDEvent);
}

void CgMFCLineDlg::OnBnClickedBtnExit()
{
	OnOK();
}

void CgMFCLineDlg::OnBnClickedBtnLoad()
{
	char szFilter[] = " All Files(*.*)|*.*|";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (CString)szFilter, NULL);

	if (dlg.DoModal() == IDOK)
	{
		CString strPathName = dlg.GetPathName();
		m_gImage.gLoad(string(CT2CA(strPathName))); // CString -> string
	}
}
void CgMFCLineDlg::OnBnClickedBtnClear()
{
	m_BTNStart = (CButton*)GetDlgItem(IDC_CHECK_START);

	//초기화
	system("cls");		//콘솔창 초기화
	FindEdge_Close();
	m_gImage.gDelObjAll();
	m_nptImg[0] = (0, 0); m_nptImg[1] = (0, 0);
	m_BTNStart->EnableWindow(true);
	m_BTNStart->SetWindowText(TEXT("START"));
}

void CgMFCLineDlg::OnBnClickedCheckStart()
{
	m_BTNStart = (CButton*)GetDlgItem(IDC_CHECK_START);
	m_BTNStart->SetWindowText(TEXT("Get Data"));
	m_BTNStart->EnableWindow(false);
}

void CgMFCLineDlg::OnStnClickedStaticgimage()
{
	m_BTNStart = (CButton*)GetDlgItem(IDC_CHECK_START);

	CPoint ptMouse, ptImg;
	m_gImage.gGetPixelInfo(ptMouse, ptImg);
	//멤버변수에 마우스 x,y 좌표값 전달
	m_nptImg[nClickCnt].x = ptImg.x;	m_nptImg[nClickCnt].y = ptImg.y;
	nClickCnt += 1;
	
	if (nClickCnt == 2) {
		m_BTNStart->SetCheck(0);
		nClickCnt = 0;
		m_BTNStart->SetWindowText(TEXT("Start"));
		m_BTNStart->EnableWindow(true);
		cout << m_nptImg[0].x << "\t" << m_nptImg[0].y << endl;
		cout << m_nptImg[1].x << "\t" << m_nptImg[1].y << endl;
		Process();
	}
}

void CgMFCLineDlg::Process()
{
	nPitch = m_gImage.gGetPitch();
	FindEdge_Initialize(nPitch, nWidth, nHeight);

	unsigned char* fm = m_gImage.gGetImgPtr();

	// 시작점(x1,y1), 끝점(x2,y2)
	int x1 = (int)m_nptImg[0].x, y1 = (int)m_nptImg[0].y;
	int x2 = (int)m_nptImg[1].x, y2 = (int)m_nptImg[1].y;

	// 데이터 길이
	double nDLen = (double)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	nDLen = ceil(nDLen); //소숫점 올림

						 // GetLineData() 함수에 들어가는 인자
	double *dPX = new double[nDLen];
	double *dPY = new double[nDLen];
	int *nGrayValue = new int[nDLen];

	// Get grayValue,pX,pY/////
	GetLineData(fm, x1, y1, x2, y2, dPX, dPY, nGrayValue);

	// 시작점 - 끝점 Line draw//////
	drawLine(x1, x2, y1, y2, dPX, dPY);

	// 데이터 값 확인
	//for (int i = 0; i < nDLen; i++) {
	//	cout << "[ #" << i + 1 << " ]" << endl;
	//	cout << "GetLienData()" << endl;
	//	cout <<"dPX,dPY["<<i<<"] : \t"<< (int)dPX[i] << "\t" << (int)dPY[i] << "\n" << "nGrayValue : \t" << nGrayValue[i] << endl;
	//	cout << "-------------------------------------------------------" << endl;
	//}

	// gChart studying.....
	//TODO : 마우스 휠 zoom in, out how?
	const char *imageMap = 0;

	// Data load
	loadData(nGrayValue, nDLen);

	// 마우스휠 zoom in, out에서 사용하는..?/////////////////////////////////
	m_ChartViewer.updateViewPort(true, true);
	m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
	m_ChartViewer.setScrollDirection(Chart::DirectionHorizontalVertical);
	m_ChartViewer.setZoomDirection(Chart::DirectionHorizontalVertical);
	m_ChartViewer.setMouseWheelZoomRatio(1.1);
	/////////////////////////////////////////////////////////////////////////
	
	// DrawChart
	drawLineChart(&m_ChartViewer, &imageMap);

	delete[] dPX, dPY, nGrayValue;
}

void CgMFCLineDlg::drawLine(int x1, int x2, int y1, int y2, double *dPX, double *dPY)
{
	// GetLineData에서 나온 픽셀 좌표들 이어서 그려본것 MAXOBJ가 안바뀜
	//for (int i = 0; i < nDLen-1; i++)
	//{
	//	m_Item.type = LINE_OBJ;
	//	m_Item.colorObj = COLOR_BLUE;
	//	m_Item.rect.left = (int)pX[i];	m_Item.rect.right  = (int)pX[i + 1];
	//	m_Item.rect.top  = (int)pY[i];	m_Item.rect.bottom = (int)pY[i + 1];
	//	m_gImage.gAddObj(m_Item);
	//}

	////오브젝트갯수 카운팅
	//cout << m_gImage.gGetObjCount() << endl;

	m_Item.type = LINE_OBJ;
	m_Item.colorObj = COLOR_RED;
	m_Item.rect.left = x1;	m_Item.rect.right = x2;
	m_Item.rect.top = y1;		m_Item.rect.bottom = y2;
	m_gImage.gAddObj(m_Item);
}

//////////////////
// Load the data//
void CgMFCLineDlg::loadData(int* GrayValue, int Len)
{
	// In this example, we just use random numbers as data.
	double *dGrayData = new double[Len];
	double *dTimestamps = new double[Len];

	for (int i = 0; i < Len; i++) {
		dGrayData[i] = (double)GrayValue[i];	// Gray Level int -> double
		dTimestamps[i] = (double)i;
	}

	m_dGrayData = DoubleArray(dGrayData, Len);
	m_dTimeStamps = DoubleArray(dTimestamps, Len);
}

// TODO : chart DOC site/////////////////////////////////////
// https://www.advsofteng.com/doc/cdcppdoc/#simpleline.htm //
/////////////////////////////////////////////////////////////
void CgMFCLineDlg::drawLineChart(CChartViewer *viewer, const char **imageMap)
{
	// Set the full x range to be the duration of the data
	viewer->setFullRange("x", m_dTimeStamps.data[0], m_dTimeStamps.data[m_dTimeStamps.len - 1]);

	// line chart 처음 그려졌을 때, 전체 차트를 보여준다 viewport width, height = 0 ~ 1 사이 값( 1 = 전체 차트 )
	viewer->setViewPortWidth(1);
	viewer->setViewPortHeight(1);

	// viewPort(보여지는 부분)의 left, top을 0으로 지정
	// chart의 (0,0) 부터 보여준다고 지정
	viewer->setViewPortLeft(0);
	viewer->setViewPortTop(0);

	// Initially set the mouse to drag to scroll mode.
	viewer->setMouseUsage(Chart::MouseUsageScroll);

	// mousewheel에 따라 보여지는 x축의 가장 왼쪽 부분
	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
	// mousewheel에 따라 보여지는 x축의 가장 오른쪽 부분
	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() + viewer->getViewPortWidth()); 

	int startIndex = (int)floor(Chart::bSearch(m_dTimeStamps, viewPortStartDate));
	int endIndex = (int)ceil(Chart::bSearch(m_dTimeStamps, viewPortEndDate));
	// mousewheel에 따라 보여지는 x축의 범위(data 개수)
	int noOfPoints = endIndex - startIndex + 1; 

	// DoubleArray 변수 선언
	// DoubleArray : chartdirect의 class 중 하나, chart를 그리기 위한 type
	// DoubleArray(const double *_data, int _len)
	// _data : chart를 그릴 data(double type 배열)의 주소, _len : chart에서 나타낼 data의 범위(data 개수)

	DoubleArray viewPortTimestamps = DoubleArray(m_dTimeStamps.data + startIndex, noOfPoints);
	DoubleArray viewPortGrayData = DoubleArray(m_dGrayData.data + startIndex, noOfPoints);

	// chart 전체 크기
	XYChart *c = new XYChart(CHART_WIDTH, CHART_HEIGHT);

	// mousewheel에 따라 보여지는 x축을 조절하기 위한 부분

	// chart title("title", "font", font size)
	c->addTitle("Gray Level Line Grahpe", "timesbi.ttf", 16);

	// chart의 위치, 크기 설정
	c->setPlotArea(45, 90, CHART_AREA_WIDTH, CHART_AREA_HEIGHT, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

	c->setClipping();

	//x, y 축의 font, fontsize, color 지정
	c->xAxis()->setLabelStyle("arialbd.ttf", 8);
	c->yAxis()->setLabelStyle("arialbd.ttf", 6);
	c->xAxis()->setColors(Chart::Transparent);
	c->yAxis()->setColors(Chart::Transparent);

	// x, y축 title
	c->yAxis()->setTitle("Gray Level", "arialbi.ttf", 10);
	c->xAxis()->setTitle("Data Length", "arialbi.ttf", 10);

	// line width = 2인 line layer 추가
	LineLayer *layer = c->addLineLayer();
	layer->setLineWidth(2);

	// X 축을 표현할 data 지정
	// line layer에 mousewheel에 따라 다르게 나타나는 ViewPortDataA 추가
	layer->setXData(viewPortTimestamps);
	layer->addDataSet(viewPortGrayData, 0xcc0000, "Gray Level");
	
	// data축 스케일 동기화 부분(휠땡기거나 할 때 동기화 해주는 부분인듯)
	viewer->syncDateAxisWithViewPort("x", c->xAxis());

	// scroll 또는 mouse move를 통해 chart가 계속 변하므로 그에 따라 track Legend 역시 update 필요
	if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
	{
		trackLineLegend(c, (0 == viewer->getChart()) ? c->getPlotArea()->getRightX():viewer->getPlotAreaMouseX());
	}

	//c->makeChart();
	delete viewer->getChart();
	viewer->setChart(c);

	// 가만히있을때 팝업창? 뜨는부분 설정
	*imageMap = c->getHTMLImageMap("clickable"," ","title='[X : {x}] {dataSetName} : {value}'");
}

void CgMFCLineDlg::trackLineLegend(XYChart *c, int mouseX)
{
	DrawArea *d = c->initDynamicLayer();

	// 현재 그려진 chart의 plotarea
	PlotArea *plotArea = c->getPlotArea();

	// chart 상에서 현재 마우스가 위치한 곳과 비슷한 곳에 위치한 차트의 x값(xValue)
	// 현재 mouseX가 가리키고 있는 곳과 비슷한 x 값 받아와 좌표 찾기
	double xValue = c->getNearestXValue(mouseX);
	int xCoor = c->getXCoor(xValue);

	// xCoor에 그려질 vertical track line
	d->vline(plotArea->getTopY(), plotArea->getBottomY(), xCoor, d->dashLineColor(0x000000, 0x0101));

	//TODO : 어디에 쓰는지 알 수 없음
	//ostringstream xlabel;
	//xlabel << "<*font,bgColor=000000*> " << c->xAxis()->getFormattedLabel(xValue, " ") << " <*/font*>";

	// 여러 개의 legend가 있는 경우를 위해 vector로 legend 저장할 공간 선언
	vector<string> legendEntries;

	// chart의 layer 개수만큼 반복
	for (int i = 0; i < c->getLayerCount(); ++i) {
		Layer *layer = c->getLayerByZ(i);

		// xValue가 layer에서 몇번째 x index에 해당하는지
		int xIndex = layer->getXIndexOf(xValue);

		for (int j = 0; j < layer->getDataSetCount(); ++j) {
			DataSet *dataSet = layer->getDataSetByZ(j);

			// dataName : layer의 dataset의 이름(ex. Power Usage A, Power Usage B ... )
			const char *dataName = dataSet->getDataName();
			int color = dataSet->getDataColor();
			if (dataName && *dataName && (color != Chart::Transparent)) {
				// get dataSet's value(= Y value)
				double dataValue = dataSet->getValue(xIndex);
				ostringstream legendEntry;
				legendEntry << "<*block*>" << dataSet->getLegendIcon() << " " << dataName << ": " <<
					((dataValue == Chart::NoValue) ? "N/A" : c->formatValue(dataValue, "{value|P4}"))
					<< "<*/*>";
				legendEntries.push_back(legendEntry.str());

				int yCoor = c->getYCoor(dataSet->getPosition(xIndex), dataSet->getUseYAxis());
				if ((yCoor >= plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
					d->circle(xCoor, yCoor, 4, 4, color, color);
					// circle : track dot를 그리기 위해

					ostringstream label;
					label << "<*font,bgColor=" << hex << color << "*> "
						<< c->formatValue(dataSet->getValue(xIndex), "{value|P4}") << " <*font*>";
					TTFText *t = d->text(label.str().c_str(), "arialbd.ttf", 8);

					// Draw the label on the right side of the dot if the mouse is on the left side the
					// chart, and vice versa. This ensures the label will not go outside the chart image.
					if (xCoor <= (plotArea->getLeftX() + plotArea->getRightX()) / 2)
						t->draw(xCoor + 5, yCoor, 0xffffff, Chart::Left);
					else
						t->draw(xCoor - 5, yCoor, 0xffffff, Chart::Right);

					t->destroy();
				}
			}
		}
	}

	// chart plot area 위에 legend display 하는 부분
	ostringstream legendText;
	legendText << "<*block,maxWidth=" << plotArea->getWidth() << "*><*block*><*font=arialbd.ttf*>[X:" 
		<< c->xAxis()->getFormattedLabel(xValue, " ") << "]<*/*>";


	// Line chart의 x value format
	for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i)
		legendText << "        " << legendEntries[i];

	// plot area 위에 legend display
	TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
	t->draw(plotArea->getLeftX() + 5, plotArea->getTopY() - 15, 0x000000, Chart::BottomLeft);
	t->destroy();
}

//커서 트래킹 함수
void CgMFCLineDlg::OnMouseMovePlotArea()
{
	trackLineLegend((XYChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX());
	m_ChartViewer.updateDisplay();
	// Hide the track cursor when the mouse leaves the plot area
	m_ChartViewer.removeDynamicLayer(CVN_MouseLeavePlotArea);

}