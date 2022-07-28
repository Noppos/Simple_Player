#include<MMPlayer\MMPlayer.h>
#include<MMAV\MMAV.h>
#include<MMQueue\MMQueue.h>
#include<chrono>
MMPlayerReaderThread::MMPlayerReaderThread(std::string _path, MMPlayerCtr* _playerCtr)
{
	path = _path;
	playerCtr = _playerCtr;



};


MMPlayerReaderThread::~MMPlayerReaderThread()
{






};


void MMPlayerReaderThread::run()
{
	MMAVReader reader;
	int ret = reader.Open(path.c_str());
	if (ret) {
		//printf("Open path:%s  Fail! ",path.c_str());
		return;
	}

		int videoStreamIndex = reader.GetVideoStreamIndex();
		int audioStreamIndex = reader.GetAudioStreamIndex();

		//TODO 初始化解码器  音频和视频
		MMPlayerDecoderThread* videoDecoderThread = new MMPlayerDecoderThread(playerCtr, MMDecoderType::MMDECODER_TYPE_VIDEO);
		MMPlayerDecoderThread* audioDecoderThread = new MMPlayerDecoderThread(playerCtr, MMDecoderType::MMDECODER_TYPE_AUDIO);
		
		MMAVStream videoStream;
		MMAVStream audioStream;
		
		reader.getStream(&videoStream, videoStreamIndex);
		reader.getStream(&audioStream, audioStreamIndex);
		
		videoDecoderThread->Init(&videoStream);
		audioDecoderThread->Init(&audioStream);
		
		videoDecoderThread->Start();
		audioDecoderThread->Start();


		while (!stopflag)
		{
			//先判断 队列中是不是多余5个packet  多余就进行自旋状态
			if (videoDecoderThread->GetPacketQueueSize() > 5 && audioDecoderThread->GetPacketQueueSize() > 5) {
				continue;
			}
			

			MMAVPacket* pkt = new MMAVPacket();
			int ret = reader.Read(pkt);
			if (ret) {
				delete pkt;
				pkt = nullptr;
				break;
			}
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//printf("Read Packet Success!\n");
			//将packet放入缓存  从缓存中取到 然后解码 使得播放时比较流畅
			//区分packet 是音频流还是视频流

			if (pkt->GetIndex() == videoStreamIndex) {
				videoDecoderThread->PutPacket(pkt);

			}

			if (pkt->GetIndex() == audioStreamIndex) {
				audioDecoderThread->PutPacket(pkt);
			}

			


			
		}
		//删掉new的audio和video

		videoDecoderThread->Stop();
		audioDecoderThread->Stop();


	reader.Close();	




};