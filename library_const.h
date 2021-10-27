#ifndef LIBRARY_CONST_H_INCLUDED
#define LIBRARY_CONST_H_INCLUDED

#include <windows.h>
#include <vector> //��� ������� ��������
#include <stdio.h> //��� sprintf() - ����� � ������
#include <ctime> //��� �������

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//��������� ��� ���������
char szProgName[]="��� ���������";
//������
char szIconName[]="MYICON";
//������
char szCursorName[]="MYCURSOR";
//��������
char szImageName[]="MYBMP";

RECT rect; ///��������� ��������� RECT ��� ���������� �������� ����

HWND hWnd;

HDC drawdc;             ///������ �������� ���������� ��� DrawFrame
bool isDrawing = true;  ///���� ������ ��������� DrawFrame
HDC backdc;             ///����� ���������
HBITMAP backBMP;        ///�� ���� ������ ��� ������������ � ����� ��� ������� �� �����


bool create_menu = true;///��������� ����
bool about = false;     ///��������� About(�������, ����������, ����������)
bool pause = false;     ///���� ���������� �� �����
bool start = false;     ///���� ������ ����
bool timer_fill = false;///��������� ���������� ������ �� ������� �������
bool fill_start = false;///���������� ����� ����� ������� ����
bool lose = false;      ///������ ������� � ������� ���� ��������� ����
bool fire = false;      ///���� ��������
bool esc = false;       ///������ ������ Esc

int dx(0);              ///�������� ������ �����/������
const absolute_dx(10);  ///�������� �� ������

const int max_bullet(20);   ///������������ ���-�� �������� ������������ �� ������
const int max_airplane(4);  ///������������ ���-�� ��������� ������������ �� ������
                            ///������ �� �� 1 ������
const int max_bomb = (max_airplane * 3); ///������������ ���-�� ����(�� 3 �� �������)

int max_X_clientrect = 0;       ///������������ ������ �� � ����������������� ����
int max_Y_clientrect = 0;       ///������������ ������ �� Y ����������������� ����

int Total_score(0);                   ///����� ������� �����
const int Score_at_bomb(1);           ///������ ����� �� ����������� �����
const int Score_at_airplane(3);       ///������ ����� �� ����������� ��������

///���������� ����
int xPos(0);
int yPos(0);

///���������� ������ ����
int Ytop1, Ybot1;
int Ytop2, Ybot2;
int Ytop3, Ybot3;
int right_border, left_border;
int centerX(0), centerY(0);

///����� ����
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
///����� � ����| "Total Score: " - ����� 13
char str_Total[14] = "Total Score: ";
char str_score[7] = "";
char str_Total_score[20];

char str_Pause[] = "Pause";

char str_Your[13] = "Your Score: ";
char str_Your_score[21];
char str_Menu[] = "Menu";
char str_Play_again[] = "Play again";

///����� ������
char str_Do_you_want[] = "Do you want to exit the program?";
char str_Yes[] = "Yes";
char str_No[] = "No";

///������ ���������� LOGFONT(�����)
LOGFONT lf_game;    ///��������� ��� ����
LOGFONT lf_menu;    ///�������� ��� ����

///��������
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

///�������� ���������
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

///�������� ����
HBITMAP bomb_red_texture;
char texture_bomb_red[] = "MYBOMBRED";

HBITMAP bomb_orange_texture;
char texture_bomb_orange[] = "MYBOMBORANGE";

HBITMAP bomb_green_texture;
char texture_bomb_green[] = "MYBOMBGREEN";

#endif // LIBRARY_CONST_H_INCLUDED
