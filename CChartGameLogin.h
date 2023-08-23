#pragma once
#include "afxdialogex.h"


// CChartGameLogin 대화 상자

class CChartGameLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CChartGameLogin)

public:
	CChartGameLogin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CChartGameLogin();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARTGAME_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Login_Id;
	CEdit m_Login_Pass;
	CButton m_Login;
	afx_msg void OnBnClickedLogin();
};
