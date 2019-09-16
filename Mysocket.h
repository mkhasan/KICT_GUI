#include "afxsock.h"

//extern int UM_ACCEPT;
//extern int UM_DATARECEIVE;

/*
class CServerSocket : public CSocket
{
public:
	void Init(CWnd *pWnd, int nPortNum){
		int res;
		m_pWnd = pWnd;
		res = Create(nPortNum);
		res = Listen();
	}
	virtual void OnAccept(int nErrorCode); //{		m_pWnd->SendMessage(UM_ACCEPT);		CSocket::OnAccept(nErrorCode);	}

protected:
	CWnd *m_pWnd;
};
*/
class CDataSocket : public CSocket //CAsyncSocket го╦И OnReceive ╬х╣й ?
{
public:
	void Init(CWnd *pWnd){ //
		m_pWnd = pWnd;

	}
	//virtual void OnReceive(int nErrorCode);// {		m_pWnd->SendMessage(UM_DATARECEIVE);		CSocket::OnReceive(nErrorCode);	}
	
	//char receive_buf[1024];
	//char send_buf[1024];

protected:
	CWnd *m_pWnd;
	//CKICT_MPDlg *wnd_p;
};
