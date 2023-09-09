#include "pch.h"
#include "Account.h"

// 가상의 계좌, 이후 DB와의 연동을 고려해서 변경되어야 함.
void CChartGameDlg::Account()
{
	CString str;

	// DB를 통해서 조회한 금액
	money = 200000;

	str.Format(_T("%d"), money);
	m_Money.SetWindowTextW(str);

	// 앞으로 사용될 총 주문액, 개수
	gs = 0;
	평균단가 = 0;
}

void CChartGameDlg::BuyCost(SChartCandlestickPoint pCandlePoint[], int candlecnt, int cnt)
{
	// 주문수 가져오기
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// 매수가 가져오기
	CString str;
	int buy = pCandlePoint[candlecnt - 1 + cnt].Close;

	if (BuyInputErr(_ttoi(get), buy) == FALSE)
	{
		// 실행 주문액
		int num = _ttoi(get) * buy;

		// 원장 최신화
		평균단가 = ((평균단가 * gs) + num) / (_ttoi(get) + gs);
		gs += _ttoi(get);
		money -= num;

		매수가();
		평가액();
		매수가능액();
		보유수();
	}
}

void CChartGameDlg::SellCost(BOOL tf, SChartCandlestickPoint pCandlePoint[], int candlecnt, int cnt)
{
	// 주문수 가져오기
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// 현재가 가져오기
	CString str;
	int now = pCandlePoint[candlecnt - 1 + cnt].Close;

	// cnt = max로 끝나는 경우
	if (tf == TRUE) {
		money += gs * now;
		gs = 0;

		m_BuyCost.SetWindowTextW(_T("0"));
		m_EsCost.SetWindowTextW(_T("0"));
		m_Profit.SetWindowTextW(_T("0"));
		m_Gs.SetWindowTextW(_T("0"));

		str.Format(_T("%d"), money);
		m_Money.SetWindowTextW(str);
	}
	else {
		if (SellInputErr(_ttoi(get)) == FALSE)
		{
			// 원장 최신화
			gs -= _ttoi(get);
			money += _ttoi(get) * now;

			// 매수가, 평가액, 순이익, 보유수, 매수가능액 최신화
			if (gs < 1)
			{
				m_BuyCost.SetWindowTextW(_T("0"));
				m_EsCost.SetWindowTextW(_T("0"));
				m_Profit.SetWindowTextW(_T("0"));
				m_Gs.SetWindowTextW(_T("0"));

				str.Format(_T("%d"), money);
				m_Money.SetWindowTextW(str);
			}
			else
			{
				평가액();
				순이익();
				보유수();
				매수가능액();
			}
		}
	}
}

BOOL CChartGameDlg::BuyInputErr(int input, int now)
{
	if (input < 1)
	{
		MessageBox(_T("최소 주문 개수는 1개입니다."), _T("Error"));
		return TRUE;
	}
	else {
		if (money < now) {
			MessageBox(_T("잔액이 부족합니다."), _T("Error"));
			return TRUE;
		}
		else if (input * now > money)
		{
			MessageBox(_T("잔액이 부족합니다."), _T("Error"));
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

BOOL CChartGameDlg::SellInputErr(int input)
{
	if (input < 1)
	{
		MessageBox(_T("최소 주문 개수는 1개입니다."), _T("Error"));
		return TRUE;
	}
	else {
		if (input > gs) {
			MessageBox(_T("보유하신 주수가 부족합니다."), _T("Error"));
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

