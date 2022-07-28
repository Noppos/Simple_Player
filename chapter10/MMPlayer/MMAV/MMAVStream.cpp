#include"MMAV.h"
#include"MMAVStreamPrivate.h"

MMAVStream::MMAVStream()
{
	imp = new MMAVStreamPrivate();
	//如何进行初始化环节  先创建一个parameters 默认值，然后再将 我们read frame得到的stream灌进去
	imp->codecpar = avcodec_parameters_alloc();

	

};
MMAVStream::~MMAVStream()
{
	if (imp->codecpar != nullptr) {
		avcodec_parameters_free(&imp->codecpar);
		imp->codecpar = nullptr;
	}
	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
};