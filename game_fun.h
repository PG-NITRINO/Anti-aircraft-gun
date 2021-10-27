#ifndef GAME_FUN_H_INCLUDED
#define GAME_FUN_H_INCLUDED
//В ней все отрисовываем
void DrawFrame();

//Деактивация при проигрыше
void AllDestroy(std::vector<Bullet> &bullet_vector_,
                std::vector<Bomb> &bomb_vector_,
                std::vector<Airplane> &airplane_vector_)
{
    for(unsigned int i = 0; i < bullet_vector_.size() - 1; i++)
    {
                bullet_vector_[i].destroy_bullet();
    }
    for(unsigned int i = 0; i < bomb_vector_.size() - 1; i++)
    {
                bomb_vector_[i].destroy_bomb();
    }
    for(unsigned int i = 0; i < airplane_vector_.size() - 1; i++)
    {
                airplane_vector_[i].destroy_airplane();
    }
}

//Бомба попала в машину
bool BombPlugMachine(const Machine &mech_, const Bomb &bomb_)
{
    if((mech_.x <= bomb_.x1 && mech_.x + mech_.length >= bomb_.x1
        && mech_.y <= bomb_.y2) ||
       (mech_.x <= bomb_.x2 && mech_.x + mech_.length >= bomb_.x2
        && mech_.y <= bomb_.y2))
    {
        return true;
    }
    else return false;
}

//Снаряд попал в бомбу
bool BulletPlugBomb(const Bullet &bul, const Bomb &bomb_)
{
    if((bul.x >= bomb_.x1) && (bul.x <= bomb_.x2) &&
        (bul.y <= bomb_.y2) && (bul.y >= bomb_.y1))
    {
        return true;
    }
    else return false;
}

//Снаряд попал в самолет
bool BulletPlugAirplane(const Bullet &bul, const Airplane &plane)
{
    if((bul.x >= plane.x1) && (bul.x <= plane.x2) &&
        (bul.y <= plane.y2) && (bul.y >= plane.y1))
    {
        return true;
    }
    else return false;
}

void CreateBullet_function(std::vector<Bullet> &bullet_vector_, Machine &mech_)
{
    int i(-1);
    bool flag = false; //Нашли неактивный снаряд
    do
    {
        i++;
        if(!bullet_vector_.at(i).check_active())
        {
            flag = true;
            bullet_vector_[i].set_bullet(mech);
        }
    }while((static_cast<unsigned int>(i)<bullet_vector_.size() - 1)
            && !(flag));
}
//Движение и уничтожение снарядов
void MoveBullet_function(HDC hdc, std::vector<Bullet> &bullet_vector_)
{
    for(unsigned int i = 0; i < bullet_vector_.size() - 1; i++)
    {
        if(bullet_vector_.at(i).check_active())
        {
            if(bullet_vector_[i].check_y_bullet())
            {
                ///летит дальше
                bullet_vector_[i].move_bullet(hdc);
            }
            else{
                ///уничтожается
                bullet_vector_[i].destroy_bullet();
            }
        }
    }
}

void GetClientCoordinates_function(HWND hWnd, RECT &rect)
{
    GetClientRect(hWnd, &rect);
    if(max_X_clientrect < rect.right)
        max_X_clientrect = rect.right;
    if(max_Y_clientrect < rect.bottom)
        max_Y_clientrect = rect.bottom;

    centerX = rect.right/2;
    centerY = rect.bottom/2;
    right_border = centerX + 75;
    left_border = centerX - 75;

    Ytop1 = centerY + 20; Ybot1 = centerY + 90;
    Ytop2 = centerY + 110; Ybot2 = centerY + 180;
    Ytop3 = centerY + 200; Ybot3 = centerY + 270;
    return;
}

void Esc_Draw(HWND hWnd, HDC hdc)
{
    GetClientCoordinates_function(hWnd, rect);
    HFONT hFont=CreateFontIndirect(&lf_game); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextColor(hdc, RGB(0,0,0)); //зададим цвет текста
    SetBkMode(hdc, 0); //прозрачный фон
    SetTextAlign(hdc, TA_CENTER|TA_BASELINE);

    HBRUSH brush_esc = CreatePatternBrush(stone_texture);//CreateSolidBrush(RGB(200, 200, 200));
    HPEN pen_esc = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
    SelectObject(hdc, pen_esc);
    SelectObject(hdc, brush_esc);

    Rectangle(hdc, centerX-170, centerY-100 ,centerX+170, centerY+100);
    Rectangle(hdc, centerX-140, centerY+60 ,centerX-10, centerY+90);
    Rectangle(hdc, centerX+10, centerY+60 ,centerX+140, centerY+90);
    TextOut(hdc, centerX-75, centerY+80, str_Yes, strlen(str_Yes));
    TextOut(hdc, centerX+75, centerY+80, str_No, strlen(str_No));
    TextOut(hdc, centerX, centerY, str_Do_you_want, strlen(str_Do_you_want));

    DeleteObject(pen_esc);
    DeleteObject(brush_esc);
    DeleteObject(hFont);
}

void About_Draw(HWND hWnd, HDC hdc)
{
    GetClientCoordinates_function(hWnd, rect);
    HBRUSH fonbrush = CreatePatternBrush(about_texture);
    SelectObject(hdc, fonbrush);
    FillRect(hdc, &rect, fonbrush);
    DeleteObject(fonbrush);

    fonbrush = CreatePatternBrush(button_texture);
    SelectObject(hdc, fonbrush);

    Rectangle(hdc, 20, 20, 170, 50);

    static int x_(170), y_(100), dy_(20);
    Rectangle(hdc, x_-20, y_-30, x_+250, y_+6*dy_+20);

    DeleteObject(fonbrush);

    HFONT hFont=CreateFontIndirect(&lf_menu); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextColor(hdc, RGB(0,0,0)); //зададим цвет текста
    SetBkMode(hdc, 0); //прозрачный фон
    //Меняем положение текста
    SetTextAlign(hdc, TA_CENTER|TA_BASELINE);

    TextOut(hdc, 95, 45, str_Back, strlen(str_Back));

    DeleteObject(hFont);

    hFont=CreateFontIndirect(&lf_game); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextAlign(hdc, TA_LEFT|TA_BASELINE);

    TextOut(hdc, x_, y_, str_LBM, strlen(str_LBM));
    TextOut(hdc, x_, y_+dy_, str_Esc, strlen(str_Esc));
    TextOut(hdc, x_, y_+2*dy_, str_P, strlen(str_P));
    TextOut(hdc, x_, y_+3*dy_, str____, strlen(str____));
    TextOut(hdc, x_, y_+4*dy_, str_red, strlen(str_red));
    TextOut(hdc, x_, y_+5*dy_, str_orange, strlen(str_orange));
    TextOut(hdc, x_, y_+6*dy_, str_green, strlen(str_green));

    DeleteObject(hFont);
}

void Menu_Draw(HWND hWnd, HDC hdc)
{
    GetClientCoordinates_function(hWnd, rect);
    HBRUSH fonbrush = CreatePatternBrush(menu_texture);
    SelectObject(hdc, fonbrush);
    FillRect(hdc, &rect, fonbrush);
    DeleteObject(fonbrush);

    fonbrush = CreatePatternBrush(button_texture);
    SelectObject(hdc, fonbrush);

    Rectangle(hdc, right_border, Ytop1, left_border, Ybot1);
    Rectangle(hdc, right_border, Ytop2, left_border, Ybot2);
    Rectangle(hdc, right_border, Ytop3, left_border, Ybot3);

    DeleteObject(fonbrush);

    HFONT hFont=CreateFontIndirect(&lf_menu); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextColor(hdc, RGB(0,0,0)); //зададим цвет текста
    SetBkMode(hdc, 0); //прозрачный фон

    //Меняем положение текста
    SetTextAlign(hdc, TA_CENTER|TA_BASELINE);
    TextOut(hdc, centerX, centerY+55+5, str_Start, strlen(str_Start));
    TextOut(hdc, centerX, centerY+145+5, str_About, strlen(str_About));
    TextOut(hdc, centerX, centerY+235+5, str_Exit, strlen(str_Exit));

    DeleteObject(hFont);
}

void Pause_Lose_Draw(HWND hWnd, HDC hdc)
{
    GetClientCoordinates_function(hWnd, rect);
    HFONT hFont=CreateFontIndirect(&lf_game); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextColor(hdc, RGB(0,0,0)); //зададим цвет текста
    SetBkMode(hdc, 0); //прозрачный фон
    SetTextAlign(hdc, TA_CENTER|TA_BASELINE);

    HBRUSH brush_lose = CreatePatternBrush(stone_texture);
    HPEN pen_lose = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
    SelectObject(hdc, pen_lose);
    SelectObject(hdc, brush_lose);
    if(lose)
    {//Игрок проиграл
        Rectangle(hdc, centerX-150, centerY-100 ,centerX+150, centerY+100);
        TextOut(hdc, centerX, centerY - 50, str_Your_score, strlen(str_Your_score));
    }
    else{//Просто пауза без проигрыша
        TextOut(hdc, centerX, centerY, str_Pause, strlen(str_Pause));
    }
    Rectangle(hdc, centerX-140, centerY+60 ,centerX-10, centerY+90);
    Rectangle(hdc, centerX+10, centerY+60 ,centerX+140, centerY+90);
    TextOut(hdc, centerX-75, centerY+80, str_Menu, strlen(str_Menu));
    TextOut(hdc, centerX+75, centerY+80, str_Play_again, strlen(str_Play_again));

    DeleteObject(pen_lose);
    DeleteObject(brush_lose);
    DeleteObject(hFont);
}

void Start_Draw(HWND hWnd, HDC hdc)
{
    static HBRUSH fonbrush_fill;
    fonbrush_fill = CreatePatternBrush(sky_night_texture);//небо
    static HBRUSH fonbrush_rect;
    fonbrush_rect = CreateSolidBrush(RGB(0, 200, 5));//трава
    static HPEN fonpen;
    fonpen = CreatePen(PS_SOLID, 0, RGB(0, 200, 5));

    SelectObject(hdc, fonbrush_fill);
    GetClientCoordinates_function(hWnd, rect);
    Rectangle(hdc, 0, 0, max_X_clientrect, max_Y_clientrect);
    DeleteObject(fonbrush_fill);

    SelectObject(hdc, fonbrush_rect);
    SelectObject(hdc, fonpen);  //трава
    Rectangle(hdc, 0, max_Y_clientrect-50, max_X_clientrect, max_Y_clientrect);
    DeleteObject(fonbrush_rect);
    DeleteObject(fonpen);

    HFONT hFont=CreateFontIndirect(&lf_game); //Cоздали шрифт
    SelectObject(hdc, hFont); //Он будет иметь силу только когда мы его выберем
    SetTextColor(hdc, RGB(0,0,0)); //зададим цвет текста
    SetBkMode(hdc, 0); //прозрачный фон

    sprintf(str_score, "%i", Total_score);
    strcpy(str_Total_score, str_Total);
    strcat(str_Total_score, str_score);

    //Меняем положение текста
    SetTextAlign(hdc, TA_LEFT|TA_BASELINE);
    TextOut(hdc, 25, max_Y_clientrect - 25 ,
            str_Total_score, strlen(str_Total_score));

    DeleteObject(hFont);
}
#endif // GAME_FUN_H_INCLUDED
