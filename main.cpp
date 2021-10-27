#include "library_const.h"
#include "game_class.h"
#include "game_fun.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    srand(static_cast<unsigned int>(time(0)));

    //HWND hWnd;
    MSG lpMsg;
    WNDCLASS w; //������ ��������� ��������� WNDCLASS

    w.lpszClassName=szProgName; //��� ��������� - ��������� ����
    w.hInstance=hInstance; //������������� �������� ����������
    w.lpfnWndProc=WndProc; //��������� �� ������� ����
    w.hCursor=LoadCursor(hInstance, szCursorName); //��������� ������
    w.hIcon=LoadIcon(hInstance, szIconName); //������ � ��� �� ����� ����
    w.lpszMenuName=0; //� ���� ���� �� �����
    w.hbrBackground = CreateSolidBrush(RGB(100,100,100));
    //w.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); //���� ���� ����
    w.style=CS_HREDRAW|CS_VREDRAW; //����� - ���������������� �� � � �� �
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    ///��������� ������ ��� ����
    lf_game.lfCharSet=DEFAULT_CHARSET; //�������� �� ���������
    lf_game.lfPitchAndFamily=DEFAULT_PITCH; //�������� �� ���������
    strcpy(lf_game.lfFaceName,"Times New Roman"); //�������� � ������ �������� ������
    lf_game.lfHeight=20; //������
    lf_game.lfWidth=10; //������
    lf_game.lfWeight=20; //�������
    lf_game.lfItalic=0; // - ���� ��� ���� �� ����� 0, ����� ����� ���������
    lf_game.lfUnderline=0; // - ���� ��� ���� �� ����� 0, ����� ����� ������������
    ///��������� ������ ��� ����
    lf_menu.lfCharSet=DEFAULT_CHARSET; //�������� �� ���������
    lf_menu.lfPitchAndFamily=DEFAULT_PITCH; //�������� �� ���������
    strcpy(lf_menu.lfFaceName,"Algerian"); //�������� � ������ �������� ������
    lf_menu.lfHeight=30; //������
    lf_menu.lfWidth=15; //������
    lf_menu.lfWeight=30; //�������
    lf_menu.lfItalic=0; // - ���� ��� ���� �� ����� 0, ����� ����� ���������
    lf_menu.lfUnderline=0; // - ���� ��� ���� �� ����� 0, ����� ����� ������������


    if(!RegisterClass(&w))
        return 0;

        ///��������
        menu_texture = LoadBitmap(hInstance, texture_menu);
        button_texture = LoadBitmap(hInstance, texture_button);
        stone_texture = LoadBitmap(hInstance, texture_stone);
        about_texture = LoadBitmap(hInstance, texture_about);
        sky_texture = LoadBitmap(hInstance, texture_sky);
        sky_night_texture = LoadBitmap(hInstance, texture_sky_night);

        mech_texture = LoadBitmap(hInstance, texture_mech);

        airplane_LtoR_red_texture = LoadBitmap(hInstance, texture_airplane_LtoR_red);
        airplane_RtoL_red_texture = LoadBitmap(hInstance, texture_airplane_RtoL_red);

        airplane_LtoR_orange_texture = LoadBitmap(hInstance, texture_airplane_LtoR_orange);
        airplane_RtoL_orange_texture = LoadBitmap(hInstance, texture_airplane_RtoL_orange);

        airplane_LtoR_green_texture = LoadBitmap(hInstance, texture_airplane_LtoR_green);
        airplane_RtoL_green_texture = LoadBitmap(hInstance, texture_airplane_RtoL_green);

        bomb_green_texture = LoadBitmap(hInstance, texture_bomb_green);
        bomb_orange_texture = LoadBitmap(hInstance, texture_bomb_orange);
        bomb_red_texture = LoadBitmap(hInstance, texture_bomb_red);


    hWnd=CreateWindow(szProgName,            //��� ���������
                    "Vendetta", //��������� ����
                    WS_OVERLAPPEDWINDOW,     //����� ���� - ���������������
                    100,                     //��������� ���� �� ������ �� �
                    100,                     //�� �
                    500,                     //������� �� �
                    400,                     //�� �
                    (HWND)NULL,         //������������� ������������� ����
                    (HMENU)NULL,        //������������� ����
                    (HINSTANCE)hInstance, //������������� ���������� ���������
                    (HINSTANCE)NULL); //���������� �������������� ����������

    //ShowWindow(hWnd, nCmdShow);  //�� �� ��� �����(��������)
    ShowWindow(hWnd, SW_SHOWMAXIMIZED); ///�� ���� �����
    UpdateWindow(hWnd);

    //������� �����, ������� ����� �������� � ���������� DrawFrame
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&DrawFrame,
                  NULL, 0, NULL); //������ ����� NULL - ������
    //������� ������
    //SetTimer(hWnd, 1000, 1000/60, NULL);

    while(GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg); //����������� ��������� ������ � �������
            DispatchMessage(&lpMsg); //������� ��������� ��������������� ������� ����
        }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps; //������ ��������� ��������� ������������ ������
    HDC hdc;

    switch(messg)
    {
        unsigned int key;

        /*����������� ���� 60 ��� � �������*/
    /*case WM_TIMER:
        timer_fill = true;
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
        break;*/

    case WM_KEYDOWN:
        key = wParam; //�������� ��� ������� �������

        switch(key)
        {
        case 32/*Space - fire!*/:
            if(start)
            {
                fire = true;
            }
            break;
        case 80/*P - pause*/:
            if(start)
            {
                pause = !pause;
            }
            break;
        case 27/*Esc - exit*/:
            if(start) pause = true;
            esc = true;
            //DestroyWindow(hWnd);
            break;
        }
        break;

    case WM_RBUTTONDOWN:
    case WM_LBUTTONDOWN:
        if(start && !pause)/*Space - fire!*/
            {
                fire = true;
            }
        if(create_menu && !esc)
        {
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);
            GetClientCoordinates_function(hWnd, rect);

            if(x>left_border && x<right_border)
            {
                if(y>Ytop1 && y<Ybot1)
                {//Start
                    start = true;
                    lose = false;
                    pause = false;
                    fill_start = true;
                    create_menu = false;
                    bullet_vector.resize(max_bullet);
                    airplane_vector.resize(max_airplane);
                    bomb_vector.resize(max_bomb);
                mech.set_mech((max_X_clientrect)/2-50, max_Y_clientrect-100, 100, 50);
                //����� - 100, ������ - 50
                    Total_score = 0;
                    xPos = centerX;
                }
                if(y>Ytop2 && y<Ybot2)
                {//About
                    about = true;
                    create_menu = false;
                }
                if(y>Ytop3 && y<Ybot3)
                {//Exit
                    DestroyWindow(hWnd);
                }
            }
        }
        if(pause && !esc) //�������� ����� � lose
        {
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);
            if(y>=centerY+60 && y<=centerY+90)
            {
                if(x>=centerX-140 && x<=centerX-10)
                {//����
                    start = false;
                    create_menu = true;
                    //��� ������������
                    AllDestroy(bullet_vector, bomb_vector, airplane_vector);
                }
                if(x>=centerX+10 && x<=centerX+140)
                {//������ �����
                    lose = false;
                    pause = false;
                    //��� ������������
                    AllDestroy(bullet_vector, bomb_vector, airplane_vector);
                mech.set_mech((max_X_clientrect)/2-50, max_Y_clientrect-100, 100, 50);
                    Total_score = 0;
                    xPos = centerX;
                }
            }
        }
        if(about && !esc)
        {
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);
            if(x>=20 && x<=170 && y>=20 && y<=50)
            {
                about = false;
                create_menu = true;
            }
        }
        if(esc)
        {
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);
            if(y>=centerY+60 && y<=centerY+90)
            {
                if(x>=centerX-140 && x<=centerX-10)
                {//Yes
                    DestroyWindow(hWnd);
                }
                if(x>=centerX+10 && x<=centerX+140)
                {//No
                    if(start) pause = false;
                    esc = false;
                }
            }
        }
        break;

    case WM_MOUSEMOVE:
        if(start)
        {//�������� ���������� ���� ��� �������� ������
            xPos=LOWORD(lParam);
        }
    case WM_PAINT :

        hdc=BeginPaint(hWnd, &ps);
{
        /*if(timer_fill)
        {
            timer_fill = false;
            if(start)
            {
                if(fill_start)
                {
                    Start_Draw(hWnd, hdc);
                }

                //������ �������� ������
                //�������� ��������� � ��������
                if(!pause)
                {
                    static int random;
                    random = rand() % (31); //��������� �������� ��������
                    if(random == 0)
                    {
                        int i(-1);
                        bool flag = false; //����� ���������� �������
                        do
                        {
                            i++;
                            if(!airplane_vector.at(i).check_active())
                            {
                                flag = true;
                                random = rand() % (2);  //0 ��� 1
                                static int rand_speed;
                                rand_speed = rand() % (3) + 3; //�� 3 �� 5
                                //����� � ������ ���������� 70�20
                                airplane_vector[i].set_airplane(70, 20, random, rand_speed);
                            }
                        }while((static_cast<unsigned int>(i) < airplane_vector.size() - 1)
                                && !(flag));
                    }

                    if(fire) //�������� ��������
                    {
                        fire = false;
                        //������������� ��� ������� �� ����������� �������� ������
                        CreateBullet_function(bullet_vector, mech);
                    }

                    {//������ �������� ������
                        int x_, y_;
                        mech.get_xy_machine(x_, y_);
                        if(x_ < xPos)
                        {
                            if(x_+absolute_dx <= xPos)  //����� �� ���� ���������
                                dx = absolute_dx;
                            else dx = 1;
                        }
                        else
                        if(x_ > xPos){
                                if(x_ - absolute_dx >= xPos)
                                    dx = -absolute_dx;
                                else dx = -1;
                        }
                        else dx = 0;
                    }
                }

                mech.Draw_Machine(hdc,dx); ///����������� ������ ���������� ������
                dx=0;

                //�������� � ����������� ��������
                MoveBullet_function(hdc, bullet_vector);

                //�������� � ����������� ���������, �������� ����
                for(unsigned int i = 0; i < airplane_vector.size() - 1; i++)
                {
                    if(airplane_vector.at(i).check_active())
                    {
                        //����� �� ������� ������ ������
                        if(airplane_vector[i].check_x_airplane(true))
                        {
                            ///���������� �� ������� �� ��������
                            //����� �� ������� �������� �����
                            if(!pause)
                            {
                                ///���������� �� ������� �� ��������
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugAirplane(bullet_vector.at(j), airplane_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //�������� ����� � ��������, ���� ���� - �� �����������
                                            if(!(airplane_vector[i].SubHealth_airplane()))
                                            {
                                                airplane_vector[i].destroy_airplane();
                                                Total_score += Score_at_airplane;
                                            }
                                        }
                                    }
                                }
                                //����� �� ������� �������� �����
                                if(airplane_vector[i].check_x_airplane(false))
                                {
                                    ///������ �����
                                    static int random_bomb;
                                    random_bomb = rand() % (21);
                                    if(random_bomb == 0)
                                    {
                                        int j(-1);
                                        bool flag = false; //����� ���������� �����
                                        do
                                        {
                                            j++;
                                            if(!bomb_vector.at(j).check_active())
                                            {
                                                flag = true;
                                                bomb_vector[j].set_bomb(airplane_vector[i]);
                                            }
                                        }while((static_cast<unsigned int>(j)<bomb_vector.size() - 1)
                                                && !(flag));
                                    }
                                }
                            }
                            ///������� ����� ������
                            airplane_vector[i].move_airplane(hdc);
                        }
                        else{
                            ///������������
                            airplane_vector[i].destroy_airplane();
                        }
                    }
                }

                //�������� ����, ������������ ���� �� ��������� � �������
                for(unsigned int i = 0; i < bomb_vector.size() - 1; i++)
                {
                    if(bomb_vector.at(i).check_active())
                    {
                        if(bomb_vector[i].check_y_bomb())
                        {
                            ///����������� �� ����� �� ��������
                            ///����������� �� ����� � �������
                            if(!pause)
                            {
                                ///����������� �� ����� �� ��������
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugBomb(bullet_vector.at(j), bomb_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //�������� ����� � �����, ���� ���� - �� �����������
                                            if(!(bomb_vector[i].SubHealth_Bomb()))
                                            {
                                                bomb_vector[i].destroy_bomb();
                                                Total_score += Score_at_bomb;
                                            }
                                        }
                                    }
                                }
                                ///����������� �� ����� � �������
                                if(BombPlugMachine(mech, bomb_vector[i]))
                                {
                                    lose = true;
                                    pause = true;
                                    sprintf(str_score, "%i", Total_score);
                                    strcpy(str_Your_score, str_Your);
                                    strcat(str_Your_score, str_score);
                                }
                                else{///����� ������
                                bomb_vector[i].move_bomb(hdc);}
                            }
                            else{///����� ������(������ �������������� ��� ��������)
                            bomb_vector[i].move_bomb(hdc);}
                        }
                        else{
                            ///������������
                            bomb_vector[i].destroy_bomb();
                        }
                    }
                }

                //���� ���������� �� ����� ��� ����� ��������
                if(pause && !esc) //��� ������ Esc ������ ����
                {
                    Pause_Lose_Draw(hWnd, hdc);
                }
            }

            if(create_menu)
            {
                Menu_Draw(hWnd, hdc);
            }

            if(about)
            {
                About_Draw(hWnd, hdc);
            }

            if(esc)
            {
                Esc_Draw(hWnd, hdc);
            }
        }*/
}

        BitBlt(hdc, 0, 0, rect.right, rect.bottom, backdc, 0, 0, SRCCOPY);

        ValidateRect(hWnd, NULL);
        EndPaint(hWnd, &ps);

        break;

    case WM_DESTROY:
        isDrawing = false; //��������� ��������� � ������ DrawFrame
        PostQuitMessage(0); //�������� ��������� ������ � ����� 0 - ���������� ����������
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //����������� ������� ���������� �� �������������
    }
return 0;
}

void DrawFrame()
{
    GetClientRect(hWnd, &rect);
    drawdc = GetDC(hWnd);
    backdc = CreateCompatibleDC(drawdc);       //������������ � ������ ���������
    backBMP = CreateCompatibleBitmap(drawdc, rect.right, rect.bottom);
    HGDIOBJ oldBMP  = SelectObject(backdc, backBMP);  //��������� ��� ������ ������ BMP

    ReleaseDC(hWnd, drawdc);

    while(isDrawing)
    {
        if(start)
            {
                if(fill_start)
                {
                    Start_Draw(hWnd, backdc);
                }

                //������ �������� ������
                //�������� ��������� � ��������
                if(!pause)
                {
                    static int random;
                    random = rand() % (31); //��������� �������� ��������
                    if(random == 0)
                    {
                        int i(-1);
                        bool flag = false; //����� ���������� �������
                        do
                        {
                            i++;
                            if(!airplane_vector.at(i).check_active())
                            {
                                flag = true;
                                random = rand() % (2);  //0 ��� 1
                                static int rand_speed;
                                rand_speed = rand() % (3) + 3; //�� 3 �� 5
                                //����� � ������ ���������� 70�20
                                airplane_vector[i].set_airplane(70, 20, random, rand_speed);
                            }
                        }while((static_cast<unsigned int>(i) < airplane_vector.size() - 1)
                                && !(flag));
                    }

                    if(fire) //�������� ��������
                    {
                        fire = false;
                        //������������� ��� ������� �� ����������� �������� ������
                        CreateBullet_function(bullet_vector, mech);
                    }

                    {//������ �������� ������
                        int x_, y_;
                        mech.get_xy_machine(x_, y_);
                        if(x_ < xPos)
                        {
                            if(x_+absolute_dx <= xPos)  //����� �� ���� ���������
                                dx = absolute_dx;
                            else dx = 1;
                        }
                        else
                        if(x_ > xPos){
                                if(x_ - absolute_dx >= xPos)
                                    dx = -absolute_dx;
                                else dx = -1;
                        }
                        else dx = 0;
                    }
                }

                mech.Draw_Machine(backdc,dx); ///����������� ������ ���������� ������
                dx=0;

                //�������� � ����������� ��������
                MoveBullet_function(backdc, bullet_vector);

                //�������� � ����������� ���������, �������� ����
                for(unsigned int i = 0; i < airplane_vector.size() - 1; i++)
                {
                    if(airplane_vector.at(i).check_active())
                    {
                        //����� �� ������� ������ ������
                        if(airplane_vector[i].check_x_airplane(true))
                        {
                            ///���������� �� ������� �� ��������
                            //����� �� ������� �������� �����
                            if(!pause)
                            {
                                ///���������� �� ������� �� ��������
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugAirplane(bullet_vector.at(j), airplane_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //�������� ����� � ��������, ���� ���� - �� �����������
                                            if(!(airplane_vector[i].SubHealth_airplane()))
                                            {
                                                airplane_vector[i].destroy_airplane();
                                                Total_score += Score_at_airplane;
                                            }
                                        }
                                    }
                                }
                                //����� �� ������� �������� �����
                                if(airplane_vector[i].check_x_airplane(false))
                                {
                                    ///������ �����
                                    static int random_bomb;
                                    random_bomb = rand() % (21);
                                    if(random_bomb == 0)
                                    {
                                        int j(-1);
                                        bool flag = false; //����� ���������� �����
                                        do
                                        {
                                            j++;
                                            if(!bomb_vector.at(j).check_active())
                                            {
                                                flag = true;
                                                bomb_vector[j].set_bomb(airplane_vector[i]);
                                            }
                                        }while((static_cast<unsigned int>(j)<bomb_vector.size() - 1)
                                                && !(flag));
                                    }
                                }
                            }
                            ///������� ����� ������
                            airplane_vector[i].move_airplane(backdc);
                        }
                        else{
                            ///������������
                            airplane_vector[i].destroy_airplane();
                        }
                    }
                }

                //�������� ����, ������������ ���� �� ��������� � �������
                for(unsigned int i = 0; i < bomb_vector.size() - 1; i++)
                {
                    if(bomb_vector.at(i).check_active())
                    {
                        if(bomb_vector[i].check_y_bomb())
                        {
                            ///����������� �� ����� �� ��������
                            ///����������� �� ����� � �������
                            if(!pause)
                            {
                                ///����������� �� ����� �� ��������
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugBomb(bullet_vector.at(j), bomb_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //�������� ����� � �����, ���� ���� - �� �����������
                                            if(!(bomb_vector[i].SubHealth_Bomb()))
                                            {
                                                bomb_vector[i].destroy_bomb();
                                                Total_score += Score_at_bomb;
                                            }
                                        }
                                    }
                                }
                                ///����������� �� ����� � �������
                                if(BombPlugMachine(mech, bomb_vector[i]))
                                {
                                    lose = true;
                                    pause = true;
                                    sprintf(str_score, "%i", Total_score);
                                    strcpy(str_Your_score, str_Your);
                                    strcat(str_Your_score, str_score);
                                }
                                else{///����� ������
                                bomb_vector[i].move_bomb(backdc);}
                            }
                            else{///����� ������(������ �������������� ��� ��������)
                            bomb_vector[i].move_bomb(backdc);}
                        }
                        else{
                            ///������������
                            bomb_vector[i].destroy_bomb();
                        }
                    }
                }

                //���� ���������� �� ����� ��� ����� ��������
                if(pause && !esc) //��� ������ Esc ������ ����
                {
                    Pause_Lose_Draw(hWnd, backdc);
                }
            }
        if(create_menu)
        {
            Menu_Draw(hWnd, backdc);
        }

        if(about)
        {
            About_Draw(hWnd, backdc);
        }

        if(esc)
        {
            Esc_Draw(hWnd, backdc);
        }

        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

        Sleep(1000/60);
    }

    SelectObject(backdc, oldBMP);
    DeleteObject(backBMP);
    DeleteDC(backdc);
}
