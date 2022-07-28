#include "MMAV.h"

#include "MMAVReaderPrivate.h"
#include "MMAVPacketPrivate.h"
#include "MMAVDecoderPrivate.h"
#include"MMAVStreamPrivate.h"

MMAVReader::MMAVReader()
{
	imp = new MMAVReaderPrivate();
	imp->formatCtx = avformat_alloc_context();
}


MMAVReader::~MMAVReader()
{
	if (imp->formatCtx != nullptr) {
		avformat_free_context(imp->formatCtx);
		imp->formatCtx = nullptr;
	}

	if (imp != nullptr) {
		delete imp;
		imp = nullptr;
	}
}

int MMAVReader::Open(const char* path)
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = avformat_open_input(&imp->formatCtx, path, nullptr, nullptr);

	if (!ret) {
		avformat_find_stream_info(imp->formatCtx, nullptr);
	}

	return ret;
}






int MMAVReader::getStreamCount()
{
	return imp->formatCtx->nb_streams;
};

int MMAVReader::getStream(MMAVStream* avStream,int streamId)
{
	AVStream* ffmpegStream = imp->formatCtx->streams[streamId];
	//将流中的参数导入到函数中  index和codecpar（原先的codec参数）
	//将流中的时基信息导入到创建的对象中
	avStream->timebaseNum = ffmpegStream->time_base.num;
	avStream->timebaseDen = ffmpegStream->time_base.den;

	avStream->streamIndex = ffmpegStream->index;	


	avcodec_parameters_copy(avStream->imp->codecpar, ffmpegStream->codecpar);

	return 0;
};


int MMAVReader::GetVideoStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_VIDEO,-1,-1,NULL,NULL);
};

int MMAVReader::GetAudioStreamIndex()
{
	return av_find_best_stream(imp->formatCtx, AVMediaType::AVMEDIA_TYPE_AUDIO, -1, -1, NULL, NULL);
};

int MMAVReader::Seek(double time)
{

	/*
	1.寻找到 举例目标时间最近的I帧
	*/
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int64_t timestamp = (int64_t)time*AV_TIME_BASE;
	av_seek_frame(imp->formatCtx,-1, timestamp,AVSEEK_FLAG_BACKWARD);

	/*
	2.清空解码器中 seek之前的数据
	*/






	/*
	3.重置playerCtr中，starttime等关键时间
	*/

	 





	return 0;
};




int MMAVReader::Close()
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	avformat_close_input(&imp->formatCtx);
	return 0;
}

int MMAVReader::Read(MMAVPacket* packet)           //成功读取一帧以后  将时间戳赋值进来
{
	if (imp->formatCtx == nullptr) {
		return -1;
	}
	int ret = av_read_frame(imp->formatCtx, packet->imp->pkt);


	return ret;
}