#pragma once
#include <vector>
#include <windows.h>
#include "PuzzlePiece.h"

extern std::vector<std::vector<int>> stageBoards[];

// currentStage 전역 변수 선언
extern int currentStage;

class Board {
public:
    int rows, cols;  // 보드 크기
    std::vector<std::vector<COLORREF>> grid;  // 보드의 각 칸에 대한 색상
    std::vector<PuzzlePiece> pieces;  // 퍼즐 조각을 저장하는 벡터

    Board(int rows, int cols);
    void Draw(HDC hdc);  // 보드 그리기
    void GenerateRandomPuzzle(int stage);  // 랜덤 퍼즐 생성
    void FixPiece(const PuzzlePiece& piece);  // 퍼즐 조각 고정
    bool CheckFit(const PuzzlePiece& piece);  // 퍼즐 조각이 맞는지 확인
    bool CheckPuzzleComplete();
};