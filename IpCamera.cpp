#include "IpCamera.h"
#include <cv.hpp>
//#include <afxwin.h> 
using namespace cv;

void IpCamera::SetAddress(char* addr)
{
	strcpy_s(Address,addr);
} 

bool IpCamera::Connect()
{
	if (!vcap0.open(Address)) {
		return false;
	}
	IsConnected = true;
	p_thread = AfxBeginThread(GetStream, this);
	return true;
}

UINT IpCamera::GetStream(void* d)
{
	Mat frame;
	IpCamera *p = (IpCamera *)d;
	int ret = 0;
	while (p->Stop != true){
		p->vcap0.read(frame);
		if (frame.cols != 0)
			p->CS.Lock();
			p->frame0 = frame.clone();
			p->CS.Unlock();
		/*
		try {
			ret = p->vcap0.read(frame);
			if (!ret)
			{
				Sleep(10);
			}
			if (!(frame.rows == 0 || frame.cols == 0))
				p->frame0 = frame.clone();
			else
				Sleep(0);
		}
		catch (...) {
			Sleep(10);
		}
		*/
		Sleep(50);
		}
	
	p->IsConnected = false;
	return 0;
}

void IpCamera::getImage(Mat &img)
{
	CS.Lock();
	img = frame0.clone();
	CS.Unlock();
}