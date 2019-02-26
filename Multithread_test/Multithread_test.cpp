// Multithread_test.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <thread>
#include<chrono>
#include<mutex>


int main()
{
	std::mutex mtx;
	int num = 0;
	volatile bool exitFlag = false;
	std::thread thr([&num, &exitFlag, &mtx] {
		while (!exitFlag) {
			std::this_thread::sleep_for(std::chrono::seconds(1));

			{
				std::lock_guard<std::mutex>lck(mtx);
				num++;
			}
		}
		std::cout << "exited thread" << std::endl;
	});

	std::cout << "Hello World!\n";
	for (int i = 0; i < 100; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//std::cout << num << std::endl;
		{
			std::lock_guard<std::mutex>lck(mtx);
			std::cout << num << std::endl;
		}
	}
	exitFlag = true;
	thr.join();
	std::cout << "finished" << std::endl;
}

