#pragma once

class MMAVPacketPrivate;
class MMAVStream;
class MMAVFrame;
class MMAVPacket
{
public:
	MMAVPacket();
	~MMAVPacket();

	int GetIndex();
public:
	MMAVPacketPrivate* imp = nullptr;
};

class MMAVReaderPrivate;

class MMAVReader
{
public:
	MMAVReader();
	~MMAVReader();

	int Open(const char* path);

	//chapter8内容
	//有多少AVStream
	int getStreamCount();      
	//得到Stream
	int getStream(MMAVStream* stream,int streamId);
	//为止
	int GetVideoStreamIndex();

	int GetAudioStreamIndex();



	int Close();

	int Read(MMAVPacket* packet);

private:
	MMAVReaderPrivate* imp = nullptr;
	
};
class MMAVStreamPrivate;
class MMAVStream 
{
public:
	MMAVStream();
	~MMAVStream();
public:
	int streamIndex = -1;
	MMAVStreamPrivate* imp = nullptr;

//private:
//	int streamIndex = -1;
//	
};


class MMAVDecoderPrivate;

class MMAVDecoder
{
public:
	//构造函数和析构函数
	MMAVDecoder();
	~MMAVDecoder();

	

	int Init(MMAVStream *stream);

	int SendPacket(MMAVPacket *pkt);
	int ReceiveFrame(MMAVFrame* frame);

	int Close();
	
public: 
	MMAVDecoderPrivate* imp = nullptr;
	
private:
	//MMAVDecoderPrivate* imp = nullptr;
};

class MMAVFramePrivate;

class MMAVFrame
{
public:
	MMAVFrame();
	~MMAVFrame();

	int VideoPrint();
	int AudioPrint();

	int GetW();
	int GetH();

	int GetY(unsigned char* y);
	int GetU(unsigned char* u);
	int GetV(unsigned char* v);
public:
	MMAVFramePrivate* imp = nullptr;

};
