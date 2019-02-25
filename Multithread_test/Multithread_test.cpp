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

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
