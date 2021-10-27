#ifndef LIBRARY_CONST_H_INCLUDED
#define LIBRARY_CONST_H_INCLUDED

#include <windows.h>
#include <vector> //для массива снарядов
#include <stdio.h> //для sprintf() - число в строку
#include <ctime> //для рандома

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//объявляем имя программы
char szProgName[]="Имя программы";
//Иконка
char szIconName[]="MYICON";
//Курсор
char szCursorName[]="MYCURSOR";
//Картинка
char szImageName[]="MYBMP";

RECT rect; ///Экземпляр структуры RECT для сохранения размеров окна

HWND hWnd;

HDC drawdc;             ///создаём контекст устройства для DrawFrame
bool isDrawing = true;  ///флаг работы процедуры DrawFrame
HDC backdc;             ///Буфер отрисовки
HBITMAP backBMP;        ///На этот битмап все отрисовываем а потом его выводим на экран


bool create_menu = true;///Отрисовка меню
bool about = false;     ///Отрисовка About(правила, управление, найстройки)
bool pause = false;     ///Игра поставлена на паузу
bool start = false;     ///Флаг начала игры
bool timer_fill = false;///Отрисовка происходит только по запросу таймера
bool fill_start = false;///Перезалить экран перед началом игры
bool lose = false;      ///Машину подбили и вылезло окно окончания игры
bool fire = false;      ///Флаг выстрела
bool esc = false;       ///Нажали кнопки Esc

int dx(0);              ///Смещение машины влево/вправо
const absolute_dx(10);  ///Смещение по модулю

const int max_bullet(20);   ///Максимальное кол-во снарядов одновременно на экране
const int max_airplane(4);  ///Максимальное кол-во самолетов одновременно на экране
                            ///почему то на 1 меньше
const int max_bomb = (max_airplane * 3); ///Максимальное кол-во бомб(по 3 на самолет)

int max_X_clientrect = 0;       ///Максимальный размер по Х пользовательского окна
int max_Y_clientrect = 0;       ///Максимальный размер по Y пользовательского окна

int Total_score(0);                   ///Всего набрано очков
const int Score_at_bomb(1);           ///Дается очков за уничтожение бомбы
const int Score_at_airplane(3);       ///Дается очков за уничтожение самолета

///Координаты мыши
int xPos(0);
int yPos(0);

///Координаты кнопок меню
int Ytop1, Ybot1;
int Ytop2, Ybot2;
int Ytop3, Ybot3;
int right_border, left_border;
int centerX(0), centerY(0);

///Текст меню
char str_Start[] = "Start";
char str_About[] = "About";
char str_Exit[] = "Exit";

char str_LBM[] = "LBM and Space - fire!";
char str_Esc[] = "Esc - Exit";
char str_P[] = "P - pause";
char str____[] = "----------------------";
char str_red[] = "Red - 1 health";
char str_orange[] = "Orange - 2 health";
char str_green[] = "Green - 3 health";
char str_Back[] = "Back";
///Текст в игре| "Total Score: " - длина 13
char str_Total[14] = "Total Score: ";
char str_score[7] = "";
char str_Total_score[20];

char str_Pause[] = "Pause";

char str_Your[13] = "Your Score: ";
char str_Your_score[21];
char str_Menu[] = "Menu";
char str_Play_again[] = "Play again";

///Текст Выхода
char str_Do_you_want[] = "Do you want to exit the program?";
char str_Yes[] = "Yes";
char str_No[] = "No";

///создаём экземпляры LOGFONT(шрифт)
LOGFONT lf_game;    ///Экземпляр для игры
LOGFONT lf_menu;    ///кземпляр для меню

///Текстуры
HBITMAP menu_texture;
char texture_menu[] = "MYMENU";

HBITMAP button_texture;
char texture_button[] = "MYBUTTON";

HBITMAP stone_texture;
char texture_stone[] = "MYSTONE";

HBITMAP about_texture;
char texture_about[] = "MYABOUT";

HBITMAP sky_texture;
char texture_sky[] = "MYSKY";

HBITMAP sky_night_texture;
char texture_sky_night[] = "MYSKYNIGHT";

HBITMAP mech_texture;
char texture_mech[] = "MYMECH";

///Текстуры самолетов
HBITMAP airplane_LtoR_red_texture;
char texture_airplane_LtoR_red[] = "MYAIRPLANE_LtoR_RED";
HBITMAP airplane_RtoL_red_texture;
char texture_airplane_RtoL_red[] = "MYAIRPLANE_RtoL_RED";

HBITMAP airplane_LtoR_orange_texture;
char texture_airplane_LtoR_orange[] = "MYAIRPLANE_LtoR_ORANGE";
HBITMAP airplane_RtoL_orange_texture;
char texture_airplane_RtoL_orange[] = "MYAIRPLANE_RtoL_ORANGE";

HBITMAP airplane_LtoR_green_texture;
char texture_airplane_LtoR_green[] = "MYAIRPLANE_LtoR_GREEN";
HBITMAP airplane_RtoL_green_texture;
char texture_airplane_RtoL_green[] = "MYAIRPLANE_RtoL_GREEN";

///Текстуры бомб
HBITMAP bomb_red_texture;
char texture_bomb_red[] = "MYBOMBRED";

HBITMAP bomb_orange_texture;
char texture_bomb_orange[] = "MYBOMBORANGE";

HBITMAP bomb_green_texture;
char texture_bomb_green[] = "MYBOMBGREEN";

#endif // LIBRARY_CONST_H_INCLUDED
