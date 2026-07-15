#ifndef SEARCH_H
#define SEARCH_H

#include "main.h"

Screen searchScreen()
{
    clearScreen();
    printTitle("查找图书");
    drawBox(10, 4, 60, 19, 14);
    gotoxy(20, 7);   cout << "1. 通过书名关键字查找";
    gotoxy(20, 9);   cout << "2. 通过作者关键字查找";
    gotoxy(20, 11);  cout << "3. 通过图书ID查找";
    gotoxy(20, 13);  cout << "4. 返回主菜单";
    gotoxy(20, 15);
    cout << "请输入您的选择:";
    int choice = _getch();

    switch (choice)
    {
        case '1': {  // 通过书名关键字查找图书
            clearScreen();
            printTitle("通过书名关键字查找图书");
            drawBox(10, 4, 60, 19, 14);

            // 输入提示放在框内左上区域
            gotoxy(14, 7);
            color(14);
            cout << "请输入书名关键字: ";
            char keyword[50];
            cin >> keyword;

            // 清空输入行下方区域，准备显示结果
            int row = 9;
            int hasResult = 0;
            Book* p = head;
            while (p != nullptr)
            {
                if (strstr(p->name, keyword) != NULL)
                {
                    gotoxy(14, row++);
                    color(10);
                    cout << "[" << p->id << "] " << p->name << " - " << p->author
                         << "  (" << p->borrowedCount << "/" << p->totalCount << ")";
                    hasResult = 1;
                }
                p = p->next;
            }

            if (!hasResult)
            {
                gotoxy(14, 9);
                color(12);
                cout << "未找到匹配的图书。";
                row = 11;  // 让下方"按任意键"和"未找到"不要距离太远
            }

            gotoxy(14, row + 1);
            color(13);
            cout << "按任意键返回搜索界面...";
            getch();
            return SEARCH;
        }
        case '2':  // 通过作者关键字查找（待实现）
        {
            clearScreen();
            printTitle("通过作者关键字查找图书");
            drawBox(10, 4, 60, 19, 14);
            gotoxy(20, 7);  cout << "请输入作者关键字:";
            char keyword[50];
            cin >> keyword;
            int row = 9;
            int hasResult = 0;
            Book* p = head;
            while (p != nullptr)
            {
                if (strstr(p->author, keyword) != NULL)
                {
                    gotoxy(20, row++);
                    color(10);
                    cout << "[" << p->id << "] " << p->name << " - " << p->author
                         << "  (" << p->borrowedCount << "/" << p->totalCount << ")";
                    hasResult = 1;
                }
                p = p->next;
            }

            if (!hasResult)
            {
                gotoxy(20, 9);
                color(12);
                cout << "未找到匹配的图书。";
                row = 11;  // 让下方"按任意键"和"未找到"不要距离太远
            }

            gotoxy(20, row + 1);
            color(13);
            cout << "按任意键返回搜索界面...";
            getch();
            return SEARCH;
        }
        case '3':  // 通过图书ID查找（待实现）
        {
            clearScreen();
            printTitle("通过图书ID查找图书");
            drawBox(10, 4, 60, 19, 14);
            gotoxy(20, 7);  cout << "请输入图书ID:";
            char id[10];
            cin >> id;
            int row = 9;
            int hasResult = 0;
            Book* p = head;
            while (p != nullptr)
            {
                if (strcmp(p->id, id) == 0)
                {
                    gotoxy(20, row++);
                    color(10);
                    cout << "[" << p->id << "] " << p->name << " - " << p->author
                         << "  (" << p->borrowedCount << "/" << p->totalCount << ")";
                    hasResult = 1;
                    
                }
                p = p->next;
            }
            if (!hasResult)
            {
                gotoxy(20, 9);
                color(12);
                cout << "未找到匹配的图书。";
                row = 11;  // 让下方"按任意键"和"未找到"不要距离太远
            }
            gotoxy(20, row + 1);
            color(13);
            cout << "按任意键返回搜索界面...";
            getch();
            return SEARCH;
        }
    default:
        return WELCOME;
}
}
#endif
