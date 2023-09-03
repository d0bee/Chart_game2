// Ind_set.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "Ind_set.h"

// 부모의 부모
#include "ChartGameDlg.h"
CChartGameDlg* m_Parents_Parents;

// 부모
#include "Indicator.h"
Indicator* m_Parents;

// Ind_set 대화 상자

IMPLEMENT_DYNAMIC(Ind_set, CDialogEx)

Ind_set::Ind_set(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARTGAME_INDSET, pParent)
{

}

Ind_set::~Ind_set()
{
}

void Ind_set::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_send);
}


BEGIN_MESSAGE_MAP(Ind_set, CDialogEx)
	ON_BN_CLICKED(IDOK, &Ind_set::OnBnClickedOk)
END_MESSAGE_MAP()


// Ind_set 메시지 처리기


void Ind_set::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	str = m_Parents->GetComboT();


	CDialogEx::OnOK();
}

void Ind_set::ChartIndSet(CString str)
{
}


BOOL Ind_set::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 부모의 부모
	m_Parents_Parents = (CChartGameDlg*)GetParent();

	// 부모
	m_Parents = (Indicator*)GetParent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
