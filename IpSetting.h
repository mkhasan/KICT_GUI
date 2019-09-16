#pragma once
#include "afxcmn.h"
#include "KICT_MPDlg.h"

// IpSetting dialog

class IpSetting : public CDialogEx
{
	DECLARE_DYNAMIC(IpSetting)

public:
	IpSetting(CWnd* pParent = NULL);   // standard constructor
	virtual ~IpSetting();

// Dialog Data
	enum { IDD = IDD_IPSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CIPAddressCtrl c_ip_robot;
	CIPAddressCtrl c_ip_robotcam;
	CIPAddressCtrl c_ip_nightleft;
	CIPAddressCtrl c_ip_nightright;
	CIPAddressCtrl c_ip_fishleft;
	CIPAddressCtrl c_ip_fishright;
	CIPAddressCtrl c_ip_frontleft;
	CIPAddressCtrl c_ip_rearright;
	CKICT_MPDlg *wnd_p;
	CIPAddressCtrl c_ip_frontright;
	CIPAddressCtrl c_ip_rearleft;
	afx_msg void OnBnClickedCancel();
};
