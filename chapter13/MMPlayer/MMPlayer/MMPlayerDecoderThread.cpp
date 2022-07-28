#include<MMPlayer\MMPlayer.h>
#include<chrono>
MMPlayerDecoderThread::MMPlayerDecoderThread(MMPlayerCtr* _playerCtr, MMDecoderType _type)
{
	decoder = new MMAVDecoder();
	playerCtr = _playerCtr;
	type = _type;

};
MMPlayerDecoderThread::~MMPlayerDecoderThread()
{
	if (decoder != nullptr) {
		decoder -> ~MMAVDecoder();
		delete decoder;
		decoder = nullptr;
	}


}




int MMPlayerDecoderThread::Init(MMAVStream* avStream)
{
	int ret=decoder->Init(avStream);
	return ret;
};


int MMPlayerDecoderThread::PutPacket(MMAVPacket* pkt)
{
	return packetQueue.Push(pkt);
};

int MMPlayerDecoderThread::GetPacketQueueSize()
{
	return packetQueue.Size();
};







void MMPlayerDecoderThread::run()
{
	//进行解码操作
	//从队列中取出需要解码的packet
	//记录frame的个数 
	int frameCount = 0;	
	while (!stopflag) {

		std::this_thread::sleep_for(std::chrono::milliseconds(1));        //睡眠使得让出cpu使用 加锁推栈（后面）能够使用到线程


		//通过队列的size来控制解码速度 如果解码过快会很快撑满内存  10与20 目前写死了 可以设置参数
		if (type == MMDecoderType::MMDECODER_TYPE_AUDIO) {
			if (playerCtr->GetAudioQueueSize() > 10) {
				continue;
			}
		}
		else if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
			if (playerCtr->GetVideoQueueSize() > 20) {
				continue;
			}
		}


 		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			//队列为空 取不到packet
			continue;
		}
		decoder->SendPacket(pkt);
		
		
		//下面是解码循环

		while (1) {
			MMAVFrame* frame=new MMAVFrame();
			ret = decoder->ReceiveFrame(frame);
			if (ret) {
				break;
			}

			frameCount++;
			//printf("Decoder success: %d\n",frameCount);
			//std::this_thread::sleep_for(std::chrono::seconds(1));

			//通过playerCtr的句柄，向其塞入frame数据
			if (type==MMDecoderType::MMDECODER_TYPE_AUDIO) {
				playerCtr->PushFrameToAudioQueue(frame);
			}
			else if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
				playerCtr->PushFrameToVideoQueue(frame);
			}

			


		}

	}




};

