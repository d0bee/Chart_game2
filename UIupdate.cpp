#include "pch.h"
#include "UIupdate.h"

void CChartGameDlg::현재가(SChartCandlestickPoint pCandlePoint[480], int candlecnt, int cnt)
{
	int now = pCandlePoint[candlecnt - 1 + cnt].Close;
	CString str;
	str.Format(_T("%d"), now);

	m_CloseCost.SetWindowTextW(str);
}

void CChartGameDlg::매수가()
{
	CString str;
	str.Format(_T("%d"), 평균단가);

	m_BuyCost.SetWindowTextW(str);
}

void CChartGameDlg::평가액()
{
	CString now;
	GetDlgItemText(IDC_CLOSECOST, now);

	int cost = _ttoi(now) * gs;
	CString str;
	str.Format(_T("%d"), cost);

	m_EsCost.SetWindowTextW(str);
}

void CChartGameDlg::순이익()
{
	CString now;
	GetDlgItemText(IDC_CLOSECOST, now);
	int cost;

	cost = (_ttoi(now) - 평균단가) * gs;

	CString str;
	str.Format(_T("%d"), cost);
	m_Profit.SetWindowTextW(str);
}

void CChartGameDlg::매수가능액()
{
	CString str;
	str.Format(_T("%d"), money);

	m_Money.SetWindowTextW(str);
}

void CChartGameDlg::보유수()
{
	CString str;
	str.Format(_T("%d"), gs);

	m_Gs.SetWindowTextW(str);
}