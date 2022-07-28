#include<MMPlayer\MMPlayer.h>

MMPlayerDecoderThread::MMPlayerDecoderThread()
{
	decoder = new MMAVDecoder();


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
		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			//队列为空 取不到packet
			continue;
		}
		decoder->SendPacket(pkt);
		
		while (1) {
			MMAVFrame frame;
			ret = decoder->ReceiveFrame(&frame);
			if (ret) {
				break;
			}

			frameCount++;
			printf("Decoder success: %d\n",frameCount);
			std::this_thread::sleep_for(std::chrono::seconds(1));

			
		}

	}




};

