#ifndef STATISTICS_H
#define STATISTICS_H

#include "main.h"

Screen statisticsScreen(){
    clearScreen();
    printTitle("统计信息");
    drawBox(10, 4, 60, 19, 14);
    color(15);
    gotoxy(20, 7);  cout << "1. 查看图书总数";
    gotoxy(20, 9);  cout << "2. 查看已借出图书数";
    gotoxy(20, 11); cout << "3. 查看在馆图书数";
    gotoxy(20, 13); cout << "4. 返回图书列表界面";
    gotoxy(20, 15); cout << "0. 返回欢迎界面";
    gotoxy(10, 20);
    color(5);
    cout << "请选择: ";
    int choice;
    cin >> choice;

    int totalBooks = 0;
    int totalBorrowedBooks = 0;
    int totalInLibraryBooks = 0;
    for (Book* t = head; t != nullptr; t = t->next) {
        totalBooks           += t->totalCount;
        totalBorrowedBooks   += t->borrowedCount;
        totalInLibraryBooks  += (t->totalCount - t->borrowedCount);
    }

    color(10);
    gotoxy(20, 10);
    switch (choice)
    {
        case 1:
            clearScreen();
            printTitle("统计信息");
            drawBox(10, 4, 60, 19, 14);
            color(10);
            gotoxy(20, 10);
            cout << "当前图书总数: " << totalBooks << " 本";
            break;
        case 2:
            clearScreen();
            printTitle("统计信息");
            drawBox(10, 4, 60, 19, 14);
            color(10);
            gotoxy(20, 10);
            cout << "当前已借出图书数: " << totalBorrowedBooks << " 本";
            break;
        case 3:
            clearScreen();
            printTitle("统计信息");
            drawBox(10, 4, 60, 19, 14);
            color(10);
            gotoxy(20, 10);
            cout << "当前在馆图书数: " << totalInLibraryBooks << " 本";
            break;
        case 0:
        case 4:
        return BOOK_LIST;

        default:
            return WELCOME;
    }

    gotoxy(10, 20);
    color(13);
    cout << "返回统计界面...";
    getch();
    return STATISTICS;
}

#endif
