	
#include<MMPlayer/MMPlayer.h>
#include<windows.h>

/*
��Ҫ���Ĺ�����
1.���ļ� �����������������ļ�  ��Ҫ��ʵ��ȥ��Ŵ򿪵���  Ȼ�������д���  
2.����
3.��ͣ
4.��������
5.ֹͣ����
6.

*/

//��ȡϵͳ��ǰʱ���


#include "MMPlayer/MMPlayer.h"

int main()
{
	MMPlayer player("d:/yjy/ffmpeg��������Ƶ.mp4");

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