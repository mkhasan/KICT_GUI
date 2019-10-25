#include "KICT_MPDlg.h"

myMosq::myMosq(const char * _id, const char * _topic, const char * _host, int _port) : mosquittopp(_id)
{
    mosqpp::lib_init();        // Mandatory initialization for mosquitto library
    this->keepalive = 60;    // Basic configuration setup for myMosq class
    this->id = _id;
    this->port = _port;
    this->host = _host;
    this->topic = _topic;

    connect_async(host,     // non blocking connection to broker request
        port,
        keepalive);

    loop_start();            // Start thread managing connection / publish / subscribe 
};

myMosq::~myMosq() {

    disconnect(); // stop 전에 
    loop_stop();            // Kill the thread
    mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

bool myMosq::send_message(const  char * _message)
{
   int ret = publish(NULL, this->topic, strlen(_message), _message, 1, false);
   return (ret == MOSQ_ERR_SUCCESS);
   // return 0;
}

void myMosq::on_disconnect(int rc) {
    int k = 0;//  std::cout << ">> myMosq - disconnection(" << rc << ")" << std::endl;
}

void myMosq::on_connect(int rc)
{
    if (rc == 0) {
		//subscribe(NULL, "KICT_MP/#");
		subscribe(NULL, SPECTATOR_PANTILT);
		subscribe(NULL, SPECTATOR_IMU);
		subscribe(NULL, SPECTATOR_GPS);
		subscribe(NULL, SPECTATOR_INFO);
  //      TRACE("connected. subscribe [slave]\r");
    }
    else {
        int k = 0;
    }
}

void myMosq::on_publish(int mid)
{
    int k = 0;// std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << std::endl;
  //  TRACE("published..\r");
}

void myMosq::on_message(const struct mosquitto_message *message)
{  
	//return;
	static char buf[256] = { 0, };
	memset(buf, 0, sizeof(buf));
	errno_t re=0;
	char *temp_p = NULL;
	if (message->payload == NULL)
		return;
	//if (message->payloadlen >100)
	//	return;

	if (!strcmp(message->topic, SPECTATOR_PANTILT)) //팬틸트
	{
		//char buf[256] = {0,};
		double v_pan = 0;
		double v_tilt = 0;
		char str[128] = { 0, };
		char * context = NULL;

		static bool first = true;
		
		//if (message->payload == NULL)
		//	return; 		
	//	memset(buf, 0, sizeof(buf));
	//	int k = sizeof(message->payload);
	//	if (k >= 100)
	//		return;
		
		//re = memcpy_s(buf, 120, message->payload, 100);
		re = memcpy_s(buf, sizeof(buf), message->payload, message->payloadlen);
		//memcpy(buf, message->payload, 255 * sizeof(char));
		if (re)
			return;

		temp_p = strtok_s(buf, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);
		//strcpy_s(str, strtok_s(buf, " ", &context)); //PAN value
		v_pan = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);
		//strcpy_s(str, strtok_s(NULL, " ", &context)); //TILT value
		v_tilt = atof(str);
		m_point->rod_pan = v_pan;
		m_point->rod_tilt = v_tilt;

		CString t_pan, t_tilt;
		t_pan.Format(_T("%.2f"), v_pan);
		m_point->ed_pan.SetWindowTextW(t_pan);
		t_tilt.Format(_T("%.2f"), v_tilt);
		m_point->ed_tilt.SetWindowTextW(t_tilt);
		if (first) {
			//int k = round(v_pan);
			//int l = round()
			m_point->expectedPan.SetValue((double)v_pan);
			m_point->expectedTilt.SetValue((double)v_tilt);
			first = false;

		}
	}
	
	else if (!strcmp(message->topic, SPECTATOR_IMU)) //IMU
	{  
		//timestamp 0123456789:0123456789
		char ts[32] = { 0, };
		double v_roll = 0.0; double v_pitch = 0.0; double v_yaw = 0.0;
		double v_acc_roll = 0.0; double v_acc_pitch = 0.0; double v_acc_yaw = 0.0;

		char str[128] = { 0, };
		char * context = NULL;

		re = memcpy_s(buf, sizeof(buf), message->payload, message->payloadlen);
		//re = memcpy_s(buf, sizeof(buf), message->payload, sizeof(buf)-1); 

		if (re)
			return;

		temp_p = strtok_s(buf, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p); //timestamp

		
		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);		
		v_roll = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);		//strcpy_s(str, strtok_s(NULL, " ", &context)); //PITCH value
		v_pitch = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);		//strcpy_s(str, strtok_s(NULL, " ", &context)); //YAW value
		v_yaw = atof(str);
		
		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);
		v_acc_roll = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);		//strcpy_s(str, strtok_s(NULL, " ", &context)); //PITCH value
		v_acc_pitch = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);		//strcpy_s(str, strtok_s(NULL, " ", &context)); //YAW value
		v_acc_yaw = atof(str);
				
		m_point->xsens_roll = v_roll;
		m_point->xsens_pitch = v_pitch;
		m_point->xsens_yaw = v_yaw;

		CString t_roll, t_pitch, t_yaw;
		t_roll.Format(_T("%.2f"), v_roll);
		m_point->ed_xsens_roll.SetWindowTextW(t_roll);
		t_pitch.Format(_T("%.2f"), v_pitch);
		m_point->ed_xsens_pitch.SetWindowTextW(t_pitch);
		t_yaw.Format(_T("%.2f"), v_yaw);
		m_point->ed_xsens_yaw.SetWindowTextW(t_yaw);

		CString t_acc_roll, t_acc_pitch, t_acc_yaw; //ACC
		t_acc_roll.Format(_T("%.2f"), v_acc_roll);
		m_point->ed_xsens_acc_roll.SetWindowTextW(t_acc_roll);
		t_acc_pitch.Format(_T("%.2f"), v_acc_pitch);
		m_point->ed_xsens_acc_pitch.SetWindowTextW(t_acc_pitch);
		t_acc_yaw.Format(_T("%.2f"), v_acc_yaw);
		m_point->ed_xsens_acc_yaw.SetWindowTextW(t_acc_yaw);
	}

	else if (!strcmp(message->topic, SPECTATOR_GPS)) //GPS
	{
		//char buf[256] = { 0, };
		char v_time[32] = { 0, };
		char v_count[8] = { 0, };		
		char v_lat[64] = { 0, }; char v_lat_dir[4] = { 0, };
		char v_lon[64] = { 0, }; char v_lon_dir[4] = { 0, };
		char v_state[8] = { 0, }; //quality
		double v_cog = 0.0; double v_vog = 0.0;

		char str[128] = { 0, };
		char * context = NULL;
		
		re = memcpy_s(buf, sizeof(buf), message->payload, message->payloadlen);

		if (re)
			return;//memcpy(buf, message->payload, 255 * sizeof(char));

		temp_p = strtok_s(buf, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_time, temp_p);
		//strcpy_s(v_time, strtok_s(buf, " ", &context));  //timestamp
		if (strcmp(v_time, "invalid") == 0) //invalid data
		{
			m_point->ed_rtk_time.SetWindowTextW(CString("Invalid"));
			return;
		}

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_count, temp_p);

		//strcpy_s(v_count, strtok_s(NULL, " ", &context)); //count of satellites
		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_lat, temp_p);
		//strcpy_s(v_lat, strtok_s(NULL, " ", &context)); //Latitude

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_lat_dir, temp_p);
		//strcpy_s(v_lat_dir, strtok_s(NULL, " ", &context)); //Latitude Dir

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_lon, temp_p);
		//strcpy_s(v_lon, strtok_s(NULL, " ", &context)); //Longitude

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_lon_dir, temp_p);
		//strcpy_s(v_lon_dir, strtok_s(NULL, " ", &context)); //Longitude Dir

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(v_state, temp_p);
		//strcpy_s(v_state, strtok_s(NULL, " ", &context)); //state(quality)

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);
		//strcpy_s(str, strtok_s(NULL, " ", &context)); //VOG
		v_vog = atof(str);

		temp_p = strtok_s(NULL, " ", &context);
		if (temp_p == NULL)
			return;
		else				strcpy_s(str, temp_p);
		//strcpy_s(str, strtok_s(NULL, " ", &context)); //COG
		v_cog = atof(str);		

		m_point->ed_rtk_time.SetWindowTextW(CString(v_time));
		m_point->ed_rtk_state.SetWindowTextW(CString(v_state));
		m_point->ed_rtk_count.SetWindowTextW(CString(v_count));
		CStringA t_lat;
		t_lat.Format("%s %s",v_lat, v_lat_dir);
		m_point->ed_rtk_latitude.SetWindowTextW(CString(t_lat));
		CStringA t_lon;
		t_lon.Format("%s %s", v_lon, v_lon_dir);
		m_point->ed_rtk_longitude.SetWindowTextW(CString(t_lon));
		
		CString t_cog, t_vog;
		t_cog.Format(_T("%.2f deg."), v_cog);
		m_point->ed_rtk_cog.SetWindowTextW(t_cog);
		
		double KNNOT2MS = 0.514;
		t_vog.Format(_T("%.2f m/s"), v_vog*KNNOT2MS);
		m_point->ed_rtk_vog.SetWindowTextW(t_vog);
	}	
	else if (!strcmp(message->topic, SPECTATOR_INFO)) //GPS
	{
		/*
		int position[4]; //LFM, RFM, LRM, RRM
		int speed[4];
		float temperature[4];
		float pwm[4];
		float current[4];
		char driverstate[2][64];
		float voltage;

		char state[16];
		char timestamp[16];
		char latitude[16];
		char longuitude[16];
		float cog;
		float vog;

		int seq;
		float estyaw;
		int gyro[3];
		int accel[3];
		int compass[3];
		*/
		char str[128] = { 0, };
		char * context = NULL;		
		re = memcpy_s(buf, sizeof(buf), message->payload, message->payloadlen);		
		if (re)
			return;

		temp_p = strtok_s(buf, "|", &context);		  //POSITION
		m_point->dr_motor->position[0] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->position[1] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->position[2] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->position[3] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);       //SPEED
		m_point->dr_motor->speed[0] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->speed[1] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->speed[2] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->speed[3] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);       //TEMPERATURE
		m_point->dr_motor->temperature[0] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->temperature[1] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->temperature[2] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->temperature[3] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);       //PWM
		m_point->dr_motor->pwm[0] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->pwm[1] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->pwm[2] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->pwm[3] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);       //CURRENT
		m_point->dr_motor->current[0] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->current[1] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->current[2] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_motor->current[3] = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);     //DRIVE STATE
		strcpy_s(m_point->dr_motor->driverstate[0], temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		strcpy_s(m_point->dr_motor->driverstate[1], temp_p);
		temp_p = strtok_s(NULL, "|", &context);     //VOLTAGE
		m_point->dr_motor->voltage = atof(temp_p);

		temp_p = strtok_s(NULL, "|", &context);     //GPS
		strcpy_s(m_point->dr_gps->state, temp_p);
		temp_p = strtok_s(NULL, "|", &context);    
		strcpy_s(m_point->dr_gps->timestamp, temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		strcpy_s(m_point->dr_gps->latitude, temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		strcpy_s(m_point->dr_gps->longuitude, temp_p);
		temp_p = strtok_s(NULL, "|", &context);   
		m_point->dr_gps->cog = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_gps->vog = atof(temp_p);

		temp_p = strtok_s(NULL, "|", &context); //IMU
		m_point->dr_imu->seq = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->estyaw = atof(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->gyro[0] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->gyro[1] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->gyro[2] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->accel[0] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->accel[1] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->accel[2] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->compass[0] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->compass[1] = atoi(temp_p);
		temp_p = strtok_s(NULL, "|", &context);
		m_point->dr_imu->compass[2] = atoi(temp_p);
		
	}

}

void myMosq::getpoint(void *p)
{
	m_point = (CKICT_MPDlg *)p;
}