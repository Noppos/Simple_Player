	
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

int main()
{

	MMPlayer player("d://yjy/ffmpeg��������Ƶ.mp4");

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