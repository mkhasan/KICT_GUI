//#include "afxdialogex.h"
#include "stdafx.h"
#include "KICT_MPDlg.h"
#include "Mobile_CTRL.h"
#include "gamepad.h"
#include "OpenglClass.h"

extern Gamepad gamepad;
extern Mobile_Ctrl Mctrl;
extern OpenglClass OG;

void CKICT_MPDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TM_PING) //로봇과 통신 체크
	{
		sprintf_s(send_buf, "PING\r\n");
		int res = m_Socket.Send(send_buf, strlen(send_buf));
		if (res <= 0)
			connected_robot = 0;
	}

	if (nIDEvent ==  TM_GRAPH)
	{		
		
		double value0[3];
		double value1[3];
		
		value0[0] = (float)dr_imu->gyro[0];
		value0[1] = (float)dr_imu->gyro[1];
		value0[2] = (float)dr_imu->gyro[2];
		_rtGraph0->AppendPoints(value0);

		value1[0] = (float)dr_imu->accel[0];
		value1[1] = (float)dr_imu->accel[1];
		value1[2] = (float)dr_imu->accel[2];
		_rtGraph1->AppendPoints(value1);
		
		/*
		static int k = 0;
		double value0[3];
		double value1[3];
		value0[0] = 180*sin((k++ % 360)*3.14/180);
		value0[1] = k % 100;
		value0[2] = k % 50 + 70;
		_rtGraph1->AppendPoints(value0);

		value1[0] = 200 * cos((k++ % 360)*3.14 / 180);
		value1[1] = -k % 20;
		value1[2] = k % 10 + 10;
		_rtGraph0->AppendPoints(value1);
		*/
	}

	if (nIDEvent == TM_ROBOT)
	{
		CString te;
		te.Format(_T("%.2f"), dr_motor->current[0]); //CURRENT
		ed_lfm_current.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->current[1]);
		ed_rfm_current.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->current[2]);
		ed_lrm_current.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->current[3]);
		ed_rrm_current.SetWindowTextW(te);

		te.Format(_T("%.2f"), dr_motor->temperature[0]); //TEMPERATURE
		ed_lfm_tem.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->temperature[1]);
		ed_rfm_tem.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->temperature[2]);
		ed_lrm_tem.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_motor->temperature[3]);
		ed_rrm_tem.SetWindowTextW(te);

		te.Format(_T("%d"), dr_motor->position[0]); //ENCODER POSITION
		ed_lfm_pos.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->position[1]);
		ed_rfm_pos.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->position[2]);
		ed_lrm_pos.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->position[3]);
		ed_rrm_pos.SetWindowTextW(te); 
		
		te.Format(_T("%.f"), dr_motor->pwm[0]); //PWM
		ed_lfm_pwm.SetWindowTextW(te);
		te.Format(_T("%.f"), dr_motor->pwm[1]);
		ed_rfm_pwm.SetWindowTextW(te);
		te.Format(_T("%.f"), dr_motor->pwm[2]);
		ed_lrm_pwm.SetWindowTextW(te);
		te.Format(_T("%.f"), dr_motor->pwm[3]);
		ed_rrm_pwm.SetWindowTextW(te);

		te.Format(_T("%d"), dr_motor->speed[0]); //ENCODER SPEED RPM
		ed_lfm_speed.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->speed[1]);
		ed_rfm_speed.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->speed[2]);
		ed_lrm_speed.SetWindowTextW(te);
		te.Format(_T("%d"), dr_motor->speed[3]);
		ed_rrm_speed.SetWindowTextW(te);

		te.Format(_T("%.2f"), dr_motor->voltage);
		ed_volt.SetWindowTextW(te);
		if (dr_motor->voltage <= 22.2) //배터리 알람 메시지 박스
			AfxMessageBox(_T("Battery low!!"),MB_ICONWARNING);
		
		ed_m_state.SetWindowTextW((CString)"Dvr0:" + (CString)dr_motor->driverstate[0] + (CString)"\r\n" + (CString)"Dvr1:" + (CString)dr_motor->driverstate[1]);

		////////////////////////////////////////////   IMU   //////////////////////
		te.Format(_T("%d"), dr_imu->seq); 
		ed_imu_seq.SetWindowTextW(te);			

		te.Format(_T("%.2f"), dr_imu->estyaw);
		ed_imu_estyaw.SetWindowTextW(te);
		////----------------OPENGL------------------------
//		OG.body_yaw = (dr_imu->estyaw)*(180/3.12);	
		OG.Invalidate();
		
		te.Format(_T("%d"), dr_imu->gyro[0]);
		ed_gyro_x.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->gyro[1]);
		ed_gyro_y.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->gyro[2]);
		ed_gyro_z.SetWindowTextW(te);
		
		te.Format(_T("%d"), dr_imu->accel[0]);
		ed_accel_x.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->accel[1]);
		ed_accel_y.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->accel[2]);
		ed_accel_z.SetWindowTextW(te);

		te.Format(_T("%d"), dr_imu->compass[0]);
		ed_compass_x.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->compass[1]);
		ed_compass_y.SetWindowTextW(te);
		te.Format(_T("%d"), dr_imu->compass[2]);
		ed_compass_z.SetWindowTextW(te);
		////////////////////////////////////////////   GPS   //////////////////////
		ed_gps_timestamp.SetWindowTextW(CString(dr_gps->timestamp));
		ed_gps_state.SetWindowTextW(CString(dr_gps->state));
		ed_gps_latitude.SetWindowTextW(CString(dr_gps->latitude));
		ed_gps_longitude.SetWindowTextW(CString(dr_gps->longuitude));
		te.Format(_T("%.2f"), dr_gps->vog);
		ed_gps_vog.SetWindowTextW(te);
		te.Format(_T("%.2f"), dr_gps->cog);
		ed_gps_cog.SetWindowTextW(te);

	}


	
	if (nIDEvent == TM_GAMEPAD)
	{
		gamepad.Refresh(); // 게임패드 앞에 D|X 에서 "X" 에 위치, 안되면 D했다가 X로 옮기기
		static int state_MP = 0; //0정지 1전진 2후진 3좌 4우  로봇
		static int state_PT = 0; //0정지 1좌 2우 3상 4하  팬틸트
		static int state_PT_STICK = 0; //0정지 1좌 2우 3상 4하  팬틸트 오른쪽 스틱 조작

		if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_UP) && (state_MP != 1))
		{
			Mctrl.Forward();//OnBnClickedBtFw();
			state_MP = 1;
		}

		else if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_DOWN) && (state_MP != 2))
		{
			Mctrl.Backward();// OnBnClickedBtBw();
			state_MP = 2;
		}

		else if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_LEFT) && (state_MP != 3))
		{
			Mctrl.L_turn();// OnBnClickedBtLeft();
			state_MP = 3;
		}

		else if (gamepad.IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT) && (state_MP != 4))
		{
			Mctrl.R_turn();// OnBnClickedBtRight();
			state_MP = 4;
		}

		else if (gamepad.IsPressed(0xff) == 0 && (state_MP != 0))
		{
			Mctrl.Stop();// OnBnClickedBtStop();
			state_MP = 0;
		}

		if (gamepad.IsPressed(XINPUT_GAMEPAD_LEFT_SHOULDER))
		{
			Mctrl.SpeedUp();
		}
		else if (gamepad.IsPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER))
		{
			Mctrl.SpeedDown();
		}

		///////////////////// 팬틸트 조이패드 오른쪽 버튼 조작(조그) ///////////////////
		if (gamepad.IsPressed(XINPUT_GAMEPAD_X) && (state_PT != 1)) //좌
		{			
			OnBnClickedBtPanM();
			state_PT = 1;
		}
		else if (gamepad.IsPressed(XINPUT_GAMEPAD_B) && (state_PT != 2)) //우
		{
			OnBnClickedBtPanP();
			state_PT = 2;
		}
		else if (gamepad.IsPressed(XINPUT_GAMEPAD_Y) && (state_PT != 3)) //상
		{			
			OnBnClickedBtTiltP();
			state_PT = 3;
		}
		else if (gamepad.IsPressed(XINPUT_GAMEPAD_A) && (state_PT != 4)) //하
		{
			OnBnClickedBtTiltM();
			state_PT = 4;
		}
		else if (gamepad.IsPressed(0xff) == 0 && (state_PT != 0))
		{		
			state_PT = 0;
		}

		///////////////////// 팬틸트 조이패드 오른쪽 스틱 조작(연속) ///////////////////
		if (gamepad.rightStickX < -0.9 && (state_PT_STICK != 1)) //좌
		{
			//mqtt0->publish(NULL, PAD_STICK_RIGHT, strlen("-1.0 0.0"), "-1.0 0.0", 1, false);
			expectedPan -= 5;
			char str[16] = { 0, };
			sprintf_s(str, "%.4f", expectedPan.GetValue());
			mqtt0->publish(NULL, SPECTATOR_GOTO_PAN_ABS, strlen(str), str, 1, false);
			state_PT_STICK = 1;
		}
		else if (gamepad.rightStickX > 0.9 && (state_PT_STICK != 2)) //우
		{
			//mqtt0->publish(NULL, PAD_STICK_RIGHT, strlen("1.0 0.0"), "1.0 0.0", 1, false);
			expectedPan += 5;
			char str[16] = { 0, };
			sprintf_s(str, "%.4f", expectedPan.GetValue());
			mqtt0->publish(NULL, SPECTATOR_GOTO_PAN_ABS, strlen(str), str, 1, false);
			state_PT_STICK = 2;
		}
		else if (gamepad.rightStickY > 0.9 && (state_PT_STICK != 3)) //상
		{
			//mqtt0->publish(NULL, PAD_STICK_RIGHT, strlen("0.0 1.0"), "0.0 1.0", 1, false);
			expectedTilt += 5;
			char str[16] = { 0, };
			sprintf_s(str, "%.4f", expectedTilt.GetValue());
			mqtt0->publish(NULL, SPECTATOR_GOTO_TILT_ABS, strlen(str), str, 1, false);
			state_PT_STICK = 3;
		}
		else if (gamepad.rightStickY < -0.9 && (state_PT_STICK != 4)) //하
		{
			//mqtt0->publish(NULL, PAD_STICK_RIGHT, strlen("0.0 -1.0"), "0.0 -1.0", 1, false);
			expectedTilt -= 5;
			char str[16] = { 0, };
			sprintf_s(str, "%.4f", expectedTilt.GetValue());
			mqtt0->publish(NULL, SPECTATOR_GOTO_TILT_ABS, strlen(str), str, 1, false);
			state_PT_STICK = 4;
		}
		else if (gamepad.rightStickX >= -0.1 && gamepad.rightStickX <= 0.1 && gamepad.rightStickY <= 0.1 && gamepad.rightStickY >= -0.1 && (state_PT_STICK != 0)) //정지
		{
			//mqtt0->publish(NULL, PAD_STICK_RIGHT, strlen("0.0 0.0"), "0.0 0.0", 1, false);

			state_PT_STICK = 0;
		}
			

	}
	
	CDialogEx::OnTimer(nIDEvent);
}