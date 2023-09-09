#include "pch.h"
#include "Account.h"

// ������ ����, ���� DB���� ������ ����ؼ� ����Ǿ�� ��.
void CChartGameDlg::Account()
{
	CString str;

	// DB�� ���ؼ� ��ȸ�� �ݾ�
	money = 200000;

	str.Format(_T("%d"), money);
	m_Money.SetWindowTextW(str);

	// ������ ���� �� �ֹ���, ����
	gs = 0;
	��մܰ� = 0;
}

void CChartGameDlg::BuyCost(SChartCandlestickPoint pCandlePoint[], int candlecnt, int cnt)
{
	// �ֹ��� ��������
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// �ż��� ��������
	CString str;
	int buy = pCandlePoint[candlecnt - 1 + cnt].Close;

	if (BuyInputErr(_ttoi(get), buy) == FALSE)
	{
		// ���� �ֹ���
		int num = _ttoi(get) * buy;

		// ���� �ֽ�ȭ
		��մܰ� = ((��մܰ� * gs) + num) / (_ttoi(get) + gs);
		gs += _ttoi(get);
		money -= num;

		�ż���();
		�򰡾�();
		�ż����ɾ�();
		������();
	}
}

void CChartGameDlg::SellCost(BOOL tf, SChartCandlestickPoint pCandlePoint[], int candlecnt, int cnt)
{
	// �ֹ��� ��������
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// ���簡 ��������
	CString str;
	int now = pCandlePoint[candlecnt - 1 + cnt].Close;

	// cnt = max�� ������ ���
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
			// ���� �ֽ�ȭ
			gs -= _ttoi(get);
			money += _ttoi(get) * now;

			// �ż���, �򰡾�, ������, ������, �ż����ɾ� �ֽ�ȭ
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
				�򰡾�();
				������();
				������();
				�ż����ɾ�();
			}
		}
	}
}

BOOL CChartGameDlg::BuyInputErr(int input, int now)
{
	if (input < 1)
	{
		MessageBox(_T("�ּ� �ֹ� ������ 1���Դϴ�."), _T("Error"));
		return TRUE;
	}
	else {
		if (money < now) {
			MessageBox(_T("�ܾ��� �����մϴ�."), _T("Error"));
			return TRUE;
		}
		else if (input * now > money)
		{
			MessageBox(_T("�ܾ��� �����մϴ�."), _T("Error"));
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
		MessageBox(_T("�ּ� �ֹ� ������ 1���Դϴ�."), _T("Error"));
		return TRUE;
	}
	else {
		if (input > gs) {
			MessageBox(_T("�����Ͻ� �ּ��� �����մϴ�."), _T("Error"));
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

