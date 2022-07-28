#include<MMPlayer/MMPlayer.h>
#include<mutex>

MMPlayerCtr::MMPlayerCtr(double _seekTime)
{
	seekTime = _seekTime;



};
MMPlayerCtr::~MMPlayerCtr()
{



};


void MMPlayerCtr::run()
{
	MMPlayerReaderThread readerThread("d://yjy/ffmpeg��������Ƶ.mp4",seekTime ,this);
	readerThread.Start();
	 
	// ��ȡ�߳�����ʱ���ʱ�� start_time
	long long startTime = MMAVTime::GetTime();

	MMAVFrame* videoFrame = nullptr;
	MMAVFrame* audioFrame = nullptr;

	long long sleepCountTime = 0;

	while (!stopflag) {
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		/*if (status==MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PAUSEING) {
			continue;
		}*/

		long long sleepTimeStart = MMAVTime::GetTime();

		while (status == MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PAUSEING) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		long long sleepTimeEnd = MMAVTime::GetTime();
		long long sleepDTime = sleepTimeEnd - sleepTimeStart;

		sleepCountTime += sleepDTime;
		

		
		// ��ȡ��ǰ��ʱ�� now_time
		long long nowTime = MMAVTime::GetTime();

		// ��ȡ����ǰʱ��Ϳ�ʼʱ��Ĳ�ֵ d_time
		long long dTime = nowTime - startTime;

		dTime = dTime - sleepCountTime;

		//	dTime����seektime dTime��λ�Ǻ��� seekTime��λ��s ���Եó���1000 Ϊ�˱��ս���ǿ������ת��

		dTime = dTime + (long long)(seekTime*1000);
		//printf("DTime: %lld\n", dTime);

		// ����Ƶ��������У���ȡһ֡��Ƶ frame_pts 
		if (videoFrame == nullptr) {
			// ����ȡһ֡����
			videoQueue.Pop(&videoFrame);
		}

		// printf("Video Queue Size: %d\n", videoQueue.Size());

		//���ж������֡�ò����ӵ� Ȼ���ڽ��������ѭ��

		if (videoFrame != nullptr) {

			if (videoFrame->GetPts() < (long long)(seekTime * 1000)) {
				delete videoFrame;
				videoFrame = nullptr;
			}
		}

		//��seekTimeǰ���֡�ӵ��Ժ�  �������֡��һ����	
		if (videoFrame != nullptr) {
			// ��� frame_pts <= d_time

			if (videoFrame->GetPts() <= dTime) {
				// ��֡��Ƶ��Ӧ���������ų���
				printf("Video Frame: %lld\n", videoFrame->GetPts());
				delete videoFrame;
				videoFrame = nullptr;
			}
			// ����
				// ��֡��Ƶ���������ŵ�ʱ��,�����������������ȥ������Ƶ
			else {

			}
		}



		// ����Ƶ��������У���ȡһ֡��Ƶ frame_pts 
		if (audioFrame == nullptr) {
			audioQueue.Pop(&audioFrame);
		}

		if (audioFrame != nullptr) {

			if (audioFrame->GetPts() < (long long)(seekTime * 1000)) {
				delete audioFrame;
				audioFrame = nullptr;
			}
		}

		if (audioFrame != nullptr) {
			// ��� frame_pts <= d_time
			if (audioFrame->GetPts() <= dTime) {
				// ��֡��Ƶ��Ӧ���������ų���
				// printf("Audio Frame\n");
				delete audioFrame;
				audioFrame = nullptr;
			}
			else {
				// ��֡��Ƶ���������ŵ�ʱ��,�������������
			}
		}
	}

	readerThread.Stop();
}




int MMPlayerCtr::GetVideoQueueSize()
{
	return videoQueue.Size();
};
int MMPlayerCtr::GetAudioQueueSize()
{
	return audioQueue.Size();
};


int MMPlayerCtr::PushFrameToVideoQueue(MMAVFrame* frame)
{
	videoQueue.Push(frame);
	return 0;
};
int MMPlayerCtr::PushFrameToAudioQueue(MMAVFrame* frame)
{
	audioQueue.Push(frame);
	return 0;
};




int MMPlayerCtr::Play()
{
	

	status = MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PLAYING;
	return 0;
};
int MMPlayerCtr::Pause()
{


	status = MMPlayerCtrStatus::MMPLAYER_CTR_STATUS_PAUSEING;
	return 0;
};
