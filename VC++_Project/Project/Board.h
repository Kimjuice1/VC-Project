// Board.h
#pragma once
#include <vector>
#include <windows.h>
#include "PuzzlePiece.h"  // PuzzlePiece ���� ����

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
    bool CheckPuzzleComplete();  // ������ �ϼ��Ǿ����� Ȯ��
};
