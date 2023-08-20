
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

	// .csv 파일 불러오기
	void ReadData(SChartCandlestickPoint(pCandlePoint)[480]);

	// Btn 활성화
	void BtnFalse();
	void BtnTrue();

	// 차트 초기화 작업
	void ChartReset();

	// 원장 관리 모듈
	void Account();
	void BuyCost();
	void SellCost(BOOL);
	BOOL BuyInputErr(int, int);
	BOOL SellInputErr(int);

	// UI 업데이트 모듈
	void 현재가();
	void 매수가();
	void 평가액();
	void 순이익();
	void 매수가능액();
	void 보유수();

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
	CButton m_Buy;
	CButton m_Sell;
	CEdit m_Input;
	afx_msg void OnBnClickedBuy();
	afx_msg void OnBnClickedSell();
	CStatic m_BuyCost;
	CStatic m_EsCost;
	CStatic m_Profit;
	CStatic m_Money;
	CStatic m_Gs;
};
