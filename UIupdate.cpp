#include "pch.h"
#include "UIupdate.h"

void CChartGameDlg::���簡(SChartCandlestickPoint pCandlePoint[480], int candlecnt, int cnt)
{
	int now = pCandlePoint[candlecnt - 1 + cnt].Close;
	CString str;
	str.Format(_T("%d"), now);

	m_CloseCost.SetWindowTextW(str);
}

void CChartGameDlg::�ż���()
{
	CString str;
	str.Format(_T("%d"), ��մܰ�);

	m_BuyCost.SetWindowTextW(str);
}

void CChartGameDlg::�򰡾�()
{
	CString now;
	GetDlgItemText(IDC_CLOSECOST, now);

	int cost = _ttoi(now) * gs;
	CString str;
	str.Format(_T("%d"), cost);

	m_EsCost.SetWindowTextW(str);
}

void CChartGameDlg::������()
{
	CString now;
	GetDlgItemText(IDC_CLOSECOST, now);
	int cost;

	cost = (_ttoi(now) - ��մܰ�) * gs;

	CString str;
	str.Format(_T("%d"), cost);
	m_Profit.SetWindowTextW(str);
}

void CChartGameDlg::�ż����ɾ�()
{
	CString str;
	str.Format(_T("%d"), money);

	m_Money.SetWindowTextW(str);
}

void CChartGameDlg::������()
{
	CString str;
	str.Format(_T("%d"), gs);

	m_Gs.SetWindowTextW(str);
}