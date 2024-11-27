#pragma once
#include <vector>
#include <windows.h>

struct Block {
    int x, y;         // ����� ��ġ
    COLORREF color;   // ��� ����
};

class PuzzlePiece {
public:
    std::vector<Block> blocks; // ���� ������ ��ϵ�
    int offsetX, offsetY;      // ȭ�鿡���� ���� ��ġ

    PuzzlePiece(const std::vector<Block>& blocks, COLORREF color);
    PuzzlePiece(const std::vector<std::vector<int>>& stageData, int startX, int startY, COLORREF color); // �� ������
    void Move(int dx, int dy);
    void Draw(HDC hdc) const;
};

PuzzlePiece* GeneratePieceFromStage(const std::vector<std::vector<int>>& stageData, COLORREF color);