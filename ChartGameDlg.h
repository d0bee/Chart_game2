
// ChartGameDlg.h: 헤더 파일
//

#pragma once
#include "ChartCtrl.h"
#include "ChartLineSerie.h"
#include "ChartCandlestickSerie.h"

// CChartGameDlg 대화 상자
class CChartGameDlg : public CDialogEx
{
// 생성입니다.
public:
	CChartGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CChartCandlestickSerie* pCandle;

	void ReadData(SChartCandlestickPoint(pCandlePoint)[600]);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARTGAME_DIALOG };
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
	CChartCtrl m_ChartCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedNext();
	CButton CNext;
	afx_msg void OnBnClickedGo();
	CStatic mCount;
	afx_msg void OnStnClickedcandcnt();
//	CStatic candcnt;
	CStatic m_CloseCost;
};
