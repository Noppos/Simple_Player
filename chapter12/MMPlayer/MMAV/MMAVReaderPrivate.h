#pragma once

extern"C"
{
#include"../3rdpart/ffmpeg/include/libavcodec/avcodec.h"
#include"../3rdpart/ffmpeg/include/libavformat/avformat.h"
}
class MMAVReaderPrivate
{
public:
	AVFormatContext* formatCtx = nullptr;
};