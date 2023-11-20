﻿#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// ユーザー定義の構造体
typedef struct {
	int* addr;  // ダイナミック配列の先頭アドレス
	int num;    // ダイナミック配列の要素数
};

// my_array を要素数nで初期化する
void initialize(my_array* ar, int n)
{
	if (ar == NULL) return;// NULLチェック

	if (n <= 0) { // 非正の値が来たら、とりあえず空にする
		ar->num = 0;
		ar->addr = NULL;
		return;
	}

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	// 確保できなかったら要素数は0とする
	if (ar->addr == NULL) ar->num = 0;
}

// my_array を解放する
void release(my_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// my_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(my_array* ar, int n)
{
	if (ar == NULL) return;  // NULL チェック

	if (n < 0) n = 0; // 非正の値が来たら、とりあえず空にする

	// 新しい領域を確保
	int* newAddr = (int*)malloc(sizeof(int) * n);

	if (newAddr == NULL) { // 確保できなかったら要素数は0とする
		ar->num = 0;
	}
	else {
		// 要素数が縮小される場合、元のデータをコピー
		int minSize = (n < ar->num) ? n : ar->num;
		for (int i = 0; i < minSize; ++i) {
			newAddr[i] = ar->addr[i];
		}

		// 古い領域を解放
		free(ar->addr);

		// 新しい領域を設定
		ar->addr = newAddr;
		ar->num = n;
	}
}

// my_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(my_array* ar, int index, int val)
{
	// ToOo:配列の要素を変更しよう！
	if (ar == NULL || index < 0 || index >= ar->num) 
		return false;

	ar->addr[index] = val;
	return true;
	}
	

// my_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const my_array* ar, int index)
{
	// ToOo:要素を所得して、indexがおかしかったら0を返そう
	if(ar == NULL || index < 0 || index >= ar->num) return 0; 

	return ar->addr[index];
}


// my_array の要素数を取得する
int size(const my_array* ar)
{
	// ToOo: 配列の要素数を返そう
	if (ar == NULL) return 0;

	return ar->num;
}