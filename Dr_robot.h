#pragma once
//#ifndef __Dr_robot_H__
//#define __Dr_robot_H__

class Dr_motor{
public:
	int position[4]; //LFM, RFM, LRM, RRM
	int speed[4];
	float temperature[4];
	float pwm[4];
	float current[4];
	char driverstate[2][64];
	float voltage;

public:
	Dr_motor(){ //持失切
		ZeroMemory(position, sizeof(position));
		ZeroMemory(speed, sizeof(speed));
		ZeroMemory(temperature, sizeof(temperature));
		ZeroMemory(pwm, sizeof(pwm));
		ZeroMemory(current, sizeof(current));
		ZeroMemory(driverstate, sizeof(driverstate));
		voltage = 99.0;
	}
	char *Dr_motor::GetDriverState(int no){ return driverstate[no]; }
	int Dr_motor::GetPosition(int no){ return position[no]; }
	int Dr_motor::GetSpeed(int no){ return speed[no]; }
	float Dr_motor::GetTemperature(int no){ return temperature[no]; }
	float Dr_motor::GetPWM(int no){ return pwm[no]; }
	float Dr_motor::GetCurrent(int no){ return current[no]; }
	float Dr_motor::GetVoltage(){ return voltage; }
};

class Dr_gps{
public:
	char state[16];
	char timestamp[16];
	char latitude[16];
	char longuitude[16];
	float cog;
	float vog;

public:
	Dr_gps(){ //持失切
		ZeroMemory(state, sizeof(state));
		ZeroMemory(timestamp, sizeof(timestamp));
		ZeroMemory(latitude, sizeof(latitude));
		ZeroMemory(longuitude, sizeof(longuitude));
		cog = 0.0;
		vog = 0.0;
	}
	
	char *Dr_gps::GetGpsState(){ return state; }
	char *Dr_gps::GetTimeStamp(){ return timestamp; }
	char *Dr_gps::GetLatitude(){ return latitude; }
	char *Dr_gps::GetLonguitude(){ return longuitude; }
	char Dr_gps::GetCog(){ return cog; }
	char Dr_gps::GetVog(){ return vog; }	
};

class Dr_imu{
public:
	int seq;
	float estyaw;
	int gyro[3];
	int accel[3];
	int compass[3];

public:
	Dr_imu(){ //持失切
		seq = 0;
		estyaw = 0;
		ZeroMemory(gyro, sizeof(gyro));
		ZeroMemory(accel, sizeof(accel));
		ZeroMemory(compass, sizeof(compass));
	}

	int Dr_imu::GetSeq(){ return seq; }
	float Dr_imu::GetEstYaw(){ return estyaw; }
	int Dr_imu::GetGyro(int no){ return gyro[no]; }
	int Dr_imu::GetAccel(int no){ return accel[no]; }
	int Dr_imu::GetCompass(int no){ return compass[no]; }	
};

//#endif //__Dr_robot_H__