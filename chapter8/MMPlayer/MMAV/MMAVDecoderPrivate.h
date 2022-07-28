#pragma once

extern"C"
{
#include"../3rdpart/FFmpeg/include/libavcodec/avcodec.h"
#include"../3rdpart/FFmpeg/include/libavformat/avformat.h"
}

class MMAVDecoderPrivate
{
public:
	AVCodecContext* codecContext = nullptr;
};