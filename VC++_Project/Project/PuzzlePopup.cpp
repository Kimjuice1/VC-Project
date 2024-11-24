#include "PuzzlePopup.h"
#include "Board.h"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> stageBoards[] = {
    { // Stage 1
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {1, 1, 1, 1},
    },
    { // Stage 2
        {0, 1, 1, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 1, 1, 0, 0},
    },
};

PuzzlePopup::PuzzlePopup(int rows, int cols) : rows(rows), cols(cols) {
    board = new Board(rows, cols);
    srand((unsigned int)time(nullptr));  // 랜덤 시드 초기화
    GenerateExamplePuzzle();  // 초기 퍼즐 생성
}

void PuzzlePopup::GenerateExamplePuzzle() {
    std::vector<Block> blocks;

    blocks.push_back({ 5, 7, RGB(255, 0, 0) });
    blocks.push_back({ 6, 5, RGB(255, 0, 0) });
    blocks.push_back({ 4, 5, RGB(255, 0, 0) });
    blocks.push_back({ 5, 4, RGB(255, 0, 0) });

    PuzzlePiece* piece = new PuzzlePiece(blocks, RGB(255, 0, 0));
    board->FixPiece(*piece);  // 보드에 퍼즐 고정
}
void RegisterPopupClass(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = DefWindowProc;  // 기본 윈도우 절차
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PuzzlePopupClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // 배경 색상
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"Failed to register PuzzlePopupClass.", L"Error", MB_OK | MB_ICONERROR);
    }
}


void PuzzlePopup::ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage) {
    RegisterPopupClass(hInstance);  // PuzzlePopupClass 등록

    HWND popupWnd = CreateWindow(L"PuzzlePopupClass", L"Puzzle Popup",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // 이동 가능 스타일
        CW_USEDEFAULT, CW_USEDEFAULT, 316, 400,
        parentWindow, nullptr, hInstance, nullptr);

    if (!popupWnd) {
        DWORD errorCode = GetLastError();
        WCHAR errorMsg[256];
        wsprintf(errorMsg, L"CreateWindow failed with error code: %lu", errorCode);
        MessageBox(parentWindow, errorMsg, L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    HDC hdc = GetDC(popupWnd);
    board->Draw(hdc);  // 퍼즐판 그리기
    ReleaseDC(popupWnd, hdc);
}
