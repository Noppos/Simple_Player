#include<MMPlayer\MMPlayer.h>
#include<MMAV\MMAV.h>

MMPlayerReaderThread::MMPlayerReaderThread(std::string _path)
{
	path = _path;




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

		//TODO ��ʼ��������
		while (!stopflag)
		{
			MMAVPacket* pkt = new MMAVPacket();
			int ret = reader.Read(pkt);
			if (ret) {
				delete pkt;
				pkt = nullptr;
				break;
			}

			//��packet���뻺��  �ӻ�����ȡ�� Ȼ����� ʹ�ò���ʱ�Ƚ�����

			printf("Read Packet Success!\n");



			delete pkt;
			pkt = nullptr;
		}
	
	reader.Close();	




};