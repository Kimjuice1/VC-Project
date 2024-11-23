#include "PuzzlePopup.h"
#include "Board.h"
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()

PuzzlePopup::PuzzlePopup(int rows, int cols) : rows(rows), cols(cols) {
    board = new Board(rows, cols);

    // ���� �õ� �ʱ�ȭ
    srand((unsigned int)time(nullptr));

    // ���� ���� ���� ����
    GenerateExamplePuzzle();
}

void PuzzlePopup::GenerateExamplePuzzle() {
    // ���÷� ����� ���� ������ ����
    std::vector<Block> blocks;

    // ���� ������ ���� ������ ��� ��ġ (���� ������ T�� ���)
    blocks.push_back({ 5, 5, RGB(255, 0, 0) });  // ������ T��
    blocks.push_back({ 6, 5, RGB(255, 0, 0) });
    blocks.push_back({ 4, 5, RGB(255, 0, 0) });
    blocks.push_back({ 5, 4, RGB(255, 0, 0) });

    // ���� ������ �����Ͽ� ���忡 ����
    PuzzlePiece* piece = new PuzzlePiece(blocks, RGB(255, 0, 0));  // ������ T�� ����
    board->FixPiece(*piece);  // ������ ������ ���忡 ����
}

void PuzzlePopup::ShowPuzzle(HINSTANCE hInstance, HWND parentWindow, int stage) {
    HWND popupWnd = CreateWindow(L"STATIC", L"Puzzle Popup", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
        parentWindow, nullptr, hInstance, nullptr);

    // ������ Ȯ���ϴ� ��ư�� �߰�
    CreateWindow(L"BUTTON", L"Confirm Puzzle", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        150, 350, 100, 30, popupWnd, (HMENU)1, hInstance, nullptr);

    // ���� ���������� �´� ���� ����
    board->GenerateRandomPuzzle(stage);  // �� ������������ �ٸ��� ���� ����

    // ������ �׸��� ���� DC (Device Context) ���
    HDC hdc = GetDC(popupWnd);

    // ���� â�� ���� �׸���
    board->Draw(hdc);

    ReleaseDC(popupWnd, hdc);  // �׸��� �� DC �ݳ�

    ShowWindow(popupWnd, SW_SHOWNORMAL);
    UpdateWindow(popupWnd);
}
