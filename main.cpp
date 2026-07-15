#include "screens.h"

/* ========== main 主循环 ========== */
int main()
{
    system("chcp 65001");
    initSampleData();

    Screen current = WELCOME;
    while (current != EXIT_APP)
    {
        switch (current)
        {
            case WELCOME:     current = welcomeScreen();   break;
            case BOOK_LIST:   current = bookListScreen();  break;
            case BORROW:      current = borrowScreen();    break;
            case RETURN_BOOK: current = returnScreen();    break;
            case SEARCH:      current = searchScreen();    break;
            case STATISTICS:  current = statisticsScreen();break;
            default:          current = EXIT_APP;          break;
        }
    }

    clearScreen();
    gotoxy(10, 10);
    color(15);
    cout << "感谢使用，再见！" << endl;

    // 释放链表内存
    Book* q = head;
    while (q != nullptr) {
        Book* tmp = q;
        q = q->next;
        delete tmp;
    }

    return 0;
}
