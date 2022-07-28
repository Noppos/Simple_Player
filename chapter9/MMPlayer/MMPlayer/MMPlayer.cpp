// MMPlayer.cpp: 定义应用程序的入口点。
//
#include <thread>
#include <chrono>
#include "MMThread/MMThread.h"
#include<vector>
using namespace std;

int a;

void threadFunction(int i) {
	printf("Thread Function: %d\n", i);
}

void threadFun(int threadIndex) {
	for (int i = 0; i < 1000;i++) {
		printf("Thread: %d, index: %d\n", threadIndex, i);
	}
}

int main2()
{
	// std::thread t(threadFunction, 10);
	// t.join();
	// t.detach();

	// t.joinable();

	std::thread t1(threadFun, 1);
	std::thread t2(threadFun, 2);

	t1.join();
	t2.join();

	return 0;
}






class MyMMThread : public MMThread
{
private:
	int a = 0;
public:
	MyMMThread(int _a)
	{
		a = _a;
	}

	virtual void run()
	{
		printf("MyMMThread %d\n", a);
	}
};

int main_thread()
{
	MyMMThread t(10);
	t.Start();

	std::this_thread::sleep_for(std::chrono::seconds(2));

	return 0;
}


#include "MMAV/MMAV.h"
#include"MMQueue\MMQueue.h"
#include"mutex"
int main() {
	MMQueue<MMAVPacket> packetQueue;
	MMAVReader reader;
	int ret = reader.Open("d://yjy/ffmpeg测试用视频.mp4");
	if (ret) {
		printf("Open File Fail!!!\n");
		return -1;
	}
	
	int videoStreamIndex = reader.GetVideoStreamIndex();
	int audioStreamIndex = reader.GetAudioStreamIndex();

	printf("videoIndex:%d\n", videoStreamIndex);
	printf("audioIndex:%d\n", audioStreamIndex);
	//vector是一个顺序动态数组，拿来存放  MMAVDecoder* 正好
	std::vector<MMAVDecoder*>DecoderList;


	int streamcount = reader.getStreamCount();
	MMAVStream avStream;
	for (int i = 0 ;i < streamcount; i++) {
		reader.getStream(&avStream, i);
		printf("StreamIndex:%d\n",avStream.streamIndex);
		                                                                //初始化编码器 decoder

		MMAVDecoder* decoder = new MMAVDecoder();                     //创建对象 并且设置指针指向它

		int ret=decoder->Init(&avStream);
		if (ret) {
			printf("initialization decoder fail");
		};
		DecoderList.push_back(decoder);
	};
	                                                                   //用解码器对于我们读入的packet进行send和receive
		FILE* f = fopen("d://yjy/ffmpeg测试视频.yuv", "wb");

	while (1) {
		MMAVPacket* pkt= new MMAVPacket();
		ret = reader.Read(pkt);
		if (ret) {
			break;
		}

		packetQueue.Push(pkt);





		int Stream_Index = pkt->GetIndex(); 
		MMAVDecoder* decoder = DecoderList[Stream_Index];

		int ret=decoder->SendPacket(pkt);	
		if (ret) {
			continue;
		}
		else
		{
			while (1) {
				MMAVFrame frame;
				ret = decoder->ReceiveFrame(&frame);
				if (ret) {
					break;
				}
				//receive success!
				if (Stream_Index == videoStreamIndex) {
//					frame.VideoPrint();

					int width = frame.GetW();
					int height = frame.GetH();

					unsigned char* y = (unsigned char*)malloc(width * height);
					unsigned char* u = (unsigned char*)malloc(width / 2 * height / 2);
					unsigned char* v = (unsigned char*)malloc(width / 2 * height / 2);

					frame.GetY(y);
					frame.GetU(u);
					frame.GetV(v);

					fwrite(y, width * height, 1, f);
					fwrite(u, width / 2 * height / 2, 1, f);
					fwrite(v, width / 2 * height / 2, 1, f);

					free(y);
					free(u);
					free(v);
				}


				if (Stream_Index == audioStreamIndex) {
					frame.AudioPrint();


				}

			}
		}

		//读不到帧的时候  解码器里面还有几帧  两个解码器 需要都对解码器读帧  参数为nullptr时 读出所有解码器


		for (int i = 0;i < DecoderList.size();i++) {
			MMAVDecoder* decoder = DecoderList[i];
			decoder->SendPacket(nullptr);
		};	

		while (1) {
			MMAVFrame frame;
			ret = decoder->ReceiveFrame(&frame);
			if (ret) {
				break;
			};
		};
			//receive success!
		//printf("Read Packet Success\n");
	}

	//清空队列 同时清掉创建的pkt      为了线程安全  加上线程锁
	while (packetQueue.Size() > 0 )
	{
		MMAVPacket* pkt = nullptr;
		packetQueue.Pop(&pkt);
		printf("packetQueue.Size():%d\n", packetQueue.Size()); 
		if (pkt != nullptr) {
			delete pkt; 
		}

		


	}



	reader.Close();

	for (int i = 0;i < DecoderList.size();i++) {
		MMAVDecoder* decoder = DecoderList[i];
		decoder->Close();
		delete decoder;
	}
	DecoderList.clear();
	

	fclose(f);

	return 0;
}
