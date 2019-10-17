#pragma once
#ifdef _DEBUG

#include <Windows.h>
#include <memory>

#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg,"%s %d�s��\0",__FILE__,__LINE__);\
	MessageBox(0,ast_msg,"���ĕ\��",MB_OK);\
	}

#define TRACE(fmt, ...) printf(fmt,__VA_ARGS__);

// ����

class _DebugConOut
{
public:
	static _DebugConOut &GetInstance(void)
	{
		return *_sInstance;
	}

private:
	/* �֐��I�u�W�F�N�g */
	struct _DebugConOutDeleter	// ������ذ��
	{
		void operator()(_DebugConOut* _debugConOut)const
		{
			delete _debugConOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter>_sInstance;
};

#else
#define AST();
#define TRACE(fmt,...)
#endif // _DEBUG