// Ind_set.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "Ind_set.h"


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
END_MESSAGE_MAP()


// Ind_set 메시지 처리기
