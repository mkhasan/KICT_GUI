// Load.cpp : implementation file
//

#include "stdafx.h"
#include "KICT_MP.h"
#include "Load.h"
#include "afxdialogex.h"

// Load dialog

IMPLEMENT_DYNAMIC(Load, CDialogEx)

Load::Load(CWnd* pParent /*=NULL*/)
	: CDialogEx(Load::IDD, pParent)
	, m_timeMC(COleDateTime::GetCurrentTime())

{

}

Load::~Load()
{
}

void Load::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ed_count);
	DDX_Radio(pDX, IDC_RA1, (int&)m_radio);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_timeMC);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, c_time_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, c_time_end);
}


BEGIN_MESSAGE_MAP(Load, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &Load::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &Load::OnBnClickedButton1)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RA1, IDC_RA3, RadioCtrl)

	ON_BN_CLICKED(IDOK, &Load::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Load::OnBnClickedCancel)
END_MESSAGE_MAP()


// Load message handlers


BOOL Load::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ed_count.SetWindowTextW(_T("record count(s) : "));

	_type = 0;
	p = (CKICT_MPDlg *)::AfxGetMainWnd();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL Load::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE; // '엔터' 종료 막기
	return CDialogEx::PreTranslateMessage(pMsg);
}


void Load::OnBnClickedButton3() //불러오기
{
	UpdateData();

	COleDateTime            m_time1, m_time2;
	VERIFY(c_time_start.GetTime(m_time1));
	VERIFY(c_time_end.GetTime(m_time2));
	if (m_time1 > m_time2)
	{
		AfxMessageBox(_T("종료 시간이 시작 시간보다 빠릅니다."));
		return;
	}
	char t_start[32] = { 0, };
	char t_end[32] = { 0, };
	sprintf_s(t_start, "%04d-%02d-%02d %02d:%02d:%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time1.GetHour(), m_time1.GetMinute(), m_time1.GetSecond());
	sprintf_s(t_end, "%04d-%02d-%02d %02d:%02d:%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time2.GetHour(), m_time2.GetMinute(), m_time2.GetSecond());
	//CDatabase robot_;
	//robot_.SetQueryTimeout(0);
	if (p->robot_db.OpenEx(_T("DSN=robot_db;UID=root;PWD=test123")) == false)
		return;
	
	CRecordset record(&p->robot_db);

	CString auto_man;
	if (_type == 0)
		auto_man = "auto_or_manual=1"; //자동
	else if (_type == 1)
		auto_man = "auto_or_manual=0"; //수동
	else if (_type == 2)
		auto_man = "(auto_or_manual=2 or auto_or_manual=3)"; //SEMI

	CString qu;
	//entry_no 찾기
	qu.Format(_T("select entry_no from real_time_data where %s and (date_time BETWEEN '%s' AND '%s')"), auto_man, CString(t_start), CString(t_end));
	if (record.Open(CRecordset::snapshot, qu) == false)
		return;
	CStringA no;
	int once = 0;
	int begin_no = 0;
	int end_no = 0;
	while (!record.IsEOF())
	{
		record.GetFieldValue(L"entry_no", no);
		if (once == 0)
		{
			begin_no = atoi(no);
			once = 1;
		}
		record.MoveNext();
	}
	end_no = atoi(no);
	record.Close();

	//entry_no 로 쿼리,(시간으로 쿼리하면 응답 매우 늦음)
	qu.Format(_T("select date_time,auto_or_manual,imu_time_stamp,roll,pitch,yaw,roll_accel,pitch_accel,yaw_accel,gps_time_stamp,satellite_count,latitude,latitude_dir,longitude,longitude_dir,quality,VOG,COG,pan_angle,tilt_angle, position_0, position_1, position_2, position_3, speed_0, speed_1, speed_2, speed_3, DR_CAM,NC_LEFT,NC_RIGHT,FH_LEFT,FH_RIGHT,FR_LEFT,FR_RIGHT,RE_LEFT,RE_RIGHT from real_time_data where %s and (entry_no BETWEEN %d AND %d)"), auto_man, begin_no, end_no);

	if (record.Open(CRecordset::snapshot, qu) == false)
		return;
	CStringA dt, auto_or_manual, imu_time_stamp, roll, pitch, yaw, roll_accel, pitch_accel, yaw_accel, gps_time_stamp, satellite_count, latitude, latitude_dir, longitude, longitude_dir, quality, VOG, COG, pan_angle, tilt_angle, position_0, position_1, position_2, position_3, speed_0, speed_1, speed_2, speed_3;

	int cnt = 0;
	static CDBVariant variant;
	char filename[128] = { 0, };
	char str[512] = { 0, };
	CStringA dir;

	if (_type == 1){ //man
		sprintf_s(str, "%04d%02d%02d_%02d%02d%02d-%02d%02d%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time1.GetHour(), m_time1.GetMinute(), m_time1.GetSecond(), m_time2.GetHour(), m_time2.GetMinute(), m_time2.GetSecond());
		sprintf_s(filename, "C:\\data\\manual\\%s\\%s.txt", str, str);
		dir.Format("C:\\data\\manual\\%s", str);
		CreateDirectoryA(dir, NULL);
	}
	else if (_type == 0){ //auto
		sprintf_s(str, "%04d%02d%02d_%02d%02d%02d-%02d%02d%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time1.GetHour(), m_time1.GetMinute(), m_time1.GetSecond(), m_time2.GetHour(), m_time2.GetMinute(), m_time2.GetSecond());
		sprintf_s(filename, "C:\\data\\auto\\%s\\%s.txt", str, str);
		dir.Format("C:\\data\\auto\\%s", str);
		CreateDirectoryA(dir, NULL);
	}
	else if (_type == 2){ //semi
		sprintf_s(str, "%04d%02d%02d_%02d%02d%02d-%02d%02d%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time1.GetHour(), m_time1.GetMinute(), m_time1.GetSecond(), m_time2.GetHour(), m_time2.GetMinute(), m_time2.GetSecond());
		sprintf_s(filename, "C:\\data\\semi\\%s\\%s.txt", str, str);
		dir.Format("C:\\data\\semi\\%s", str);
		CreateDirectoryA(dir, NULL);
	}

	FILE *fp;
	fopen_s(&fp, filename, "w");
	sprintf_s(str, "no date time mode imu_time_stamp roll pitch yaw roll_accel pitch_accel yaw_accel gps_time_stamp satellite_count latitude latitude_dir longitude longuitude_dir quality VOG COG pan_angle tilt_angle position_LFM position_RFM position_LRM position_RRM speed_LFM speed_RFM speed_LRM speed_RRM\r\n");
	fwrite(str, sizeof(char), strlen(str), fp);
	while (!record.IsEOF())
	{
		cnt = record.GetRecordCount();
		record.GetFieldValue(L"date_time", dt);
		record.GetFieldValue(L"auto_or_manual", auto_or_manual);
		record.GetFieldValue(L"imu_time_stamp", imu_time_stamp);
		record.GetFieldValue(L"roll", roll);
		record.GetFieldValue(L"pitch", pitch);
		record.GetFieldValue(L"yaw", yaw);

		record.GetFieldValue(L"roll_accel", roll_accel);
		record.GetFieldValue(L"pitch_accel", pitch_accel);
		record.GetFieldValue(L"yaw_accel", yaw_accel);

		record.GetFieldValue(L"gps_time_stamp", gps_time_stamp);
		record.GetFieldValue(L"satellite_count", satellite_count);
		record.GetFieldValue(L"latitude", latitude);
		record.GetFieldValue(L"latitude_dir", latitude_dir);
		record.GetFieldValue(L"longitude", longitude);
		record.GetFieldValue(L"longitude_dir", longitude_dir);
		record.GetFieldValue(L"quality", quality);
		record.GetFieldValue(L"VOG", VOG);
		record.GetFieldValue(L"COG", COG);

		record.GetFieldValue(L"pan_angle", pan_angle);
		record.GetFieldValue(L"tilt_angle", tilt_angle);

		record.GetFieldValue(L"position_0", position_0);
		record.GetFieldValue(L"position_1", position_1);
		record.GetFieldValue(L"position_2", position_2);
		record.GetFieldValue(L"position_3", position_3);

		record.GetFieldValue(L"speed_0", speed_0);
		record.GetFieldValue(L"speed_1", speed_1);
		record.GetFieldValue(L"speed_2", speed_2);
		record.GetFieldValue(L"speed_3", speed_3);

		char mode[16] = { 0, };
		if (auto_or_manual == '1')
			strcpy_s(mode, "auto");
		else if (auto_or_manual == '0')
			strcpy_s(mode, "man");
		else if (auto_or_manual == '2')
			strcpy_s(mode, "semi");
		else if (auto_or_manual == '3')
			strcpy_s(mode, "snap");

		sprintf_s(str, "%d %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\r\n", cnt, dt, mode, imu_time_stamp, roll, pitch, yaw, roll_accel, pitch_accel, yaw_accel, gps_time_stamp, satellite_count, latitude, latitude_dir, longitude, longitude_dir, quality, VOG, COG, pan_angle, tilt_angle, position_0, position_1, position_2, position_3, speed_0, speed_1, speed_2, speed_3);
		fwrite(str, sizeof(char), strlen(str), fp); //데이터 쓰기

		CString IMG[9] = { _T("DR_CAM"), _T("NC_LEFT"), _T("NC_RIGHT"), _T("FH_LEFT"), _T("FH_RIGHT"), _T("FR_LEFT"), _T("FR_RIGHT"), _T("RE_LEFT"), _T("RE_RIGHT") };

		for (int i = 0; i < 9; i++){ //이미지 불러오기
			record.GetFieldValue(IMG[i], variant, SQL_C_BINARY);
			CLongBinary *p = variant.m_pbinary;
			LPSTR	buffer = (LPSTR)GlobalLock(p->m_hData);
			dt.Replace(":", "");
			CString ImgName = (CString)dir + "\\" + (CString)dt + " " + IMG[i] + ".jpg";

			if (buffer){
				CFile	outFile(ImgName, CFile::modeCreate | CFile::modeWrite);

				outFile.Write(buffer, p->m_dwDataLength);
				GlobalUnlock(p->m_hData);
				outFile.Close();				
			}			
		}
		record.MoveNext();
	}
	record.Close();
	p->robot_db.Close();
	fclose(fp);
	
}
void Load::OnBnClickedButton1() //조회
{
	UpdateData();	

	COleDateTime            m_time1, m_time2;
	VERIFY(c_time_start.GetTime(m_time1));
	VERIFY(c_time_end.GetTime(m_time2));
	if (m_time1 > m_time2)
	{
		AfxMessageBox(_T("종료 시간이 시작 시간보다 빠릅니다."));
		return;
	}
	char t_start[32] = { 0, };
	char t_end[32] = { 0, };
	sprintf_s(t_start, "%04d-%02d-%02d %02d:%02d:%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time1.GetHour(), m_time1.GetMinute(), m_time1.GetSecond());
	sprintf_s(t_end, "%04d-%02d-%02d %02d:%02d:%02d", m_timeMC.GetYear(), m_timeMC.GetMonth(), m_timeMC.GetDay(), m_time2.GetHour(), m_time2.GetMinute(), m_time2.GetSecond());

	BOOL re;		
	try {	
		re=p->robot_db.OpenEx(_T("DSN=robot_db;UID=root;PWD=test123"),CDatabase::noOdbcDialog);
	}	
	catch (CDBException * pEX) {
		pEX->ReportError();
		//AfxMessageBox(pEX->m_strError);
		pEX->Delete();
	}
	if (!re){	
		return;
	}		

	CRecordset record(&p->robot_db);
	CString auto_man;
	if (_type == 0)
		auto_man = "auto_or_manual=1"; //자동
	else if (_type == 1)
		auto_man = "auto_or_manual=0"; //수동
	else if (_type == 2)
		auto_man = "(auto_or_manual=2 or auto_or_manual=3)"; //SEMI

	CString qu;	
	//qu.Format(_T("select date_time from real_time_data where (auto_or_manual=%d) and (date_time BETWEEN '%s' AND '%s')"), _type, CString(t_start), CString(t_end));
	qu.Format(_T("select date_time from real_time_data where %s and (date_time BETWEEN '%s' AND '%s')"), auto_man, CString(t_start), CString(t_end));
	//qu.Format(_T("select NC_LEFT,date_time,DR_CAM from real_time_data where (auto_or_manual=%d) limit 100"), _type);
	if (record.Open(CRecordset::snapshot, qu) == false)
		return;	
	
	int cnt = 0;	
	while (!record.IsEOF())
	{		
		cnt = record.GetRecordCount();
		record.MoveNext();
	}
	CString count;
	count.Format(_T("record count(s): %d"),cnt);
	ed_count.SetWindowTextW(count);
	record.Close();
	p->robot_db.Close();
}

void Load::RadioCtrl(UINT ID)
{
	UpdateData(TRUE);
	switch (m_radio)
	{
		case 0:
			_type = 0; //자동			
			break;
		case 1:
			_type = 1; //수동
			break;
		case 2:
			_type = 2; //SEMI
			break;
	}
}

void Load::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void Load::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
