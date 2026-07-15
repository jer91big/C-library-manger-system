#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

/* ========== 界面状态枚举 ========== */
enum Screen { WELCOME, BOOK_LIST, BORROW, RETURN_BOOK, SEARCH, ADMIN, EXIT_APP, STATISTICS };

/* ========== 图书结构体 + 全局数据 ========== */
struct Book {
    char id[10];
    char name[50];
    char author[30];
    int  totalCount;     // 馆藏总量
    int  borrowedCount;  // 已借出数量
    Book* next;          // 指向下一本书
};

Book books[100];
Book* head = nullptr;
int  bookCount = 0;

/* ========== 通用界面工具函数 ========== */
void gotoxy(int x, int y)
{
    COORD c; c.X = x; c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawBox(int x1, int y1, int x2, int y2, int colorCode)
{
    color(colorCode);
    for (int i = y1; i <= y2; i++)
    {
        for (int j = x1; j <= x2; j++)
        {
            gotoxy(j, i);
            if (i == y1 || i == y2) cout << "=";
            else if (j == x1 || j == x2) cout << "||";
        }
    }
}

void printTitle(const char* title)
{
    color(11);
    int totalLen = 20 + (int)strlen(title);
    int startX = 40 - totalLen / 2;
    gotoxy(startX, 2);
    cout << "========== " << title << " ==========";
}

void clearScreen()
{
    system("cls");
}

/* ========== 文件路径常量 ========== */
const char* DATA_FILE = "books.dat";

/* ========== 保存数据到文件 ========== */
void saveBooksToFile() {
    ofstream out(DATA_FILE, ios::binary);
    if (!out) {
        color(12);
        gotoxy(5, 24);
        cout << "错误：无法保存数据文件！";
        return;
    }

    Book* p = head;
    while (p != nullptr) {
        out.write((char*)p, sizeof(Book));
        p = p->next;
    }
    out.close();
}

/* ========== 从文件加载数据 ========== */
bool loadBooksFromFile() {
    ifstream in(DATA_FILE, ios::binary);
    if (!in) return false;

    Book* tail = nullptr;
    while (true) {
        Book* b = new Book;
        if (in.read((char*)b, sizeof(Book))) {
            b->next = nullptr;
            if (head == nullptr) {
                head = b;
                tail = b;
            } else {
                tail->next = b;
                tail = b;
            }
        } else {
            delete b;
            break;
        }
    }
    in.close();
    return true;
}

/* ========== 测试数据初始化 ========== */
void initSampleData() {
    if (!loadBooksFromFile()) {
        Book* b1 = new Book;
        strcpy(b1->id, "001");
        strcpy(b1->name, "C++ Primer");
        strcpy(b1->author, "Lippman");
        b1->totalCount    = 5;
        b1->borrowedCount = 2;
        b1->next = nullptr;

        Book* b2 = new Book;
        strcpy(b2->id, "002");
        strcpy(b2->name, "算法导论");
        strcpy(b2->author, "Cormen");
        b2->totalCount    = 3;
        b2->borrowedCount = 3;
        b2->next = nullptr;

        b1->next = b2;
        head = b1;
        saveBooksToFile();
    }
}

/* ========== 各界面函数声明 ========== */
Screen welcomeScreen();
Screen bookListScreen();
Screen borrowScreen();
Screen returnScreen();
Screen searchScreen();
Screen adminScreen();
Screen statisticsScreen();

#endif // MAIN_H
