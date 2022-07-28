cmake_minimum_required (VERSION 3.8)

include_directories(../3rdpart/ffmpeg/include)

add_library(
	MMAV
	MMAVReader.cpp
	MMAVPacket.cpp
	MMAVStream.cpp
	MMAVFrame.cpp
	MMAVDecoder.cpp	
	MMAVDecoder.cpp
	MMAVDecoderPrivate.h 
	MMAVStreamPrivate.h 
	MMAVFrame.cpp 
	MMAVFramePrivate.h
	MMAVTime.cpp
	)