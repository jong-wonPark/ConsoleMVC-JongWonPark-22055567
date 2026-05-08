#include "MainMenuView.h"
#include <iostream>
#include <limits>
#include <string>

void MainMenuView::displayBanner() const {
    clearScreen();
    std::cout << "============================================\n";
    std::cout << "    s-semi 주문/생산/재고 관리 시스템 v1.0  \n";
    std::cout << "============================================\n\n";
}

void MainMenuView::displayMainMenu() const {
    std::cout << "  [ 메인 메뉴 ]\n";
    std::cout << "  1. 주문 관리\n";
    std::cout << "  2. 재고 관리\n";
    std::cout << "  3. 생산 관리\n";
    std::cout << "  0. 종료\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "선택: ";
}

int MainMenuView::getMenuChoice(int min, int max) const {
    int choice;
    while (true) {
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [오류] " << min << "~" << max << " 사이의 숫자를 입력하세요: ";
    }
}

void MainMenuView::displayMessage(const std::string& msg) const {
    std::cout << "  " << msg << "\n";
}

void MainMenuView::displayError(const std::string& msg) const {
    std::cout << "  [오류] " << msg << "\n";
}

void MainMenuView::displaySuccess(const std::string& msg) const {
    std::cout << "  [완료] " << msg << "\n";
}

void MainMenuView::pause() const {
    std::cout << "\n  계속하려면 Enter를 누르세요...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MainMenuView::clearScreen() const {
    system("cls");
}

void MainMenuView::displaySeparator() const {
    std::cout << "--------------------------------------------\n";
}
