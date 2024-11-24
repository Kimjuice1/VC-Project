#include "Board.h"
#include "PuzzlePiece.h"
#include <cstdlib>
#include <ctime>
#include <vector>

Board::Board(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<COLORREF>(cols, RGB(255, 255, 255))) {
    srand((unsigned int)time(nullptr));  // ���� �õ� �ʱ�ȭ
}

// ���� ������ ���� �״�� ����


void Board::GenerateRandomPuzzle(int stage) {
    pieces.clear();  // ���� ���� �������� �ʱ�ȭ

    int numPieces = stage * 2 + 3;  // ���������� ���� ���� ���� ���� �ٸ��� ����

    for (int i = 0; i < numPieces; ++i) {
        int blockCount = rand() % 5 + 3;  // �� ���� ������ ���Ե� ����� ���� (3~7��)
        std::vector<Block> blocks;

        // �������� ��� ��� ���� (����, L��, T�� ��)
        for (int j = 0; j < blockCount; ++j) {
            int x = rand() % cols;
            int y = rand() % rows;

            // ��� ��� ���� (��: 0: ����, 1: L��, 2: T�� ��)
            int shapeType = rand() % 3;  // 0: ����, 1: L��, 2: T��
            COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);  // ���� ����

            // �� ��翡 �´� ��� ��ġ
            if (shapeType == 0) {  // ���� ����
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
            }
            else if (shapeType == 1) {  // L�� ����
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
                blocks.push_back({ x, y + 1, color });
            }
            else if (shapeType == 2) {  // T�� ����
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
                blocks.push_back({ x - 1, y, color });
            }
        }

        // ������ ��ϵ��� ����� ���� ���� ����
        PuzzlePiece piece(blocks, RGB(rand() % 256, rand() % 256, rand() % 256));
        pieces.push_back(piece);  // ������ ������ ����Ʈ�� �߰�
    }
}

void Board::Draw(HDC hdc) {
    // �׸��� ��� �׸���
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            RECT rect = { j * 30, i * 30, (j + 1) * 30, (i + 1) * 30 };
            HBRUSH hBrush = CreateSolidBrush(grid[i][j]);
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // �׵θ� �׸���
            FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
    }

    // ���� ���� �׸���
    for (const auto& piece : pieces) {
        piece.Draw(hdc);
    }
}

bool Board::CheckFit(const PuzzlePiece& piece) {
    for (const auto& block : piece.blocks) {
        int x = block.x + piece.offsetX;
        int y = block.y + piece.offsetY;

        // ���� ��� üũ
        if (x < 0 || x >= cols || y < 0 || y >= rows) {
            return false;
        }

        // ��ħ üũ
        if (grid[y][x] != RGB(255, 255, 255)) {
            return false;
        }
    }
    return true;
}

void Board::FixPiece(const PuzzlePiece& piece) {
    for (const auto& block : piece.blocks) {
        int x = block.x + piece.offsetX;
        int y = block.y + piece.offsetY;

        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            grid[y][x] = block.color; // ��� ���� ����
        }
    }
}

// ������ ���߸� �������� Ŭ����
bool Board::CheckPuzzleComplete() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (stageBoards[currentStage - 1][i][j] == 1 && grid[i][j] == RGB(255, 255, 255)) {
                return false; // �������� �ʿ��� ����� ��� ������ ����
            }
        }
    }
    return true;
}