// CChartGameLogin.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "CChartGameLogin.h"


// CChartGameLogin 대화 상자

IMPLEMENT_DYNAMIC(CChartGameLogin, CDialogEx)

CChartGameLogin::CChartGameLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARTGAME_LOGIN, pParent)
{

}

CChartGameLogin::~CChartGameLogin()
{
}

void CChartGameLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOGIN_ID, m_Login_Id);
	DDX_Control(pDX, IDC_LOGIN_PASS, m_Login_Pass);
	DDX_Control(pDX, IDD_INSERT, m_Login);
}


BEGIN_MESSAGE_MAP(CChartGameLogin, CDialogEx)
	ON_BN_CLICKED(IDC_LOGIN, &CChartGameLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CChartGameLogin 메시지 처리기


void CChartGameLogin::OnBnClickedLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

int db_connect(char* oracle_user, char* oracle_password, char* db_name)
{
    EXEC SQL BEGIN DECLARE SECTION;
    varchar id[64];
    varchar password[64];
    varchar tns[128];
    EXEC SQL END DECLARE SECTION;

    memset(&id, 0x00, sizeof(id));
    memset(&password, 0x00, sizeof(password));
    memset(&tns, 0x00, sizeof(tns));

    strcpy((char*)id.arr, oracle_user);
    strcpy((char*)password.arr, oracle_password);
    strcpy((char*)tns.arr, db_name);

    id.len = strlen((char*)id.arr);
    password.len = strlen((char*)password.arr);
    tns.len = strlen((char*)tns.arr);

    EXEC SQL CONNECT : id IDENTIFIED BY : password USING : tns;

    if (!SQL_SUCCESS)
    {
        return sqlca.sqlcode;
    }
    return 1;
}