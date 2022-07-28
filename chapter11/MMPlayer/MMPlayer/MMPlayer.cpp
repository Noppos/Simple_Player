#include "MMPlayer.h"

MMPlayer::MMPlayer(std::string _path)
{
	path = _path;



};

MMPlayer::~MMPlayer()
{



};


int MMPlayer::Open()
{
	/*首先为了防止open被卡住 所以得新建1个线程。在线程里面打开这个流  外面调用stop函数的时候 把这个线程关闭即可*/
	//先启动线程
	if (readerThread == nullptr) {
		readerThread = new MMPlayerReaderThread(path);
		readerThread->Start();
		return 0;
	}
	return -1;
};


int MMPlayer::Play()
{


	return 0;
};
int MMPlayer::Stop()
{
	if(readerThread != nullptr){
		readerThread->Stop();
		delete readerThread;
		readerThread = nullptr;
		return 0;
	}
	return -1;
};



int MMPlayer::Pause()
{

	return 0;
};

int MMPlayer::Seek(double time)
{


	return 0;
};

