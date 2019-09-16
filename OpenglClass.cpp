// OpenglClass.cpp : 구현 파일입니다.
//
#include <math.h>
#include "stdafx.h"
#include "OpenglClass.h"
#include "KICT_MPDlg.h"

using namespace std;
/*
struct arr{
	float x;
	float y;
	float z;
	float dis;	
};
#define PI 3.141592654
*/
//extern arr coord[10000];
//extern float coord_f[500][3];
//extern int count_f;
//void plane_fit(float p_plane[][3],float res[3]); //평면 피팅
//float z_axis,x_axis,x_degree;
//float wx_f,wy_f,wz_f;
//float na,nb,nc;//법선벡터
//CString temp;

IMPLEMENT_DYNAMIC(OpenglClass, CWnd)

OpenglClass::OpenglClass()
{
	scale=0.02;
	//body_yaw = 0.0;
}

OpenglClass::~OpenglClass()
{
}

BEGIN_MESSAGE_MAP(OpenglClass, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// OpenglClass 메시지 처리기입니다.

void OpenglClass::CreateOGL()
{
	wnd_p = (CKICT_MPDlg*)::AfxGetMainWnd();
	HWND p = wnd_p->GetSafeHwnd();
	CString classname = AfxRegisterWndClass( CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		AfxGetApp()->LoadStandardCursor( IDC_ARROW ),
		(HBRUSH)::GetStockObject( BLACK_BRUSH),	NULL);
	//CreateEx(0, classname, _T("OpenGl"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CRect(0,0,800,800), 0, 0);
	CreateEx(0, classname, _T("OpenGl"), WS_CHILD | WS_VISIBLE, wnd_p->rect_pic_xy, CWnd::FromHandle(p), 0);
	/*	this->wx=0;	this->wy=0;	this->wz=0;	*/
}

void OpenglClass::OnPaint()
{		
	ValidateRect(NULL);
	CPaintDC dc(this); // device context for painting
	HDC hdc=GetDC()->m_hDC;

	CWnd::OnPaint(); // invalidate할 때 깜빡거림 

	draw();
	SwapBuffers(hdc);
}

void OpenglClass::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);  //처음, 그리고 윈도우 변경될때 호출
	glViewport(0,0,(GLsizei)cx,(GLsizei)cy);

	float ratio = (float) cy/cx;
	
	WinXsize = cx;
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	float AmbientColor[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	float DiffuseColor[] = { 0.05f, 0.05f, 0.05f, 0.0f };
	float SpecularColor[] = { 0.2f, 0.2f, 0.2f, 0.0f };
	float Position[] = {-30000, 30000, 30000, 1.0f };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(GLdouble)cx/(GLdouble)cy,1.0,200000);
	//glFrustum(-1, 1, -1, 1, 3.0,20.0);	
	glMatrixMode(GL_MODELVIEW);
	}

void OpenglClass::draw()
{
	//HDC hdc=GetDC()->m_hDC;
	
	glClearColor(0.5, 0.5, 0.5, 0);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	glPushMatrix();

		glLoadIdentity();	
		gluLookAt(0,0,100,0,0,0,0,1,0);

		static char str0[100]={0,};
		glColor3f(1,1,0);
		if(abs(wx)<=15000 && abs(wy)<=15000 && abs(wz)<=15000)
		{
			sprintf_s(str0,"X: %d, Y: %d, Z: %d",(int)wx,(int)wy,(int)wz);
			glRasterPos3f(-5,5,87); 
			for(int k=0;k<strlen(str0);k++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str0[k]);

			sprintf_s(str0, "Distance(m): %.3f", sqrt(wx*wx + wy*wy + wz*wz) / 1000);
			glRasterPos3f(-5,4.6,87); 
			for(int k=0;k<strlen(str0);k++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str0[k]);

		}	
		//glFlush();
	glPopMatrix();
	*/
	
	glLoadIdentity();	
	gluLookAt(pos[0], pos[1], pos[2], lookAt[0], lookAt[1], lookAt[2], upVec[0], upVec[1], upVec[2]);
	
	glScalef(scale,scale,scale);
	GLUquadricObj* cyl;
    cyl= gluNewQuadric();

	GLfloat m[4][4];		
	m[0][0] = rotationMat[0][0];
	m[0][1] = rotationMat[0][1];
	m[0][2] = rotationMat[0][2];

	m[1][0] = rotationMat[1][0];
	m[1][1] = rotationMat[1][1];
	m[1][2] = rotationMat[1][2];

	m[2][0] = rotationMat[2][0];
	m[2][1] = rotationMat[2][1];
	m[2][2] = rotationMat[2][2];

	m[0][3] = m[1][3] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;

	glMultMatrixf(&m[0][0]);

//////////////////////////////////////////////////////////////////////////
	//gluQuadricDrawStyle(cyl, GLU_FILL);
	gluQuadricOrientation(cyl, GLU_OUTSIDE);


	glDisable(GL_LIGHTING);
	glPushMatrix();
		glRotatef(180, 0, 0, 1);
		glRotatef(90, 1, 0, 0); //X Y Z 일치
		glLineWidth(1.0);		
		glBegin(GL_LINES);  
			glColor3f(1,0,0);
			glVertex3f(0,0,0);
			glVertex3f(10000,0,0);

			glColor3f(0,1,0);
			glVertex3f(0,0,0);
			glVertex3f(0,10000,0);

			glColor3f(0,0,1);
			glVertex3f(0,0,0);
			glVertex3f(0,0,10000);
		glEnd();
		glColor3f(1,1,0); 
		gluCylinder (cyl, 3000,3050, 5, 64, 1);
		gluCylinder (cyl,6000,6050,5, 64, 1 );
		gluCylinder (cyl,9000,9050,5, 64, 1 );

		glColor3f(1,1,1); //문자색
		char str[100]={0,};
		sprintf_s(str,"3m");
		glRasterPos3f(0,3000,0); 
		for(int k=0;k<strlen(str);k++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[k]); //glut64.lib 필요

		sprintf_s(str,"6m");
		glRasterPos3f(0,6000,0); 
		for(int k=0;k<strlen(str);k++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[k]);

		sprintf_s(str,"9m");
		glRasterPos3f(0,9000,0); 
		for(int k=0;k<strlen(str);k++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[k]);

		glEnable(GL_LIGHTING);
		glRotatef(wnd_p->xsens_roll, 1, 0, 0);
		glRotatef(wnd_p->xsens_pitch, 0, 1, 0); //pitch		
		glRotatef(wnd_p->xsens_yaw, 0, 0, 1); //yaw 회전 시계방향 +
		
		glPushMatrix();
			//glColor3f(0.1,0.15,0.1); //몸체
			glColor3f(0.1, 0.1, 0.7); //몸체
			glTranslatef(0, 0, 200);
			glScaled(0.7, 1, 0.3);
			glutSolidCube(1000);			
		glPopMatrix();

		glColor3f(0.3, 0.3, 0.3);		
		glPushMatrix();
			glTranslatef(300, 300, 100);
			glRotatef(90, 0, 1, 0);			
			gluCylinder(cyl, 180, 180, 140, 64, 1); //바퀴 전 우
			glTranslatef(0, 0, 139); 
			gluDisk(cyl, 0, 180, 32, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-300, 300, 100);
			glRotatef(-90, 0, 1, 0);		
			gluCylinder(cyl, 180, 180, 140, 64, 1); //바퀴 전 우
			glTranslatef(0, 0, 139);
			gluDisk(cyl, 0, 180, 32, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(300, -300, 100);
			glRotatef(90, 0, 1, 0);
			gluCylinder(cyl, 180, 180, 140, 64, 1); //바퀴 후 우
			glTranslatef(0, 0, 139);
			gluDisk(cyl, 0, 180, 32, 1);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-300, -300, 100);
			glRotatef(-90, 0, 1, 0);
			gluCylinder(cyl, 180, 180, 140, 64, 1); //바퀴 후 우
			glTranslatef(0, 0, 139);
			gluDisk(cyl, 0, 180, 32, 1);
		glPopMatrix();
				
		glPushMatrix(); //저조도카메라 기둥
			glTranslatef(0, 280, 200);	
			glColor3f(0.3, 0.3, 0.3);
			gluCylinder(cyl, 60, 60, 500, 4, 1);			
			
			glPushMatrix();			
				glTranslatef(0, 0, 500);

				glRotatef(wnd_p->rod_pan, 0, 0, -1);// 시계 방향 +
				glRotatef(wnd_p->rod_tilt, 1, 0, 0); //위로 +
				
				glColor3f(0.2, 0.2, 0.2);
				glScaled(2, 0.5, 0.5);
				glutSolidCube(250);
				glScaled(0.5, 2, 2);

				glRotatef(-90, 1, 0, 0);
				glTranslatef(150, 0, 0);
				glColor3f(0.3, 0.3, 0.1);
				gluCylinder(cyl, 70, 70, 150, 16, 1); //우 카메라

				glTranslatef(-300, 0, 0);			
				gluCylinder(cyl, 70, 70, 150, 16, 1); //좌 카메라
			
				glTranslatef(0, 0, 150);
				glColor3f(0.8, 0.8, 0.8);
				glScaled(1, 1, 0.5);
				gluSphere(cyl, 70, 16, 10); //렌즈 좌

				glTranslatef(300, 0, 0);
				gluSphere(cyl, 70, 16, 10); //렌즈 우		
			glPopMatrix();

		glPopMatrix();

		glPushMatrix(); //안테나
			glColor3f(0.9, 0.9, 0.9);
			glTranslatef(-150, -300, 300);			
			glutSolidCone(20,400,32,10); 
			glTranslatef(100,0, 0);
			glutSolidCone(20, 400, 32, 10);
			glTranslatef(100, 0, 0);
			glutSolidCone(20, 400, 32, 10);
			glTranslatef(100, 0, 0);
			glutSolidCone(20, 400, 32, 10);
		glPopMatrix();

	glPopMatrix();
}

int OpenglClass::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) // 윈도 생성되면 제일 먼저 호출
		return -1;
	InitOGL();
	return 0;
}


void OpenglClass::InitOGL()
{
	pos[0] =-60.f; //opengl 셋업
	pos[1] =70.f; //위
	pos[2] =-90.f;
	lookAt[0] = -20.0f;
	lookAt[1] = 20.0f;
	lookAt[2] = 0.0f;
	upVec[0] = 0.f;
	upVec[1] = 1.f;
	upVec[2] = 0.f;

	static PIXELFORMATDESCRIPTOR pfd =
 {
  sizeof(PIXELFORMATDESCRIPTOR),
  1,
  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
  PFD_TYPE_RGBA,
  32, // bit depth
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  16, // z-buffer depth
  0, 0, 0, 0, 0, 0, 0,
 };
	HGLRC hrc;
	HDC hdc=GetDC()->m_hDC;
	int m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	int re=SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	hrc= wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	rotationMat[0][0]=1.0;
	rotationMat[0][1]=0.0;
	rotationMat[0][2]=0.0;

	rotationMat[1][0]=0.0;
	rotationMat[1][1]=1.0;
	rotationMat[1][2]=0.0;

	rotationMat[2][0]=0.0;
	rotationMat[2][1]=0.0;
	rotationMat[2][2]=1.0;

}

void OpenglClass::LookVec(void){
	//벡터화
	lookVec[0] = lookAt[0] - pos[0];
	lookVec[1] = lookAt[1] - pos[1];
	lookVec[2] = lookAt[2] - pos[2];
	//단위벡터화
	GLfloat root = sqrt(lookVec[0]*lookVec[0] + lookVec[1]*lookVec[1] + lookVec[2]*lookVec[2]);
	lookVec[0] = lookVec[0] / root;
	lookVec[1] = lookVec[1] / root;
	lookVec[2] = lookVec[2] / root;
}

void OpenglClass::LeftVec(void){
	LookVec();
	leftVec[0] = ( upVec[1] * lookVec[2] ) - ( upVec[2] * lookVec[1] );
	leftVec[1] = ( upVec[2] * lookVec[0] ) - ( upVec[0] * lookVec[2] );
	leftVec[2] = ( upVec[0] * lookVec[1] ) - ( upVec[1] * lookVec[0] );
	//단위벡터화
	GLfloat root = sqrt(leftVec[0]*leftVec[0] + leftVec[1]*leftVec[1] + leftVec[2]*leftVec[2]);
	leftVec[0] = leftVec[0] / root;
	leftVec[1] = leftVec[1] / root;
	leftVec[2] = leftVec[2] / root;
}
void OpenglClass::rotMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point 
	R[0][0] = ((1 - cosTheta) * x * x + cosTheta);
	R[0][1] = ((1 - cosTheta) * x * y - sinTheta * z);
	R[0][2] = ((1 - cosTheta) * x * z + sinTheta * y);

	// Find the new y position for the new rotated point
	R[1][0] = ((1 - cosTheta) * x * y + sinTheta * z);
	R[1][1] = ((1 - cosTheta) * y * y + cosTheta);
	R[1][2] = ((1 - cosTheta) * y * z - sinTheta * x);

	// Find the new z position for the new rotated point
	R[2][0] = ((1 - cosTheta) * x * z - sinTheta * y);
	R[2][1] = ((1 - cosTheta) * y * z + sinTheta * x);
	R[2][2] = ((1 - cosTheta) * z * z + cosTheta);
}

void OpenglClass::OnMouseMove(UINT nFlags, CPoint point)
{
  
	GLdouble projection[16];
    GLdouble modelView[16];
    GLint viewPort[4];

    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glGetDoublev(GL_MODELVIEW_MATRIX,modelView);
    glGetIntegerv(GL_VIEWPORT,viewPort);
	/*
    GLfloat zCursor,winX,winY;
    //GLdouble wx,wy,wz;
    winX = (float)point.x;
    winY = (float)viewPort[3]-(float)point.y;
    glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zCursor); 
   // zCursor=0.5;
    if(gluUnProject(winX,winY,zCursor,modelView,projection,viewPort,&wx,&wy,&wz)==GLU_FALSE){
	    printf("실패\n");
	}
	if(!(abs(wx)<=15000 && abs(wy)<=15000 && abs(wz)<=15000)){
		wx=0;wy=0;wz=0;
	}
	*/
	//마우스 근처 점들 12cm 이내///////////////////////////////////////////
	/*
	int j=0;
	count_f=0;
	ZeroMemory(coord_f,sizeof(coord_f));
	if(wx!=0 && wy!=0 && wz!=0){
		for(int i=0;i<10000;i++){
			//for(int j=0;j<500;){
				int x,y,z;
				x=coord[i].x;
				y=coord[i].y;
				z=coord[i].z;
				int dis=sqrt((wx-x)*(wx-x)+(wy-y)*(wy-y)+(wz-z)*(wz-z));
				if(dis<120 && j<500){ //마우스 포인터와 점의 거리가 12cm 이내이면
					coord_f[j][0]=coord[i].x;
					coord_f[j][1]=coord[i].y;
					coord_f[j][2]=coord[i].z;
					j++;
				}
			//}	
		}
		count_f=j-1;
	}
	*/
	/////////////////////////////////////////////
	//Invalidate(FALSE);
	if(ml_on==true){ //마우스 왼쪽 버튼 =>>축회전
		
		float mousePreX=m_x;
		float mousePreY=-m_y;

		float mouseCurrX=point.x;
		float mouseCurrY=-point.y;

		float diffX=mouseCurrX-mousePreX;
		float diffY=mouseCurrY-mousePreY;

		if(diffX==0 && diffY==0) return;

		float rotAxisX=diffY;
		float rotAxisY=diffX;

		//normalize
		float t=sqrt(rotAxisX*rotAxisX+rotAxisY*rotAxisY);
		rotAxisX=rotAxisX/t;
		rotAxisY=rotAxisY/t;

		float angle = t/400.0;

		double x,y;
		x=rotAxisX;
		y=rotAxisY;

		float rot[3][3]=
		{{x*x+y*y*cos(angle), (1-cos(angle))*x*y  , -y*sin(angle)},
		 {(1-cos(angle))*x*y, y*y+x*x*cos(angle), x*sin(angle)},
		 {y*sin(angle)      , -x*sin(angle)     , cos(angle)}};
		
		//rotationMat=rotationMat*rot;
		float rot_t[3][3]=
		{{rotationMat[0][0]*rot[0][0]+rotationMat[0][1]*rot[1][0]+rotationMat[0][2]*rot[2][0],
		  rotationMat[0][0]*rot[0][1]+rotationMat[0][1]*rot[1][1]+rotationMat[0][2]*rot[2][1]
		 ,rotationMat[0][0]*rot[0][2]+rotationMat[0][1]*rot[1][2]+rotationMat[0][2]*rot[2][2] },

		 {rotationMat[1][0]*rot[0][0]+rotationMat[1][1]*rot[1][0]+rotationMat[1][2]*rot[2][0],
		  rotationMat[1][0]*rot[0][1]+rotationMat[1][1]*rot[1][1]+rotationMat[1][2]*rot[2][1]
		 ,rotationMat[1][0]*rot[0][2]+rotationMat[1][1]*rot[1][2]+rotationMat[1][2]*rot[2][2] },

		 {rotationMat[2][0]*rot[0][0]+rotationMat[2][1]*rot[1][0]+rotationMat[2][2]*rot[2][0],
		  rotationMat[2][0]*rot[0][1]+rotationMat[2][1]*rot[1][1]+rotationMat[2][2]*rot[2][1]
		 ,rotationMat[2][0]*rot[0][2]+rotationMat[2][1]*rot[1][2]+rotationMat[2][2]*rot[2][2]}};
		
		//memcpy(rotationMat,rot_t,sizeof(rot_t)); 
		memset(rotationMat, 0, sizeof(rotationMat));
		memcpy_s(rotationMat, sizeof(rotationMat), rot_t, sizeof(rot_t));

		m_x = point.x;
		m_y = point.y;
			
		Invalidate(FALSE);

	}
	if(mr_on==true){ //마우스 오른쪽 버튼 =>>이동
		GLfloat Angle = 0;
		GLfloat V_[3] = { 0, 0, 0 };
		GLfloat V__[3] = { 0, 0, 0 };

		//Yaw		
		LookVec();

		Angle = ( point.x - m_x ) * 0.001;
		rotMatrix(Angle, 0, 1, 0);
			
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++)
				V_[i] += R[i][j] * lookVec[j];
		}
			
		//pitch
		Angle = ( m_y - point.y ) * 0.001;
		LeftVec();

		rotMatrix(Angle, leftVec[0], leftVec[1], leftVec[2]);
			
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++)
				V__[i] += R[i][j] * V_[j];
		}
			
		for(int i = 0; i < 3; i++)
			lookAt[i] = pos[i] + V__[i];

		m_x = point.x;
		m_y = point.y;

		Invalidate(FALSE);
	}
	CWnd::OnMouseMove(nFlags, point);
}


BOOL OpenglClass::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(zDelta<0 && scale>0.02){
		scale-=0.01;
		
		Invalidate(FALSE);//draw();    휠
	}
	//if(zDelta>0 && pos[0]>0.0){
	if(zDelta>0){
		scale+=0.01;
		Invalidate(FALSE);//draw();
	}

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void OpenglClass::OnLButtonDown(UINT nFlags, CPoint point)
{
	ml_on = TRUE; 
	m_x = point.x; //마우스 왼쪽 누르면 좌표 기억
	m_y = point.y; //이거는 오픈지엘에 사용......
	//Invalidate(FALSE);
	/*
	float vec[3]={0,};
	///////////////////////////////////////// plane fitting////////////////////////////////
	if(count_f>4){ // 샘플 포인트가 5개보다 많으면
		plane_fit(coord_f,vec);
		float tmp=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
		//float na,nb,nc;
		na=vec[0]/tmp;
		nb=vec[1]/tmp;
		nc=vec[2]/tmp;

		x_axis=atan(nb/sqrt(na*na+nb*nb))*(180/PI);
		x_degree=atan(nc/nb)*(180/PI); //그릴 때 사용할 각. 회전 순서 X축->Z축
		z_axis=atan(na/sqrt(nb*nb+nc*nc))*(180/PI);

		temp.Format(L"%.6f, %.6f, %.6f",vec[0],vec[1],vec[2]);
		wx_f=wx;wy_f=wy;wz_f=wz;
		nx=vec[0];ny=vec[1];nz=vec[2];
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	*/
	CWnd::OnLButtonDown(nFlags, point);
}


void OpenglClass::OnRButtonDown(UINT nFlags, CPoint point)
{
	mr_on = TRUE; 
	m_x = point.x; //마우스 왼쪽 누르면 좌표 기억
	m_y = point.y; //이거는 오픈지엘에 사용......

	CWnd::OnRButtonDown(nFlags, point);
}


void OpenglClass::OnRButtonUp(UINT nFlags, CPoint point)
{
	mr_on = FALSE;
	CWnd::OnRButtonUp(nFlags, point);
}


void OpenglClass::OnLButtonUp(UINT nFlags, CPoint point)
{
	ml_on = FALSE;
	CWnd::OnLButtonUp(nFlags, point);
}
/*
void plane_fit(float p_plane[][3],float res[3]){ 
////////////////////////////// 면 fitting ////////////////////////////////////////
//  AX=b ATAX=ATb X=(ATA)-1 (ATb) X=(a,b,c) ,ax+by+cz=1 면의 방정식, (0,0,0)을 지나지 않는다.
	float arr_A[500][3]={0,}; // 행렬 A
	float arr_AT[3][500]={0,}; // 행렬 transpose A
	float arr_b[500]={0,}; // 벡터 b
	float arr_ATb[3]={0,}; // 벡터 ATb
	//float arr_F[3]={0,};   // 최종 X (a b c)
	
	float tk[3][3]={0,}; //임시 매트릭스
	int p_count=0; //점의 갯수
	p_count=count_f;

	for(int i=0;i<p_count;i++){
		arr_A[i][0]=p_plane[i][0];
		arr_A[i][1]=p_plane[i][1];
		arr_A[i][2]=p_plane[i][2];

		arr_AT[0][i]=p_plane[i][0];
		arr_AT[1][i]=p_plane[i][1];
		arr_AT[2][i]=p_plane[i][2];

		arr_b[i]=1;
	}
// AT*A 구하기	
	for(int i=0;i<p_count;i++){
		tk[0][0] += arr_AT[0][i]*arr_A[i][0];
		tk[0][1] += arr_AT[0][i]*arr_A[i][1];
		tk[0][2] += arr_AT[0][i]*arr_A[i][2];
		tk[1][0] += arr_AT[1][i]*arr_A[i][0];
		tk[1][1] += arr_AT[1][i]*arr_A[i][1];
		tk[1][2] += arr_AT[1][i]*arr_A[i][2];
		tk[2][0] += arr_AT[2][i]*arr_A[i][0];
		tk[2][1] += arr_AT[2][i]*arr_A[i][1];
		tk[2][2] += arr_AT[2][i]*arr_A[i][2];

		arr_ATb[0] += arr_AT[0][i];
		arr_ATb[1] += arr_AT[1][i];
		arr_ATb[2] += arr_AT[2][i];
	}
	double det3 = tk[0][0]*(tk[1][1]*tk[2][2]-tk[1][2]*tk[2][1])-tk[0][1]*(tk[1][0]*tk[2][2]-tk[1][2]*tk[2][0])+tk[0][2]*(tk[1][0]*tk[2][1]-tk[1][1]*tk[2][0]);

	float det_inv = 1/det3;

	float inv_K[3][3] = {0,};
	inv_K[0][0]= det_inv*(tk[1][1]*tk[2][2]-tk[1][2]*tk[2][1]);
	inv_K[0][1]= det_inv*(tk[0][2]*tk[2][1]-tk[0][1]*tk[2][2]);
	inv_K[0][2]= det_inv*(tk[0][1]*tk[1][2]-tk[0][2]*tk[1][1]);
	
	inv_K[1][0]= det_inv*(tk[1][2]*tk[2][0]-tk[1][0]*tk[2][2]);
	inv_K[1][1]= det_inv*(tk[0][0]*tk[2][2]-tk[0][2]*tk[2][0]);
	inv_K[1][2]= det_inv*(tk[0][2]*tk[1][0]-tk[0][0]*tk[1][2]);
	
	inv_K[2][0]= det_inv*(tk[1][0]*tk[2][1]-tk[1][1]*tk[2][0]);
	inv_K[2][1]= det_inv*(tk[0][1]*tk[2][0]-tk[0][0]*tk[2][1]);
	inv_K[2][2]= det_inv*(tk[0][0]*tk[1][1]-tk[0][1]*tk[1][0]);	

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			res[i] += inv_K[i][j]*arr_ATb[j]; //a b c
		}
	}
//	res[0]=res[0];
//	res[1]=res[1];
//	res[2]=res[2];

}
*/