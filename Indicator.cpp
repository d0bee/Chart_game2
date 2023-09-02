// Indicator.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "Indicator.h"

// Indicator_set Child
#include "Ind_set.h"

// To Parents
#include "ChartGameDlg.h"
CChartGameDlg* m_Parents;

// Indicator 대화 상자

IMPLEMENT_DYNAMIC(Indicator, CDialogEx)

Indicator::Indicator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARTGAME_INDICATOR, pParent)
{
	
}

Indicator::~Indicator()
{
}

void Indicator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INDCOMBO, CtrlCBox);
}

void Indicator::AddIND()
{
	CtrlCBox.AddString(_T("이동평균선"));
	CtrlCBox.AddString(_T("볼린저밴드"));
	CtrlCBox.AddString(_T("TEST 1"));
	CtrlCBox.AddString(_T("TEST 2"));
	CtrlCBox.AddString(_T("TEST 3"));
	CtrlCBox.AddString(_T("TEST 4"));
	CtrlCBox.AddString(_T("TEST 5"));
	CtrlCBox.AddString(_T("TEST 6"));
	CtrlCBox.AddString(_T("TEST 7"));
	CtrlCBox.AddString(_T("TEST 8"));
}

BEGIN_MESSAGE_MAP(Indicator, CDialogEx)
	ON_CBN_SELCHANGE(IDC_INDCOMBO, &Indicator::OnCbnSelchangeIndcombo)
END_MESSAGE_MAP()


// Indicator 메시지 처리기

CString Indicator::GetComboT()
{
	CString str;
	CtrlCBox.GetLBText(CtrlCBox.GetCurSel(), str);
	
	return str;
}

void Indicator::OnCbnSelchangeIndcombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = GetComboT();

	Ind_set* pInd_set = new Ind_set;
	pInd_set->Create(IDD_CHARTGAME_INDSET, this);
	pInd_set->CenterWindow();
	pInd_set->ShowWindow(SW_SHOW);
}


BOOL Indicator::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL Indicator::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	// parents set
	m_Parents = ((CChartGameDlg*)GetParent());
	
	// combobox indicator add
	AddIND();
	// m_Parents->m_EsCost.SetWindowTextW(_T("5"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
