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
    srand((unsigned int)time(nullptr));  // ���� �õ� �ʱ�ȭ
    GenerateExamplePuzzle();  // �ʱ� ���� ����
}

void PuzzlePopup::GenerateExamplePuzzle() {
    std::vector<Block> blocks;

    blocks.push_back({ 5, 7, RGB(255, 0, 0) });
    blocks.push_back({ 6, 5, RGB(255, 0, 0) });
    blocks.push_back({ 4, 5, RGB(255, 0, 0) });
    blocks.push_back({ 5, 4, RGB(255, 0, 0) });

    PuzzlePiece* piece = new PuzzlePiece(blocks, RGB(255, 0, 0));
    board->FixPiece(*piece);  // ���忡 ���� ����
}
void RegisterPopupClass(HINSTANCE hInstance) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = DefWindowProc;  // �⺻ ������ ����
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PuzzlePopupClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // ��� ����
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, L"Failed to register PuzzlePopupClass.", L"Error", MB_OK | MB_ICONERROR);
    }
}


void PuzzlePopup::ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage) {
    RegisterPopupClass(hInstance);  // PuzzlePopupClass ���

    HWND popupWnd = CreateWindow(L"PuzzlePopupClass", L"Puzzle Popup",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,  // �̵� ���� ��Ÿ��
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
    board->Draw(hdc);  // ������ �׸���
    ReleaseDC(popupWnd, hdc);
}
