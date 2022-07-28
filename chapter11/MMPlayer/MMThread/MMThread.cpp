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

		t->join();                    //阻塞 一直等到thread执行结束  就是一直到线程执行完毕（播放完毕）再去delete
		 
		delete t;
		t = nullptr;
	};

	return 0;
};