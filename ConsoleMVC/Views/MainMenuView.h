#pragma once
#include <string>

class MainMenuView {
public:
    void displayBanner() const;
    void displayMainMenu() const;
    int  getMenuChoice(int min, int max) const;
    void displayMessage(const std::string& msg) const;
    void displayError(const std::string& msg) const;
    void displaySuccess(const std::string& msg) const;
    void pause() const;
    void clearScreen() const;
    void displaySeparator() const;
};
