#pragma once
#pragma warning (disable : 4819)
#include <cv.hpp>
#include <afxwin.h> 
#include <afxmt.h>  //CCriticalSection

using namespace cv;

class IpCamera{
public:
	char Address[128];
	bool IsConnected;
	bool Stop;
	VideoCapture vcap0;
	Mat frame0; 
	void SetAddress(char*);
	bool Connect();	
	CWinThread *p_thread;
	static UINT GetStream(void*);
	CCriticalSection CS;
	void getImage(Mat &img);
	IpCamera(){ //»ý¼ºÀÚ
		ZeroMemory(Address, sizeof(Address));
		IsConnected = false;
		Stop = false;
		//frame0 = Scalar(0);
	}
};