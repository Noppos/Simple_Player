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
	//���н������
	//�Ӷ�����ȡ����Ҫ�����packet
	//��¼frame�ĸ��� 
	int frameCount = 0;	
	while (!stopflag) {

		std::this_thread::sleep_for(std::chrono::milliseconds(1));        //˯��ʹ���ó�cpuʹ�� ������ջ�����棩�ܹ�ʹ�õ��߳�


		//ͨ�����е�size�����ƽ����ٶ� �����������ܿ�����ڴ�  10��20 Ŀǰд���� �������ò���
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
			//����Ϊ�� ȡ����packet
			continue;
		}
		decoder->SendPacket(pkt);
		
		
		//�����ǽ���ѭ��

		while (1) {
			MMAVFrame* frame=new MMAVFrame();
			ret = decoder->ReceiveFrame(frame);
			if (ret) {
				break;
			}

			frameCount++;
			//printf("Decoder success: %d\n",frameCount);
			//std::this_thread::sleep_for(std::chrono::seconds(1));

			//ͨ��playerCtr�ľ������������frame����
			if (type==MMDecoderType::MMDECODER_TYPE_AUDIO) {
				playerCtr->PushFrameToAudioQueue(frame);
			}
			else if (type == MMDecoderType::MMDECODER_TYPE_VIDEO) {
				playerCtr->PushFrameToVideoQueue(frame);
			}

			


		}

	}




};

