#pragma once
#include "afxdialogex.h"


// Indicator 대화 상자

class Indicator : public CDialogEx
{
	DECLARE_DYNAMIC(Indicator)

public:
	Indicator(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Indicator();
	void AddIND();
	CString GetComboT();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARTGAME_INDICATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox CtrlCBox;
	afx_msg void OnCbnSelchangeIndcombo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
