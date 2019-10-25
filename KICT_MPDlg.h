#pragma once
#pragma warning (disable : 4267 4819)

#include "stdafx.h"

#include "afxdb.h"
//#define UM_ACCEPT (WM_USER+200)       
//#define UM_DATARECEIVE (WM_USER+201)
#include "resource.h" //C2065 
#include "afxcmn.h"
#include "afxwin.h"
#include "Mysocket.h"

#include "OScopeCtrl.h" //그래프
#include "Dr_robot.h"
#include "gamepad.h"
#include "IpCamera.h"

#include "mosquittopp.h" //MQTT

#include "CSnapAround.h"



#define TM_PING 100
#define TM_GAMEPAD 123
#define TM_GRAPH 200
#define TM_ROBOT 300

//조이패드 MQTT TOPIC
#define PAD_BUTTON_XYAB "KICT_MP/CLIENT/RIGHT_BUTTON_GROUP" //팬틸트 조이패드 버튼제어
#define PAD_STICK_RIGHT "KICT_MP/CLIENT/RIGHT_STICK"        //팬틸트 조이패드 스틱제어
#define GET_PANTILT "KICT_MP/CLIENT/GET_ANGLES_START"       //팬틸트 값 요청 GET_ANGLES, GET_ANGLES_STOP
#define SPECTATOR_PANTILT "KICT_MP/SPECTATOR/POSITION"      //팬틸트 값 리턴

#define SPECTATOR_GOTO_PAN_ABS "KICT_MP/CLIENT/GOTO_PAN_ABS"      //팬 ABS
#define SPECTATOR_GOTO_TILT_ABS "KICT_MP/CLIENT/GOTO_TILT_ABS"     //틸트 ABS
//#define SPECTATOR_GOTO_HOME "KICT_MP/CLIENT/HOMING"     //not use
#define SPECTATOR_GOTO_ABS "KICT_MP/CLIENT/GOTO_ABS"     //팬틸트 ABS 동시 " 0.0 0.0"

#define GET_IMU "KICT_MP/CLIENT/IMU_START" // #define GET_PANTILT "KICT_MP/CLIENT/IMU_STOP"
#define GET_GPS "KICT_MP/CLIENT/GPS_START" //"KICT_MP/CLIENT/GPS_STOP"

#define SPECTATOR_IMU "KICT_MP/IMU"                         //XSENS IMU
#define SPECTATOR_GPS "KICT_MP/GPS"                         //XSENS GPS

#define SPECTATOR_INFO "KICT_MP/SPEEDO_INFO"                //Mobile info, speed ...

#define LIGHT_ON "KICT_MP/CLIENT/LIGHTS_ON"  //1,2,3,4 전 좌 우 후
#define LIGHT_OFF "KICT_MP/CLIENT/LIGHTS_OFF" 
#define SPEED_LIMIT 500


template <class T>
class ExpectedValue {
	T theta;
	T lowerLimit;
	T upperLimit;
public:
	ExpectedValue() {

	}

 	ExpectedValue(T _theta, T _lowerLimit, T _upperLimit)
		: theta(_theta), lowerLimit(_lowerLimit), upperLimit(_upperLimit)
	{

	}
	void SetValue(T alpha) {
		if (alpha >= lowerLimit && alpha <= upperLimit)
			theta = alpha;

	}
	T GetValue() const {
		return theta;
	}
	
	const ExpectedValue & operator = (T alpha) {
		this->SetValue(alpha);
		return *this;
	}
	
	const ExpectedValue & operator+= (T alpha) {
		if ((theta + alpha <= upperLimit) && theta + alpha >= lowerLimit) {
			theta += alpha;
		}
		return *this;
	}

	const ExpectedValue & operator -= (T alpha) {
		if ((theta - alpha <= upperLimit) && theta - alpha >= lowerLimit) {
			theta -= alpha;
		}
		return *this;

	}
	


};
//class ExpectedValue;	// forward declaration
//MQTT///////////////////////////////////////////////////////////////////////////

class myMosq : public mosqpp::mosquittopp
{
private:
	const char     *     host;
	const char    *     id;
	const char    *     topic;
	int                port;
	int                keepalive;

	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_publish(int mid);
	void on_message(const struct mosquitto_message *message);

public:
	//myMosq(const char *id="Id0", const char * _topic="test", const char *host="localhost", int port=1883);
	myMosq(const char *id, const char * _topic, const char *host, int port);
	~myMosq();
	bool send_message(const char * _message);

	class CKICT_MPDlg *m_point; //mqtt calss에서 접근하기 위해서
	void getpoint(void*);
};

// CKICT_MPDlg dialog
class CKICT_MPDlg : public CDialogEx
{
// Construction
public:
	CKICT_MPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KICT_MP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	myMosq *mqtt0;

	COScopeCtrl *_rtGraph0;
	COScopeCtrl *_rtGraph1;
	
	Dr_motor *dr_motor;
	Dr_gps *dr_gps;
	Dr_imu *dr_imu;

	Gamepad gamepad;

	void Screen();
	afx_msg void OnBnClickedBtFw();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtExit();
	afx_msg void OnBnClickedBtConn();
	char send_buf[128];
	char receive_buf[1024];
	
	CAsyncSocket m_Socket;
	//SOCKET m_recvSocket;
	CButton c_conn_mot;
	CButton c_conn_cam0;
	CButton bt_fw;
	CButton bt_stop;
	CButton bt_bw;
	CButton bt_left;
	CButton bt_right;
	CSliderCtrl sl_speed;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit ed_speed;
	int Speed0; 
	afx_msg void OnBnClickedBtBw();
	afx_msg void OnBnClickedBtStop();
	afx_msg void OnBnClickedBtLeft();
	afx_msg void OnBnClickedBtRight();
	afx_msg void OnBnClickedBtEstop();
	afx_msg void OnBnClickedBtRelease();
	CButton bt_estop;
	CButton bt_release;
	CButton bt_light_on;
	CButton bt_light_off;
	afx_msg void OnBnClickedBtLightOn();
	afx_msg void OnBnClickedBtLightOff();
	afx_msg void OnBnClickedBtConn2();
	
	static UINT cam_mobile(void*); 
	static UINT cam_nightL(void*);	
	static UINT cam_frontL(void*);
	static UINT cam_rearR(void*);
	static UINT cam_left(void*);
	static UINT cam_right(void*);
	
	static UINT cam_nightR(void*);//추가
	static UINT cam_frontR(void*); 
	static UINT cam_rearL(void*);

	CWinThread *p_recvM;
	static UINT recvMobile(void*);

	CDC* pDC_pic_xy;
	CDC* pDC_pic0; //cam0
	CDC* pDC_pic_nightL;
	CDC* pDC_pic_nightR;
	CDC* pDC_pic_front_left;
	CDC* pDC_pic_rear_right;
	CDC* pDC_pic_rear_left; 
	CDC* pDC_pic_front_right;
	CDC* pDC_pic_left;
	CDC* pDC_pic_right;
	CStatic pic0;
	CRect rect_pic0; 
	CRect rect_pic_nightL;
	CRect rect_pic_nightR;
	CRect rect_pic_xy;
	CRect rect_pic_front_left;
	CRect rect_pic_front_right;
	CRect rect_pic_rear_left;
	CRect rect_pic_rear_right;
	CRect rect_pic_left; //어안
	CRect rect_pic_right;
	CStatic pic_xy;
	CStatic pic_nightL;
	CStatic pic_nightR;
	CStatic pic_front_left;
	CStatic pic_front_right;
	CStatic pic_rear_left;
	CStatic pic_rear_right;
	CStatic pic_left; //어안
	CStatic pic_right;

	afx_msg void OnTimer(UINT_PTR nIDEvent); //ping 로봇에 주기적으로 신호를 주지 않으면 스스로 정지함
	int connected_robot;
	int connected_cam0;

	CStatic st_control;
	CStatic st_cam0;
	CStatic gr_conn;
	CStatic gr_ctrl;
	CButton bt_joy_on;
	CButton bt_joy_off;
	afx_msg void OnBnClickedBtJoyOn();
	afx_msg void OnBnClickedBtJoyOff();
	CStatic st_speed;
	CStatic gr_motor;
	CStatic st_m_pos;
	CStatic st_m_speed;
	CStatic st_m_tem;
	CStatic st_m_pwm;
	CStatic st_m_current;
	CStatic st_lfm;
	CStatic st_rfm;
	CStatic st_lrm;
	CStatic st_rrm;
	CEdit ed_lfm_pos;
	CEdit ed_lfm_speed;
	CEdit ed_lfm_tem;
	CEdit ed_lfm_pwm;
	CEdit ed_lfm_current;
	CEdit ed_rfm_pos;
	CEdit ed_rfm_speed;
	CEdit ed_rfm_tem;
	CEdit ed_rfm_pwm;
	CEdit ed_rfm_current;
	CEdit ed_lrm_pos;
	CEdit ed_lrm_speed;
	CEdit ed_lrm_tem;
	CEdit ed_lrm_pwm;
	CEdit ed_lrm_current;
	CEdit ed_rrm_pos;
	CEdit ed_rrm_speed;
	CEdit ed_rrm_tem;
	CEdit ed_rrm_pwm;
	CEdit ed_rrm_current;
	CStatic gr_imu;
	CStatic st_gyro;
	CStatic st_accel;
	CStatic st_compass;
	CStatic st_imu_x;
	CStatic st_imu_y;
	CStatic st_imu_z;
	CStatic st_imu_seq;
	CStatic st_imu_estyaw;
	CEdit ed_gyro_x;
	CEdit ed_gyro_y;
	CEdit ed_gyro_z;
	CEdit ed_accel_x;
	CEdit ed_accel_y;
	CEdit ed_accel_z;
	CEdit ed_compass_x;
	CEdit ed_compass_y;
	CEdit ed_compass_z;
	CEdit ed_imu_seq;
	CEdit ed_imu_estyaw;
	CStatic gr_gps;
	CStatic st_gps_state;
	CStatic st_gps_latitude;
	CStatic st_gps_longitude;
	CStatic st_gps_timestamp;
	CStatic st_gps_cog;
	CStatic st_gps_vog;
	CEdit ed_gps_state;
	CEdit ed_gps_timestamp;
	CEdit ed_gps_latitude;
	CEdit ed_gps_longitude;
	CEdit ed_gps_cog;
	CEdit ed_gps_vog;
	CEdit ed_volt;
	CStatic st_volt;
	CStatic st_m_state;
	CEdit ed_m_state;
	CStatic gr_rtk_gps;
	CStatic gr_imu_xsens;
	afx_msg void OnHelpAbout();
	afx_msg void OnSettingExit();
	//afx_msg void OnSettingConnetc();
	CStatic pic_graph0;
	CStatic pic_graph1;
	boolean _usegamepad;
	afx_msg void OnSettingIp();
	void LoadIpSetting();

	char _ip_DrMobile[32];
	char _ip_DrCamera[32];
	char _ip_NightCameraL[32];
	char _ip_NightCameraR[32];
	char _ip_FishL[32];
	char _ip_FishR[32];
	char _ip_FrontL[32];
	char _ip_RearR[32];

	char _ip_FrontR[32];
	char _ip_RearL[32]; //추가
	
	IpCamera *cam0;
	IpCamera *nightL;
	IpCamera *nightR;
	IpCamera *fishL;
	IpCamera *fishR;
	IpCamera *frontL;
	IpCamera *rearR;

	IpCamera *frontR; //추가
	IpCamera *rearL;

	CWinThread *p_cam0;
	CWinThread *p_cam_nightL;	
	CWinThread *p_cam_nightR;
	CWinThread *p_cam_left;
	CWinThread *p_cam_right;
	CWinThread *p_cam_frontL;
	CWinThread *p_cam_rearR;

	CWinThread *p_cam_frontR; //추가
	CWinThread *p_cam_rearL;
		
	CStatic st_camall;
	CButton c_conn_camall;
	afx_msg void OnBnClickedBtConn3();
	CButton c_set_ip;
	afx_msg void OnBnClickedSetIp();

	bool _defish_on; //어안카메라 왜곡 복원 옵션
	
	int scn_mode; // 기본 1, 확장2

	afx_msg void OnGoogleearthGoogleearth();
	afx_msg void OnViewNormal();
	afx_msg void OnViewExpand();
	CStatic st_xsens_roll;
	CStatic st_xsens_pitch;
	CStatic st_xsens_yaw;
	CEdit ed_xsens_roll;
	CEdit ed_xsens_pitch;
	CEdit ed_xsens_yaw;
	CStatic st_rtk_state;
	CEdit ed_rtk_state;
	CStatic st_rtk_latitude;
	CEdit ed_rtk_latitude;
	CStatic st_rtk_cog;
	CEdit ed_rtk_cog;
	CStatic st_rtk_longitude;
	CEdit ed_rtk_longitude;
	CStatic st_rtk_vog;
	CEdit ed_rtk_vog;
	CButton bt_tilt_plus;
	CButton bt_tilt_minus;
	CButton bt_pan_minus;
	CButton bt_pan_plus;
	CButton c_cap;

	
	CSnapAround m_snapper;



	afx_msg void OnBnClickedBtCap();
	afx_msg void OnBnClickedBtPanP();
	afx_msg void OnBnClickedBtPanM();
	afx_msg void OnBnClickedBtTiltP();
	afx_msg void OnBnClickedBtTiltM();
	CEdit ed_pan;
	CEdit ed_tilt;

	float rod_pan, rod_tilt; //저조도 카메라 팬틸트
	float xsens_roll, xsens_pitch, xsens_yaw; //XSENS 롤치요
	CStatic st_rtk_count;
	CEdit ed_rtk_count;
	CStatic st_rtk_time;
	CEdit ed_rtk_time;
	afx_msg void OnDataOpenfolder();
	afx_msg void OnDataLoad();
	afx_msg void OnDataSave();
	int _save; // none 0 auto 1 semi-auto 2
	CEdit ed_speed_in;
	int v_speed_in;
	CButton bt_speed_set;
	afx_msg void OnBnClickedBtSpeedSet();
	CButton bt_pt_cal;
	// pan : -180 ~ +180
	CStatic st_pan;
	// tilt : -45 
	CStatic st_tilt;
	// //Pan 
	CEdit ed_pan_in;
	CEdit ed_tilt_in;
	int v_pan_in;
	// sssdsdsd
	int v_tilt_in;
	CButton bt_pan_set;
	CButton bt_tilt_set;
	afx_msg void OnBnClickedBtPanSet();
	afx_msg void OnBnClickedBtTiltSet();
	afx_msg void OnBnClickedBtPtCal();
	CStatic gr_led;
	CStatic st_led_front;
	CStatic st_led_rear;
	CStatic st_led_left;
	CStatic st_led_right;
	CButton bt_led_front;
	CButton bt_led_rear;
	CButton bt_led_left;
	CButton bt_led_right;
	CStatic st_base_cam;
	CStatic st_robot3d;
	CStatic st_front_left;
	CStatic st_rear_right;
	CStatic st_left_night;
	CStatic st_right_night;
	CStatic st_left_fisheye;
	CStatic st_right_fisheye;
	afx_msg void OnBnClickedBtLedFrontOn();
	afx_msg void OnBnClickedBtLedRearOn();
	afx_msg void OnBnClickedBtLedLeftOn();
	afx_msg void OnBnClickedBtLedRightOn();
	CStatic st_rear_left;
	CStatic st_front_right;
	afx_msg void OnSettingReboot();
	afx_msg void OnSettingPowerOff();
	CDatabase robot_db;
	CEdit ed_xsens_acc_roll;
	CEdit ed_xsens_acc_pitch;
	CEdit ed_xsens_acc_yaw;
	CStatic st_xsens_acc_roll;
	CStatic st_xsens_acc_pitch;
	CStatic st_xsens_acc_yaw;
	afx_msg void OnDataDeleteall();
	
	afx_msg void OnSnapAround();
	afx_msg void OnClose();


public:
	const int STEP_ANGLE = 10;
	
	ExpectedValue<double> expectedPan;
	ExpectedValue<double> expectedTilt;
	
	



};
