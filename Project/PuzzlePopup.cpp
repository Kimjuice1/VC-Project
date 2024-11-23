#include "PuzzlePopup.h"
#include "Board.h"
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

PuzzlePopup::PuzzlePopup(int rows, int cols) : rows(rows), cols(cols) {
    board = new Board(rows, cols);

    // 랜덤 시드 초기화
    srand((unsigned int)time(nullptr));

    // 예시 퍼즐 조각 생성
    GenerateExamplePuzzle();
}

void PuzzlePopup::GenerateExamplePuzzle() {
    // 예시로 사용할 퍼즐 조각들 정의
    std::vector<Block> blocks;

    // 예시 퍼즐을 위한 고정된 블록 위치 (예시 퍼즐이 T자 모양)
    blocks.push_back({ 5, 5, RGB(255, 0, 0) });  // 빨간색 T자
    blocks.push_back({ 6, 5, RGB(255, 0, 0) });
    blocks.push_back({ 4, 5, RGB(255, 0, 0) });
    blocks.push_back({ 5, 4, RGB(255, 0, 0) });

    // 퍼즐 조각을 생성하여 보드에 고정
    PuzzlePiece* piece = new PuzzlePiece(blocks, RGB(255, 0, 0));  // 빨간색 T자 퍼즐
    board->FixPiece(*piece);  // 생성된 퍼즐을 보드에 고정
}

void PuzzlePopup::ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage) {
    HWND popupWnd = CreateWindow(L"STATIC", L"Puzzle Popup", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
        parentWindow, nullptr, hInstance, nullptr);

    // 퍼즐을 확인하는 버튼을 추가
    CreateWindow(L"BUTTON", L"Confirm Puzzle", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        150, 350, 100, 30, popupWnd, (HMENU)1, hInstance, nullptr);

    // 현재 스테이지에 맞는 퍼즐 생성
    board->GenerateRandomPuzzle(stage);  // 각 스테이지마다 다르게 퍼즐 생성

    // 퍼즐을 그리기 위한 DC (Device Context) 얻기
    HDC hdc = GetDC(popupWnd);

    // 작은 창에 퍼즐 그리기
    board->Draw(hdc);

    ReleaseDC(popupWnd, hdc);  // 그리기 후 DC 반납

    ShowWindow(popupWnd, SW_SHOWNORMAL);
    UpdateWindow(popupWnd);
}
