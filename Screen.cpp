//"Static", SS_BITMAP,
#include "stdafx.h" //안하면 에러남
#include "KICT_MPDlg.h"
#include "OpenglClass.h"
extern OpenglClass OG;


void CKICT_MPDlg::Screen(){
	static int _once = 0; //그래프 한번만 생성

	int p, q;
	Speed0 = 100;
	connected_cam0 = 0;
	
	sl_speed.SetRange(0, SPEED_LIMIT);// sl_speed.SetRange(0, 1000);
	sl_speed.SetPos(100);
	sl_speed.SetTicFreq(10);	// 속성의 Tick Marks와 Auto Ticks가 True로 되어 있어야 한다.
	sl_speed.SetLineSize(10);	// 키보드 커서키로 슬라이더를 움직일때의 증가 크기를 설정
	sl_speed.SetPageSize(10);	// 키보드의 PgUp, PgDn키를 누르거나 마우스로 슬라이더의 몸동을 클릭시 움직일 크기 

	p = 10;	q = 10;
	gr_conn.MoveWindow(p, q, 167, 282);////////연결 그룹///////////////////////////////////////
	p = p + 10;	q = q + 25;

	st_control.MoveWindow(p, q + 5, 55, 28);
	st_cam0.MoveWindow(p, q + 36 + 5, 55, 28);
	st_camall.MoveWindow(p, q + 36 + 36 + 5, 55, 28);

	c_conn_mot.MoveWindow(p + 65, q, 80, 28);
	c_conn_cam0.MoveWindow(p + 65, q + 36, 80, 28);
	c_conn_camall.MoveWindow(p + 65, q + 36 + 36, 80, 28);

	c_set_ip.MoveWindow(p + 10, q + 36 + 36 + 36 + 10, 80, 28); //Set IP
	c_cap.MoveWindow(p + 10, q + 36 + 36 + 36 + 36 + 10, 80, 28);//capture

	st_volt.MoveWindow(p, q + 36 + 36 + 36 + 36 + 36 + 20, 60, 28);
	ed_volt.MoveWindow(p + 65, q + 36 + 36 + 36 + 36 + 36 + 18, 50, 28);

	p = 185;	q = 10;
	gr_ctrl.MoveWindow(p, q, 353, 282); //제어 그룹////////////////////////////////////
	p = 190;	q = 25;
	sl_speed.MoveWindow(p, q + 5, 340, 20);
	st_speed.MoveWindow(p + 15, q + 30, 45, 24);
	ed_speed_in.MoveWindow(p + 12, q + 53, 40, 24); //속도 입력
	bt_speed_set.MoveWindow(p + 57, q + 53, 50, 26); //속도 

	ed_speed.MoveWindow(p + 60, q + 30, 50, 24); //속도 현재 값
	ed_speed.SetWindowTextW(L"100");
	ed_speed_in.SetWindowTextW(L"100");

	p = 270; q = 10; //팬틸트
	st_pan.MoveWindow(p + 82, q + 45, 40, 16);
	st_tilt.MoveWindow(p + 82, q + 70, 40, 16);

	ed_pan.MoveWindow(p + 116, q + 45, 46, 16); //팬/틸트 현재 값
	ed_tilt.MoveWindow(p + 116, q + 70, 46, 16);

	ed_pan_in.MoveWindow(p + 172, q + 43, 40, 22); //팬틸트 입력
	ed_tilt_in.MoveWindow(p + 172, q + 68, 40, 22);

	bt_pan_set.MoveWindow(p + 215, q + 42, 40, 24);
	bt_tilt_set.MoveWindow(p + 215, q + 67, 40, 24);
	ed_pan.SetWindowTextW(L"0.0");
	ed_tilt.SetWindowTextW(L"0.0");

	p = 252; q = 118;
	bt_fw.MoveWindow(p, q + 3, 50, 25);//전후진 좌회전 우회전
	bt_stop.MoveWindow(p, q + 32, 50, 25);
	bt_left.MoveWindow(p - 52, q + 32, 50, 25);
	bt_right.MoveWindow(p + 52, q + 32, 50, 25);
	bt_bw.MoveWindow(p, q + 61, 50, 25);

	p = 420; q = 150;  // 팬, 틸트
	bt_tilt_plus.MoveWindow(p, q - 29, 50, 25);
	bt_tilt_minus.MoveWindow(p, q + 29, 50, 25);
	bt_pt_cal.MoveWindow(p, q, 50, 25);
	bt_pan_minus.MoveWindow(p - 52, q, 50, 25);
	bt_pan_plus.MoveWindow(p + 52, q, 50, 25);

	p = 215; q = 210;
	bt_estop.MoveWindow(p, q + 10, 60, 26);           //EMERGENCY STOP, RELEASE
	bt_release.MoveWindow(p + 62, q + 10, 60, 26);

	bt_light_on.MoveWindow(p + 170, q + 10, 60, 26); //LIGHT ON OFF
	bt_light_off.MoveWindow(p + 170 + 65, q + 10, 60, 26);

	p = 205; q = 255;
	st_m_state.MoveWindow(p, q, 35, 30);       //state
	ed_m_state.MoveWindow(p + 37, q - 3, 110, 30);

	bt_joy_on.MoveWindow(p + 180, q, 60, 25); //GamePad ON OFF
	bt_joy_off.MoveWindow(p + 180 + 65, q, 60, 25);

	if (scn_mode == 1)//기본
	{
     	////////////////////////////////////// MOROT SENSOR///////////////

		p = 10; q = 410;
		gr_motor.ShowWindow(false); //.MoveWindow(p, q, 405, 210);
		st_m_pos.ShowWindow(false); //.MoveWindow(p + 50, q + 25, 60, 24);
		st_m_speed.ShowWindow(false); //.MoveWindow(p + 50 + 70, q + 25, 60, 24);
		st_m_tem.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70, q + 25, 60, 24);
		st_m_pwm.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70, q + 25, 60, 24);
		st_m_current.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q + 25, 60, 24);

		p = 10; q = q + 50;
		st_lfm.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lfm_pos.ShowWindow(false); //.MoveWindow(p + 50, q, 60, 24);
		ed_lfm_speed.ShowWindow(false); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_lfm_tem.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_lfm_pwm.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_lfm_current.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		p = 10; q = q + 40;
		st_rfm.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rfm_pos.ShowWindow(false); //.MoveWindow(p + 50, q, 60, 24);
		ed_rfm_speed.ShowWindow(false); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_rfm_tem.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_rfm_pwm.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_rfm_current.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		p = 10; q = q + 40;
		st_lrm.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lrm_pos.ShowWindow(false); //.MoveWindow(p + 50, q, 60, 24);
		ed_lrm_speed.ShowWindow(false); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_lrm_tem.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_lrm_pwm.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_lrm_current.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		p = 10; q = q + 40;
		st_rrm.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rrm_pos.ShowWindow(false); //.MoveWindow(p + 50, q, 60, 24);
		ed_rrm_speed.ShowWindow(false); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_rrm_tem.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_rrm_pwm.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_rrm_current.ShowWindow(false); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		//////////////////////////////////////////IMU///////////////////////////////////////////
		p = 10; q = 625;
		gr_imu.ShowWindow(false); //.MoveWindow(p, q + 5, 405, 170);
		st_imu_x.ShowWindow(false); //.MoveWindow(p + 70, q + 25, 60, 24);
		st_imu_y.ShowWindow(false); //.MoveWindow(p + 70 + 70, q + 25, 60, 24);
		st_imu_z.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70, q + 25, 60, 24);

		st_imu_seq.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 30, 60, 24);
		ed_imu_seq.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 55, 60, 24);
		st_imu_estyaw.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 100, 60, 24);
		ed_imu_estyaw.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 125, 60, 24);

		p = 10; q = q + 50;
		st_gyro.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_gyro_x.ShowWindow(false); //.MoveWindow(p + 70, q, 60, 24);
		ed_gyro_y.ShowWindow(false); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_gyro_z.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		p = 10; q = q + 40;
		st_accel.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_accel_x.ShowWindow(false); //.MoveWindow(p + 70, q, 60, 24);
		ed_accel_y.ShowWindow(false); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_accel_z.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		p = 10; q = q + 40;
		st_compass.ShowWindow(false); //.MoveWindow(p + 10, q + 5, 50, 24);
		ed_compass_x.ShowWindow(false); //.MoveWindow(p + 70, q, 60, 24);
		ed_compass_y.ShowWindow(false); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_compass_z.ShowWindow(false); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		/////////////////////////////////////////////GPS/////////////////////////////////////////////////////
		p = 10; q = 810;
		gr_gps.ShowWindow(false); //.MoveWindow(p, q, 405, 160);
		st_gps_state.ShowWindow(false); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_state.ShowWindow(false); //.MoveWindow(p + 10 + 70, q + 25, 60, 24);
		st_gps_timestamp.ShowWindow(false); //.MoveWindow(p + 10 + 180, q + 5 + 25, 60, 24);
		ed_gps_timestamp.ShowWindow(false); //.MoveWindow(p + 10 + 70 + 180, q + 25, 80, 24);

		p = 10; q = q + 40;
		st_gps_latitude.ShowWindow(false); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_latitude.ShowWindow(false); //.MoveWindow(p + 10 + 70, q + 25, 90, 24);
		st_gps_cog.ShowWindow(false); //.MoveWindow(p + 10 + 200, q + 5 + 25, 60, 24);
		ed_gps_cog.ShowWindow(false); //.MoveWindow(p + 10 + 70 + 200, q + 25, 60, 24);

		p = 10; q = q + 50;
		st_gps_longitude.ShowWindow(false); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_longitude.ShowWindow(false); //.MoveWindow(p + 10 + 70, q + 25, 90, 24);
		st_gps_vog.ShowWindow(false); //.MoveWindow(p + 10 + 200, q + 5 + 25, 60, 24);
		ed_gps_vog.ShowWindow(false); //.MoveWindow(p + 10 + 70 + 200, q + 25, 60, 24);

		/////////////////////////////CAMERA ///////////////////////////////////////////////////////
		p = 40; q = 320;
		float ratio = 0.67f;
		int wid = 470;
		int hei = 350;
		pic0.MoveWindow(p, q, (int)(640 * ratio), (int)(480 * ratio));// DR_Camera
		pic0.GetClientRect(&rect_pic0);
				
		pic_xy.MoveWindow(p, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //XY OpenGL 
		//pic_xy.GetClientRect(&rect_pic_xy);
		pic_xy.GetWindowRect(rect_pic_xy);
		ScreenToClient(rect_pic_xy);
		
		if (OG) //Expand에서 flase 하기 때문에
			OG.ShowWindow(true);
		pic_xy.ShowWindow(true);
		
		pic_front_right.ShowWindow(false);
		pic_rear_left.ShowWindow(false);

		p = p + wid;
		pic_front_left.MoveWindow(p, q, (int)(640 * ratio), (int)(480 * ratio)); //전방 
		pic_front_left.GetClientRect(&rect_pic_front_left);

		pic_rear_right.MoveWindow(p, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //후방
		pic_rear_right.GetClientRect(&rect_pic_rear_right);

		p = p + wid;
		pic_nightL.MoveWindow(p, q, (int)(640 * ratio), (int)(480 * ratio));//저조도  좌
		pic_nightL.GetClientRect(&rect_pic_nightL);		
	
		pic_left.MoveWindow(p, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //어안 좌
		pic_left.GetClientRect(&rect_pic_left);		

		p = p + wid;
		pic_nightR.MoveWindow(p, q, (int)(640 * ratio), (int)(480 * ratio));//저조도  우
		pic_nightR.GetClientRect(&rect_pic_nightR);

		pic_right.MoveWindow(p, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //어안  우
		pic_right.GetClientRect(&rect_pic_right);

		/// Label
		p = 30; q = 303;
		wid = 470;
		hei = 350;
		st_base_cam.MoveWindow(p, q, 200, 16);
		st_robot3d.MoveWindow(p, q + hei, 200, 16);

		st_front_left.MoveWindow(p + wid, q, 200, 16);
		st_rear_right.MoveWindow(p + wid, q + hei, 200, 16);

		st_left_night.MoveWindow(p + wid + wid, q, 200, 16);
		st_left_fisheye.MoveWindow(p + wid + wid, q + hei, 200, 16);

		st_right_night.MoveWindow(p + wid + wid + wid, q, 200, 16);
		st_right_fisheye.MoveWindow(p + wid + wid + wid, q + hei, 200, 16);

		st_front_right.ShowWindow(false);
		st_rear_left.ShowWindow(false);
		st_robot3d.ShowWindow(true);
		//////////////////////////////////RTK GPS //////////////////////////////////////////////
		p = 697; q = 10;
		gr_rtk_gps.MoveWindow(p, q, 218, 283);

		q = q + 5;
		st_rtk_time.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_time.MoveWindow(p + 15 + 60, q + 25, 100, 24);

		q = q + 35;
		st_rtk_state.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_state.MoveWindow(p + 15 + 60, q + 25, 100, 24);
				
		q = q + 35;
		st_rtk_latitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_latitude.MoveWindow(p + 15 + 60, q + 25, 135, 24);
		
		q = q + 35;
		st_rtk_longitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_longitude.MoveWindow(p + 15 + 60, q + 25, 135, 24);
		
		q = q + 35;
		st_rtk_count.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_count.MoveWindow(p + 75, q + 25, 100, 24);

		q = q + 35;
		st_rtk_cog.MoveWindow(p + 10 , q + 5 + 25, 60, 24);
		ed_rtk_cog.MoveWindow(p + 75, q + 25, 100, 24);

		q = q + 35;
		st_rtk_vog.MoveWindow(p + 10 , q + 5 + 25, 60, 24);
		ed_rtk_vog.MoveWindow(p + 75, q + 25, 100, 24);

		//////////////////////////////////IMU XSENSE //////////////////////////////////////////////
		p = 545; q = 10;
		gr_imu_xsens.MoveWindow(p, q , 145, 127);//		gr_imu_xsens.MoveWindow(p, q, 325, 160);
		p = p - 5; q = q + 25;
		st_xsens_roll.MoveWindow(p + 10, q, 60, 24);
		ed_xsens_roll.MoveWindow(p + 10 + 65, q, 65, 24);

		st_xsens_pitch.MoveWindow(p + 10, q + 30, 60, 24);
		ed_xsens_pitch.MoveWindow(p + 10 + 65, q + 30, 65, 24);

		st_xsens_yaw.MoveWindow(p + 10, q + 30 + 30, 60, 24);
		ed_xsens_yaw.MoveWindow(p + 10 + 65, q + 30 + 30, 65, 24);

		st_xsens_acc_roll.ShowWindow(false);
		st_xsens_acc_pitch.ShowWindow(false);
		st_xsens_acc_yaw.ShowWindow(false);
		ed_xsens_acc_roll.ShowWindow(false);
		ed_xsens_acc_pitch.ShowWindow(false);
		ed_xsens_acc_yaw.ShowWindow(false);

		//////////////////////////////////LEDs //////////////////////////////////////////////
		p = 545; q = 140; 
		gr_led.MoveWindow(p, q, 145, 152);
		p = p - 5; q = q + 25;
		st_led_front.MoveWindow(p + 10 + 3, q, 60, 24);
		bt_led_front.MoveWindow(p + 10 + 65, q, 65, 24);

		st_led_rear.MoveWindow(p + 10 + 3, q + 30, 60, 24);
		bt_led_rear.MoveWindow(p + 10 + 65, q + 30, 65, 24);

		st_led_left.MoveWindow(p + 10 + 3, q + 30 + 30, 60, 24);
		bt_led_left.MoveWindow(p + 10 + 65, q + 30 + 30, 65, 24);

		st_led_right.MoveWindow(p + 10 + 3, q + 30 + 30 + 30, 60, 24);
		bt_led_right.MoveWindow(p + 10 + 65, q + 30 + 30 + 30, 65, 24);

		//////////////////////////////////GRAPH-0//////////////////////////////////////////////
		p = 925; q = 15;

		pic_graph0.MoveWindow(p, q, 485, 278);
		CRect rtGraph0;
		pic_graph0.GetWindowRect(rtGraph0);
		ScreenToClient(rtGraph0);
		
		//////////////////////////////////GRAPH-1//////////////////////////////////////////////
		pic_graph1.MoveWindow(p + 495, q , 485, 278);
		CRect rtGraph1; // 그래프 그리기 설정	
		pic_graph1.GetWindowRect(rtGraph1);
		ScreenToClient(rtGraph1);			

		if (_once == 0)
		{
			_rtGraph0 = new COScopeCtrl(3);
			_rtGraph0->Create(WS_VISIBLE | WS_CHILD, rtGraph0, this, IDC_PIC_GRAPH0);
			_rtGraph0->SetRanges(-300, 300);
			_rtGraph0->autofitYscale = true;
			_rtGraph0->SetYUnits(L"Imu Gyro");
			_rtGraph0->SetXUnits(L"", L"", L"Now");
			_rtGraph0->SetLegendLabel(L"GyroX", 0);
			_rtGraph0->SetLegendLabel(L"GyroY", 1);
			_rtGraph0->SetLegendLabel(L"GyroZ", 2);
			_rtGraph0->SetBackgroundColor(RGB(150, 150, 150));
			_rtGraph0->SetPlotColor(RGB(255, 255, 255), 0);
			_rtGraph0->SetPlotColor(RGB(255, 255, 0), 1);
			_rtGraph0->SetPlotColor(RGB(0, 255, 0), 2);
			_rtGraph0->m_nShiftPixels = 4;//한 데이터가 추가될 때 옆으로 밀리는 픽셀 수 1이되면 더 조밀하게 2배 시간을 볼 수 있다.	//_rtGraph.m_nMaxPointCnt=50;	
			_rtGraph0->InvalidateCtrl();

			_rtGraph1 = new COScopeCtrl(3);
			_rtGraph1->Create(WS_VISIBLE | WS_CHILD, rtGraph1, this, IDC_PIC_GRAPH1);
			_rtGraph1->SetRanges(-300, 300);
			_rtGraph1->autofitYscale = true;
			_rtGraph1->SetYUnits(L"Imu Accel");
			_rtGraph1->SetXUnits(L"", L"", L"Now");
			_rtGraph1->SetLegendLabel(L"AccelX", 0);
			_rtGraph1->SetLegendLabel(L"AccelY", 1);
			_rtGraph1->SetLegendLabel(L"AccelZ", 2);
			_rtGraph1->SetBackgroundColor(RGB(130, 130, 130));
			_rtGraph1->SetPlotColor(RGB(255, 255, 255), 0);
			_rtGraph1->SetPlotColor(RGB(255, 255, 0), 1);
			_rtGraph1->SetPlotColor(RGB(0, 255, 0), 2);
			_rtGraph1->m_nShiftPixels = 4;//한 데이터가 추가될 때 옆으로 밀리는 픽셀 수 1이되면 더 조밀하게 2배 시간을 볼 수 있다.	//_rtGraph.m_nMaxPointCnt=50;	
			_rtGraph1->InvalidateCtrl();

			_once = 1;
		}		
		_rtGraph0->MoveWindow(rtGraph0);
		_rtGraph1->MoveWindow(rtGraph1);
		_rtGraph0->ShowWindow(true);
		_rtGraph1->ShowWindow(true);
	}

	else if (scn_mode == 2)//확장
	{
		//////////////////////////////////LEDs //////////////////////////////////////////////
		p = 10; q = 300;
		gr_led.MoveWindow(p, q, 145, 152);
		p = p - 5; q = q + 25;
		st_led_front.MoveWindow(p + 10 + 3, q, 60, 24);
		bt_led_front.MoveWindow(p + 10 + 65, q, 65, 24);

		st_led_rear.MoveWindow(p + 10 + 3, q + 30, 60, 24);
		bt_led_rear.MoveWindow(p + 10 + 65, q + 30, 65, 24);

		st_led_left.MoveWindow(p + 10 + 3, q + 30 + 30, 60, 24);
		bt_led_left.MoveWindow(p + 10 + 65, q + 30 + 30, 65, 24);

		st_led_right.MoveWindow(p + 10 + 3, q + 30 + 30 + 30, 60, 24);
		bt_led_right.MoveWindow(p + 10 + 65, q + 30 + 30 + 30, 65, 24);
		
		//////////////////////////////////RTK GPS //////////////////////////////////////////////
		p = 163; q = 300;
		gr_rtk_gps.MoveWindow(p, q, 375, 152);

		q = q + 3;
		st_rtk_time.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_time.MoveWindow(p + 15 + 60, q + 25, 80, 24);

		q = q + 30;
		st_rtk_state.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_state.MoveWindow(p + 15 + 60, q + 25, 60, 24);
		st_rtk_count.MoveWindow(p + 215, q + 5 + 25, 60, 24);
		ed_rtk_count.MoveWindow(p + 70 + 190, q + 25, 100, 24);

		q = q + 30;
		st_rtk_latitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_latitude.MoveWindow(p + 15 + 60, q + 25, 120, 24);
		st_rtk_cog.MoveWindow(p + 215, q + 5 + 25, 60, 24);
		ed_rtk_cog.MoveWindow(p + 70 + 190, q + 25, 100, 24);

		q = q + 30;
		st_rtk_longitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_rtk_longitude.MoveWindow(p + 15 + 60, q + 25, 120, 24);
		st_rtk_vog.MoveWindow(p + 215, q + 5 + 25, 60, 24);
		ed_rtk_vog.MoveWindow(p + 70 + 190, q + 25, 100, 24);
		
		//////////////////////////////////IMU XSENSE //////////////////////////////////////////////
		p = 10; q = 455;//462
		gr_imu_xsens.MoveWindow(p, q, 527, 85);

		st_xsens_roll.MoveWindow(p + 10, q + 28, 50, 24);
		ed_xsens_roll.MoveWindow(p + 10 + 70, q + 25, 80, 24);

		st_xsens_pitch.MoveWindow(p + 10 + 160 + 20, q + 28, 50, 24);
		ed_xsens_pitch.MoveWindow(p + 10 + 160 + 90, q + 25, 80, 24);

		st_xsens_yaw.MoveWindow(p + 10 + 320 + 20, q + 28, 50, 24);
		ed_xsens_yaw.MoveWindow(p + 10 + 320 + 90, q + 25, 80, 24);


		st_xsens_acc_roll.MoveWindow(p + 10, q + 55, 70, 24);
		ed_xsens_acc_roll.MoveWindow(p + 10 + 70, q + 55, 80, 24);

		st_xsens_acc_pitch.MoveWindow(p + 10 + 160 + 20, q + 55, 70, 24);
		ed_xsens_acc_pitch.MoveWindow(p + 10 + 160 + 90, q + 55, 80, 24);

		st_xsens_acc_yaw.MoveWindow(p + 10 + 320 + 20, q + 55, 70, 24);
		ed_xsens_acc_yaw.MoveWindow(p + 10 + 320 + 90, q + 55, 80, 24);

		st_xsens_acc_roll.ShowWindow(true);
		st_xsens_acc_pitch.ShowWindow(true);
		st_xsens_acc_yaw.ShowWindow(true);
		ed_xsens_acc_roll.ShowWindow(true);
		ed_xsens_acc_pitch.ShowWindow(true);
		ed_xsens_acc_yaw.ShowWindow(true);
		
		////////////////////////////////////// MOROT SENSOR///////////////
		p = 20; q = 547;
		gr_motor.MoveWindow(p - 10, q, 527, 175);
		st_m_pos.MoveWindow(p + 50, q + 25, 70, 24);
		st_m_speed.MoveWindow(p + 50 + 90, q + 25, 70, 24);
		st_m_tem.MoveWindow(p + 50 + 90 + 90, q + 25, 70, 24);
		st_m_pwm.MoveWindow(p + 50 + 90 + 90 + 90, q + 25, 70, 24);
		st_m_current.MoveWindow(p + 50 + 90 + 90 + 90 + 90, q + 25, 70, 24);

		q = q + 50;
		st_lfm.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lfm_pos.MoveWindow(p + 50, q, 70, 24);
		ed_lfm_speed.MoveWindow(p + 50 + 90, q, 70, 24);
		ed_lfm_tem.MoveWindow(p + 50 + 90 + 90, q, 70, 24);
		ed_lfm_pwm.MoveWindow(p + 50 + 90 + 90 + 90, q, 70, 24);
		ed_lfm_current.MoveWindow(p + 50 + 90 + 90 + 90 + 90, q, 70, 24);

		q = q + 30;
		st_rfm.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rfm_pos.MoveWindow(p + 50, q, 70, 24);
		ed_rfm_speed.MoveWindow(p + 50 + 90, q, 70, 24);
		ed_rfm_tem.MoveWindow(p + 50 + 90 + 90, q, 70, 24);
		ed_rfm_pwm.MoveWindow(p + 50 + 90 + 90 + 90, q, 70, 24);
		ed_rfm_current.MoveWindow(p + 50 + 90 + 90 + 90 + 90, q, 70, 24);

		q = q + 30;
		st_lrm.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lrm_pos.MoveWindow(p + 50, q, 70, 24);
		ed_lrm_speed.MoveWindow(p + 50 + 90, q, 70, 24);
		ed_lrm_tem.MoveWindow(p + 50 + 90 + 90, q, 70, 24);
		ed_lrm_pwm.MoveWindow(p + 50 + 90 + 90 + 90, q, 70, 24);
		ed_lrm_current.MoveWindow(p + 50 + 90 + 90 + 90 + 90, q, 70, 24);

		q = q + 30;
		st_rrm.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rrm_pos.MoveWindow(p + 50, q, 70, 24);
		ed_rrm_speed.MoveWindow(p + 50 + 90, q, 70, 24);
		ed_rrm_tem.MoveWindow(p + 50 + 90 + 90, q, 70, 24);
		ed_rrm_pwm.MoveWindow(p + 50 + 90 + 90 + 90, q, 70, 24);
		ed_rrm_current.MoveWindow(p + 50 + 90 + 90 + 90 + 90, q, 70, 24);

		//////////////////////////////////////////IMU///////////////////////////////////////////
		p = 20; q = 720;
		gr_imu.MoveWindow(p - 10, q + 5, 527, 135);

		st_imu_x.MoveWindow(p + 70, q + 25, 80, 24);
		st_imu_y.MoveWindow(p + 70 + 100, q + 25, 80, 24);
		st_imu_z.MoveWindow(p + 70 + 100 + 100, q + 25, 80, 24);

		st_imu_seq.MoveWindow(p + 400, q + 25, 80, 24);
		ed_imu_seq.MoveWindow(p + 400, q + 45, 80, 24);

		st_imu_estyaw.MoveWindow(p + 400, q + 80, 80, 24);
		ed_imu_estyaw.MoveWindow(p + 400, q + 100, 80, 24);

		q = q + 45;
		st_gyro.MoveWindow(p + 10, q + 5, 30, 24);
		ed_gyro_x.MoveWindow(p + 70, q, 80, 24);
		ed_gyro_y.MoveWindow(p + 70 + 100, q, 80, 24);
		ed_gyro_z.MoveWindow(p + 70 + 100 + 100, q, 80, 24);

		q = q + 30;
		st_accel.MoveWindow(p + 10, q + 5, 30, 24);
		ed_accel_x.MoveWindow(p + 70, q, 80, 24);
		ed_accel_y.MoveWindow(p + 70 + 100, q, 80, 24);
		ed_accel_z.MoveWindow(p + 70 + 100 + 100, q, 80, 24);

		q = q + 30;
		st_compass.MoveWindow(p + 10, q + 5, 50, 24);
		ed_compass_x.MoveWindow(p + 70, q, 80, 24);
		ed_compass_y.MoveWindow(p + 70 + 100, q, 80, 24);
		ed_compass_z.MoveWindow(p + 70 + 100 + 100, q, 80, 24);

		/////////////////////////////////////////////GPS/////////////////////////////////////////////////////
		p = 20; q = 865;
		gr_gps.MoveWindow(p - 10, q, 527, 120);
		st_gps_state.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_state.MoveWindow(p + 10 + 70, q + 25, 60, 24);
		st_gps_timestamp.MoveWindow(p + 260, q + 5 + 25, 60, 24);
		ed_gps_timestamp.MoveWindow(p + 75 + 250, q + 25, 110, 24);

		q = q + 30;
		st_gps_latitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_latitude.MoveWindow(p + 10 + 70, q + 25, 125, 24);
		st_gps_cog.MoveWindow(p + 80 + 175 + 20, q + 5 + 25, 50, 24);
		ed_gps_cog.MoveWindow(p + 80 + 175 + 50 + 20, q + 25, 110, 24);

		q = q + 30;
		st_gps_longitude.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_longitude.MoveWindow(p + 10 + 70, q + 25, 125, 24);
		st_gps_vog.MoveWindow(p + 80 + 175 + 20, q + 5 + 25, 50, 24);
		ed_gps_vog.MoveWindow(p + 80 + 175 + 50 + 20, q + 25, 110, 24);		

		gr_motor.ShowWindow(true); //.MoveWindow(p, q, 405, 210);
		st_m_pos.ShowWindow(true); //.MoveWindow(p + 50, q + 25, 60, 24);
		st_m_speed.ShowWindow(true); //.MoveWindow(p + 50 + 70, q + 25, 60, 24);
		st_m_tem.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70, q + 25, 60, 24);
		st_m_pwm.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70, q + 25, 60, 24);
		st_m_current.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q + 25, 60, 24);

		st_lfm.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lfm_pos.ShowWindow(true); //.MoveWindow(p + 50, q, 60, 24);
		ed_lfm_speed.ShowWindow(true); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_lfm_tem.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_lfm_pwm.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_lfm_current.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		st_rfm.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rfm_pos.ShowWindow(true); //.MoveWindow(p + 50, q, 60, 24);
		ed_rfm_speed.ShowWindow(true); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_rfm_tem.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_rfm_pwm.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_rfm_current.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		st_lrm.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_lrm_pos.ShowWindow(true); //.MoveWindow(p + 50, q, 60, 24);
		ed_lrm_speed.ShowWindow(true); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_lrm_tem.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_lrm_pwm.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_lrm_current.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		st_rrm.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_rrm_pos.ShowWindow(true); //.MoveWindow(p + 50, q, 60, 24);
		ed_rrm_speed.ShowWindow(true); //.MoveWindow(p + 50 + 70, q, 60, 24);
		ed_rrm_tem.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70, q, 60, 24);
		ed_rrm_pwm.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70, q, 60, 24);
		ed_rrm_current.ShowWindow(true); //.MoveWindow(p + 50 + 70 + 70 + 70 + 70, q, 60, 24);

		gr_imu.ShowWindow(true); //.MoveWindow(p, q + 5, 405, 170);
		st_imu_x.ShowWindow(true); //.MoveWindow(p + 70, q + 25, 60, 24);
		st_imu_y.ShowWindow(true); //.MoveWindow(p + 70 + 70, q + 25, 60, 24);
		st_imu_z.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70, q + 25, 60, 24);

		st_imu_seq.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 30, 60, 24);
		ed_imu_seq.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 55, 60, 24);
		st_imu_estyaw.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 100, 60, 24);
		ed_imu_estyaw.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70 + 70 + 30, q + 125, 60, 24);

		st_gyro.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_gyro_x.ShowWindow(true); //.MoveWindow(p + 70, q, 60, 24);
		ed_gyro_y.ShowWindow(true); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_gyro_z.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		st_accel.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 30, 24);
		ed_accel_x.ShowWindow(true); //.MoveWindow(p + 70, q, 60, 24);
		ed_accel_y.ShowWindow(true); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_accel_z.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		st_compass.ShowWindow(true); //.MoveWindow(p + 10, q + 5, 50, 24);
		ed_compass_x.ShowWindow(true); //.MoveWindow(p + 70, q, 60, 24);
		ed_compass_y.ShowWindow(true); //.MoveWindow(p + 70 + 70, q, 60, 24);
		ed_compass_z.ShowWindow(true); //.MoveWindow(p + 70 + 70 + 70, q, 60, 24);

		gr_gps.ShowWindow(true); //.MoveWindow(p, q, 405, 160);
		st_gps_state.ShowWindow(true); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_state.ShowWindow(true); //.MoveWindow(p + 10 + 70, q + 25, 60, 24);
		st_gps_timestamp.ShowWindow(true); //.MoveWindow(p + 10 + 180, q + 5 + 25, 60, 24);
		ed_gps_timestamp.ShowWindow(true); //.MoveWindow(p + 10 + 70 + 180, q + 25, 80, 24);

		st_gps_latitude.ShowWindow(true); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_latitude.ShowWindow(true); //.MoveWindow(p + 10 + 70, q + 25, 90, 24);
		st_gps_cog.ShowWindow(true); //.MoveWindow(p + 10 + 200, q + 5 + 25, 60, 24);
		ed_gps_cog.ShowWindow(true); //.MoveWindow(p + 10 + 70 + 200, q + 25, 60, 24);

		p = 10; q = q + 50;
		st_gps_longitude.ShowWindow(true); //.MoveWindow(p + 10, q + 5 + 25, 60, 24);
		ed_gps_longitude.ShowWindow(true); //.MoveWindow(p + 10 + 70, q + 25, 90, 24);
		st_gps_vog.ShowWindow(true); //.MoveWindow(p + 10 + 200, q + 5 + 25, 60, 24);
		ed_gps_vog.ShowWindow(true); //.MoveWindow(p + 10 + 70 + 200, q + 25, 60, 24);


		/////////////////////////////CAMERA ///////////////////////////////////////////////////////

		OG.ShowWindow(false); // Robot Model not display
		pic_xy.ShowWindow(false);

		pic_front_right.ShowWindow(true);
		pic_rear_left.ShowWindow(true);
		
		p = 590; q = 35;
		float ratio = 0.63f;
		int wid = 430;
		int hei = 325;

		pic0.MoveWindow(p, q, (int)(640 * ratio), (int)(480 * ratio));// DR_Camera
		pic0.GetClientRect(&rect_pic0);

		pic_nightL.MoveWindow(p + wid, q, (int)(640 * ratio), (int)(480 * ratio));//저조도 좌
		pic_nightL.GetClientRect(&rect_pic_nightL);

		pic_nightR.MoveWindow(p + wid + wid, q, (int)(640 * ratio), (int)(480 * ratio));//저조도 우
		pic_nightR.GetClientRect(&rect_pic_nightR);

		pic_front_left.MoveWindow(p, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //전방 좌
		pic_front_left.GetClientRect(&rect_pic_front_left);

		pic_front_right.MoveWindow(p + wid, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //전방 우
		pic_front_right.GetClientRect(&rect_pic_front_right);

		pic_left.MoveWindow(p + wid + wid, q + hei, (int)(640 * ratio), (int)(480 * ratio)); //좌 어안
		pic_left.GetClientRect(&rect_pic_left);

		pic_rear_left.MoveWindow(p, q + hei + hei, (int)(640 * ratio), (int)(480 * ratio)); //후방 좌
		pic_rear_left.GetClientRect(&rect_pic_rear_left); 
		
		pic_rear_right.MoveWindow(p + wid, q + hei + hei, (int)(640 * ratio), (int)(480 * ratio)); //후방 우
		pic_rear_right.GetClientRect(&rect_pic_rear_right);

		pic_right.MoveWindow(p + wid + wid, q + hei + hei, (int)(640 * ratio), (int)(480 * ratio)); //우 어안
		pic_right.GetClientRect(&rect_pic_right);
		
		/// Label/////////////////////////////////////
		st_front_right.ShowWindow(true);
		st_rear_left.ShowWindow(true);
		st_robot3d.ShowWindow(false);
		
		p = p - 20;
		q = q - 16;
		st_base_cam.MoveWindow(p, q, 200, 16);
		st_left_night.MoveWindow(p + wid, q, 200, 16);
		st_right_night.MoveWindow(p + wid + wid, q, 200, 16);

		st_front_left.MoveWindow(p, q + hei, 200, 16);
		st_front_right.MoveWindow(p + wid, q + hei, 200, 16);
		st_left_fisheye.MoveWindow(p + wid + wid, q + hei, 200, 16); 
		
		st_rear_left.MoveWindow(p, q + hei + hei, 200, 16);
		st_rear_right.MoveWindow(p + wid, q + hei + hei, 200, 16);
		st_right_fisheye.MoveWindow(p + wid + wid, q + hei + hei, 200, 16);

		//////////////////////////////////GRAPH-0//////////////////////////////////////////////
		_rtGraph0->ShowWindow(false);
		_rtGraph1->ShowWindow(false);
		/*
		p = 430; q = 420;

		pic_graph0.MoveWindow(p, q, 660, 180);
		CRect rtGraph0;
		pic_graph0.GetWindowRect(rtGraph0);
		ScreenToClient(rtGraph0);		
		//////////////////////////////////GRAPH-1//////////////////////////////////////////////
		pic_graph1.MoveWindow(p, q + 190, 660, 180);
		CRect rtGraph1; // 그래프 그리기 설정	
		pic_graph1.GetWindowRect(rtGraph1);
		ScreenToClient(rtGraph1);
		
		if (_once == 0)
		{
			_rtGraph0 = new COScopeCtrl(3);
			_rtGraph0->Create(WS_VISIBLE | WS_CHILD, rtGraph0, this, IDC_PIC_GRAPH0);
			_rtGraph0->SetRanges(-300, 300);
			_rtGraph0->autofitYscale = true;
			_rtGraph0->SetYUnits(L"Imu Gyro");
			_rtGraph0->SetXUnits(L"", L"", L"Now");
			_rtGraph0->SetLegendLabel(L"GyroX", 0);
			_rtGraph0->SetLegendLabel(L"GyroY", 1);
			_rtGraph0->SetLegendLabel(L"GyroZ", 2);
			_rtGraph0->SetBackgroundColor(RGB(150, 150, 150));
			_rtGraph0->SetPlotColor(RGB(255, 255, 255), 0);
			_rtGraph0->SetPlotColor(RGB(255, 255, 0), 1);
			_rtGraph0->SetPlotColor(RGB(0, 255, 0), 2);
			_rtGraph0->m_nShiftPixels = 4;//한 데이터가 추가될 때 옆으로 밀리는 픽셀 수 1이되면 더 조밀하게 2배 시간을 볼 수 있다.	//_rtGraph.m_nMaxPointCnt=50;	
			_rtGraph0->InvalidateCtrl();
			
			_rtGraph1 = new COScopeCtrl(3);
			_rtGraph1->Create(WS_VISIBLE | WS_CHILD, rtGraph1, this, IDC_PIC_GRAPH1);
			_rtGraph1->MoveWindow(rtGraph1);
			_rtGraph1->SetRanges(-300, 300);
			_rtGraph1->autofitYscale = true;
			_rtGraph1->SetYUnits(L"Imu Accel");
			_rtGraph1->SetXUnits(L"", L"", L"Now");
			_rtGraph1->SetLegendLabel(L"AccelX", 0);
			_rtGraph1->SetLegendLabel(L"AccelY", 1);
			_rtGraph1->SetLegendLabel(L"AccelZ", 2);
			_rtGraph1->SetBackgroundColor(RGB(130, 130, 130));
			_rtGraph1->SetPlotColor(RGB(255, 255, 255), 0);
			_rtGraph1->SetPlotColor(RGB(255, 255, 0), 1);
			_rtGraph1->SetPlotColor(RGB(0, 255, 0), 2);
			_rtGraph1->m_nShiftPixels = 4;//한 데이터가 추가될 때 옆으로 밀리는 픽셀 수 1이되면 더 조밀하게 2배 시간을 볼 수 있다.	//_rtGraph.m_nMaxPointCnt=50;	
			_rtGraph1->InvalidateCtrl();

			_once = 1;
		}	
		_rtGraph0->MoveWindow(rtGraph0);
		_rtGraph1->MoveWindow(rtGraph1);
		*/
	}
}


