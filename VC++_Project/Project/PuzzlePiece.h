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
    PuzzlePiece(const std::vector<std::vector<int>>& stageData, int startX, int startY, COLORREF color); // 새 생성자
    void Move(int dx, int dy);
    void Draw(HDC hdc) const;
};

PuzzlePiece* GeneratePieceFromStage(const std::vector<std::vector<int>>& stageData, COLORREF color);