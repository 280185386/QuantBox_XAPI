#pragma once
#include "MsgQueue.h"

// ��Ҫ��zmq��czmq��Ŀ¼��Additional Include Directories�����
#include "zmq.h"
#include "czmq.h"

#ifdef _WIN64
#else
#pragma comment(lib, "../include/ZeroMQ/x86/czmq.lib")
#endif

class DLL_PUBLIC CRemoteQueue :
	public CMsgQueue
{
public:
	CRemoteQueue(char* address);
	~CRemoteQueue();

protected:
	virtual void RunInThread();
	virtual void Output(ResponeItem* pItem);

private:
	zctx_t*		m_ctx;
	void*		m_pubisher;

	char		m_Address[1024];
};

