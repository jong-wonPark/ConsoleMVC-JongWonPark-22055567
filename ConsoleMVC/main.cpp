#include <Windows.h>
#include "Controllers/AppController.h"

int main() {
    // 콘솔 UTF-8 설정 (한글 출력)
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    AppController app;
    app.run();

    return 0;
}
