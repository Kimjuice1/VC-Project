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
    board = new Board(rows, cols);  // 메인 보드와 동일한 크기 설정
    srand((unsigned int)time(nullptr));  // 랜덤 시드 초기화
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
    RegisterPopupClass(hInstance);

    int cellSize = 30;  // 각 셀의 크기
    int windowWidth = cols * cellSize + 16;  // 열 * 셀 크기 + 여유(테두리)
    int windowHeight = rows * cellSize + 39; // 행 * 셀 크기 + 여유(제목 표시줄)

    HWND popupWnd = CreateWindow(L"PuzzlePopupClass", L"Puzzle Popup",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight,
        parentWindow, nullptr, hInstance, nullptr);

    if (!popupWnd) {
        DWORD errorCode = GetLastError();
        WCHAR errorMsg[256];
        wsprintf(errorMsg, L"CreateWindow failed with error code: %lu", errorCode);
        MessageBox(parentWindow, errorMsg, L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    HDC hdc = GetDC(popupWnd);
    board->Draw(hdc);  // 보드 그리기
    ReleaseDC(popupWnd, hdc);
}
