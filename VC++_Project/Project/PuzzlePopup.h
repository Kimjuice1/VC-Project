#pragma once
#include <windows.h>
#include "Board.h"

class PuzzlePopup {
public:
    Board* board;
    int rows, cols;

    PuzzlePopup(int rows, int cols);
    void ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage);  // stage 추가
    void GenerateExamplePuzzle();  // 예시 퍼즐 생성 함수 추가
};
