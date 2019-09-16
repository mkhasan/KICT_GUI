#pragma once
#include "afxwin.h"
#include "ATLComTime.h"
#include "afxdtctl.h"
#include "KICT_MPDlg.h"

// Load dialog

class Load : public CDialogEx
{
	DECLARE_DYNAMIC(Load)

public:
	Load(CWnd* pParent = NULL);   // standard constructor
	virtual ~Load();

// Dialog Data
	enum { IDD = IDD_LOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit ed_count;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	UINT m_radio;
	afx_msg void RadioCtrl(UINT ID);
	int _type; //0 auto 1 manual 2 semi
	COleDateTime m_timeMC;
	CDateTimeCtrl c_time_start;
	CDateTimeCtrl c_time_end;
	afx_msg void OnBnClickedOk();	
	afx_msg void OnBnClickedCancel();
	(CKICT_MPDlg *) p;//ºÎ¸ð
};
