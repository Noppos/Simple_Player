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

		//TODO 初始化解码器
		while (!stopflag)
		{
			MMAVPacket* pkt = new MMAVPacket();
			int ret = reader.Read(pkt);
			if (ret) {
				delete pkt;
				pkt = nullptr;
				break;
			}

			//将packet放入缓存  从缓存中取到 然后解码 使得播放时比较流畅

			printf("Read Packet Success!\n");



			delete pkt;
			pkt = nullptr;
		}
	
	reader.Close();	




};