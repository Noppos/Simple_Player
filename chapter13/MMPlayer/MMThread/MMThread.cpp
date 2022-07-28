#include "MMThread.h"
#include <thread>

int MMThread::Start()
{
	if (t == nullptr) {
		stopflag = 0;
		t = new std::thread(&MMThread::run, this);
	}
	return 0;
}

int MMThread::Stop()
{

	if (t != nullptr) {
		 
		stopflag = 1;	

		t->join();                    //���� һֱ�ȵ�threadִ�н���  ����һֱ���߳�ִ����ϣ�������ϣ���ȥdelete
		 
		delete t;
		t = nullptr;
	};

	return 0;
};