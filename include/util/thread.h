//	Copyright (c) 2008-2009, Inc, ���ڿƼ���Ȩ����.
//
//	�ļ��� : uithread.h.h
//	��  �� : ��װ�̶߳����Զ�������������������
//
//	��  �� : no
//	
//	��  �� : 1.0
//	��  �� : ����
//	��  �� : 2008-08-10

// �޸ļ�¼ ==================================================================
// ����				����			�汾		����
// 
// ===========================================================================

# ifndef _UITHREAD_H_
# define _UITHREAD_H_

#include <suicore/uiobject.h>
#include <suicore/uilocker.h>

namespace suic {

class ThreadControl : public RefObject
{
public:

    /*
     * ���캯��Ĭ�ϵõ���ǰ�̣߳����ǲ��ܵ���join��detach
     */
    ThreadControl();

#ifdef __OS_WIN32
    ThreadControl(HANDLE, DWORD);
#else
    explicit ThreadControl(pthread_t);
#endif

    /*
     * ��  ��: �ж������߳��Ƿ���ȣ��˺���ֻ�����߳���Чʱ���ò�������
     * ��  ��: ��
     * ����ֵ: ��
     * ��  ��: ��
     */
    bool operator==(const ThreadControl&) const;
    bool operator!=(const ThreadControl&) const;

    /*
     * ��  ��: �ȴ�ֱ���߳�ִ�н���
     * ��  ��: ��
     * ����ֵ: ��
     * ��  ��: ��
     */
    void join();

    /*
     * ��  ��: �ر��̣߳��˺�����joinֻ�ܱ�����һ�Σ��ٴε��ÿ��ܻ�����δ����Ĵ���
     * ��  ��: ��
     * ����ֵ: ��
     * ��  ��: ��
     */
    void detach();

    /*-
     * �߳�ID
     */
#ifdef __OS_WIN32
    typedef DWORD ID;
#else
    typedef pthread_t ID;
#endif 
    ID id() const;

    static void sleep(const Int32&);
    static void yield();

private:

#ifdef __OS_WIN32
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;
    bool _detachable;
#endif
};

class Thread : virtual public RefObject
{
public:

    Thread();
    virtual ~Thread();

    virtual void Run() = 0;

    ThreadControl Start(Int32 = 0);
    ThreadControl GetThreadControl() const;

    bool operator==(const Thread&) const;
    bool operator!=(const Thread&) const;
    bool operator<(const Thread&) const;

    //
    // ���һ���߳��Ƿ���������
    //
    bool IsAlive() const;

    void Clear();
    void Join();

    static void Sleep(const Int32&);
    static void YieldThr();
    static Uint32 CurrentThreadId();

public:

    void _Done();

protected:

    Mutex _stateMutex;
    bool _started;
    bool _running;

#ifdef __OS_WIN32
    HANDLE _handle;
    DWORD  _id;
#else
    pthread_t _thread;
#endif

private:

    Thread(const Thread&);
    void operator=(const Thread&); 
};

typedef Shared<Thread> ThreadPtr;

}

# endif