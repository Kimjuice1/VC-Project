#include "Board.h"
#include "PuzzlePiece.h"
#include <cstdlib>
#include <ctime>
#include <vector>

Board::Board(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<COLORREF>(cols, RGB(255, 255, 255))) {
    srand((unsigned int)time(nullptr));  // 랜덤 시드 초기화
}

// 이후 내용은 원본 그대로 유지


void Board::GenerateRandomPuzzle(int stage) {
    pieces.clear();  // 기존 퍼즐 조각들을 초기화

    int numPieces = stage * 2 + 3;  // 스테이지에 따라 퍼즐 조각 수를 다르게 설정

    for (int i = 0; i < numPieces; ++i) {
        int blockCount = rand() % 5 + 3;  // 각 퍼즐 조각에 포함될 블록의 개수 (3~7개)
        std::vector<Block> blocks;

        // 랜덤으로 블록 모양 결정 (직선, L자, T자 등)
        for (int j = 0; j < blockCount; ++j) {
            int x = rand() % cols;
            int y = rand() % rows;

            // 블록 모양 결정 (예: 0: 직선, 1: L자, 2: T자 등)
            int shapeType = rand() % 3;  // 0: 직선, 1: L자, 2: T자
            COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);  // 랜덤 색상

            // 각 모양에 맞는 블록 배치
            if (shapeType == 0) {  // 직선 형태
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
            }
            else if (shapeType == 1) {  // L자 형태
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
                blocks.push_back({ x, y + 1, color });
            }
            else if (shapeType == 2) {  // T자 형태
                blocks.push_back({ x, y, color });
                blocks.push_back({ x + 1, y, color });
                blocks.push_back({ x - 1, y, color });
            }
        }

        // 생성된 블록들을 사용해 퍼즐 조각 생성
        PuzzlePiece piece(blocks, RGB(rand() % 256, rand() % 256, rand() % 256));
        pieces.push_back(piece);  // 생성된 조각을 리스트에 추가
    }
}

void Board::Draw(HDC hdc) {
    // 그리드 배경 그리기
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            RECT rect = { j * 30, i * 30, (j + 1) * 30, (i + 1) * 30 };
            HBRUSH hBrush = CreateSolidBrush(grid[i][j]);
            FillRect(hdc, &rect, hBrush);
            DeleteObject(hBrush);

            // 테두리 그리기
            FrameRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        }
    }

    // 퍼즐 조각 그리기
    for (const auto& piece : pieces) {
        piece.Draw(hdc);
    }
}

bool Board::CheckFit(const PuzzlePiece& piece) {
    for (const auto& block : piece.blocks) {
        int x = block.x + piece.offsetX;
        int y = block.y + piece.offsetY;

        // 보드 경계 체크
        if (x < 0 || x >= cols || y < 0 || y >= rows) {
            return false;
        }

        // 겹침 체크
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
            grid[y][x] = block.color; // 블록 색상 저장
        }
    }
}

// 퍼즐을 맞추면 스테이지 클리어
bool Board::CheckPuzzleComplete() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (stageBoards[currentStage - 1][i][j] == 1 && grid[i][j] == RGB(255, 255, 255)) {
                return false; // 퍼즐판의 필요한 블록이 비어 있으면 실패
            }
        }
    }
    return true;
}