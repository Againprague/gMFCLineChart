#pragma once

//////////////////////////////////////////////////////////////////////////////
// 
//  Edge 구하는 함수                            2000. 2. 29  고영우 
//                               VER 02.00      2021.10. 18  김준우
//                               VER 02.01      2021.10. 20  김준우
//
/////////////////////////////////////////////////////////////////////////////
//
// [ 용어정리 ]
//
//  INPUT
//		n : 픽셀데이타 수 
//		*data: 픽셀데이타 
//  OUTPUT
//		*edge: 구한 Edge
//		*slope: 이웃하는 픽셀간의 차 즉, ABS(data[i+1]-data[i]). slope는 절대값을 사용한다.
//		*dir=0: White->Black
//			=1: Black->White
//  INPUT
//		unsigned char*: unsigned char* 또는 int *
//		fm    : 메모리 시작번지 
//		(x1,y1) : Line의 시작좌표 
//		(x2,y2) : Line의 끝좌표        x1>x2 또는 x2>=x1, y1>y2 또는 y2>=y1
//		nPitch  : 메모리 폭 ( M8, MVB03인경우 1024, 보통 BMP처리시는 640)
//      (left, top) : 영역의 좌상귀좌표 
//      (right, bottom): 영역의 우하귀 좌표  반드시, right>left, bottom>top
//  OUTPUT
//		(*edgeX, *edgeY) : 구한 Edge의 좌표 
//
//
//  함수 이름에 대해서 
//
//  LN_  : 한 Line에 대해 Edge구함 
//  AR_  : 한영역에서 여러 Line에 대해 Edge를 구함 
//  _B2W : Black에서 White로 변하는 Edge구함 
//  _W2B : White에서 Black으로 변하는 Edge구함 
//  _ABS : Black->White, 또는 White->Black 구별없이 조건만 맞으로 Edge구함 
//  _T2B : Top에서 Bottom으로 Pixel Data를 얻어서 Edge를 구함
//  _L2R : Left에서 Right로 Pixel Data를 얻어서 Edge를 구함 
//  _B2T : bottom 에서 Top 방향으로 Pixel Data를 얻어서 Edge를 구함 
//  _R2L : Right에서 Left로 Pixel Data를 얻어 Edge를 구함 
//
// (예) LN_FindEdge1_B2W : 한 Line Data에 대해서 Black->White로 변하는 기울기가 가장큰 1개의 Edge구함 
//                         이때 구한 결과는  *edge 이다.
//      LN_FindEdgePos1_W2B: 한 Line의 시작점에서 출발하여 끝점까지 White->Black으로 변하는 Edge중
//                         기울기가 가장큰 1개의 Edge구함 
//                         구한 결과는 (*edgeX, *edgeY)이다.
//   
//  
// return >0 SUCCESS (Edge Number)
//        <0 FAILURE 

// VER 02.00 추가
void	FindEdge_Initialize(int nPitch, int nWidth, int nHeight);
void	FindEdge_Close();

// from FindEdge.cpp ////////////////
extern double* PixelX;
extern double* PixelY;
extern double* EdgeM;
extern int* PixelV;

// (x1,y1)-(x2,y2)를 1Pixel간격으로 Sampling하는 함수 

int GetLineData(unsigned char* fm, int x1, int y1, int x2, int y2,
	double* pX, double* pY, int* pGrayValue);

// 두개의 직선으로부터 Cross하는 점 구하기
int FindCrossPoint(double t1, double a1, double b1,
	double t2, double a2, double b2, double* cx, double* cy);


// Edge를 1개만 구하는 함수-----------------------------------------------------------------

// n 개의 Pixel data로부터 기울기가 가장 큰 Edge를 구하는 함수 
// B2W : Black->White로 변하는 Edge중에서 구함 
// W2B : White->Black로 변하는 Edge중에서 구함
// ASB : 기울기가 가장큰 Edge구함 
int LN_FindEdge1_B2W(int n, int *data, double *edge, int *slope);
int LN_FindEdge1_W2B(int n, int *data, double *edge, int *slope);
int LN_FindEdge1_ABS(int n, int *data, double *edge, int *slope, int *dir);

// 시작점(x1,y1)-끝점(x2,y2) 에서  기울기가 가장 큰 Edge를 구하는 함수 
int LN_FindEdgePos1_B2W(unsigned char* fm, int x1, int y1, int x2, int y2,
						double *edgeX, double *edgeY, int *slope);
int LN_FindEdgePos1_W2B(unsigned char* fm, int x1, int y1, int x2, int y2,
						double *edgeX, double *edgeY, int *slope);
int LN_FindEdgePos1_ABS(unsigned char* fm, int x1, int y1, int x2, int y2,
						double *edgeX, double *edgeY, int *slope, int *dir);

//기울기가 slope보다 큰 첫번째 Edge를 1개 구하는 함수
int LN_FindEdge1st_B2W(int n, int *data, int slope, double *edge);
int LN_FindEdge1st_W2B(int n, int *data, int slope, double *edge);
int LN_FindEdge1st_ABS(int n, int *data, int slope, double *edge, int *dir);

// 시작점(x1,y1)-끝점(x2,y2) 에서 기울기가  slope보다 큰 첫번째 Edge를 구하는 함수 
int LN_FindEdgePos1st_B2W(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						  double *edgeX, double *edgeY);
int LN_FindEdgePos1st_W2B(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						  double *edgeX, double *edgeY);
int LN_FindEdgePos1st_ABS(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						  double *edgeX, double *edgeY, int *dir);
//------------------------------------------------------------------------------------------


// Edge를 여러개 구하는 함수 ---------------------------------------------------------------
// n 개의 Pixel data로부터 기울기가 slope보다 큰 모든 Edge를 구하는 함수 
int LN_FindEdgeM_B2W(int n, int *data, int slope, double *edge, int max_edges);
int LN_FindEdgeM_W2B(int n, int *data, int slope, double *edge, int max_edges);
int LN_FindEdgeM_ABS(int n, int *data, int slope, double *edge, int *dir, int max_edges);

// 시작점(x1,y1)-끝점(x2,y2) 에서 기울기가  slope보다 큰 모든 Edge를 구하는 함수 
int LN_FindEdgePosM_B2W(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						double *edgeX, double *edgeY, int max_edges);
int LN_FindEdgePosM_W2B(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						double *edgeX, double *edgeY, int max_edges);
int LN_FindEdgePosM_ABS(unsigned char* fm, int x1, int y1, int x2, int y2, int slope,
						double *edgeX, double *edgeY, int *dir, int max_edges);
//------------------------------------------------------------------------------------------



// AR_FindEdge_T2B_B2W을 예로들어 설명하면... 
// 아래 그림에서 각 수직선마다 Edge를 하나씩 구하여 그 Edge로 Line Fitting한다.
// Fitting한 Line과 영역의 중심을 지나는 수직선과 만나는 점을 이 영역의 Edge Point로 간주한다.
//
//    _____
//   |  |  |     .... : 수직선에 의해 구한 Edge들
//   |  |  |       *  : 이 Edge를 잇는 Line과 영역의 중심 수직선과의 만나는 점 
//   |..*..|    
//   |  |  |
//   |__|__|
//  

int AR_FindEdge_T2B_B2W(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_T2B_W2B(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_L2R_B2W(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_L2R_W2B(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_B2T_B2W(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_B2T_W2B(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_R2L_B2W(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);
int AR_FindEdge_R2L_W2B(unsigned char* fm, int left, int top, int right, int bottom,
						double *edgeX, double *edgeY);


// 함수설명 : 임의의 라인을 1Pixel 간격으로 ReSampling해주는 함수 
// return Value : 구한 좌표의 개수       
//               <0 FAILURE
int GetLineData(unsigned char* fm, int x1, int y1, int x2, int y2,
				double *pX, double *pY, int *pGrayValue);


//Line이 거의 수직이 아닐때 사용하는 Line Fitting함수 
int LineFitting(int dataN, double *x, double *y, int removeN, double ErrorLimit,
				 double *t, double *a, double *b);
//Line이 거의 수직일때 사용하는 Line Fitting함수
int LineFitting1(int dataN, double *x, double *y, int removeN, double ErrorLimit,
				 double *t, double *a, double *b);
