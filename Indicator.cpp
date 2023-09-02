// Indicator.cpp: 구현 파일
//

#include "pch.h"
#include "ChartGame.h"
#include "afxdialogex.h"
#include "Indicator.h"


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
}


BEGIN_MESSAGE_MAP(Indicator, CDialogEx)
END_MESSAGE_MAP()


// Indicator 메시지 처리기
