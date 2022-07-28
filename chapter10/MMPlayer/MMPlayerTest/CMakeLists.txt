# CMakeList.txt: MMPlayer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

include_directories(../)

link_directories(../3rdpart/ffmpeg/lib)

# 将源代码添加到此项目的可执行文件。
add_executable (
	MMPlayerTest
	Main.cpp
	
	)

target_link_libraries(MMPlayerTest MMThread)
target_link_libraries(MMPlayerTest MMAV)
target_link_libraries(MMPlayerTest MMPlayer)

target_link_libraries(MMPlayerTest avcodec)
target_link_libraries(MMPlayerTest avdevice)
target_link_libraries(MMPlayerTest avformat)
target_link_libraries(MMPlayerTest avutil)
target_link_libraries(MMPlayerTest swresample)
target_link_libraries(MMPlayerTest swscale)

# TODO: 如有需要，请添加测试并安装目标。
