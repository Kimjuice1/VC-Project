#pragma once
#include <vector>
#include <windows.h>
#include "PuzzlePiece.h"

extern std::vector<std::vector<int>> stageBoards[];

// currentStage ���� ���� ����
extern int currentStage;

class Board {
public:
    int rows, cols;  // ���� ũ��
    std::vector<std::vector<COLORREF>> grid;  // ������ �� ĭ�� ���� ����
    std::vector<PuzzlePiece> pieces;  // ���� ������ �����ϴ� ����

    Board(int rows, int cols);
    void Draw(HDC hdc);  // ���� �׸���
    void GenerateRandomPuzzle(int stage);  // ���� ���� ����
    void FixPiece(const PuzzlePiece& piece);  // ���� ���� ����
    bool CheckFit(const PuzzlePiece& piece);  // ���� ������ �´��� Ȯ��
    bool CheckPuzzleComplete();
};