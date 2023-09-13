// Ind_set.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "Ind_set.h"

// 부모의 부모
CChartGameDlg* m_Parents_Parents;

// 부모
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
	DDX_Control(pDX, IDC_mValue1, m_V1);
	DDX_Control(pDX, IDC_mValue2, m_V2);
	DDX_Control(pDX, IDC_mValue3, m_V3);
	DDX_Control(pDX, IDC_mValue4, m_V4);
	DDX_Control(pDX, IDC_mValue5, m_V5);
	DDX_Control(pDX, IDC_LABEL1, m_L1);
	DDX_Control(pDX, IDC_LABEL2, m_L2);
	DDX_Control(pDX, IDC_LABEL3, m_L3);
	DDX_Control(pDX, IDC_LABEL4, m_L4);
	DDX_Control(pDX, IDC_LABEL5, m_L5);
	DDX_Control(pDX, IDC_LABEL6, m_L6);
	DDX_Control(pDX, IDC_mValue6, m_V6);
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

	// str에 이동평균선, 볼린저밴드 등의 TXT가 들어있는 상태
	// str에 따라서 m_Parents_Parents의 라인 차트를 조정해야함.
	if (str == "이동평균선")
	{
		mov_avg();
	}

	CDialogEx::OnOK();
}

void Ind_set::ChartIndSet(CString str)
{
	// 2. ChartIndSet 분류를 통해 m_Parents_Parents의 pSeries의 형태를 변형, 추가시켜야 함.
	// m_Parents_Parents->XVal, close 등의 변수를 이용
	// 이동평균선 기간이 10이라면 최우선 생성되는 9일은 이동평균선이 없어야 함.
	// pSeries->SetPoints()의 경우 XVal = 날짜, YVal = 값인데 XVal이 + 변수 - 1부터 계산되어야 하는 부분
	// 여러모로 고려해야할 사항이 많을 것으로 생각된다.

	if (str == "이동평균선")
	{
		m_L1.SetWindowTextW(_T("기간1"));
		m_L2.SetWindowTextW(_T("기간2"));
		m_L3.SetWindowTextW(_T("기간3"));
		m_L4.SetWindowTextW(_T("기간4"));
		m_L5.SetWindowTextW(_T("기간5"));
		m_L6.SetWindowTextW(_T("기간6"));

		mov_avg();
	}
}

// m_Parents_Parents->
void Ind_set::mov_avg()
{
	CString str;
	int arr[6] = { 0 };

	m_V1.GetWindowTextW(str);
	arr[0] = _ttoi(str);

	m_V2.GetWindowTextW(str);
	arr[1] = _ttoi(str);

	m_V3.GetWindowTextW(str);
	arr[2] = _ttoi(str);

	m_V4.GetWindowTextW(str);
	arr[3] = _ttoi(str);

	m_V5.GetWindowTextW(str);
	arr[4] = _ttoi(str);

	m_V6.GetWindowTextW(str);
	arr[5] = _ttoi(str);

	m_Parents_Parents->pSeries;
}

BOOL Ind_set::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 부모의 부모
	m_Parents_Parents = (CChartGameDlg*)GetParent();

	// 부모
	m_Parents = (Indicator*)GetParent();

	CString str;
	m_Parents->CtrlCBox.GetWindowTextW(str);
	ChartIndSet(str);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
