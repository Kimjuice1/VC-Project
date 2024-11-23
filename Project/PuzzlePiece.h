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
    void Move(int dx, int dy); // ������ �̵�
    void Draw(HDC hdc) const;  // ������ ȭ�鿡 �׸� (const�� ����)
};
