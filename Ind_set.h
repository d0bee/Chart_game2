﻿#pragma once
#include "afxdialogex.h"


// Ind_set 대화 상자

class Ind_set : public CDialogEx
{
	DECLARE_DYNAMIC(Ind_set)

public:
	Ind_set(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Ind_set();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARTGAME_INDSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_send;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void ChartIndSet(CString);
};
