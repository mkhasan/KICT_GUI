// Save.cpp : implementation file
//

#include "stdafx.h"
#include "KICT_MP.h"
#include "Save.h"
#include "afxdialogex.h"


// Save dialog

IMPLEMENT_DYNAMIC(Save, CDialogEx)

Save::Save(CWnd* pParent /*=NULL*/)
	: CDialogEx(Save::IDD, pParent)
	, v_sec(1)
	, m_ImageSel(0)
{

}

Save::~Save()
{
}

void Save::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPIN1, c_sp);
	DDX_Text(pDX, IDC_ED_SEC, v_sec);
	DDV_MinMaxInt(pDX, v_sec, 1, 60);
	DDX_Control(pDX, IDC_ED_STATE, ed_state_auto);
	DDX_Control(pDX, IDC_ED_STATE2, ed_state_semi);
	DDX_Control(pDX, IDC_BT_AUTOSAVE, m_autosave);
	DDX_Control(pDX, IDC_BT_SEMISAVE, m_semisave);
	DDX_Control(pDX, IDC_BT_AUTOSTOP, m_stopauto);
	DDX_Control(pDX, IDC_BT_SEMISTOP, m_stopsemi);
	DDX_Control(pDX, IDC_BT_MANAUTO, m_automan);
	DDX_Control(pDX, IDC_BT_MANSEMI, m_semiman);
}


BEGIN_MESSAGE_MAP(Save, CDialogEx)
	ON_BN_CLICKED(IDOK, &Save::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &Save::OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BT_AUTOSAVE, &Save::OnBnClickedBtAutosave)
	//ON_BN_CLICKED(IDC_BT_STOP, &Save::OnBnClickedBtStop)
	//ON_BN_CLICKED(IDC_BT_MANSAVE, &Save::OnBnClickedBtMansave)
	ON_BN_CLICKED(IDC_BT_MANAUTO, &Save::OnBnClickedBtManauto)
	ON_BN_CLICKED(IDC_BT_AUTOSTOP, &Save::OnBnClickedBtAutostop)
	ON_BN_CLICKED(IDC_BT_SEMISAVE, &Save::OnBnClickedBtSemisave)
	ON_BN_CLICKED(IDC_BT_SEMISTOP, &Save::OnBnClickedBtSemistop)
	ON_BN_CLICKED(IDC_BT_MANSEMI, &Save::OnBnClickedBtMansemi)
	ON_BN_CLICKED(IDC_RADIO_IMAGE, &Save::OnBnClickedRadioImage)
	ON_BN_CLICKED(IDC_RADIO_VIDEO, &Save::OnBnClickedRadioVideo)
END_MESSAGE_MAP()


// Save message handlers


BOOL Save::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE; // '엔터' 종료 막기
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL Save::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	wnd_p = (CKICT_MPDlg*)::AfxGetMainWnd();
	spin_value = 1;
	c_sp.SetRange(1,60);
	// auto 1 semi-auto 2
	if (wnd_p->_save == 1){
		ed_state_auto.SetWindowTextW(_T("Saving"));
		ed_state_semi.SetWindowTextW(_T("Stop"));

		m_semisave.EnableWindow(false);
		m_semiman.EnableWindow(false);
		m_stopsemi.EnableWindow(false);
	}

	else if (wnd_p->_save == 2){
		ed_state_semi.SetWindowTextW(_T("Saving"));
		ed_state_auto.SetWindowTextW(_T("Stop"));

		m_autosave.EnableWindow(false);
		m_automan.EnableWindow(false);
		m_stopauto.EnableWindow(false);
	}
	else
	{
		ed_state_semi.SetWindowTextW(_T("Stop"));
		ed_state_auto.SetWindowTextW(_T("Stop"));
	}

	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_IMAGE);
	pButton->SetCheck(true);
	imageSelected = true;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void Save::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void Save::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	if (pNMUpDown->iDelta < 0){
		spin_value++;
	}
	else
	{
		spin_value--;
	}

	*pResult = 0;
}


void Save::OnBnClickedBtAutosave() //저장 시작
{
	if (UpdateData()) //normal
	{
		int sec = v_sec;
		ed_state_auto.SetWindowTextW(_T("Saving"));
		wnd_p->_save = 1;
		char str[16] = { 0, };
		sprintf_s(str,"%.3f",(1/(float)v_sec));
		
		//int k = imageSelected;
		if (imageSelected)
			wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/AUTO_SAVE_START", strlen(str), str, 1, false);
		else
			wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/AUTO_VIDEO_START", strlen(str), str, 1, false);

		m_semisave.EnableWindow(false);
		m_semiman.EnableWindow(false);
		m_stopsemi.EnableWindow(false);
		GetDlgItem(IDC_RADIO_IMAGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_VIDEO)->EnableWindow(FALSE);
	}	
}

void Save::OnBnClickedBtManauto()
{
	wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/MANUAL_SAVE", 0, "", 1, false);
}

void Save::OnBnClickedBtAutostop()
{
	ed_state_auto.SetWindowTextW(_T("Stop"));
	wnd_p->_save = 0;
	if (imageSelected)
		wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/AUTO_SAVE_STOP", 0, "", 1, false);
	else
		wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/AUTO_VIDEO_STOP", 0, "", 1, false);

	m_semisave.EnableWindow(true);
	m_semiman.EnableWindow(true);
	m_stopsemi.EnableWindow(true);
	GetDlgItem(IDC_RADIO_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_VIDEO)->EnableWindow(TRUE);

}

void Save::OnBnClickedBtSemisave()
{
	if (UpdateData()) //normal
	{
		int sec = v_sec;
		ed_state_semi.SetWindowTextW(_T("Saving"));
		wnd_p->_save = 2;
		char str[16] = { 0, };
		sprintf_s(str, "%.3f", (1 / (float)v_sec));
		wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/SEMI_AUTO_START", strlen(str), str, 1, false);

		m_autosave.EnableWindow(false);
		m_automan.EnableWindow(false);
		m_stopauto.EnableWindow(false);
	}
}

void Save::OnBnClickedBtSemistop()
{
	ed_state_semi.SetWindowTextW(_T("Stop"));
	wnd_p->_save = 0;
	wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/SEMI_AUTO_STOP", 0, "", 1, false);
	m_autosave.EnableWindow(true);
	m_automan.EnableWindow(true);
	m_stopauto.EnableWindow(true);
	GetDlgItem(IDC_RADIO_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_VIDEO)->EnableWindow(TRUE);

}


void Save::OnBnClickedBtMansemi()
{
	wnd_p->mqtt0->publish(NULL, "KICT_MP/CLIENT/SEMI_AUTO_SNAP", 0, "", 1, false);
}

void Save::OnBnClickedRadioImage()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int k = m_ImageSel;
	GetDlgItem(IDC_BT_MANAUTO)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BT_MANSEMI)->EnableWindow(TRUE);
	imageSelected = true;
}


void Save::OnBnClickedRadioVideo()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int k = m_ImageSel;
	GetDlgItem(IDC_BT_MANAUTO)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BT_MANSEMI)->EnableWindow(FALSE);
	imageSelected = false;
	
}
