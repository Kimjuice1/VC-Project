#include "PuzzlePiece.h"

// PuzzlePiece 생성자
PuzzlePiece::PuzzlePiece(const std::vector<Block>& blocks, COLORREF color)
    : blocks(blocks), offsetX(0), offsetY(0) {
    // 모든 블록의 색상을 설정
    for (auto& block : this->blocks) {
        block.color = color;
    }
}

// PuzzlePiece 이동 메소드 (offsetX, offsetY 수정)
void PuzzlePiece::Move(int dx, int dy) {
    offsetX += dx;
    offsetY += dy;
}

// PuzzlePiece 그리기 메소드 (const로 수정)
void PuzzlePiece::Draw(HDC hdc) const {
    for (const auto& block : blocks) {  // const 객체에서 'blocks' 접근
        RECT rect = {
            (block.x + offsetX) * 30,
            (block.y + offsetY) * 30,
            (block.x + offsetX + 1) * 30,
            (block.y + offsetY + 1) * 30
        };
        HBRUSH hBrush = CreateSolidBrush(block.color);
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }
}
