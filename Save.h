#pragma once
#include "KICT_MPDlg.h"
#include "afxcmn.h"
#include "afxwin.h"


// Save dialog

class Save : public CDialogEx
{
	DECLARE_DYNAMIC(Save)

public:
	Save(CWnd* pParent = NULL);   // standard constructor
	virtual ~Save();

// Dialog Data
	enum { IDD = IDD_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CKICT_MPDlg *wnd_p;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int spin_value;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CSpinButtonCtrl c_sp;
	int v_sec;
	CEdit ed_state_auto;
	CEdit ed_state_semi;
	afx_msg void OnBnClickedBtAutosave();
	//afx_msg void OnBnClickedBtStop();
	//afx_msg void OnBnClickedBtMansave();
	afx_msg void OnBnClickedBtManauto();
	afx_msg void OnBnClickedBtAutostop();
	afx_msg void OnBnClickedBtSemisave();
	afx_msg void OnBnClickedBtSemistop();
	afx_msg void OnBnClickedBtMansemi();
	CButton m_autosave;
	CButton m_semisave;
	CButton m_stopauto;
	CButton m_stopsemi;
	CButton m_automan;
	CButton m_semiman;
};
