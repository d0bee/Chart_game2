#pragma once
#include "afxdialogex.h"


// ChartGameChild 대화 상자

class ChartGameChild : public CDialogEx
{
	DECLARE_DYNAMIC(ChartGameChild)

public:
	ChartGameChild(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ChartGameChild();

	void DBConn();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARTGAME_CHILD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
};
