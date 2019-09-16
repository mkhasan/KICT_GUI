#include "afxdialogex.h"
#include "KICT_MPDlg.h"

#include <cv.hpp>
using namespace cv; 

extern void DisplayImage(Mat *image, CDC *pDC, CRect rect);

/*

UINT CKICT_MPDlg::cam0(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;

	VideoCapture vcap0;
	Mat image0;

	BYTE ipFirst, ipSecond, ipThird, ipForth;
	char t_ip[32] = { 0, };
	char StreamAddress_ip[256] = { 0, };

	p->c_cam0_ip.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	sprintf_s(t_ip, "%d.%d.%d.%d", ipFirst, ipSecond, ipThird, ipForth);

	sprintf_s(StreamAddress_ip, "rtsp://%s/axis-media/media.amp?videocodec=h264", t_ip);	//string videoStreamAddress = "rtsp://192.168.0.65:554/axis-media/media.amp?videocodec=h264";
	if (!vcap0.open(StreamAddress_ip)) {
		return 0;
	}
	p->connected_cam0 = 1;
	p->c_conn_cam0.SetWindowTextW(L"disconnect");

	while (p->cam0_stop != 1){
		if (vcap0.read(image0)) {			//resize(image0, Frame0, cv::Size(640, 480), 0, 0, CV_INTER_NN);
			//image0.copyTo(Frame0);
			//Frame0 = image0;
			DisplayImage(&image0, p->pDC_pic0, p->rect_pic0);
			Sleep(1);
		}
	}
	p->connected_cam0 = 0;
	return 0;
}

UINT CKICT_MPDlg::cam_night(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
	//BYTE ipFirst, ipSecond, ipThird, ipForth;
	VideoCapture vcap0;
	Mat image0;

	char t_ip[32] = { 0, };
	char StreamAddress_ip[256] = { 0, };

	sprintf_s(StreamAddress_ip, "rtsp://admin:1234@192.168.1.100:554/video1s1");
	if (!vcap0.open(StreamAddress_ip)) {
		return 0;
	}
	p->connected_cam0 = 1;
	p->c_conn_cam0.SetWindowTextW(L"disconnect");

	while (p->cam0_stop != 1){
		if (vcap0.read(image0)) {			//resize(image0, Frame0, cv::Size(640, 480), 0, 0, CV_INTER_NN);

			DisplayImage(&image0, p->pDC_pic_night, p->rect_pic_night);
			Sleep(1);
		}
	}
	p->connected_cam0 = 0;
	return 0;
}

UINT CKICT_MPDlg::cam_left(void* data){
	CKICT_MPDlg *p = (CKICT_MPDlg *)data;
//	BYTE ipFirst, ipSecond, ipThird, ipForth;
	VideoCapture vcap0;
	Mat image0;

	char t_ip[32] = { 0, };
	char StreamAddress_ip[256] = { 0, };

	sprintf_s(StreamAddress_ip, "rtsp://192.168.1.20:554/user=admin_password=_channel=1_stream=1.sdp?real_stream"); //704 x 576  password ¾øÀ½
	//sprintf_s(StreamAddress_ip, "rtsp://192.168.3.13:554/user=admin_password=tlJwpbo6_channel=1_stream=0.sdp?real_stream"); //2560 x 1440
	if (!vcap0.open(StreamAddress_ip)) {
		return 0;
	}
	p->connected_cam0 = 1;
	p->c_conn_cam0.SetWindowTextW(L"disconnect");

	while (p->cam0_stop != 1){
		if (vcap0.read(image0)) {			//resize(image0, Frame0, cv::Size(640, 480), 0, 0, CV_INTER_NN);

			DisplayImage(&image0, p->pDC_pic_left, p->rect_pic_left);
			//Sleep(1);
		}
	}
	p->connected_cam0 = 0;
	return 0;
}


UINT CKICT_MPDlg::cam_front(void* data){
CKICT_MPDlg *p = (CKICT_MPDlg *)data;

while (p->cam0_stop != 1){
//DisplayImage(&Frame0, p->pDC_pic_front, p->rect_pic_front);
Sleep(1);
}
//p->connected_cam0 = 0;
return 0;
}
UINT CKICT_MPDlg::cam_rear(void* data){
CKICT_MPDlg *p = (CKICT_MPDlg *)data;

while (p->cam0_stop != 1){
//DisplayImage(&Frame0, p->pDC_pic_front, p->rect_pic_front);
//DisplayImage(&Frame0, p->pDC_pic_rear, p->rect_pic_rear);
//DisplayImage(&image0, p->pDC_pic_left, p->rect_pic_left);
//DisplayImage(&image0, p->pDC_pic_right, p->rect_pic_right);
Sleep(1);			//waitKey();			//imshow("Cam0", image0);		//imshow("Cam0", p->image0);		if (cv::waitKey(1) >= 0)			break;
}
//p->connected_cam0 = 0;
return 0;
}
*/