#include "library_const.h"
#include "game_class.h"
#include "game_fun.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    srand(static_cast<unsigned int>(time(0)));

    //HWND hWnd;
    MSG lpMsg;
    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName=szProgName; //имя программы - объявлено выше
    w.hInstance=hInstance; //идентификатор текущего приложения
    w.lpfnWndProc=WndProc; //указатель на функцию окна
    w.hCursor=LoadCursor(hInstance, szCursorName); //загружаем курсор
    w.hIcon=LoadIcon(hInstance, szIconName); //иконки у нас не будет пока
    w.lpszMenuName=0; //и меню пока не будет
    w.hbrBackground = CreateSolidBrush(RGB(100,100,100));
    //w.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
    w.style=CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    ///Настройки текста для игры
    lf_game.lfCharSet=DEFAULT_CHARSET; //значение по умолчанию
    lf_game.lfPitchAndFamily=DEFAULT_PITCH; //значения по умолчанию
    strcpy(lf_game.lfFaceName,"Times New Roman"); //копируем в строку название шрифта
    lf_game.lfHeight=20; //высота
    lf_game.lfWidth=10; //ширина
    lf_game.lfWeight=20; //толщина
    lf_game.lfItalic=0; // - если это поле не равно 0, шрифт будет курсивный
    lf_game.lfUnderline=0; // - если это поле не равно 0, шрифт будет подчёркнутый
    ///Настройки текста для меню
    lf_menu.lfCharSet=DEFAULT_CHARSET; //значение по умолчанию
    lf_menu.lfPitchAndFamily=DEFAULT_PITCH; //значения по умолчанию
    strcpy(lf_menu.lfFaceName,"Algerian"); //копируем в строку название шрифта
    lf_menu.lfHeight=30; //высота
    lf_menu.lfWidth=15; //ширина
    lf_menu.lfWeight=30; //толщина
    lf_menu.lfItalic=0; // - если это поле не равно 0, шрифт будет курсивный
    lf_menu.lfUnderline=0; // - если это поле не равно 0, шрифт будет подчёркнутый


    if(!RegisterClass(&w))
        return 0;

        ///Текстуры
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


    hWnd=CreateWindow(szProgName,            //Имя программы
                    "Vendetta", //Заголовок окна
                    WS_OVERLAPPEDWINDOW,     //Стиль окна - перекрывающееся
                    100,                     //положение окна на экране по х
                    100,                     //по у
                    500,                     //размеры по х
                    400,                     //по у
                    (HWND)NULL,         //идентификатор родительского окна
                    (HMENU)NULL,        //идентификатор меню
                    (HINSTANCE)hInstance, //идентификатор экземпляра программы
                    (HINSTANCE)NULL); //отсутствие дополнительных параметров

    //ShowWindow(hWnd, nCmdShow);  //не на все экран(стандарт)
    ShowWindow(hWnd, SW_SHOWMAXIMIZED); ///на весь экран
    UpdateWindow(hWnd);

    //Создаем поток, который будет работать с процедурой DrawFrame
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&DrawFrame,
                  NULL, 0, NULL); //Вместо нулей NULL - ошибка
    //Создаем таймер
    //SetTimer(hWnd, 1000, 1000/60, NULL);

    while(GetMessage(&lpMsg, NULL, 0, 0))
        {
            TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
            DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
        }
    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
    HDC hdc;

    switch(messg)
    {
        unsigned int key;

        /*Перерисовка окна 60 раз в секунду*/
    /*case WM_TIMER:
        timer_fill = true;
        RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
        break;*/

    case WM_KEYDOWN:
        key = wParam; //Получаем код нажатой клавиши

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
                //длина - 100, высота - 50
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
        if(pause && !esc) //Работает также с lose
        {
            int x=LOWORD(lParam);
            int y=HIWORD(lParam);
            if(y>=centerY+60 && y<=centerY+90)
            {
                if(x>=centerX-140 && x<=centerX-10)
                {//Меню
                    start = false;
                    create_menu = true;
                    //Все деактивируем
                    AllDestroy(bullet_vector, bomb_vector, airplane_vector);
                }
                if(x>=centerX+10 && x<=centerX+140)
                {//Играть снова
                    lose = false;
                    pause = false;
                    //Все деактивируем
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
        {//Получаем координаты мыши для движения машины
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

                //Расчет смещения машины
                //создание самолетов и снарядов
                if(!pause)
                {
                    static int random;
                    random = rand() % (31); //Случайное создание самолета
                    if(random == 0)
                    {
                        int i(-1);
                        bool flag = false; //Нашли неактивный самолет
                        do
                        {
                            i++;
                            if(!airplane_vector.at(i).check_active())
                            {
                                flag = true;
                                random = rand() % (2);  //0 или 1
                                static int rand_speed;
                                rand_speed = rand() % (3) + 3; //от 3 до 5
                                //Длина и высота постоянные 70Х20
                                airplane_vector[i].set_airplane(70, 20, random, rand_speed);
                            }
                        }while((static_cast<unsigned int>(i) < airplane_vector.size() - 1)
                                && !(flag));
                    }

                    if(fire) //Создание снарядов
                    {
                        fire = false;
                        //Просматриваем все снаряды на возможность создания нового
                        CreateBullet_function(bullet_vector, mech);
                    }

                    {//Расчет смещения машины
                        int x_, y_;
                        mech.get_xy_machine(x_, y_);
                        if(x_ < xPos)
                        {
                            if(x_+absolute_dx <= xPos)  //Чтобы не было колебаний
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

                mech.Draw_Machine(hdc,dx); ///Перерисовка машины происходит всегда
                dx=0;

                //Движение и уничтожение снарядов
                MoveBullet_function(hdc, bullet_vector);

                //Движение и уничтожение самолетов, создание бомб
                for(unsigned int i = 0; i < airplane_vector.size() - 1; i++)
                {
                    if(airplane_vector.at(i).check_active())
                    {
                        //Может ли самолет лететь дальше
                        if(airplane_vector[i].check_x_airplane(true))
                        {
                            ///Столкнулся ли самолет со снарядом
                            //Может ли самолет сбросить бомбу
                            if(!pause)
                            {
                                ///Столкнулся ли самолет со снарядом
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugAirplane(bullet_vector.at(j), airplane_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //Вычитаем жизнь у самолета, если ноль - то деактивация
                                            if(!(airplane_vector[i].SubHealth_airplane()))
                                            {
                                                airplane_vector[i].destroy_airplane();
                                                Total_score += Score_at_airplane;
                                            }
                                        }
                                    }
                                }
                                //Может ли самолет сбросить бомбу
                                if(airplane_vector[i].check_x_airplane(false))
                                {
                                    ///Падает бомба
                                    static int random_bomb;
                                    random_bomb = rand() % (21);
                                    if(random_bomb == 0)
                                    {
                                        int j(-1);
                                        bool flag = false; //Нашли неактивную бомбу
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
                            ///Самолет летит дальше
                            airplane_vector[i].move_airplane(hdc);
                        }
                        else{
                            ///уничтожается
                            airplane_vector[i].destroy_airplane();
                        }
                    }
                }

                //Движение бомб, столкновение бомб со снарядами и машиной
                for(unsigned int i = 0; i < bomb_vector.size() - 1; i++)
                {
                    if(bomb_vector.at(i).check_active())
                    {
                        if(bomb_vector[i].check_y_bomb())
                        {
                            ///Столкнулась ли бомба со снарядом
                            ///Столкнулась ли бомба с машиной
                            if(!pause)
                            {
                                ///Столкнулась ли бомба со снарядом
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugBomb(bullet_vector.at(j), bomb_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //Вычитаем жизнь у бомбы, если ноль - то деактивация
                                            if(!(bomb_vector[i].SubHealth_Bomb()))
                                            {
                                                bomb_vector[i].destroy_bomb();
                                                Total_score += Score_at_bomb;
                                            }
                                        }
                                    }
                                }
                                ///Столкнулась ли бомба с машиной
                                if(BombPlugMachine(mech, bomb_vector[i]))
                                {
                                    lose = true;
                                    pause = true;
                                    sprintf(str_score, "%i", Total_score);
                                    strcpy(str_Your_score, str_Your);
                                    strcat(str_Your_score, str_score);
                                }
                                else{///летит дальше
                                bomb_vector[i].move_bomb(hdc);}
                            }
                            else{///летит дальше(просто перерисовываем без расчетов)
                            bomb_vector[i].move_bomb(hdc);}
                        }
                        else{
                            ///уничтожается
                            bomb_vector[i].destroy_bomb();
                        }
                    }
                }

                //Игра поставлена на паузу или игрок проиграл
                if(pause && !esc) //Для кнопки Esc другой блок
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
        isDrawing = false; //Закрываем отрисовку в потоке DrawFrame
        PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
return 0;
}

void DrawFrame()
{
    GetClientRect(hWnd, &rect);
    drawdc = GetDC(hWnd);
    backdc = CreateCompatibleDC(drawdc);       //Отрисовываем в другом контексте
    backBMP = CreateCompatibleBitmap(drawdc, rect.right, rect.bottom);
    HGDIOBJ oldBMP  = SelectObject(backdc, backBMP);  //Сохраняем при выборе старый BMP

    ReleaseDC(hWnd, drawdc);

    while(isDrawing)
    {
        if(start)
            {
                if(fill_start)
                {
                    Start_Draw(hWnd, backdc);
                }

                //Расчет смещения машины
                //создание самолетов и снарядов
                if(!pause)
                {
                    static int random;
                    random = rand() % (31); //Случайное создание самолета
                    if(random == 0)
                    {
                        int i(-1);
                        bool flag = false; //Нашли неактивный самолет
                        do
                        {
                            i++;
                            if(!airplane_vector.at(i).check_active())
                            {
                                flag = true;
                                random = rand() % (2);  //0 или 1
                                static int rand_speed;
                                rand_speed = rand() % (3) + 3; //от 3 до 5
                                //Длина и высота постоянные 70Х20
                                airplane_vector[i].set_airplane(70, 20, random, rand_speed);
                            }
                        }while((static_cast<unsigned int>(i) < airplane_vector.size() - 1)
                                && !(flag));
                    }

                    if(fire) //Создание снарядов
                    {
                        fire = false;
                        //Просматриваем все снаряды на возможность создания нового
                        CreateBullet_function(bullet_vector, mech);
                    }

                    {//Расчет смещения машины
                        int x_, y_;
                        mech.get_xy_machine(x_, y_);
                        if(x_ < xPos)
                        {
                            if(x_+absolute_dx <= xPos)  //Чтобы не было колебаний
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

                mech.Draw_Machine(backdc,dx); ///Перерисовка машины происходит всегда
                dx=0;

                //Движение и уничтожение снарядов
                MoveBullet_function(backdc, bullet_vector);

                //Движение и уничтожение самолетов, создание бомб
                for(unsigned int i = 0; i < airplane_vector.size() - 1; i++)
                {
                    if(airplane_vector.at(i).check_active())
                    {
                        //Может ли самолет лететь дальше
                        if(airplane_vector[i].check_x_airplane(true))
                        {
                            ///Столкнулся ли самолет со снарядом
                            //Может ли самолет сбросить бомбу
                            if(!pause)
                            {
                                ///Столкнулся ли самолет со снарядом
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugAirplane(bullet_vector.at(j), airplane_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //Вычитаем жизнь у самолета, если ноль - то деактивация
                                            if(!(airplane_vector[i].SubHealth_airplane()))
                                            {
                                                airplane_vector[i].destroy_airplane();
                                                Total_score += Score_at_airplane;
                                            }
                                        }
                                    }
                                }
                                //Может ли самолет сбросить бомбу
                                if(airplane_vector[i].check_x_airplane(false))
                                {
                                    ///Падает бомба
                                    static int random_bomb;
                                    random_bomb = rand() % (21);
                                    if(random_bomb == 0)
                                    {
                                        int j(-1);
                                        bool flag = false; //Нашли неактивную бомбу
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
                            ///Самолет летит дальше
                            airplane_vector[i].move_airplane(backdc);
                        }
                        else{
                            ///уничтожается
                            airplane_vector[i].destroy_airplane();
                        }
                    }
                }

                //Движение бомб, столкновение бомб со снарядами и машиной
                for(unsigned int i = 0; i < bomb_vector.size() - 1; i++)
                {
                    if(bomb_vector.at(i).check_active())
                    {
                        if(bomb_vector[i].check_y_bomb())
                        {
                            ///Столкнулась ли бомба со снарядом
                            ///Столкнулась ли бомба с машиной
                            if(!pause)
                            {
                                ///Столкнулась ли бомба со снарядом
                                for(unsigned int j = 0; j < bullet_vector.size() - 1; j++)
                                {
                                    if(bullet_vector.at(j).check_active())
                                    {
                                        if(BulletPlugBomb(bullet_vector.at(j), bomb_vector[i]))
                                        {
                                            bullet_vector[j].destroy_bullet();

                                            //Вычитаем жизнь у бомбы, если ноль - то деактивация
                                            if(!(bomb_vector[i].SubHealth_Bomb()))
                                            {
                                                bomb_vector[i].destroy_bomb();
                                                Total_score += Score_at_bomb;
                                            }
                                        }
                                    }
                                }
                                ///Столкнулась ли бомба с машиной
                                if(BombPlugMachine(mech, bomb_vector[i]))
                                {
                                    lose = true;
                                    pause = true;
                                    sprintf(str_score, "%i", Total_score);
                                    strcpy(str_Your_score, str_Your);
                                    strcat(str_Your_score, str_score);
                                }
                                else{///летит дальше
                                bomb_vector[i].move_bomb(backdc);}
                            }
                            else{///летит дальше(просто перерисовываем без расчетов)
                            bomb_vector[i].move_bomb(backdc);}
                        }
                        else{
                            ///уничтожается
                            bomb_vector[i].destroy_bomb();
                        }
                    }
                }

                //Игра поставлена на паузу или игрок проиграл
                if(pause && !esc) //Для кнопки Esc другой блок
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
