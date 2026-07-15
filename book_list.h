#ifndef BOOK_LIST_H
#define BOOK_LIST_H

#include "main.h"

Screen bookListScreen()
{
    const int BOOKS_PER_PAGE = 11;
    const int LIST_START_ROW  = 6;

    int currentPage = 0;

    while (true) {
        int totalBooks = 0;
        for (Book* t = head; t != nullptr; t = t->next) totalBooks++;
        int totalPages = (totalBooks > 0) ? ((totalBooks + BOOKS_PER_PAGE - 1) / BOOKS_PER_PAGE) : 1;

        if (currentPage >= totalPages) currentPage = totalPages - 1;
        if (currentPage < 0) currentPage = 0;

        clearScreen();
        printTitle("图书列表");
        drawBox(3, 3, 70, 17, 14);

        // ---- 表头 ----
        color(11);
        gotoxy(5, 4);
        cout << "编号" << "\t" << "书名" << "\t\t" << "作者" << "\t" << "借阅/总量";

        // ---- 颜色图例 ----
        gotoxy(5, 5);
        color(10);  cout << "● 全在馆  ";
        color(14);  cout << "● 部分借出  ";
        color(12);  cout << "● 全借出";
        cout << "                    ";

        // ---- 显示当前页的图书 ----
        int  skip  = currentPage * BOOKS_PER_PAGE;
        int  shown = 0;
        int  idx   = 0;
        Book* p    = head;

        while (p != nullptr && shown < BOOKS_PER_PAGE) {
            if (idx >= skip) {
                gotoxy(5, LIST_START_ROW + shown);
                cout << "                                                                  ";
                gotoxy(5, LIST_START_ROW + shown);
                if (p->borrowedCount >= p->totalCount)
                    color(12);
                else if (p->borrowedCount > 0)
                    color(14);
                else
                    color(10);
                cout << p->id << "\t" << p->name << "\t\t" << p->author << "\t"
                     << p->borrowedCount << "/" << p->totalCount;
                shown++;
            }
            p = p->next;
            idx++;
        }

        // ---- 清空多余的旧行 ----
        for (int r = shown; r < BOOKS_PER_PAGE; r++) {
            gotoxy(5, LIST_START_ROW + r);
            cout << "                                                                  ";
        }

        // ---- 底部提示栏 ----
        gotoxy(5, 18);
        color(15);
        if (totalBooks > 0) {
            cout << "第" << (currentPage + 1) << "/" << totalPages << "页  ";
            color(14);  cout << "<- ->";
            color(15);
        } else {
            cout << "(暂无图书)  ";
        }
        cout << " 翻页 | 1添加 2删除 3借书 4还书 | 其他键返回主菜单";

        // ---- 读取按键 ----
        int choice = _getch();

        // 方向键
        if (choice == 224 || choice == 0) {
            int arrow = _getch();
            if (arrow == 75 && currentPage > 0) {
                currentPage--;
            } else if (arrow == 77 && currentPage < totalPages - 1) {
                currentPage++;
            }
            continue;
        }

        // ---- 清空操作提示区 ----
        auto clearBottom = []() {
            for (int r = 19; r <= 23; r++) {
                gotoxy(5, r);
                cout << "                                                              ";
            }
        };

        switch (choice) {
        case '1': {  // 添加书籍
            Book* newBook = new Book;
            clearBottom();

            gotoxy(5, 19);
            color(14);
            cout << "请输入编号: ";
            cin >> newBook->id;

            bool dup = false;
            for (Book* q = head; q != nullptr; q = q->next) {
                if (strcmp(q->id, newBook->id) == 0) { dup = true; break; }
            }
            if (dup) {
                color(12);
                gotoxy(5, 21);
                cout << "编号已存在！按任意键重新添加...";
                getch();
                delete newBook;
                continue;
            }

            gotoxy(5, 20);
            cout << "请输入书名: ";
            cin >> newBook->name;
            gotoxy(5, 21);
            cout << "请输入作者: ";
            cin >> newBook->author;
            gotoxy(5, 22);
            cout << "请输入馆藏总量: ";
            cin >> newBook->totalCount;
            if (newBook->totalCount < 1) newBook->totalCount = 1;
            newBook->borrowedCount = 0;
            newBook->next = nullptr;

            if (head == nullptr) {
                head = newBook;
            } else {
                Book* t = head;
                while (t->next != nullptr) t = t->next;
                t->next = newBook;
            }
            saveBooksToFile();

            color(10);
            gotoxy(5, 23);
            cout << "添加成功！按任意键刷新...";
            getch();
            continue;
        }
        case '2': {  // 删除书籍
            clearBottom();

            gotoxy(5, 19);
            color(14);
            cout << "请输入要删除的图书编号: ";
            char delId[10];
            cin >> delId;

            Book* prev = nullptr;
            Book* cur  = head;
            while (cur != nullptr) {
                if (strcmp(cur->id, delId) == 0) break;
                prev = cur;
                cur  = cur->next;
            }

            if (cur == nullptr) {
                color(12);
                gotoxy(5, 21);
                cout << "未找到该编号的图书！按任意键继续...";
                getch();
                continue;
            }

            if (prev == nullptr)
                head = cur->next;
            else
                prev->next = cur->next;
            delete cur;
            saveBooksToFile();

            color(10);
            gotoxy(5, 21);
            cout << "删除成功！按任意键刷新...";
            getch();
            continue;
        }
        case '3': return BORROW;
        case '4': return RETURN_BOOK;
        default:  return WELCOME;
        }
    }
}

#endif
