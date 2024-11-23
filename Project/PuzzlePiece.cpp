#include "PuzzlePiece.h"

// PuzzlePiece ������
PuzzlePiece::PuzzlePiece(const std::vector<Block>& blocks, COLORREF color)
    : blocks(blocks), offsetX(0), offsetY(0) {
    // ��� ����� ������ ����
    for (auto& block : this->blocks) {
        block.color = color;
    }
}

// PuzzlePiece �̵� �޼ҵ� (offsetX, offsetY ����)
void PuzzlePiece::Move(int dx, int dy) {
    offsetX += dx;
    offsetY += dy;
}

// PuzzlePiece �׸��� �޼ҵ� (const�� ����)
void PuzzlePiece::Draw(HDC hdc) const {
    for (const auto& block : blocks) {  // const ��ü���� 'blocks' ����
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
