	
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

int main()
{

	MMPlayer player("d://yjy/ffmpeg测试用视频.mp4");

	int ret = player.Open();
	if (ret) {
		printf("Player Open Fail");
		return -1;	
	}
	Sleep(1000 * 10000);
	player.Play();
	

	//wait

	player.Pause();
	//wait
	
	//wait
	player.Stop();

	player.~MMPlayer();

	return 0;
}