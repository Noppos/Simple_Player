#include"MMAV.h"
#include"MMAVStreamPrivate.h"

MMAVStream::MMAVStream()
{
	imp = new MMAVStreamPrivate();
	//��ν��г�ʼ������  �ȴ���һ��parameters Ĭ��ֵ��Ȼ���ٽ� ����read frame�õ���stream���ȥ
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