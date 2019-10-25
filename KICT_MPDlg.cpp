//"Static", SS_BITMAP,
#include "stdafx.h"
#include "afxdialogex.h"
#include "KICT_MP.h"
#include "KICT_MPDlg.h"

#include "IpSetting.h"
#include "OpenglClass.h"
#include "Mobile_CTRL.h"
#include "Mobile_CTRL.h"
#include "Save.h"
#include "Load.h"
#include <cv.hpp>
#include "MMSystem.h" //조이스틱 제어 time event

#pragma comment(lib, "winmm.lib")
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;

OpenglClass OG;
Mobile_Ctrl Mctrl;


#define MQTT_SERVER_IP "192.168.0.2" //mosquitto 실행 서버

#define CAP_DIR "C:\\capture"//C:\capture

#define KNNOT2MS  0.514444444
double resTable[25] = { 114660, 84510, 62927, 47077, 35563, 27119, 20860, 16204, 12683, 10000, 7942, 6327, 5074, 4103, 3336, 2724, 2237, 1846, 1530, 1275, 1068, 899.3, 760.7, 645.2, 549.4 };
double tempTable[25] = { -20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100 };
double FULLAD = 4095;
float ad2Temperature(int adValue);
//int _style;CRect _originWindow;
void DisplayImage(Mat *image, CDC *pDC, CRect rect);

SYSTEMTIME tm;
char lotime[64] = { 0, };

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	afx_msg void OnBnClickedOk();
	//virtual BOOL OnInitDialog();
	HBITMAP hbit0; 
	CStatic pic_mp;
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT_PIC, pic_mp);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()



CKICT_MPDlg::CKICT_MPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKICT_MPDlg::IDD, pParent)
	, v_speed_in(100) //속도 설정
	, v_pan_in(0)
	, v_tilt_in(0)
//	, expectedPan(ExpectedValue<int>(0, -180, 180))
//	, expectedTilt(ExpectedValue<int>(0, -45, 45))
{
	//lowerLimits[0] = -180
	//int k = (expectedPan += -190).GetValue();

	expectedPan = ExpectedValue<double>(0, -180, 180);
	expectedTilt = ExpectedValue<double>(0, -45, 45);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKICT_MPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BT_CONN, c_conn_mot);
	DDX_Control(pDX, IDC_BT_CONN2, c_conn_cam0);
	DDX_Control(pDX, IDC_BT_FW, bt_fw);
	DDX_Control(pDX, IDC_BT_STOP, bt_stop);
	DDX_Control(pDX, IDC_BT_BW, bt_bw);
	DDX_Control(pDX, IDC_BT_LEFT, bt_left);
	DDX_Control(pDX, IDC_BT_RIGHT, bt_right);
	DDX_Control(pDX, IDC_SL_SPEED, sl_speed);
	DDX_Control(pDX, IDC_EDIT1, ed_speed);
	DDX_Control(pDX, IDC_BT_ESTOP, bt_estop);
	DDX_Control(pDX, IDC_BT_RELEASE, bt_release);
	DDX_Control(pDX, IDC_BT_LIGHT_ON, bt_light_on);
	DDX_Control(pDX, IDC_BT_LIGHT_OFF, bt_light_off);
	DDX_Control(pDX, IDC_PIC0, pic0);
	DDX_Control(pDX, IDC_ST_CONTROL, st_control);
	DDX_Control(pDX, IDC_ST_CAM0, st_cam0);
	DDX_Control(pDX, IDC_GR_CONN, gr_conn);
	DDX_Control(pDX, IDC_GR_CTRL, gr_ctrl);
	DDX_Control(pDX, IDC_BT_JOY_ON, bt_joy_on);
	DDX_Control(pDX, IDC_BT_JOY_OFF, bt_joy_off);
	DDX_Control(pDX, IDC_ST_SPEED, st_speed);
	DDX_Control(pDX, IDC_GR_MOTOR, gr_motor);
	DDX_Control(pDX, IDC_ST_M_POS, st_m_pos);
	DDX_Control(pDX, IDC_ST_M_SPEED, st_m_speed);
	DDX_Control(pDX, IDC_ST_M_TEM, st_m_tem);
	DDX_Control(pDX, IDC_ST_M_PWM, st_m_pwm);
	DDX_Control(pDX, IDC_ST_M_CURRENT, st_m_current);
	DDX_Control(pDX, IDC_ST_LFM, st_lfm);
	DDX_Control(pDX, IDC_ST_RFM, st_rfm);
	DDX_Control(pDX, IDC_ST_LRM, st_lrm);
	DDX_Control(pDX, IDC_ST_RRM, st_rrm);
	DDX_Control(pDX, IDC_ED_LFM_POS, ed_lfm_pos);
	DDX_Control(pDX, IDC_ED_LFM_SPEED, ed_lfm_speed);
	DDX_Control(pDX, IDC_ED_LFM_TEM, ed_lfm_tem);
	DDX_Control(pDX, IDC_ED_LFM_PWM, ed_lfm_pwm);
	DDX_Control(pDX, IDC_ED_LFM_CURRENT, ed_lfm_current);
	DDX_Control(pDX, IDC_ED_RFM_POS, ed_rfm_pos);
	DDX_Control(pDX, IDC_ED_RFM_SPEED, ed_rfm_speed);
	DDX_Control(pDX, IDC_ED_RFM_TEM, ed_rfm_tem);
	DDX_Control(pDX, IDC_EDI_RFM_PWM, ed_rfm_pwm);
	DDX_Control(pDX, IDC_ED_RFM_CURRENT, ed_rfm_current);
	DDX_Control(pDX, IDC_ED_LRM_POS, ed_lrm_pos);
	DDX_Control(pDX, IDC_ED_LRM_SPEED, ed_lrm_speed);
	DDX_Control(pDX, IDC_ED_LRM_TEM, ed_lrm_tem);
	DDX_Control(pDX, IDC_ED_LRM_PWM, ed_lrm_pwm);
	DDX_Control(pDX, IDC_ED_LRM_CURRENT, ed_lrm_current);
	DDX_Control(pDX, IDC_ED_RRM_POS, ed_rrm_pos);
	DDX_Control(pDX, IDC_ED_RRM_SPEED, ed_rrm_speed);
	DDX_Control(pDX, IDC_ED_RRM_TEM, ed_rrm_tem);
	DDX_Control(pDX, IDC_EDI_RRM_PWM, ed_rrm_pwm);
	DDX_Control(pDX, IDC_ED_RRM_CURRENT, ed_rrm_current);
	DDX_Control(pDX, IDC_GR_IMU, gr_imu);
	DDX_Control(pDX, IDC_ST_GYRO, st_gyro);
	DDX_Control(pDX, IDC_ST_ACCEL, st_accel);
	DDX_Control(pDX, IDC_ST_COMPASS, st_compass);
	DDX_Control(pDX, IDC_ST_IMU_X, st_imu_x);
	DDX_Control(pDX, IDC_ST_IMU_Y, st_imu_y);
	DDX_Control(pDX, IDC_ST_IMU_Z, st_imu_z);
	DDX_Control(pDX, IDC_ST_IMU_SEQ, st_imu_seq);
	DDX_Control(pDX, IDC_ST_IMU_ESTYAW, st_imu_estyaw);
	DDX_Control(pDX, IDC_ED_GYRO_X, ed_gyro_x);
	DDX_Control(pDX, IDC_ED_GYRO_Y, ed_gyro_y);
	DDX_Control(pDX, IDC_ED_GYRO_Z, ed_gyro_z);
	DDX_Control(pDX, IDC_ED_ACCEL_X, ed_accel_x);
	DDX_Control(pDX, IDC_ED_ACCEL_Y, ed_accel_y);
	DDX_Control(pDX, IDC_ED_ACCEL_Z, ed_accel_z);
	DDX_Control(pDX, IDC_ED_COMPASS_X, ed_compass_x);
	DDX_Control(pDX, IDC_ED_COMPASS_Y, ed_compass_y);
	DDX_Control(pDX, IDC_ED_COMPASS_Z, ed_compass_z);
	DDX_Control(pDX, IDC_ED_IMU_SEQ, ed_imu_seq);
	DDX_Control(pDX, IDC_ED_IMU_ESTYAW, ed_imu_estyaw);
	DDX_Control(pDX, IDC_GR_GPS, gr_gps);
	DDX_Control(pDX, IDC_ST_GPS_STATE, st_gps_state);
	DDX_Control(pDX, IDC_ST_GPS_LATITUDE, st_gps_latitude);
	DDX_Control(pDX, IDC_ST_GPS_LONGITUDE, st_gps_longitude);
	DDX_Control(pDX, IDC_ST_GPS_TIMESTAMP, st_gps_timestamp);
	DDX_Control(pDX, IDC_ST_GPS_COG, st_gps_cog);
	DDX_Control(pDX, IDC_ST_GPS_VOG, st_gps_vog);
	DDX_Control(pDX, IDC_ED_GPS_STATE, ed_gps_state);
	DDX_Control(pDX, IDC_ED_GPS_TIMESTAMP, ed_gps_timestamp);
	DDX_Control(pDX, IDC_ED_GPS_LATITUDE, ed_gps_latitude);
	DDX_Control(pDX, IDC_ED_GPS_LONGITUDE, ed_gps_longitude);
	DDX_Control(pDX, IDC_ED_GPS_COG, ed_gps_cog);
	DDX_Control(pDX, IDC_ED_GPS_VOG, ed_gps_vog);
	DDX_Control(pDX, IDC_ED_VOLT, ed_volt);
	DDX_Control(pDX, IDC_ST_VOLT, st_volt);
	DDX_Control(pDX, IDC_ST_M_STATE, st_m_state);
	DDX_Control(pDX, IDC_ED_M_STATE, ed_m_state);
	DDX_Control(pDX, IDC_PIC_XY, pic_xy);
	DDX_Control(pDX, IDC_PIC_NIGHT_LEFT, pic_nightL);
	DDX_Control(pDX, IDC_PIC_NIGHT_RIGHT, pic_nightR);
	DDX_Control(pDX, IDC_PIC_FRONT_LEFT, pic_front_left);
	DDX_Control(pDX, IDC_PIC_REAR_RIGHT, pic_rear_right);
	DDX_Control(pDX, IDC_PIC_REAR_LEFT, pic_rear_left);
	DDX_Control(pDX, IDC_PIC_FRONT_RIGHT, pic_front_right);
	DDX_Control(pDX, IDC_PIC_LEFT, pic_left);
	DDX_Control(pDX, IDC_PIC_RIGHT, pic_right);
	DDX_Control(pDX, IDC_GR_RTK_GPS, gr_rtk_gps);
	DDX_Control(pDX, IDC_GR_IMU_XSENS, gr_imu_xsens);
	DDX_Control(pDX, IDC_PIC_GRAPH0, pic_graph0);
	DDX_Control(pDX, IDC_PIC_GRAPH1, pic_graph1);
	DDX_Control(pDX, IDC_ST_CAM1, st_camall);
	DDX_Control(pDX, IDC_BT_CONN3, c_conn_camall);
	DDX_Control(pDX, IDC_SET_IP, c_set_ip);
	DDX_Control(pDX, IDC_ST_XSENS_ROLL, st_xsens_roll);
	DDX_Control(pDX, IDC_ST_XSENS_PITCH, st_xsens_pitch);
	DDX_Control(pDX, IDC_ST_XSENS_YAW, st_xsens_yaw);
	DDX_Control(pDX, IDC_ED_XSENS_ROLL, ed_xsens_roll);
	DDX_Control(pDX, IDC_ED_XSENS_PITCH, ed_xsens_pitch);
	DDX_Control(pDX, IDC_ED_XSENS_YAW, ed_xsens_yaw);
	DDX_Control(pDX, IDC_ST_RTK_STATE, st_rtk_state);
	DDX_Control(pDX, IDC_ED_RTK_STATE, ed_rtk_state);
	DDX_Control(pDX, IDC_ST_RTK_LATITUDE, st_rtk_latitude);
	DDX_Control(pDX, IDC_ED_RTK_LATITUDE, ed_rtk_latitude);
	DDX_Control(pDX, IDC_ST_RTK_COG, st_rtk_cog);
	DDX_Control(pDX, IDC_ED_RTK_COG, ed_rtk_cog);
	DDX_Control(pDX, IDC_ST_RTK_LONGITUDE, st_rtk_longitude);
	DDX_Control(pDX, IDC_ED_RTK_LONGITUDE, ed_rtk_longitude);
	DDX_Control(pDX, IDC_ST_RTK_VOG, st_rtk_vog);
	DDX_Control(pDX, IDC_ED_RTK_VOG, ed_rtk_vog);
	DDX_Control(pDX, IDC_BT_TILT_P, bt_tilt_plus);
	DDX_Control(pDX, IDC_BT_TILT_M, bt_tilt_minus);
	DDX_Control(pDX, IDC_BT_PAN_M, bt_pan_minus);
	DDX_Control(pDX, IDC_BT_PAN_P, bt_pan_plus);
	DDX_Control(pDX, IDC_BT_CAP, c_cap);
	DDX_Control(pDX, IDC_ED_PAN, ed_pan);
	DDX_Control(pDX, IDC_ED_TILT, ed_tilt);
	DDX_Control(pDX, IDC_ST_RTK_COUNT, st_rtk_count);
	DDX_Control(pDX, IDC_ED_RTK_COUNT, ed_rtk_count);
	DDX_Control(pDX, IDC_ST_RTK_TIME, st_rtk_time);
	DDX_Control(pDX, IDC_ED_RTK_TIME, ed_rtk_time);
	DDX_Control(pDX, IDC_ED_SPEED_IN, ed_speed_in);
	DDX_Text(pDX, IDC_ED_SPEED_IN, v_speed_in);
	DDV_MinMaxInt(pDX, v_speed_in, 0, 500);
	DDX_Control(pDX, IDC_BT_SPEED_SET, bt_speed_set);
	DDX_Control(pDX, IDC_BT_PT_CAL, bt_pt_cal);
	DDX_Control(pDX, IDC_ST_PAN, st_pan);
	DDX_Control(pDX, IDC_ST_TILT, st_tilt);
	DDX_Control(pDX, IDC_ED_PAN_IN, ed_pan_in);
	DDX_Control(pDX, IDC_ED_TILT_IN, ed_tilt_in);
	DDX_Text(pDX, IDC_ED_PAN_IN, v_pan_in);
	DDV_MinMaxInt(pDX, v_pan_in, -180, 180);
	DDX_Text(pDX, IDC_ED_TILT_IN, v_tilt_in);
	DDV_MinMaxInt(pDX, v_tilt_in, -45, 45);
	DDX_Control(pDX, IDC_BT_PAN_SET, bt_pan_set);
	DDX_Control(pDX, IDC_BT_TILT_SET, bt_tilt_set);
	DDX_Control(pDX, IDC_GR_LED, gr_led);
	DDX_Control(pDX, IDC_ST_LED_FRONT, st_led_front);
	DDX_Control(pDX, IDC_ST_LED_REAR, st_led_rear);
	DDX_Control(pDX, IDC_ST_LED_LEFT, st_led_left);
	DDX_Control(pDX, IDC_ST_LED_RIGHT, st_led_right);
	DDX_Control(pDX, IDC_BT_LED_FRONT_ON, bt_led_front);
	DDX_Control(pDX, IDC_BT_LED_REAR_ON, bt_led_rear);
	DDX_Control(pDX, IDC_BT_LED_LEFT_ON, bt_led_left);
	DDX_Control(pDX, IDC_BT_LED_RIGHT_ON, bt_led_right);
	DDX_Control(pDX, IDC_ST_BASE_CAM, st_base_cam);
	DDX_Control(pDX, IDC_ST_ROBOT_MODEL, st_robot3d);
	DDX_Control(pDX, IDC_ST_FRONT_LEFT, st_front_left);
	DDX_Control(pDX, IDC_ST_REAR_RIGHT, st_rear_right);
	DDX_Control(pDX, IDC_ST_LEFT_NIGHT, st_left_night);
	DDX_Control(pDX, IDC_ST_RIGHT_NIGHT, st_right_night);
	DDX_Control(pDX, IDC_ST_LEFT_FISHEYE, st_left_fisheye);
	DDX_Control(pDX, IDC_ST_RIGHT_FISHEYE, st_right_fisheye);
	DDX_Control(pDX, IDC_ST_REAR_LEFT, st_rear_left);
	DDX_Control(pDX, IDC_ST_FRONT_RIGHT, st_front_right);
	DDX_Control(pDX, IDC_ED_XSENS_ACC_ROLL, ed_xsens_acc_roll);
	DDX_Control(pDX, IDC_ED_XSENS_ACC_PITCH, ed_xsens_acc_pitch);
	DDX_Control(pDX, IDC_ED_XSENS_ACC_YAW, ed_xsens_acc_yaw);
	DDX_Control(pDX, IDC_ST_XSENS_ACC_ROLL, st_xsens_acc_roll);
	DDX_Control(pDX, IDC_ST_XSENS_ACC_PITCH, st_xsens_acc_pitch);
	DDX_Control(pDX, IDC_ST_XSENS_ACC_YAW, st_xsens_acc_yaw);
}

BEGIN_MESSAGE_MAP(CKICT_MPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_FW, &CKICT_MPDlg::OnBnClickedBtFw)
	ON_BN_CLICKED(IDC_BT_CONN, &CKICT_MPDlg::OnBnClickedBtConn)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BT_BW, &CKICT_MPDlg::OnBnClickedBtBw)
	ON_BN_CLICKED(IDC_BT_STOP, &CKICT_MPDlg::OnBnClickedBtStop)
	ON_BN_CLICKED(IDC_BT_LEFT, &CKICT_MPDlg::OnBnClickedBtLeft)
	ON_BN_CLICKED(IDC_BT_RIGHT, &CKICT_MPDlg::OnBnClickedBtRight)
	ON_BN_CLICKED(IDC_BT_ESTOP, &CKICT_MPDlg::OnBnClickedBtEstop)
	ON_BN_CLICKED(IDC_BT_RELEASE, &CKICT_MPDlg::OnBnClickedBtRelease)
	ON_BN_CLICKED(IDC_BT_LIGHT_ON, &CKICT_MPDlg::OnBnClickedBtLightOn)
	ON_BN_CLICKED(IDC_BT_LIGHT_OFF, &CKICT_MPDlg::OnBnClickedBtLightOff)
	ON_BN_CLICKED(IDC_BT_CONN2, &CKICT_MPDlg::OnBnClickedBtConn2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BT_JOY_ON, &CKICT_MPDlg::OnBnClickedBtJoyOn)
	ON_BN_CLICKED(IDC_BT_JOY_OFF, &CKICT_MPDlg::OnBnClickedBtJoyOff)
	ON_COMMAND(ID_HELP_ABOUT, &CKICT_MPDlg::OnHelpAbout)
	ON_COMMAND(ID_SETTING_EXIT, &CKICT_MPDlg::OnSettingExit)	
	ON_COMMAND(ID_SETTING_IP, &CKICT_MPDlg::OnSettingIp)
	ON_BN_CLICKED(IDC_BT_CONN3, &CKICT_MPDlg::OnBnClickedBtConn3)
	ON_BN_CLICKED(IDC_SET_IP, &CKICT_MPDlg::OnBnClickedSetIp)
	ON_COMMAND(ID_GOOGLEEARTH_GOOGLEEARTH, &CKICT_MPDlg::OnGoogleearthGoogleearth)
	ON_COMMAND(ID_VIEW_NORMAL, &CKICT_MPDlg::OnViewNormal)
	ON_COMMAND(ID_VIEW_EXPAND, &CKICT_MPDlg::OnViewExpand)
	ON_BN_CLICKED(IDC_BT_CAP, &CKICT_MPDlg::OnBnClickedBtCap)
	ON_BN_CLICKED(IDC_BT_PAN_P, &CKICT_MPDlg::OnBnClickedBtPanP)
	ON_BN_CLICKED(IDC_BT_PAN_M, &CKICT_MPDlg::OnBnClickedBtPanM)
	ON_BN_CLICKED(IDC_BT_TILT_P, &CKICT_MPDlg::OnBnClickedBtTiltP)
	ON_BN_CLICKED(IDC_BT_TILT_M, &CKICT_MPDlg::OnBnClickedBtTiltM)
	ON_COMMAND(ID_DATA_OPENFOLDER, &CKICT_MPDlg::OnDataOpenfolder)	
	ON_COMMAND(ID_DATA_LOAD, &CKICT_MPDlg::OnDataLoad)
	ON_COMMAND(ID_DATA_SAVE, &CKICT_MPDlg::OnDataSave)
	ON_BN_CLICKED(IDC_BT_SPEED_SET, &CKICT_MPDlg::OnBnClickedBtSpeedSet)
	ON_BN_CLICKED(IDC_BT_PAN_SET, &CKICT_MPDlg::OnBnClickedBtPanSet)
	ON_BN_CLICKED(IDC_BT_TILT_SET, &CKICT_MPDlg::OnBnClickedBtTiltSet)
	ON_BN_CLICKED(IDC_BT_PT_CAL, &CKICT_MPDlg::OnBnClickedBtPtCal)
	ON_BN_CLICKED(IDC_BT_LED_FRONT_ON, &CKICT_MPDlg::OnBnClickedBtLedFrontOn)
	ON_BN_CLICKED(IDC_BT_LED_REAR_ON, &CKICT_MPDlg::OnBnClickedBtLedRearOn)
	ON_BN_CLICKED(IDC_BT_LED_LEFT_ON, &CKICT_MPDlg::OnBnClickedBtLedLeftOn)
	ON_BN_CLICKED(IDC_BT_LED_RIGHT_ON, &CKICT_MPDlg::OnBnClickedBtLedRightOn)
	ON_COMMAND(ID_SETTING_REBOOT, &CKICT_MPDlg::OnSettingReboot)
	ON_COMMAND(ID_Menu, &CKICT_MPDlg::OnSettingPowerOff)	
	ON_COMMAND(ID_DATA_DELETEALL, &CKICT_MPDlg::OnDataDeleteall)
	
	ON_COMMAND(ID_SNAP_AROUND, &CKICT_MPDlg::OnSnapAround)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CKICT_MPDlg message handlers

BOOL CKICT_MPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	mqtt0 = new myMosq("KICT_CLIENT", "KICT_MP", MQTT_SERVER_IP, 1883);
	mqtt0->getpoint(this);
		
	scn_mode = 1; //기본1 확장2

	SetWindowPos(NULL, 0, 0, 1920, 1080, NULL);
	ShowWindow(SW_MAXIMIZE);

	AfxSocketInit(); //통신위한 소켓 초기화
	robot_db.SetQueryTimeout(3600);
	Screen();
	OG.CreateOGL();//OPENGL
	LoadIpSetting();

	pDC_pic_xy = pic_xy.GetDC();
	pDC_pic0 = pic0.GetDC();
	pDC_pic_nightL = pic_nightL.GetDC();
	pDC_pic_nightR = pic_nightR.GetDC();
	pDC_pic_front_left = pic_front_left.GetDC();
	pDC_pic_rear_right = pic_rear_right.GetDC();
	pDC_pic_rear_left = pic_rear_left.GetDC(); 
	pDC_pic_front_right = pic_front_right.GetDC();
	pDC_pic_left = pic_left.GetDC();
	pDC_pic_right = pic_right.GetDC();

	Mctrl.init(this);
	_defish_on = false; // 어안 케메라 이미지 왜곡 복원 기본 false //구현 안되었음
	dr_motor = new Dr_motor;
	dr_gps = new Dr_gps;
	dr_imu = new Dr_imu;

	cam0 = new IpCamera;
	nightL = new IpCamera;
	nightR = new IpCamera;
	fishL = new IpCamera;
	fishR = new IpCamera;
	frontL = new IpCamera;
	rearR = new IpCamera;

	frontR = new IpCamera; //추가
	rearL = new IpCamera;
	rod_pan = 0.0;
	rod_tilt = 0.0;
	xsens_roll = 0.0;
	xsens_pitch = 0.0;
	xsens_yaw = 0.0;
	SetTimer(TM_GRAPH, 50, NULL);

	//SetTimer(TM_ROBOT, 50, NULL);
	//MQTT 수신 시작
	mqtt0->publish(NULL, GET_PANTILT, 0, NULL, 1, false);
	mqtt0->publish(NULL, GET_IMU, 0, NULL, 1, false);
	mqtt0->publish(NULL, GET_GPS, 0, NULL, 1, false);
	_save = 0; // 0 중지 1 저장중

	/////////////// snap around /////////////////

	if (!m_snapper.CreateDispatch(_T("KICT.SnapAround")))

	{

		AfxMessageBox(_T("KICT.SnapAround component not found"));

		return FALSE;

	}


	

	//////////////////////////////////////////


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKICT_MPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKICT_MPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKICT_MPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CKICT_MPDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) return TRUE; // '엔터' 종료 막기

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CKICT_MPDlg::OnBnClickedBtExit()
{
	OnOK();
}

void CKICT_MPDlg::OnBnClickedBtConn()
{/*
	bt_fw.EnableWindow(TRUE);
	bt_stop.EnableWindow(TRUE);
	bt_bw.EnableWindow(TRUE);
	bt_left.EnableWindow(TRUE);
	bt_right.EnableWindow(TRUE);

	bt_pan_plus.EnableWindow(TRUE);
	bt_pan_minus.EnableWindow(TRUE);
	bt_tilt_plus.EnableWindow(TRUE);
	bt_tilt_minus.EnableWindow(TRUE);

	return;
	*/

	if (connected_robot == 1){
		KillTimer(TM_PING);
		KillTimer(TM_GRAPH);
		KillTimer(TM_ROBOT);		
		connected_robot = 0; //연결 종료
		::WaitForSingleObject(p_recvM->m_hThread, INFINITE); // 스레드 join 	
		c_conn_mot.SetWindowTextW(L"connect");
	
		m_Socket.Close();
		
		bt_fw.EnableWindow(FALSE);
		bt_stop.EnableWindow(FALSE);
		bt_bw.EnableWindow(FALSE);
		bt_left.EnableWindow(FALSE);
		bt_right.EnableWindow(FALSE);
		/*
		bt_pan_plus.EnableWindow(FALSE);
		bt_pan_minus.EnableWindow(FALSE);
		bt_tilt_plus.EnableWindow(FALSE);
		bt_tilt_minus.EnableWindow(FALSE);
		*/
		return;
	}

	m_Socket.Create(0, SOCK_STREAM, 0); //tcp	
	
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(m_Socket.m_hSocket, &fdset);
	timeval timeOut;
	timeOut.tv_sec = 2;
	timeOut.tv_usec = 0;

	static CString robotAddr(_ip_DrMobile);//connect 는 주소 포인터를 사용하기 때문에 Connect(CString(ip)) 에러 발생할 수 있음
	
	//int ret = m_Socket.Connect(robotAddr, 10001); // 성공 1 없으면0 1 for success only for CSocket *********************
	int ret = m_Socket.Connect(robotAddr, 5000); // 성공 1 없으면0 1 for success only for CSocket *********************
	/*
	if (ret == 0) {
		DWORD lastError = ::GetLastError();
		lastError = WSAENETDOWN;
	}
	*/
	if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		return ;
	
	// 여기서 3초간 블럭
	if (select(0, NULL, &fdset, NULL, &timeOut) == SOCKET_ERROR)
		return ;
	
	// 3초 후에 블럭이 플렸다면 현재 소켓이 열려 있는지 확인
	if (!FD_ISSET(m_Socket.m_hSocket, &fdset))

	{		/// 2초만에 안열린 것이고
		closesocket(m_Socket.m_hSocket);
		m_Socket.m_hSocket = INVALID_SOCKET;
		AfxMessageBox(L"연결 실패");
		return ;
	}
	
	connected_robot = 1; //연결 됨
	c_conn_mot.SetWindowTextW(L"disconnect");
	SetTimer(TM_PING, 200, NULL);
	p_recvM = AfxBeginThread(recvMobile, this);
	
	bt_fw.EnableWindow(TRUE);
	bt_stop.EnableWindow(TRUE);
	bt_bw.EnableWindow(TRUE);
	bt_left.EnableWindow(TRUE);
	bt_right.EnableWindow(TRUE);
	/*
	bt_pan_plus.EnableWindow(TRUE);
	bt_pan_minus.EnableWindow(TRUE);
	bt_tilt_plus.EnableWindow(TRUE);
	bt_tilt_minus.EnableWindow(TRUE);
	*/
	SetTimer(TM_GRAPH, 50, NULL); 
	SetTimer(TM_ROBOT, 50, NULL);	
}

void CKICT_MPDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar)
	{
		if (pScrollBar == (CScrollBar*)&sl_speed)
		{
			// 슬라이더의 위치를 검사한다.
			Speed0 = sl_speed.GetPos();
			CString str;
			str.Format(_T("%d"), Speed0);
			ed_speed.SetWindowTextW(str);					
		}
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CKICT_MPDlg::OnBnClickedBtFw() //전진
{
	Mctrl.Forward();
	//sprintf_s(send_buf, "MMW !M %d -%d\r\n", Speed0, Speed0);
	//int res = m_Socket.Send(send_buf, strlen(send_buf)); //int res = m_Socket.Send(send_buf, sizeof(send_buf));
}

void CKICT_MPDlg::OnBnClickedBtBw() //후진
{
	Mctrl.Backward();
	//sprintf_s(send_buf, "MMW !M -%d %d\r\n", Speed0, Speed0);
	//int res = m_Socket.Send(send_buf, strlen(send_buf));
}

void CKICT_MPDlg::OnBnClickedBtStop() //정지
{
	Mctrl.Stop();
	//sprintf_s(send_buf, "MMW !M 0 0\r\n");
	//int res = m_Socket.Send(send_buf, strlen(send_buf));
}

void CKICT_MPDlg::OnBnClickedBtLeft()
{
	Mctrl.L_turn();
	//sprintf_s(send_buf, "MMW !M -%d -%d\r\n", Speed0, Speed0);
	//int res = m_Socket.Send(send_buf, strlen(send_buf));
}

void CKICT_MPDlg::OnBnClickedBtRight()
{
	Mctrl.R_turn();
	//sprintf_s(send_buf, "MMW !M %d %d\r\n", Speed0, Speed0);
	//int res = m_Socket.Send(send_buf, strlen(send_buf));
}


void CKICT_MPDlg::OnBnClickedBtEstop() //모터 긴급 정지
{
	sprintf_s(send_buf, "MMW !EX\r\n");
	int res = m_Socket.Send(send_buf, strlen(send_buf)); //int res = m_Socket.Send(send_buf, sizeof(send_buf));
}


void CKICT_MPDlg::OnBnClickedBtRelease() //릴리즈 모터
{
	sprintf_s(send_buf, "MMW !MG\r\n");
	int res = m_Socket.Send(send_buf, strlen(send_buf)); //int res = m_Socket.Send(send_buf, sizeof(send_buf));
	}


void CKICT_MPDlg::OnBnClickedBtLightOn()
{
	sprintf_s(send_buf, "SYS MMC 255\r\n");//	sprintf_s(send_buf, "SYS MMC %c\r\n", 0xff);
	int res = m_Socket.Send(send_buf, strlen(send_buf));
}


void CKICT_MPDlg::OnBnClickedBtLightOff()
{
	sprintf_s(send_buf, "SYS MMC 127\r\n");
	int res = m_Socket.Send(send_buf, strlen(send_buf));
}


void CKICT_MPDlg::OnBnClickedBtConn2()
{
	if (cam0->IsConnected == true){
		c_conn_cam0.SetWindowTextW(L"connect");
		
		cam0->Stop = true; //카메라 스레드 종료하고
		::WaitForSingleObject(p_cam0->m_hThread, INFINITE);
		return;
	}
	cam0->Stop = false;
	char addr[128] = { 0, };	
	
	sprintf_s(addr, "rtsp://%s/axis-media/media.amp?videocodec=h264", _ip_DrCamera);
	cam0->SetAddress(addr);//root drrobot
	p_cam0 = AfxBeginThread(cam_mobile, this);		
}

UINT CKICT_MPDlg::recvMobile(void* data)
{
	return 0; //moqq에서 speedo_info가 대신함

	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	char recvbuf[1024];
	char temp[4]; 
	int d_cnt = 0;
	int cnt = 0;
	char* context = NULL;
	char str[512] = { 0, };
	int res = 0;	//memcpy_s(&t_recvsocket, sizeof(t_recvsocket), &p->m_Socket, sizeof(t_recvsocket));
	 
	double motorAmp[4] = { 0, };
	double motorTemp[4] = { 0, };
	int encoderPos[4] = { 0, };
	int motorPower[4] = { 0, }; //PWM 0~1000
	int encoderSpeed[4] = { 0, };
	double drvVoltage[4] = { 0, };
	double motVoltage[4] = { 0, };
	double reg5Voltage[4] = { 0, };
	int driverState[4] = { 0, };

	int index = 0;
	char *temp_p=NULL;
	CSocket t_socket;
	t_socket.Attach(p->m_Socket.m_hSocket); //스레드에서 사용할 소켓, 스레드에서는 포인터로 접근 안됨
	
	while (p->connected_robot)
	{
		t_socket.Receive(temp, 1);
		if (temp[0] == '#')
		{
			while (d_cnt < 15)
			{
				t_socket.Receive(temp, 1);
				recvbuf[cnt++] = temp[0];
				if (temp[0] == ',')
					d_cnt++;
			}
			temp_p = strtok_s(recvbuf, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p);
			//strcpy_s(str, strtok_s(recvbuf, ",", &context));//0
			p->dr_imu->seq = atoi(str);
			
			strtok_s(NULL, ",", &context);//1 버리고
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//2		
			p->dr_imu->estyaw = atof(str);			
			
			strtok_s(NULL, ",", &context);//3 버리고
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p);
			//strcpy_s(str, strtok_s(NULL, ",", &context));//4		
			p->dr_imu->gyro[0] = atoi(str);
			
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//5		
			p->dr_imu->gyro[1] = atoi(str); 
			
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//6		
			p->dr_imu->gyro[2] = atoi(str); 
			
			strtok_s(NULL, ",", &context);//7 버리고
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//8		
			p->dr_imu->accel[0] = atoi(str); 
			
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//9		
			p->dr_imu->accel[1] = atoi(str); 
			
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//10		
			p->dr_imu->accel[2] = atoi(str); 
			
			strtok_s(NULL, ",", &context);//11		버리고	
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//12		
			p->dr_imu->compass[0] = atoi(str); 
					
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//13		
			p->dr_imu->compass[1] = atoi(str); 
						
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//14		
			p->dr_imu->compass[2] = atoi(str); 
			
			ZeroMemory(recvbuf, sizeof(recvbuf));
			d_cnt = 0;
			cnt = 0;
		}
		else if (temp[0] == '$')
		{
			while (d_cnt < 9)
			{
				t_socket.Receive(temp, 1);
				recvbuf[cnt++] = temp[0];
				if (temp[0] == ',')
					d_cnt++;
			}
			strtok_s(recvbuf, ",", &context);//0			

			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p);
			//strcpy_s(str, strtok_s(NULL, ",", &context));//1	 TIMESTAMP	
			strcpy_s(p->dr_gps->timestamp, str);
	
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 

			//strcpy_s(str, strtok_s(NULL, ",", &context));//2	 STATE	
			if (str[0] == 'A')
				strcpy_s(p->dr_gps->state, "Valid");
			else if (str[0] == 'V')
				strcpy_s(p->dr_gps->state, "Invlid");

			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));;//3     LATITUDE
			CStringA la = (CStringA)str;
			
			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//4
			if (str[0] == 'S')
				la = (CStringA)"S:-" + la;
			else if (str[0] == 'N')
				la = (CStringA)"N:" + la;
			strcpy_s(p->dr_gps->latitude,la.GetBuffer());

			temp_p = strtok_s(NULL, ",", &context);
			if (temp_p == NULL)
				break;
			else				strcpy_s(str, temp_p); 
			//strcpy_s(str, strtok_s(NULL, ",", &context));//5	 LONGITUDE
			CStringA lo = (CStringA)str;
			strcpy_s(str, strtok_s(NULL, ",", &context));//6		
			if (str[0] == 'W')
				lo = (CStringA)"W:-" + lo;
			else if(str[0] == 'E')
				lo = (CStringA)"E:" + lo;
			strcpy_s(p->dr_gps->longuitude, lo.GetBuffer());

			if (context[0] != ',') // ,,가 연속으로 오기때문에
			{
				strcpy_s(str, strtok_s(NULL, ",", &context));//7	VOG
				float vog = atof(str);
				vog = vog*KNNOT2MS;
				CString te;
				te.Format(_T("%.2f"), vog);
				p->dr_gps->vog = vog;
			}
			else
				context = &context[1];
			if (context[0] != ',')
			{
				strcpy_s(str, strtok_s(NULL, ",", &context));//8	COG
				p->dr_gps->cog = atof(str);
			}
			ZeroMemory(recvbuf, sizeof(recvbuf));
			d_cnt = 0;
			cnt = 0;
			//Sleep(1);
		}

		else if (temp[0] == 'M')
		{
			t_socket.Receive(temp, 1); //MM0 ~ MM3;
			if (temp[0] == 'M')
			{
				t_socket.Receive(temp, 1);
				if (temp[0] == '0')
					index = 0;
				else if (temp[0] == '1')
					index = 1;
				t_socket.Receive(temp, 1);
				t_socket.Receive(temp, 2);

				if (temp[0] == 'A' && temp[1] == '=') //MOTOR AMP = current
				{
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];						
					}					
					temp_p = strtok_s(recvbuf, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(recvbuf, ":", &context));//0			
					motorAmp[index * 2 + 0] = atof(str) / 10;
					
					temp_p = strtok_s(NULL, "\r", &context);;
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p); 
					//strcpy_s(str, strtok_s(NULL, "\r", &context));//1
					motorAmp[index * 2 + 1] = atof(str) / 10;
					cnt = 0;
					d_cnt = 0;

					p->dr_motor->current[0] = motorAmp[0];
					p->dr_motor->current[1] = motorAmp[1];
					p->dr_motor->current[2] = motorAmp[2];
					p->dr_motor->current[3] = motorAmp[3];
				}
				else if (temp[0] == 'A' && temp[1] == 'I') //MOTOR TEMPERATURE
				{
					t_socket.Receive(temp, 1); // "AI="
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];						
					}
					strtok_s(recvbuf, ":", &context);//0			
					strtok_s(NULL, ":", &context);//1

					temp_p = strtok_s(NULL, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, ":", &context));//3			
					motorTemp[index * 2 + 0] = ad2Temperature(atoi(str));					
					
					temp_p = strtok_s(NULL, ":", &context);
					if (temp_p == NULL)
						break; //여기 널이 온 적 있었음
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, ":", &context));//4
					motorTemp[index * 2 + 1] = ad2Temperature(atoi(str));
					cnt = 0;
					d_cnt = 0;

					p->dr_motor->temperature[0] = motorTemp[0];
					p->dr_motor->temperature[1] = motorTemp[1];
					p->dr_motor->temperature[2] = motorTemp[2];
					p->dr_motor->temperature[3] = motorTemp[3];
				}
				else if (temp[0] == 'C' && temp[1] == '=') //ENCODER POS
				{
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];
					}					
					temp_p = strtok_s(recvbuf, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(recvbuf, ":", &context));//0			
					encoderPos[index * 2 + 0] = atoi(str);
										
					temp_p = strtok_s(NULL, "\r", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, "\r", &context));//1
					encoderPos[index * 2 + 1] = atoi(str);
					cnt = 0;
					d_cnt = 0;
					p->dr_motor->position[0] = encoderPos[0];
					p->dr_motor->position[1] = encoderPos[1];
					p->dr_motor->position[2] = encoderPos[2];
					p->dr_motor->position[3] = encoderPos[3];

				}
				else if (temp[0] == 'P' && temp[1] == '=') //output PWM value, 0 ~ 1000
				{
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];
					}					
					temp_p = strtok_s(recvbuf, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(recvbuf, ":", &context));//0			
					motorPower[index * 2 + 0] = atoi(str);
					
					temp_p = strtok_s(NULL, "\r", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, "\r", &context));//1
					motorPower[index * 2 + 1] = atoi(str);
					cnt = 0;
					d_cnt = 0;

					p->dr_motor->pwm[0] = motorPower[0];
					p->dr_motor->pwm[1] = motorPower[1];
					p->dr_motor->pwm[2] = motorPower[2];
					p->dr_motor->pwm[3] = motorPower[3];
				}
				else if (temp[0] == 'S' && temp[1] == '=') //encoder velocity data RPM
				{
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];
					}
					temp_p = strtok_s(recvbuf, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(recvbuf, ":", &context));//0			
					encoderSpeed[index * 2 + 0] = atoi(str);

					temp_p = strtok_s(NULL, "\r", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p); 
					//strcpy_s(str, strtok_s(NULL, "\r", &context));//1
					encoderSpeed[index * 2 + 1] = atoi(str);
					cnt = 0;
					d_cnt = 0;

					p->dr_motor->speed[0] = encoderSpeed[0];
					p->dr_motor->speed[1] = encoderSpeed[1];
					p->dr_motor->speed[2] = encoderSpeed[2];
					p->dr_motor->speed[3] = encoderSpeed[3];					
				}
				else if (temp[0] == 'V' && temp[1] == '=')  // voltage data
				{
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];
					}
					temp_p = strtok_s(recvbuf, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(recvbuf, ":", &context));//0			
					drvVoltage[index] = atof(str) / 10;

					temp_p = strtok_s(NULL, ":", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, ":", &context));//1
					motVoltage[index] = atof(str) / 10;   //display

					temp_p = strtok_s(NULL, "\r", &context);
					if (temp_p == NULL)
						break;
					else				strcpy_s(str, temp_p);
					//strcpy_s(str, strtok_s(NULL, "\r", &context));//2
					reg5Voltage[index] = atof(str) / 1000;
					cnt = 0;
					d_cnt = 0;

					p->dr_motor->voltage = motVoltage[0];
				}
				else if (temp[0] == 'F' && temp[1] == 'F')  // driver board state
				{
					t_socket.Receive(temp, 1);
					while (temp[0] != '\r')
					{
						t_socket.Receive(temp, 1);
						recvbuf[cnt++] = temp[0];
					}
					driverState[index] = atoi(recvbuf);
					cnt = 0;
					d_cnt = 0;

					CStringA Drv0, Drv1;
					if ((driverState[0] & 0x1) != 0){
						Drv0 = "OH";
					}
					if ((driverState[0] & 0x2) != 0){
						Drv0 += "OV";
					}
					if ((driverState[0] & 0x4) != 0){
						Drv0 += "UV";
					}
					if ((driverState[0] & 0x8) != 0){
						Drv0 += "SHT";
					}
					if ((driverState[0] & 0x10) != 0){
						Drv0 += "ESTOP";
					}
					if ((driverState[0] & 0x20) != 0){
						Drv0 += "SEPF";
					}
					if ((driverState[0] & 0x40) != 0){
						Drv0 += "PromF";
					}
					if ((driverState[0] & 0x80) != 0){
						Drv0 += "ConfF";
					}
					if ((driverState[0] & 0x1) != 0){
						Drv0 = "OH";
					}
					if ((driverState[1] & 0x2) != 0){
						Drv1 += "OV";
					}
					if ((driverState[1] & 0x4) != 0){
						Drv1 += "UV";
					}
					if ((driverState[1] & 0x8) != 0){
						Drv1 += "SHT";
					}
					if ((driverState[1] & 0x10) != 0){
						Drv1 += "ESTOP";
					}
					if ((driverState[1] & 0x20) != 0){
						Drv1 += "SEPF";
					}
					if ((driverState[1] & 0x40) != 0){
						Drv1 += "PromF";
					}
					if ((driverState[1] & 0x80) != 0){
						Drv1 += "ConfF";
					}
					//p->ed_m_state.SetWindowTextW((CString)"Dvr0:" + (CString)Drv0 + (CString)"\r\n" + (CString)"Dvr1:" + (CString)Drv1);
					strcpy_s(p->dr_motor->driverstate[0], Drv0.GetBuffer());
					strcpy_s(p->dr_motor->driverstate[1], Drv1.GetBuffer());
				}
			}
		}
	}

	t_socket.Detach(); //해야 메인에서 m_socket close() 할 수 있음
	t_socket.Close();

	return 0;
}

void DisplayImage(Mat *image, CDC *pDC, CRect rect)
{
	BITMAPINFO bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(bitmapInfo));
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biWidth = image->cols;
	bitmapInfo.bmiHeader.biHeight = -image->rows;

	//Mat img = image->clone();
	//IplImage *tempImage;
	if (image->cols == 0)
		return;
	//tempImage = cvCloneImage(&IplImage(*image));
	//bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;
	bitmapInfo.bmiHeader.biBitCount = 8 * 3;
	
	pDC->SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top,
		rect.right, rect.bottom,
		0, 0, image->cols, image->rows,
		image->datastart, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	
	//cvReleaseImage(&tempImage);

	/*
	IplImage *tempImage;
	if (image->cols == 0 )
		return;
	return;
	tempImage = cvCloneImage(&IplImage(*image));

	bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;

	pDC->SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top,
		rect.right, rect.bottom,
		0, 0, tempImage->width, tempImage->height,
		tempImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	cvReleaseImage(&tempImage);
	*/
}

void CKICT_MPDlg::OnBnClickedBtJoyOn()
{
	int ret = gamepad.Refresh();
	if (ret){
		SetTimer(TM_GAMEPAD, 100, NULL);
		_usegamepad = true;
	}
}

void CKICT_MPDlg::OnBnClickedBtJoyOff()
{
	KillTimer(TM_GAMEPAD);
	_usegamepad = false;
}

float ad2Temperature(int adValue)
{
	//for new temperature sensor
	double tempM = 0;
	double k = (adValue / FULLAD);
	double resValue = 0;
	if (k != 1)
	{
		resValue = 10000 * k / (1 - k);      //AD value to resistor
	}
	else
	{
		resValue = resTable[0];
	}

	int index = -1;
	if (resValue >= resTable[0])       //too lower
	{
		tempM = -20;
	}
	else if (resValue <= resTable[24])
	{
		tempM = 100;
	}
	else
	{
		for (int i = 0; i < 24; i++)
		{
			if ((resValue <= resTable[i]) && (resValue >= resTable[i + 1]))
			{
				index = i;
				break;
			}
		}
		if (index >= 0)
		{
			tempM = tempTable[index] + (resValue - resTable[index]) / (resTable[index + 1] - resTable[index]) * (tempTable[index + 1] - tempTable[index]);
		}
		else
		{
			tempM = 0;
		}
	}

	return tempM;
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CKICT_MPDlg::OnHelpAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CKICT_MPDlg::OnSettingExit()
{
	cam0->Stop = true;
	nightL->Stop = true; 
	fishL->Stop = true;
	fishR->Stop = true;	
	frontL->Stop = true;
	rearR->Stop = true;

	nightR->Stop = true;  //추가
	frontR->Stop = true;
	rearL->Stop = true;

	if (p_cam0)
		::WaitForSingleObject(p_cam0->m_hThread, INFINITE); 
	if (p_cam_nightL)
		::WaitForSingleObject(p_cam_nightL->m_hThread, INFINITE);
	if (p_cam_left)
		::WaitForSingleObject(p_cam_left->m_hThread, INFINITE);
	if (p_cam_right)
		::WaitForSingleObject(p_cam_right->m_hThread, INFINITE);
	if (p_cam_frontL)
	::WaitForSingleObject(p_cam_frontL->m_hThread, INFINITE);
	if (p_cam_rearR)
		::WaitForSingleObject(p_cam_rearR->m_hThread, INFINITE);
	if (p_cam_nightR)
	::WaitForSingleObject(p_cam_nightR->m_hThread, INFINITE);//추가
	if (p_cam_frontR)
		::WaitForSingleObject(p_cam_frontR->m_hThread, INFINITE);
	if (p_cam_rearL)
		::WaitForSingleObject(p_cam_rearL->m_hThread, INFINITE);

	delete _rtGraph0;
	delete _rtGraph1;
	delete dr_motor;

	delete nightL;
	delete cam0;	
	delete fishL;
	delete fishR;
	delete frontL;
	delete rearR;

	delete nightR; //추가
	delete frontR; 
	delete rearL;


	OnOK();
}

void CKICT_MPDlg::OnSettingIp() //IP 설정 창을 뜨움
{
	IpSetting ipsettingDlg;
	if (ipsettingDlg.DoModal() == IDOK)
		LoadIpSetting();	
}

void CKICT_MPDlg::LoadIpSetting()
{
	FILE *fp_setting;
	errno_t err;
	char fname[128] = { 0, };
	sprintf_s(fname, "IpSetting.txt");
	if ((err = fopen_s(&fp_setting, fname, "r")) != 0) //0이면 성공, 파일 읽어서 이전 setting 값을 불러 온다.
	{ 
		strcpy_s(_ip_DrMobile, "0.0.0.0");
		strcpy_s(_ip_DrCamera, "0.0.0.0");
		strcpy_s(_ip_NightCameraL, "0.0.0.0");
		strcpy_s(_ip_NightCameraR, "0.0.0.0");
		strcpy_s(_ip_FishL, "0.0.0.0");
		strcpy_s(_ip_FishR, "0.0.0.0");
		strcpy_s(_ip_FrontL, "0.0.0.0");
		strcpy_s(_ip_RearR, "0.0.0.0");
		strcpy_s(_ip_FrontR, "0.0.0.0"); //추가
		strcpy_s(_ip_RearL, "0.0.0.0");
	}
	else //IpSetting.txt 파일이 있으면
	{
		char str[128] = { 0, };
		char* context = NULL;
				
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_DrMobile, str);
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_DrCamera, str);
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_NightCameraL, str);
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_NightCameraR, str);
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_FishL, str);
		fgets(str, sizeof(str), fp_setting); 
		strtok_s(str, ":", &context);
		strcpy_s(_ip_FishR, str);
		fgets(str, sizeof(str), fp_setting);
		strtok_s(str, ":", &context);
		strcpy_s(_ip_FrontL, str);

		fgets(str, sizeof(str), fp_setting);
		strtok_s(str, ":", &context);
		strcpy_s(_ip_FrontR, str);

		fgets(str, sizeof(str), fp_setting);
		strtok_s(str, ":", &context);
		strcpy_s(_ip_RearL, str);

		fgets(str, sizeof(str), fp_setting);
		strtok_s(str, ":", &context);
		strcpy_s(_ip_RearR, str);
	}
	if (fp_setting)
		fclose(fp_setting);
}

UINT CKICT_MPDlg::cam_mobile(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->cam0->Connect();	
	if (ret){
		p->cam0->IsConnected = true;
		p->c_conn_cam0.SetWindowTextW(L"disconnect");
		while (!p->cam0->Stop){			// (p->scn_mode==2)//확장모드이면
				//DisplayImage(&p->cam0->frame0, p->pDC_pic0, p->rect_pic0);			
			p->cam0->getImage(t);
			DisplayImage(&t, p->pDC_pic0, p->rect_pic0);

			Sleep(50);
		}
	}
	p->cam0->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_nightL(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->nightL->Connect();
	p->c_conn_camall.SetWindowTextW(L"disconnect");
	if (ret){
		p->nightL->IsConnected = true;
		while (!p->nightL->Stop){
			//DisplayImage(&p->nightL->frame0, p->pDC_pic_nightL, p->rect_pic_nightL);
			p->nightL->getImage(t);
			DisplayImage(&t, p->pDC_pic_nightL, p->rect_pic_nightL);
			Sleep(50);
		}
	}
	p->nightL->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_nightR(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->nightR->Connect();
	//p->c_conn_camall.SetWindowTextW(L"disconnect");
	if (ret){
		p->nightR->IsConnected = true;
		while (!p->nightR->Stop){
			//DisplayImage(&p->nightR->frame0, p->pDC_pic_nightR, p->rect_pic_nightR);
			p->nightR->getImage(t);
			DisplayImage(&t, p->pDC_pic_nightR, p->rect_pic_nightR);

			Sleep(50);
		}
	}
	p->nightR->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_left(void* data){ // 어안렌즈 Defish 옵션 메인에 bool _defish_on
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->fishL->Connect();
	if (ret){
		p->fishL->IsConnected = true;
		while (!p->fishL->Stop){
			//DisplayImage(&p->fishL->frame0, p->pDC_pic_left, p->rect_pic_left);
			p->fishL->getImage(t);
			DisplayImage(&t, p->pDC_pic_left, p->rect_pic_left);
			Sleep(50);
		}
	}
	p->fishL->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_right(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->fishR->Connect();
	if (ret){
		p->fishR->IsConnected = true;
		while (!p->fishR->Stop){
			//DisplayImage(&p->fishR->frame0, p->pDC_pic_right, p->rect_pic_right);
			p->fishR->getImage(t);
			DisplayImage(&t, p->pDC_pic_right, p->rect_pic_right);
			Sleep(50);
		}
	}
	p->fishR->IsConnected = false;
	return 0;
}
UINT CKICT_MPDlg::cam_frontL(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->frontL->Connect();
	//p->c_conn_camall.SetWindowTextW(L"disconnect");
	if (ret){
		p->frontL->IsConnected = true;
		while (!p->frontL->Stop){
			//DisplayImage(&p->frontL->frame0, p->pDC_pic_front_left, p->rect_pic_front_left);
			p->frontL->getImage(t);
			DisplayImage(&t, p->pDC_pic_front_left, p->rect_pic_front_left);
			Sleep(50);
		}
	}
	p->frontL->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_frontR(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->frontR->Connect();
	if (ret){
		p->frontR->IsConnected = true;
		while (!p->frontR->Stop){
			//DisplayImage(&p->frontR->frame0, p->pDC_pic_front_right, p->rect_pic_front_right);
			p->frontR->getImage(t);
			DisplayImage(&t, p->pDC_pic_front_right, p->rect_pic_front_right);
			Sleep(50);
		}
	}
	p->frontR->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_rearR(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->rearR->Connect();
	//p->c_conn_camall.SetWindowTextW(L"disconnect");
	if (ret){
		p->rearR->IsConnected = true;
		while (!p->rearR->Stop){
			//DisplayImage(&p->rearR->frame0, p->pDC_pic_rear_right, p->rect_pic_rear_right);
			p->rearR->getImage(t);
			DisplayImage(&t, p->pDC_pic_rear_right, p->rect_pic_rear_right);			
			Sleep(50);
		}
	}
	p->rearR->IsConnected = false;
	return 0;
}

UINT CKICT_MPDlg::cam_rearL(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	Mat t;
	bool ret = p->rearL->Connect();
	if (ret){
		p->rearL->IsConnected = true;
		while (!p->rearL->Stop){
			//DisplayImage(&p->rearL->frame0, p->pDC_pic_rear_left, p->rect_pic_rear_left);
			p->rearL->getImage(t);
			DisplayImage(&t, p->pDC_pic_rear_left, p->rect_pic_rear_left);
			Sleep(50);
		}
	}
	p->rearL->IsConnected = false;
	return 0;
}

void CKICT_MPDlg::OnBnClickedBtConn3() // 11-21 임시 p_cam_nightR, p_cam_frontR, p_cam_rearL
{
	if (nightL->IsConnected == true){
		c_conn_camall.SetWindowTextW(L"connect");

		nightL->Stop = true; //카메라 스레드 종료하고		
		fishL->Stop = true;
		fishR->Stop = true;		
		frontL->Stop = true;
		rearR->Stop = true;
		nightR->Stop = true;
		frontR->Stop = true;
		rearL->Stop = true;

		if (p_cam_nightL)
		::WaitForSingleObject(p_cam_nightL->m_hThread, INFINITE);		
		if (p_cam_left)
		::WaitForSingleObject(p_cam_left->m_hThread, INFINITE);
		if (p_cam_right)
		::WaitForSingleObject(p_cam_right->m_hThread, INFINITE);
		if (p_cam_frontL)
		::WaitForSingleObject(p_cam_frontL->m_hThread, INFINITE);
		if (p_cam_rearR)
		::WaitForSingleObject(p_cam_rearR->m_hThread, INFINITE);
		if (p_cam_nightR)
		::WaitForSingleObject(p_cam_nightR->m_hThread, INFINITE); 
		if (p_cam_frontR)
		::WaitForSingleObject(p_cam_frontR->m_hThread, INFINITE);
		if (p_cam_rearL)
		::WaitForSingleObject(p_cam_rearL->m_hThread, INFINITE);

		Sleep(50);

		return;
	}

	nightL->Stop = false;	
	fishL->Stop = false;
	fishR->Stop = false;
	frontL->Stop = false;
	rearR->Stop = false;
	nightR->Stop = false; 
	frontR->Stop = false;
	rearL->Stop = false;

	bool ret = false;
	char addr[128] = { 0, };
	
	sprintf_s(addr, "rtsp://admin:1234@%s:554/video1s1", _ip_NightCameraL);  //cam_nightL에서 	p->c_conn_camall.SetWindowTextW(L"disconnect");
	//sprintf_s(addr, "rtsp://admin:1234@%s:554/video1", _ip_NightCameraL); 
	nightL->SetAddress(addr);
	p_cam_nightL = AfxBeginThread(cam_nightL, this); 
	
	sprintf_s(addr, "rtsp://%s:554/user=admin_password=_channel=1_stream=1.sdp?real_stream", _ip_FishL);
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=_channel=1_stream=0.sdp?real_stream", _ip_FishL);
	fishL->SetAddress(addr);
	p_cam_left = AfxBeginThread(cam_left, this);

	sprintf_s(addr, "rtsp://%s:554/user=admin_password=_channel=1_stream=1.sdp?real_stream", _ip_FishR);
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=_channel=1_stream=0.sdp?real_stream", _ip_FishR);
	fishR->SetAddress(addr);
	p_cam_right = AfxBeginThread(cam_right, this);	

	sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/2", _ip_FrontL);
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/1", _ip_FrontL);
	frontL->SetAddress(addr);
	p_cam_frontL = AfxBeginThread(cam_frontL, this);

	sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/2", _ip_RearR); 
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/1", _ip_RearR);
	rearR->SetAddress(addr);
	p_cam_rearR = AfxBeginThread(cam_rearR, this);

	////////////////// 추가
	sprintf_s(addr, "rtsp://admin:1234@%s:554/video1s1", _ip_NightCameraR);
	//sprintf_s(addr, "rtsp://admin:1234@%s:554/video1", _ip_NightCameraR);
	nightR->SetAddress(addr);
	p_cam_nightR = AfxBeginThread(cam_nightR, this);
	
	sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/2", _ip_FrontR); 
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/1", _ip_FrontR);
	frontR->SetAddress(addr);
	p_cam_frontR = AfxBeginThread(cam_frontR, this);

	sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/2", _ip_RearL); 
	//sprintf_s(addr, "rtsp://%s:554/user=admin_password=admin/Streaming/Channels/1", _ip_RearL);
	rearL->SetAddress(addr);
	p_cam_rearL = AfxBeginThread(cam_rearL, this);	
}
void CKICT_MPDlg::OnBnClickedSetIp()
{
	/*
	ed_xsens_roll.SetWindowTextW(_T("-0.22"));
	ed_xsens_pitch.SetWindowTextW(_T("-0.82"));
	ed_xsens_yaw.SetWindowTextW(_T("135.2"));

	ed_rtk_time.SetWindowTextW(_T("032445.00"));
	ed_rtk_cog.SetWindowTextW(_T("0.03 deg."));
	ed_rtk_count.SetWindowTextW(_T("9"));
	ed_rtk_vog.SetWindowTextW(_T("2.42 m/s"));
	ed_rtk_latitude.SetWindowTextW(_T("3623.56955594 N"));
	ed_rtk_longitude.SetWindowTextW(_T("12723.95829048 E"));
	ed_rtk_state.SetWindowTextW(_T("4"));

	return;
	*/
	//AfxMessageBox(_T("Battery low!!"), MB_ICONWARNING);
//	mqtt0->publish(NULL, GET_PANTILT, 0, NULL, 1, false);
//	mqtt0->publish(NULL, GET_IMU, 0, NULL, 1, false);
//	mqtt0->publish(NULL, GET_GPS, 0, NULL, 1, false); 

	IpSetting ipsettingDlg;
	if (ipsettingDlg.DoModal() == IDOK)
		LoadIpSetting();
}

void CKICT_MPDlg::OnGoogleearthGoogleearth()
{
	//system("C:\\\"Program Files\"\\Google\\\"Google Earth Pro\"\\client\\googleearth.exe");
	ShellExecute(NULL, _T("open"), _T("C:\\Program Files\\Google\\Google Earth Pro\\client\\googleearth.exe"), NULL, NULL, SW_SHOW);
}

void CKICT_MPDlg::OnViewNormal() //기본보기
{
	scn_mode = 1;
	Screen();
	Invalidate(true);
}

void CKICT_MPDlg::OnViewExpand() //확장보기
{
	scn_mode = 2;
	Screen();
	Invalidate(true);
}

void CKICT_MPDlg::OnBnClickedBtCap() //capture once
{
	if (nightL->IsConnected == false)
		return;

	GetLocalTime(&tm);
	char str[64] = {0,};	
	CStringA te;
	sprintf_s(lotime, "%04d%02d%02d_%02d%02d%02d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	te.Format("C:\\capture\\%s",lotime);
	CreateDirectoryA(te, NULL); //폴더를 만들고 그 폴더안에 8개 이미지 저장

	sprintf_s(str, "%s\\%s\\%s_nightL.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, nightL->frame0);
	
	sprintf_s(str, "%s\\%s\\%s_nightR.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, nightR->frame0);
	sprintf_s(str, "%s\\%s\\%s_fishL.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, fishL->frame0);
	sprintf_s(str, "%s\\%s\\%s_fishR.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, fishR->frame0);

	sprintf_s(str, "%s\\%s\\%s_frontL.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, frontL->frame0);
	sprintf_s(str, "%s\\%s\\%s_frontR.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, frontR->frame0);

	sprintf_s(str, "%s\\%s\\%s_rearL.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, rearL->frame0);
	sprintf_s(str, "%s\\%s\\%s_rearR.jpg", CAP_DIR, lotime, lotime);
	imwrite(str, rearR->frame0); 
}


void CKICT_MPDlg::OnBnClickedBtPanP()
{

	
	expectedPan += STEP_ANGLE;
	char str[16] = { 0, };
	sprintf_s(str, "%.4f", expectedPan.GetValue());
	mqtt0->publish(NULL, SPECTATOR_GOTO_PAN_ABS, strlen(str), str, 1, false);
	
	//mqtt0->publish(NULL, PAD_BUTTON_XYAB, strlen("B"), "B", 1, false);
}


void CKICT_MPDlg::OnBnClickedBtPanM()
{
	expectedPan -= STEP_ANGLE;
	char str[16] = { 0, };
	sprintf_s(str, "%.4f", expectedPan.GetValue());
	mqtt0->publish(NULL, SPECTATOR_GOTO_PAN_ABS, strlen(str), str, 1, false);

	//mqtt0->publish(NULL, PAD_BUTTON_XYAB, strlen("X"), "X", 1, false);
}


void CKICT_MPDlg::OnBnClickedBtTiltP()
{
	
	expectedTilt += STEP_ANGLE;
	char str[16] = { 0, };
	sprintf_s(str, "%.4f", expectedTilt.GetValue());
	mqtt0->publish(NULL, SPECTATOR_GOTO_TILT_ABS, strlen(str), str, 1, false);
	//mqtt0->publish(NULL, PAD_BUTTON_XYAB, strlen("Y"), "Y", 1, false);
}


void CKICT_MPDlg::OnBnClickedBtTiltM()
{
	expectedTilt -= STEP_ANGLE;
	char str[16] = { 0, };
	sprintf_s(str, "%.4f", expectedTilt.GetValue());
	mqtt0->publish(NULL, SPECTATOR_GOTO_TILT_ABS, strlen(str), str, 1, false);

	//mqtt0->publish(NULL, PAD_BUTTON_XYAB, strlen("A"), "A", 1, false);
}


void CKICT_MPDlg::OnDataOpenfolder()
{
	::ShellExecute(NULL, _T("open"), NULL, NULL, _T("c:\\data"), SW_SHOW); //저장 폴더 열기
}


void CKICT_MPDlg::OnDataLoad()
{
	Load LoadDlg;
	if (LoadDlg.DoModal() == IDOK)
		int k = 0;
}


void CKICT_MPDlg::OnDataSave()
{
	Save SaveDlg;
	if (SaveDlg.DoModal() == IDOK)
		int k = 0;
}


void CKICT_MPDlg::OnBnClickedBtSpeedSet() //속도 입력
{
	int re=UpdateData(true); //입력값 0~1000

	if (re)
	{
		Speed0 = v_speed_in;
		sl_speed.SetPos(Speed0);
		CString str;
		str.Format(_T("%d"), Speed0);
		ed_speed.SetWindowTextW(str);
	}
}


void CKICT_MPDlg::OnBnClickedBtPanSet()
{
	int re = UpdateData(true);  //-180 ~ 180

	if (re)
	{
		int value = v_pan_in;
		CString valStr;
		double angle;
		try {
			GetDlgItem(IDC_ED_PAN_IN)->GetWindowText(valStr);
			angle = stod(valStr.GetBuffer());

		}
		catch (...) {
			angle = (double)value;
		}


		expectedPan = angle;

		
		char str[50] = { 0, };
		sprintf_s(str, "%.4f", expectedPan.GetValue());		
		mqtt0->publish(NULL, SPECTATOR_GOTO_PAN_ABS, strlen(str), str, 1, false);
	}
}

void CKICT_MPDlg::OnBnClickedBtTiltSet()
{
	int re = UpdateData(true); // -45 ~ 45

	if (re)
	{
		int value = v_tilt_in;
		CString valStr;
		double angle;
		try {
			GetDlgItem(IDC_ED_TILT_IN)->GetWindowText(valStr);
			angle = stod(valStr.GetBuffer());
			
		}
		catch (...) {
			angle = (double)value;
		}


		expectedTilt = angle;
		char str[50] = { 0, };
		sprintf_s(str, "%.4f", expectedTilt.GetValue());
		mqtt0->publish(NULL, SPECTATOR_GOTO_TILT_ABS, strlen(str), str, 1, false);
	}
}

void CKICT_MPDlg::OnBnClickedBtPtCal() //cal. 0,0
{
	mqtt0->publish(NULL, SPECTATOR_GOTO_ABS, strlen("0.0 0.0"), "0.0 0.0", 1, false);
}


void CKICT_MPDlg::OnBnClickedBtLedFrontOn()
{
	static int togg = 0; //현재 상태
	if (togg)
	{
		bt_led_front.SetWindowTextW(_T("On"));
		togg = 0;
		mqtt0->publish(NULL, LIGHT_OFF, strlen("1"), "1", 1, false);
	}
	else
	{
		bt_led_front.SetWindowTextW(_T("Off"));
		togg = 1;
		mqtt0->publish(NULL, LIGHT_ON, strlen("1"), "1", 1, false);
	}
}


void CKICT_MPDlg::OnBnClickedBtLedRearOn()
{
	static int togg = 0; //현재 상태
	if (togg)
	{
		bt_led_rear.SetWindowTextW(_T("On"));
		togg = 0;
		mqtt0->publish(NULL, LIGHT_OFF, strlen("4"), "4", 1, false);
	}
	else
	{
		bt_led_rear.SetWindowTextW(_T("Off"));
		togg = 1;
		mqtt0->publish(NULL, LIGHT_ON, strlen("4"), "4", 1, false);
	}
}

void CKICT_MPDlg::OnBnClickedBtLedLeftOn()
{
	static int togg = 0; //현재 상태
	if (togg)
	{
		bt_led_left.SetWindowTextW(_T("On"));
		togg = 0;
		mqtt0->publish(NULL, LIGHT_OFF, strlen("2"), "2", 1, false);
	}
	else
	{
		bt_led_left.SetWindowTextW(_T("Off"));
		togg = 1;
		mqtt0->publish(NULL, LIGHT_ON, strlen("2"), "2", 1, false);
	}
}


void CKICT_MPDlg::OnBnClickedBtLedRightOn()
{
	static int togg = 0; //현재 상태
	if (togg)
	{
		bt_led_right.SetWindowTextW(_T("On"));
		togg = 0;
		mqtt0->publish(NULL, LIGHT_OFF, strlen("3"), "3", 1, false);
	}
	else
	{
		bt_led_right.SetWindowTextW(_T("Off"));
		togg = 1;
		mqtt0->publish(NULL, LIGHT_ON, strlen("3"), "3", 1, false);
	}
}


void CKICT_MPDlg::OnSettingReboot()
{
	mqtt0->publish(NULL, "KICT_MP/CLIENT/REBOOT", 0, "", 1, false);
}


void CKICT_MPDlg::OnSettingPowerOff()
{
	mqtt0->publish(NULL, "KICT_MP/CLIENT/POWEROFF", 0, "", 1, false);
}



void CKICT_MPDlg::OnDataDeleteall()
{
	int re=AfxMessageBox(
		L"Delete all records\n"
		L"Are you sure?",MB_YESNO|MB_ICONWARNING);

	if (re != IDYES)
		return;
	
	if(robot_db.OpenEx(_T("DSN=robot_db;UID=root;PWD=test123"))==false)
		return;

	robot_db.ExecuteSQL(L"delete from real_time_data");
	robot_db.Close();	
}





void CKICT_MPDlg::OnSnapAround()
{
	// TODO: Add your command handler code here
	BOOL result;
	//AfxMessageBox(_T("KICT.SnapAround found lor!!!"));

	CString str("here you go");
	static BYTE parms[] = VTS_BSTR;
	m_snapper.InvokeHelper(1, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, str);

	TRACE("%d", result);

}


void CKICT_MPDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_snapper.ReleaseDispatch();
	CDialogEx::OnClose();
}

