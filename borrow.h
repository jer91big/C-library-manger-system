#ifndef BORROW_H
#define BORROW_H

#include "main.h"

Screen borrowScreen()
{
    clearScreen();
    printTitle("借书");
    gotoxy(5, 5);
    color(11);
    cout<< "（按 ESC 退出到图书列表）";
    gotoxy(5, 4);
    color(14);
    cout << "请输入要借阅的图书编号: ";

    char inputId[10];
    int len = 0;

    while (true)
    {
        char ch = _getch();

        if (ch == 27) {
            return BOOK_LIST;
        }
        else if (ch == '\r') {
            if (len > 0) break;
        }
        else if (ch == '\b') {
            if (len > 0) {
                len--;
                inputId[len] = '\0';
                cout << "\b \b";
            }
        }
        else if (len < 9 && ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
            inputId[len] = ch;
            len++;
            cout << ch;
        }
    }
    inputId[len] = '\0';

    Book* found = nullptr;
    Book* p = head;
    while (p != nullptr) {
        if (strcmp(p->id, inputId) == 0) {
            found = p;
            break;
        }
        p = p->next;
    }

    gotoxy(5, 6);
    if (found == nullptr)
    {
        color(12);
        cout << "未找到该编号的图书！";
    }
    else if (found->borrowedCount >= found->totalCount)
    {
        color(12);
        cout << "该书已全部借出，暂时无法借阅！";
    }
    else
    {
        found->borrowedCount++;
        saveBooksToFile();
        color(10);
        cout << "借阅成功：《" << found->name << "》"
             << "（剩余 " << (found->totalCount - found->borrowedCount)
             << "/" << found->totalCount << " 本）";
    }
    gotoxy(5, 9);
    color(13);
    cout << "按任意键返回主菜单...";
    getch();
    return WELCOME;
}

#endif
