// ChartGameChild.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "ChartGameChild.h"

// dlg bind
// #include "ChartGameDlg.h";

// oracle
#include <oleacc.h>
#include <occi.h>

// 콘솔 디버깅용
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

using namespace oracle::occi;

Environment* env = 0;
Connection* conn = 0;
Statement* stmt = 0;
ResultSet* rs = 0;

void ChartGameChild::DBConn()
{
	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		// IP가 안될 경우 컴퓨터명 DESKTOP-AQO7IS7 입력
		conn = env->createConnection("sys as sysdba", "lhy45ovos45", "//DESKTOP-AQO7IS7:1521/orcl");

		printf("성공");

		//m_game = new CChartGameDlg();
		//m_game->Create(IDD_CHARTGAME_DIALOG, this);
		//m_game->ShowWindow(SW_SHOW);
	}
	catch (oracle::occi::SQLException ex) {
		printf("실패");
	}
}


// ChartGameChild 대화 상자

IMPLEMENT_DYNAMIC(ChartGameChild, CDialogEx)

ChartGameChild::ChartGameChild(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARTGAME_CHILD, pParent)
{

}

ChartGameChild::~ChartGameChild()
{
}

void ChartGameChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChartGameChild, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &ChartGameChild::OnBnClickedLogin)
END_MESSAGE_MAP()


// ChartGameChild 메시지 처리기


void ChartGameChild::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DBConn();
}
