#include <iostream>  
#include <time.h> //случайные числа
#include <stdio.h> //для printf
#include <windows.h> // дл¤ HANDLE, курсора, цвета
#include <conio.h>  //для kbhit
#include <mmsystem.h>

#pragma comment (lib, "Winmm.lib")
using namespace std;



HANDLE hConsole;
//HANDLE hStdout, hStdin;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GotoXY(int X, int Y)
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}
//÷вет
enum  ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};


//функция для добавления цвета
void SetColor(ConsoleColor text, ConsoleColor background)
{
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


class Snake  // структура змейка 
{
public:COORD* t; //точки
public:int PCount; //количество яблок
};
enum uprawlenie { LEFT, UP, RIGHT, DOWN }; //направление змейки
class Game //даные-точности: змейки, блок, передвижение по X и Y, задержка, направление
{
public:Snake snake; //змейка
public:COORD apple; //яблоко
public:int dx, dy; //передвижение
public:int pause; //задержка
public:int nap; //направление

};


//функция для воспроизведения музыки при начале игры
void playmusicStart()
{
    PlaySound(TEXT("start.wav"), 0, SND_ASYNC);
}

//функция для воспроизведения музыки при конце игры
void playmusicGameEnd()
{
    PlaySound(TEXT("finish.wav"), NULL, SND_ASYNC);
}


//Функция разброски яблок
void PlusApple(Game& g) 
{
    int i, x, y;
    int n = g.snake.PCount;
    do
    { 
        //кординаты яблока
        x = rand() % 56 + 3; 
        y = rand() % 19 + 3; 
        for (i = 0; i < n; i++)
        {
            // проверка чтоб яблоко не бросить на змею
            if (x == g.snake.t[i].X && y == g.snake.t[i].Y)
                break;
        }
    } while (i < n);
    g.apple.X = x; //
    g.apple.Y = y; //запоминаем позицию яблока
    SetConsoleCursorPosition(hConsole, g.apple); //переносим курсор в эту позицию
    SetConsoleTextAttribute(hConsole, 0x0c); //цвет яблока  
    printf("%c", 4); //рисуем яблоко каким хотим символом

}

// Функция старта змейки ее координат и скорости
void skorostGame(Game& g) 
{
    system("cls");
    //сколько точек в змейке
    g.snake.PCount = 3;
    //создали точки
    g.snake.t = new COORD[3];
    for (int i = 0; i < 3; i++)
    {
        g.snake.t[i].X = 20 + i;
        g.snake.t[i].Y = 20;

    }
    g.dx = 1;
    g.dy = 0;
    //скорость передвижение змеи
    g.pause = 170;
    //рисуем яблоко
    PlusApple(g);
}
void Level()
{
    GotoXY(10, 10);cout << "Вы никогда не выиграете" << endl; //Вы никогда не выиграете
    GotoXY(10, 11);cout << "если не будете бдительны!" << endl; //если не будете бдительны!
}

//появление змейки на поле
void SnakeStart()
{
    GotoXY(10, 15);
    cout << "Соберите 50 яблок" << endl; //Соберите 50 яблок
}
void STENA_2() //Информация отображаемая справа при старте игры
{
    SetColor(LightBlue, Black);GotoXY(20, 0);cout << "Игра змейка" << endl;  
    SetColor(LightBlue, Black);GotoXY(20, 1);cout << "ГУАП Game Studios" << endl;
    GotoXY(64, 2);cout << "Данные:" << endl; //данные
    GotoXY(64, 3);cout << "Яблок:0" << endl; //яблоки
    GotoXY(64, 4); cout << "Длина:3" << endl; //длина
    GotoXY(64, 5); cout << "Скорость:170" << endl; //скорость
    GotoXY(64, 7); cout << "Управление:" << endl; //управление
    GotoXY(64, 8); cout << "Esc:Выход" << endl; //выход
    GotoXY(64, 9); cout << "P:Пауза" << endl; //пауза
    GotoXY(64, 10); cout << "S:Старт" << endl; //старт
    GotoXY(64, 11); cout << "L:Уровень" << endl; //уровень
    GotoXY(64, 13);printf("%c", 24);cout << ":Вверх" << endl; //вверх
    GotoXY(64, 14);printf("%c", 25);cout << ":Вниз" << endl;   //вниз
    GotoXY(64, 15);printf("%c", 27);cout << ":Влево" << endl;  //влево
    GotoXY(64, 16);printf("%c", 26);cout << ":Вправо" << endl; //вправо
    {SetColor(LightMagenta, Black);

    //рисуем верхнюю горизонтальную линию-стенку
    GotoXY(2, 2); 
    int m = 0;
    for (m = 0; m < 60; m++)
    {
        printf("*");
    }
    }

    {
        //рисуем нижнюю горизонтальную линию-стенку
        GotoXY(2, 24); 
        int m = 0;
        for (m = 0; m < 60;m++)
        {
            printf("*");
        }
    }
    {   //рисуем левую вертикальную линию-стенку
        GotoXY(2, 3); cout << "*" << endl;
        GotoXY(2, 4); cout << "*" << endl;
        GotoXY(2, 5); cout << "*" << endl;
        GotoXY(2, 6); cout << "*" << endl;
        GotoXY(2, 7); cout << "*" << endl;
        GotoXY(2, 8); cout << "*" << endl;
        GotoXY(2, 9); cout << "*" << endl;
        GotoXY(2, 10); cout << "*" << endl;
        GotoXY(2, 11); cout << "*" << endl;
        GotoXY(2, 12); cout << "*" << endl;
        GotoXY(2, 13); cout << "*" << endl;
        GotoXY(2, 14); cout << "*" << endl;
        GotoXY(2, 15); cout << "*" << endl;
        GotoXY(2, 16); cout << "*" << endl;
        GotoXY(2, 17); cout << "*" << endl;
        GotoXY(2, 18); cout << "*" << endl;
        GotoXY(2, 19); cout << "*" << endl;
        GotoXY(2, 20); cout << "*" << endl;
        GotoXY(2, 21); cout << "*" << endl;
        GotoXY(2, 22); cout << "*" << endl;
        GotoXY(2, 23); cout << "*" << endl;
    }
    {   //рисуем правую вертикальную линию-стенку
        GotoXY(61, 3); cout << "*" << endl;
        GotoXY(61, 4); cout << "*" << endl;
        GotoXY(61, 5); cout << "*" << endl;
        GotoXY(61, 6); cout << "*" << endl;
        GotoXY(61, 7); cout << "*" << endl;
        GotoXY(61, 8); cout << "*" << endl;
        GotoXY(61, 9); cout << "*" << endl;
        GotoXY(61, 10); cout << "*" << endl;
        GotoXY(61, 11); cout << "*" << endl;
        GotoXY(61, 12); cout << "*" << endl;
        GotoXY(61, 13); cout << "*" << endl;
        GotoXY(61, 14); cout << "*" << endl;
        GotoXY(61, 15); cout << "*" << endl;
        GotoXY(61, 16); cout << "*" << endl;
        GotoXY(61, 17); cout << "*" << endl;
        GotoXY(61, 18); cout << "*" << endl;
        GotoXY(61, 19); cout << "*" << endl;
        GotoXY(61, 20); cout << "*" << endl;
        GotoXY(61, 21); cout << "*" << endl;
        GotoXY(61, 22); cout << "*" << endl;
        GotoXY(61, 23); cout << "*" << endl;
    }
}


//Функция которая двигает и рисует
enum { FINISH, STENA, PLUS, MOVE };
int Move(Game& g)
{
    int& n = g.snake.PCount;
    //голова
    COORD head = g.snake.t[n - 1];
     //хвост
    COORD tail = g.snake.t[0];
    COORD next;
    next.X = head.X + g.dx;
    //проверка следующей точки по направлению
    next.Y = head.Y + g.dy; 

    //если уперлась в стену?
    if (next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)
        return STENA;

    if (n > 4)
    {
        for (int i = 0; i < n; i++)
            //если наехала ли на себя?
            if (next.X == g.snake.t[i].X && next.Y == g.snake.t[i].Y)
                return FINISH;
    }

    if (next.X == g.apple.X && next.Y == g.apple.Y)
    {
        //новый масив больший на 1
        COORD* temp = new COORD[++n]; 
        for (int i = 0; i < n; i++)
            //перекопируем
            temp[i] = g.snake.t[i];
        //добавляем одну
        temp[n - 1] = next; 
        delete[] g.snake.t;
        g.snake.t = temp;

        SetConsoleCursorPosition(hConsole, head);
        //закрашываем яблоко которое съели
        SetConsoleTextAttribute(hConsole, 0x0a); 
        printf("*");
        SetConsoleCursorPosition(hConsole, next);
        SetConsoleTextAttribute(hConsole, 0x0a);
        printf("%c", 1);
        PlusApple(g);
        return PLUS;
    }

    for (int i = 0; i < n - 1; i++)
        g.snake.t[i] = g.snake.t[i + 1];
    g.snake.t[n - 1] = next;
    //закрашиваем хвостик
    SetConsoleCursorPosition(hConsole, tail);
    printf(" ");

    SetConsoleCursorPosition(hConsole, head);
    //красим хвост змеи в зелений цвет
    SetConsoleTextAttribute(hConsole, 0x0a);
    printf("*");
    SetConsoleCursorPosition(hConsole, next);
    //красим курсор в белый цвет (голову змеи)
    SetConsoleTextAttribute(hConsole, 0x0f); 
    printf("%c", 1);

    return MOVE;
}

void intro()
{
    GotoXY(15, 10); 
    printf("Нажмите Enter,чтобы начать. Esc - выход из игры.");
    GotoXY(15, 11);
    printf("Вам нужно собрать 50 яблок,чтобы пройти уровень!");
    GotoXY(18, 15);
    printf("Скорость змейки можно уменьшить в коде");
    _getch();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //получаем дескриптор консоли
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    intro();
    playmusicStart();
    int key = 0, count = 0;
    bool Pause = false;
    Game g;
    skorostGame(g);
    STENA_2();
    srand(time(0));
    bool pause = false;
    while (key != 27)
    {
        //ждет пока нажмем
        while (!_kbhit()) 
        {     
            if (Pause == true)
            {
                Sleep(1);
                continue;
            }

            //движение
            switch (Move(g))
            {

            case PLUS:
                ++count;
                g.pause -= 1;
                SetColor(LightBlue, Black);
                GotoXY(64, 2);cout << "Данные:" << endl;
                GotoXY(64, 3); cout << "Яблок:" << count << endl;
                GotoXY(64, 4); cout << "Длина:" << g.snake.PCount << endl;
                GotoXY(64, 5); cout << "Скорость:" << g.pause << endl;
                GotoXY(64, 7); cout << "Управление:" << endl;
                GotoXY(64, 8); cout << "Esc:Выход" << endl;
                GotoXY(64, 9); cout << "P:Пауза" << endl;
                GotoXY(64, 10); cout << "S:Старт" << endl;
                GotoXY(64, 11); cout << "L:Уровень" << endl;
                GotoXY(64, 13);printf("%c", 24);cout << ":Вверх" << endl;
                GotoXY(64, 14);printf("%c", 25);cout << ":Вниз" << endl;
                GotoXY(64, 15);printf("%c", 27);cout << ":Влево" << endl;
                GotoXY(64, 16);printf("%c", 26);cout << ":Вправо" << endl;
                if (count == 50)
                {
                    SetColor(White, Black);
                    GotoXY(24, 1); cout << "Вы выиграли,поздравляю!" << endl; 
                    _getch();
                    return(0);
                }
                break;

            case STENA:

            case FINISH:
                GotoXY(23, 1); printf("Вы проиграли!!!\n\n\t\t\t"); 
                playmusicGameEnd();
                _getch();
                break;
            }

            Sleep(g.pause); //пауза
        }
        key = _getch();

        //поставить игру на паузу
        if (key == 'P' || key == 'p')
            Pause = !Pause;
        else if (key == 'S' || key == 's') {
            playmusicStart();
            SnakeStart();
        }
           
        //выбор уровня
        else if (key == 'L' || key == 'l')
            Level();
        else if (key == 0 || key == 224)
        {
            key = _getch();

            if (key == 72 && g.nap != DOWN)
            {
                g.nap = UP;
                g.dx = 0;
                g.dy = -1;
            }
            else if (key == 80 && g.nap != UP)
            {
                g.nap = DOWN;
                g.dx = 0;
                g.dy = 1;
            }
            else if (key == 75 && g.nap != RIGHT)
            {
                g.nap = LEFT;
                g.dx = -1;
                g.dy = 0;
            }
            else if (key == 77 && g.nap != LEFT)
            {
                g.nap = RIGHT;
                g.dx = 1;
                g.dy = 0;
            }
        }
    }
}