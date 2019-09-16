#include "Mysocket.h"
//#include "KICT_MPDlg.h" //부모
/*
void CServerSocket::OnAccept(int nErrorCode)
{
	if (Accept(m_DataSocket))
	{
		AfxMessageBox(L"Accept 실패");
		return ;
	}
	m_DataSocket.Init(this);
	AfxMessageBox(L"Accept 성공");
	return ;
}
*/
/*
void CDataSocket::OnReceive(int nErrorCode)
{
//	CKICT_MPDlg *wnd_p = (CKICT_MPDlg *)::AfxGetMainWnd();
	char receive_buf[256];
	Receive(receive_buf, sizeof(receive_buf));

	


	ZeroMemory(receive_buf, sizeof(receive_buf));	//m_DataSocket.Close();
	CSocket::OnReceive(nErrorCode);
}
*/