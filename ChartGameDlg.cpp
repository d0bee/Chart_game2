
// ChartGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ChartGame.h"
#include "ChartGameDlg.h"
#include "afxdialogex.h"
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 콘솔 디버깅용
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace std;

// 캔들 조작용
CChartCandlestickSerie* pCandle = nullptr;
SChartCandlestickPoint pCandlePoint[480];

// 차트 카운트 계산용 변수
int cnt;

// 차트 랜덤 불러오기용 난수
int candlecnt;

// 임시 계좌잔액, DB를 연동하는 경우에도 결국 전역변수와 비슷하게 쓰일 것이기 때문에 전역변수로 구현.
int money;
int gm;
int gs;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CChartGameDlg 대화 상자
CChartGameDlg::CChartGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARTGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
	DDX_Control(pDX, IDC_NEXT, CNext);
	DDX_Control(pDX, IDC_COUNT, mCount);
	DDX_Control(pDX, IDC_CLOSECOST, m_CloseCost);
	DDX_Control(pDX, IDC_BUY, m_Buy);
	DDX_Control(pDX, IDC_SELL, m_Sell);
	DDX_Control(pDX, IDC_INPUT, m_Input);
	DDX_Control(pDX, IDC_BUYCOST, m_BuyCost);
	DDX_Control(pDX, IDC_ESCOST, m_EsCost);
	DDX_Control(pDX, IDC_Profit, m_Profit);
	DDX_Control(pDX, IDC_MONEY, m_Money);
	DDX_Control(pDX, IDC_GS, m_Gs);
}

BEGIN_MESSAGE_MAP(CChartGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_NEXT, &CChartGameDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_GO, &CChartGameDlg::OnBnClickedGo)
	ON_BN_CLICKED(IDC_BUY, &CChartGameDlg::OnBnClickedBuy)
	ON_BN_CLICKED(IDC_SELL, &CChartGameDlg::OnBnClickedSell)
END_MESSAGE_MAP()


// CChartGameDlg 메시지 처리기

BOOL CChartGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	BtnFalse();
	// 원장 초기화, DB와의 연동때 변경되어야 함.
	Account();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CChartGameDlg::BtnFalse()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_NEXT);
	CButton* pBuy = (CButton*)GetDlgItem(IDC_BUY);
	CButton* pSell = (CButton*)GetDlgItem(IDC_SELL);

	pBtn->EnableWindow(FALSE);
	pBuy->EnableWindow(FALSE);
	pSell->EnableWindow(FALSE);
}

void CChartGameDlg::BtnTrue()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_NEXT);
	CButton* pBuy = (CButton*)GetDlgItem(IDC_BUY);
	CButton* pSell = (CButton*)GetDlgItem(IDC_SELL);

	pBtn->EnableWindow(TRUE);
	pBuy->EnableWindow(TRUE);
	pSell->EnableWindow(TRUE);
}

void CChartGameDlg::ChartReset() 
{
	// 난수값을 얻기 위한 random_device
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 450);

	mCount.SetWindowTextW(_T("0/30"));

	m_ChartCtrl.RemoveAllSeries();
	CChartDateTimeAxis* pBottomAxis = m_ChartCtrl.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	CChartStandardAxis* pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	pBottomAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	;
	pCandle = m_ChartCtrl.CreateCandlestickSerie();

	candlecnt = dis(gen);
	ReadData(pCandlePoint);

	pCandle->SetPoints(pCandlePoint, candlecnt);
	pCandle->SetColor(RGB(0, 255, 0));

	cnt = 0;
}

void CChartGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CChartGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CChartGameDlg::ReadData(SChartCandlestickPoint(pCandlePoint)[480])
{
	// 난수값을 얻기 위한 random_device
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 450);

	UpdateData(TRUE);

	//@ 파일에서 데이터 불러오기
	// 파일열기
	 
	// 랜덤용 변수
	CString str;
	int random = dis(gen) % 5 + 1;
	str.Format(_T("%d"), random);
	
	// 파일명 초기화 작업
	CStringA strCSVfileName = "";
	strCSVfileName = (CStringA)theApp.m_sAppPath + L"\\data\\testdata" + (CStringA)str + ".csv";
	char* BufOfFileName = strCSVfileName.GetBuffer(strCSVfileName.GetLength());
	FILE* f = nullptr;
	errno_t err;

	err = fopen_s(&f, BufOfFileName, "rt");	//읽기모드
	if (err || f == NULL)
	{
		AfxMessageBox(L"파일열기 실패");
		return;
	}

	double temp;
	int year, month, day;

	for (int i = 0; i < 480; i++)
	{
		fscanf_s(f, "%4d%2d%2d,%lf,%lf,%lf,%lf,%lf\n",	//  날짜, 시가, 종가, 고가, 저가, 거래량
			&year, &month, &day,
			&pCandlePoint[i].Open,
			&pCandlePoint[i].Close,
			&pCandlePoint[i].High,
			&pCandlePoint[i].Low,
			&temp);

		COleDateTime date(year, month, day, 0, 0, 0);
		pCandlePoint[i].XVal = CChartCtrl::DateToValue(date);
	}

	fclose(f);				//파일 닫기
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CChartGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CChartGameDlg::OnBnClickedNext()
{
	// 변환용 str
	CString str;

	// 최대 cnt
	int Max_cnt = 30;

	// 현재가
	int now;

	if (cnt < Max_cnt) {
		str.Format(_T("%d"), ++cnt);
		pCandle->AddPoints(pCandlePoint, candlecnt + (cnt));
		mCount.SetWindowTextW(str + "/30");

		now = pCandlePoint[candlecnt - 1 + cnt].Close;
		str.Format(_T("%d"), now);
		m_CloseCost.SetWindowTextW(str);

		// 현재가(now)에 따라 평가액(gs*now), 순이익(gs*now - gm) 이 최신화 되어야 함.
		str.Format(_T("%d"), gs * now);
		m_EsCost.SetWindowTextW(str);

		str.Format(_T("%d"), gs * now - gm);
		m_Profit.SetWindowTextW(str);
	}
	
	if (cnt==Max_cnt){
		mCount.SetWindowTextW(_T("END"));
		BtnFalse();
		// if gm이 존재할 경우 자동 SELL이 진행되도록 해야함.
		SellCost(TRUE);
	}
}

void CChartGameDlg::OnBnClickedGo()
{
	// 정수 변환용 str
	CString str;

	BtnTrue();
	ChartReset();

	str.Format(_T("%.0lf"), pCandlePoint[candlecnt-1].Close);
	m_CloseCost.SetWindowTextW(str);
	m_BuyCost.SetWindowTextW(_T("0"));
}

BOOL CChartGameDlg::BuyInputErr(int input, int now)
{
	if (input<1) 
	{
		MessageBox(_T("최소 주문 개수는 1개입니다."), _T("Error"));
		return TRUE;
	}
	else {
		if (money < now) {
			MessageBox(_T("잔액이 부족합니다."), _T("Error"));
			return TRUE;
		}
		else if (input*now > money) 
		{
			MessageBox(_T("잔액이 부족합니다."), _T("Error"));
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}

void CChartGameDlg::BuyCost()
{
	// 주문수 가져오기
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// 매수가 가져오기
	CString str;
	int buy = pCandlePoint[candlecnt - 1 + cnt].Close;

	if (BuyInputErr(_ttoi(get),buy)==FALSE)
	{
		// 실제 평가액 계산
		int num = _ttoi(get) * buy;

		// 원장 최신화
		gm += num;
		gs += _ttoi(get);

		// 매수가 최신화
		double buycost = gm / gs;
		str.Format(_T("%.0lf"), buycost);
		m_BuyCost.SetWindowTextW(str);

		// 평가액 최신화
		str.Format(_T("%d"), gm);
		m_EsCost.SetWindowTextW(str);

		// 매수가능액 최신화
		money -= num;
		str.Format(_T("%d"), money);
		m_Money.SetWindowTextW(str);

		// 보유주 최신화
		str.Format(_T("%d"), gs);
		m_Gs.SetWindowTextW(str);

		printf("gm : %d gs : %d money : %d buycost : %d input : %d\n", gm, gs, money, buy, _ttoi(get));
	}
}

void CChartGameDlg::OnBnClickedBuy()
{
	BuyCost();
	m_Input.SetWindowTextW(_T(""));
	// 원장 최신화, SENTBS()를 통해서 DB업데이트 추가
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

void CChartGameDlg::SellCost(BOOL tf)
{
	// 주문수 가져오기
	CString get;
	GetDlgItemText(IDC_INPUT, get);

	// 현재가 가져오기
	CString str;
	int now = pCandlePoint[candlecnt - 1 + cnt].Close;

	// 순이익 계산용
	CString abc;

	// cnt = max로 끝나는 경우
	if (tf == TRUE) {
		money += gs * now;
		gm = 0;
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
			gm -= _ttoi(get) * now;
			money += _ttoi(get) * now;

			// 매수가, 평가액, 순이익, 보유수, 매수가능액 최신화
			if (gs < 1)
			{
				// 평단 계산용 변수인 gm이 0으로 초기화 되어야 한다.
				gm = 0;

				m_BuyCost.SetWindowTextW(_T("0"));
				m_EsCost.SetWindowTextW(_T("0"));
				m_Profit.SetWindowTextW(_T("0"));
				m_Gs.SetWindowTextW(_T("0"));

				str.Format(_T("%d"), money);
				m_Money.SetWindowTextW(str);
			}
			else
			{
				// 평가액, 순이익, 보유수, 매수가능액 최신화
				str.Format(_T("%d"), now * gs);
				m_EsCost.SetWindowTextW(str);
				// 23100 * 1 - 20600 , / gs , 23100 * 2 - 43700 (46200 - 43700 = 2600
				GetDlgItemText(IDC_BUYCOST,abc);
				str.Format(_T("%d"), (now - _ttoi(abc)) * gs);
				m_Profit.SetWindowTextW(str);

				str.Format(_T("%d"), gs);
				m_Gs.SetWindowTextW(str);

				str.Format(_T("%d"), money);
				m_Money.SetWindowTextW(str);
			}

			printf("gm : %d gs : %d money : %d sellcost : %d input : %d\n", gm, gs, money, now, _ttoi(get));
		}
	}
}

void CChartGameDlg::OnBnClickedSell()
{
	SellCost(FALSE);
	m_Input.SetWindowTextW(_T(""));
	// 원장 최신화, SENTBS()를 통해서 DB업데이트 추가
}


// 가상의 계좌, 이후 DB와의 연동을 고려해서 변경되어야 함.
void CChartGameDlg::Account()
{
	CString str;

	// DB를 통해서 조회한 금액
	money = 200000;

	str.Format(_T("%d"), money);
	m_Money.SetWindowTextW(str);

	// 앞으로 사용될 총 주문액, 개수
	gm = 0;
	gs = 0;
}

// 원장 최신화 메서드, DB 최신화
void SentBS()
{
}

// pCandle->CreateBalloonLabel(6, _T("candle"));
// 강제로 끝나는 경우 자동 SellCost(TRUE) + SentBS()를 통해 최신화
