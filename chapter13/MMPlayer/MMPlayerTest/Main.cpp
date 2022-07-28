	
#include<MMPlayer/MMPlayer.h>
#include<windows.h>

/*
需要做的工作：
1.打开文件 无论是网络流还是文件  需要用实例去存放打开的流  然后对其进行处理  
2.播放
3.暂停
4.继续播放
5.停止播放
6.

*/

//获取系统当前时间戳


#include "MMPlayer/MMPlayer.h"

int main()
{
	MMPlayer player("d:/yjy/ffmpeg测试用视频.mp4");

	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail\n");
		return -1;
	}

	

	player.Play();
	printf("======================1 PLAY=====================\n");
	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));



	player.Seek(10);
	std::this_thread::sleep_for(std::chrono::seconds(2));




	player.Pause();
	printf("======================1 PAUSE====================\n");
	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));

	player.Play();
	printf("======================2 PLAY=====================\n");
	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));


	player.Pause();
	printf("======================2 PAUSE====================\n");
	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(1));


	player.Play();
	printf("======================3 PLAY=====================\n");
	//.....wait
	std::this_thread::sleep_for(std::chrono::seconds(60 * 60));


	player.Stop();

	return 0;
}