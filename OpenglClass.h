#pragma once

// OpenglClass
#include "opengl\gl.h" 
#include "opengl\glu.h"
#include "opengl\glut.h"
#include "KICT_MPDlg.h"

class OpenglClass : public CWnd
{
	DECLARE_DYNAMIC(OpenglClass)

public:
	OpenglClass();
	virtual ~OpenglClass();

	void CreateOGL();
	void draw();
	void InitOGL();
	void LookVec(void);
	void LeftVec(void);
	void rotMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	bool ml_on; //왼쪽 버튼이 눌러졌는지 -> 회전
	bool mr_on; //오른쪽                 -> 이동
	GLfloat scale;

	float rotationMat[3][3];

	float WinXsize;

	GLfloat m_x;
	GLfloat m_y;
	GLfloat R[3][3];
	//카메라 변수
	GLfloat pos[3];
	GLfloat lookAt[3];
	GLfloat upVec[3];
	GLfloat lookVec[3];
	GLfloat leftVec[3];
	//float nx,ny,nz;
	//GLdouble wx,wy,wz;

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CKICT_MPDlg *wnd_p;
	//float body_yaw;
};


