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
	//���н������
	//�Ӷ�����ȡ����Ҫ�����packet
	//��¼frame�ĸ��� 
	int frameCount = 0;	
	while (!stopflag) {
		MMAVPacket* pkt = nullptr;
		int ret = packetQueue.Pop(&pkt);
		if (ret) {
			//����Ϊ�� ȡ����packet
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

