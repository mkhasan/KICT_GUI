// IpSetting.cpp : implementation file
//

#include "stdafx.h"
#include "KICT_MPDlg.h"
#include "IpSetting.h"
IMPLEMENT_DYNAMIC(IpSetting, CDialogEx)

IpSetting::IpSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IpSetting::IDD, pParent)
{

}

IpSetting::~IpSetting()
{
}

void IpSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IP_ROBOT, c_ip_robot);
	DDX_Control(pDX, IDC_IP_ROBOTCAM, c_ip_robotcam);
	DDX_Control(pDX, IDC_IP_NIGHTLEFT, c_ip_nightleft);
	DDX_Control(pDX, IDC_IP_NIGHTRIGHT, c_ip_nightright);
	DDX_Control(pDX, IDC_IP_FISHLEFT, c_ip_fishleft);
	DDX_Control(pDX, IDC_IP_FISHRIGHT, c_ip_fishright);
	DDX_Control(pDX, IDC_IP_FRONTLEFT, c_ip_frontleft);
	DDX_Control(pDX, IDC_IP_REARRIGHT, c_ip_rearright);
	DDX_Control(pDX, IDC_IP_FRONTRIGHT, c_ip_frontright);
	DDX_Control(pDX, IDC_IP_REARLEFT, c_ip_rearleft);
}


BEGIN_MESSAGE_MAP(IpSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &IpSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &IpSetting::OnBnClickedCancel)
END_MESSAGE_MAP()


// IpSetting message handlers


BOOL IpSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	wnd_p = (CKICT_MPDlg*)::AfxGetMainWnd();

	char tmp[32] = { 0, };
	char c_ipFirst[6], c_ipSecond[6], c_ipThird[6], c_ipForth[6];
	int i_ipFirst, i_ipSecond, i_ipThird, i_ipForth;
	char* context = NULL;

	strcpy_s(tmp, wnd_p->_ip_DrMobile);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_robot.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_DrCamera);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_robotcam.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_NightCameraL);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_nightleft.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_NightCameraR);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_nightright.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_FishL);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_fishleft.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_FishR);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_fishright.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_FrontL);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_frontleft.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);


	strcpy_s(tmp, wnd_p->_ip_FrontR);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_frontright.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_RearL);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_rearleft.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	strcpy_s(tmp, wnd_p->_ip_RearR);
	strcpy_s(c_ipFirst, strtok_s(tmp, ".", &context));
	strcpy_s(c_ipSecond, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipThird, strtok_s(NULL, ".", &context));
	strcpy_s(c_ipForth, strtok_s(NULL, ".", &context));
	i_ipFirst = atoi(c_ipFirst);	i_ipSecond = atoi(c_ipSecond);	i_ipThird = atoi(c_ipThird);	i_ipForth = atoi(c_ipForth);
	c_ip_rearright.SetAddress(i_ipFirst, i_ipSecond, i_ipThird, i_ipForth);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

}


BOOL IpSetting::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE; // '엔터' 종료 막기
	return CDialogEx::PreTranslateMessage(pMsg);
}

void IpSetting::OnBnClickedOk()
{
	FILE *fp_setting;//파일 만들어 setting 값을 저장
	char str[128] = { 0, };
	BYTE ipFirst, ipSecond, ipThird, ipForth;
	char t_ip[32] = { 0, };
	char fname[128] = { 0, };
	sprintf_s(fname, "IpSetting.txt");
	fopen_s(&fp_setting, fname, "w");
	////////////////////////////////////////// IP 저장 ///////

	c_ip_robot.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_robotcam.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_nightleft.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_nightright.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_fishleft.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_fishright.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_frontleft.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_frontright.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_rearleft.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	c_ip_rearright.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(str, "%s:\n", t_ip);
	fwrite(str, sizeof(char), strlen(str), fp_setting);

	fclose(fp_setting);

	//wnd_p->LoadIpSetting();

	CDialogEx::OnOK();
}


void IpSetting::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
