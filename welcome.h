#ifndef WELCOME_H
#define WELCOME_H

#include "main.h"

Screen welcomeScreen()
{
    clearScreen();
    printTitle("图书管理系统");
    drawBox(10, 4, 60, 19, 14);

    color(15);
    gotoxy(20, 7);  cout << "1. 查看图书列表";
    gotoxy(20, 9);  cout << "2. 借书";
    gotoxy(20, 11); cout << "3. 还书";
    gotoxy(20, 13); cout << "4. 查找图书";
    gotoxy(20, 15); cout << "5. 统计信息";
    gotoxy(20, 17); cout << "0. 退出系统";

    gotoxy(10, 20);
    color(5);
    cout << "请选择: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
        case 1: return BOOK_LIST;
        case 2: return BORROW;
        case 3: return RETURN_BOOK;
        case 4: return SEARCH;
        case 5: return STATISTICS;
        case 0: return EXIT_APP;
        default: return WELCOME;
    }
}

#endif
