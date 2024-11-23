#pragma once
#include <vector>
#include <windows.h>

struct Block {
    int x, y;         // 블록의 위치
    COLORREF color;   // 블록 색상
};

class PuzzlePiece {
public:
    std::vector<Block> blocks; // 퍼즐 조각의 블록들
    int offsetX, offsetY;      // 화면에서의 현재 위치

    PuzzlePiece(const std::vector<Block>& blocks, COLORREF color);
    void Move(int dx, int dy); // 조각을 이동
    void Draw(HDC hdc) const;  // 조각을 화면에 그림 (const로 수정)
};
