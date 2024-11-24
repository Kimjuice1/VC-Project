#pragma once
#include <windows.h>
#include "Board.h"

class PuzzlePopup {
public:
    Board* board;
    int rows, cols;

    PuzzlePopup(int rows, int cols);
    void ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage);  // stage �߰�
    void GenerateExamplePuzzle();  // ���� ���� ���� �Լ� �߰�
};
