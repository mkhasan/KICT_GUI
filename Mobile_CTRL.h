#pragma once
#include "afxwin.h"
#include "KICT_MPDlg.h"

class Mobile_Ctrl
{
private:
	(CKICT_MPDlg *)pCWnd;
public:
	void init(CWnd *CWnd){
		pCWnd = (CKICT_MPDlg *)CWnd;
	}
	void Forward()	{
		sprintf_s(pCWnd->send_buf, "MMW !M %d -%d\r\n", pCWnd->Speed0, pCWnd->Speed0);
		int res = pCWnd->m_Socket.Send(pCWnd->send_buf, strlen(pCWnd->send_buf));
	}
	void Backward(){
		sprintf_s(pCWnd->send_buf, "MMW !M -%d %d\r\n", pCWnd->Speed0, pCWnd->Speed0);
		int res = pCWnd->m_Socket.Send(pCWnd->send_buf, strlen(pCWnd->send_buf));
	}
	void L_turn(){
		int tem = 0;
		tem = 240 + (pCWnd->Speed0)*0.5; //턴은 180+에서 동작 시작
		sprintf_s(pCWnd->send_buf, "MMW !M -%d -%d\r\n", tem, tem);
		int res = pCWnd->m_Socket.Send(pCWnd->send_buf, strlen(pCWnd->send_buf));
	}
	void R_turn(){
		int tem = 0;
		tem = 240 + (pCWnd->Speed0)*0.5; 
		sprintf_s(pCWnd->send_buf, "MMW !M %d %d\r\n", tem, tem);
		int res = pCWnd->m_Socket.Send(pCWnd->send_buf, strlen(pCWnd->send_buf));
	}
	void Stop(){
		sprintf_s(pCWnd->send_buf, "MMW !M 0 0\r\n", pCWnd->Speed0, pCWnd->Speed0);
		int res = pCWnd->m_Socket.Send(pCWnd->send_buf, strlen(pCWnd->send_buf));
	}
	
	void SpeedUp(){
		if (pCWnd->Speed0 >= SPEED_LIMIT)
			return;
		pCWnd->Speed0 = pCWnd->Speed0 + 20;
		pCWnd->sl_speed.SetPos(pCWnd->Speed0);
		CString str0;
		str0.Format(L"%d", pCWnd->Speed0);
		pCWnd->ed_speed.SetWindowTextW(str0);
	}
	void SpeedDown(){
		if (pCWnd->Speed0 < 20)
			return;
		pCWnd->Speed0 = pCWnd->Speed0 - 20;
		pCWnd->sl_speed.SetPos(pCWnd->Speed0);
		CString str0;
		str0.Format(L"%d", pCWnd->Speed0);
		pCWnd->ed_speed.SetWindowTextW(str0);
	}
};
