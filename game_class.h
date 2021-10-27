#ifndef GAME_CLASS_H_INCLUDED
#define GAME_CLASS_H_INCLUDED
class Bomb;
class Airplane;

class Machine{
private:
    int x, y; //���������� ������ �������� ����
    int height, length;  //������ � ����� ������
    HPEN p_main;
    HBRUSH b_main;

public:
    //�����������
    Machine()
    {
        p_main = CreatePen(PS_SOLID, 1, RGB(255,0,0));
        b_main = CreateSolidBrush(RGB(50,50,250));
    }

    void set_mech(int x1, int y1, int length1, int height1)
    {
        x = x1;
        y = y1;
        height = height1;
        length = length1;
    }
    //dx - �������� �� �
    void Draw_Machine(HDC hdc, int dx)
    {
        if((x+dx>=0) && (x+length+dx<=max_X_clientrect) && !pause)
        {
            x = x+dx;
        }
        //SelectObject(hdc, p_main);
        //SelectObject(hdc, b_main);
        //Rectangle(hdc, x, y, x+length, y+height);
        BITMAP mech_object;
        GetObject (mech_texture, sizeof(BITMAP), &mech_object);
        HDC memdc = CreateCompatibleDC(hdc);
        SelectObject(memdc, mech_texture);

BitBlt(hdc, x, y, mech_object.bmWidth, mech_object.bmHeight, memdc, 0, 0, SRCCOPY);

        DeleteDC(memdc);
        return;
    }

    //���������� �������� ������ ��� ��������
    void get_xy_machine(int &x1, int &y1)
    {
        x1=x + length/2;
        y1=y;
        return;
    }

    friend class Bullet;  //������� ������������ ������
    //�������� ��������� ����� � ������
    friend bool BombPlugMachine(const Machine &mech_, const Bomb &bomb_);

    //����������
    ~Machine()
    {
        DeleteObject(p_main);
        DeleteObject(b_main);
    }
};

Machine mech;

class Bullet{
private:
    int x, y; // ���������� �������
    bool active; //������ ���������� � ��������� �� ������
    HPEN p_main;
    HBRUSH b_main;
public:
    //�����������
    Bullet()
    {
        active = false;
        p_main = CreatePen(PS_SOLID, 1, RGB(0,255,0));
        b_main = CreateSolidBrush(RGB(0,0,0));
    }

    void move_bullet(HDC hdc)
    {
        if(!pause) y = y-5;
        SelectObject(hdc, p_main);
        SelectObject(hdc, b_main);
        Ellipse(hdc, x - 2, y - 5, x + 2, y + 5);
    }

    void set_bullet(const Machine &mech_) //��������� ������ �������
    {
        x = mech_.x + mech_.length/2;
        y = mech_.y;
        active = true;
        return;
    }

    void destroy_bullet() //����������� ������� ��� ������ �� ������� ������
    {
        active = false;
    }

    bool check_active()  //�������� ���������� �������
    {
        return active;
    }

    bool check_y_bullet()  //�������� �� ����� �� ������ �� ������� ������
    {
        return (y>-10);
    }

    //������ ����� � �����
    friend bool BulletPlugBomb(const Bullet &bul, const Bomb &bomb_);
    //������ ����� � �������
    friend bool BulletPlugAirplane(const Bullet &bul, const Airplane &plane);
    //����������� ��� ���������
    friend void AllDestroy(std::vector<Bullet> &bullet_vector_,
                std::vector<Bomb> &bullet_bomb_,
                std::vector<Airplane> &bullet_airplane_);

    //����������
    ~Bullet()
    {
        DeleteObject(p_main);
        DeleteObject(b_main);
    }
};

std::vector<Bullet> bullet_vector;

class Airplane{
private:
    int x1, y1; // ���������� ��������(����� ������� ����)
    int x2, y2; // ������ ������ ����
    int speed;  //�������� ��������
    bool active; //������� ���������� � ��������� �� ������
    bool direction; //true - ����� ������, false - ������ ������
    int health;      //���������� ��������� ����������� ��� �����������
    HPEN p_main;
    HBRUSH b_main;
    HPEN p_green, p_orange, p_red;
public:
    //�����������
    Airplane()
    {
        active = false;
        p_main = CreatePen(PS_SOLID, 1, RGB(0,255,0));
        b_main = CreateSolidBrush(RGB(0,0,0));
        p_green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
        p_orange = CreatePen(PS_SOLID, 2, RGB(255, 100, 0));
        p_red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    }

    void move_airplane(HDC hdc)
    {
        if(!pause)
        {
            x1 += speed;
            x2 += speed;
        }
        BITMAP mech_object;
        HDC memdc = CreateCompatibleDC(hdc);
        if(speed < 0)
        {
            switch(health)
            {
                case 1: GetObject (airplane_LtoR_red_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_LtoR_red_texture);//SelectObject(hdc, p_red);
                        break;
                case 2: GetObject (airplane_LtoR_orange_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_LtoR_orange_texture);//SelectObject(hdc, p_orange);
                        break;
                case 3: GetObject (airplane_LtoR_green_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_LtoR_green_texture);//SelectObject(hdc, p_green);
                        break;
            }
        }
        else{
                switch(health)
            {
                case 1: GetObject (airplane_RtoL_red_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_RtoL_red_texture);//SelectObject(hdc, p_red);
                        break;
                case 2: GetObject (airplane_RtoL_orange_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_RtoL_orange_texture);//SelectObject(hdc, p_orange);
                        break;
                case 3: GetObject (airplane_RtoL_green_texture, sizeof(BITMAP), &mech_object);
                        SelectObject(memdc, airplane_RtoL_green_texture);//SelectObject(hdc, p_green);
                        break;
            }
        }
        /*switch(health)
        {
        case 1:SelectObject(hdc, p_red); break;
        case 2:SelectObject(hdc, p_orange); break;
        case 3:SelectObject(hdc, p_green); break;
        }*/
        //SelectObject(hdc, b_main);
        //Rectangle(hdc, x1, y1, x2, y2);
BitBlt(hdc, x1, y1, mech_object.bmWidth, mech_object.bmHeight, memdc, 0, 0, SRCCOPY);
        DeleteDC(memdc);
    }

    //��������� ������ ��������
    void set_airplane(int length, int height, bool direct, int speed_)
    {
        active = true;
        health = rand() % 3 + 1; //�� 1 �� 3
        direction = direct;
        if(direction)
        {
            x1 = 0 - length;
            x2 = 0;
            y1 = 10;
            y2 = y1 + height;
            speed = speed_;
        }
        else{
            x1 = max_X_clientrect;
            x2 = max_X_clientrect + length;
            y1 = 20 + height;
            y2 = y1 + height;
            speed = -speed_;
        }

        return;
    }

    int SubHealth_airplane()
    {
        health = health - 1;
        return health;
    }

    void destroy_airplane() //����������� �������� ��� ������ �� ������� ������
    {
        active = false;
    }

    bool check_active()  //�������� ���������� ��������
    {
        return active;
    }

    //check = 1 ��������� �� ������ �� ������� �� �������
    //check = 0 ��������� ����� �� �������� �����
    bool check_x_airplane(bool check)  //�������� �� ����� �� ������ �� ������� ������
    {
        if(check)
        {
            if(direction)
            {
                return (x1 < max_X_clientrect);
            }
            return (x2 > 0);
        }
        else{ static int border = 100;
            if(direction)
            {
                return (x1 < max_X_clientrect - border && x2 > border);
            }
            return (x1 > border && x2 < max_X_clientrect - border);
        }

    }

    friend class Bomb;  //����� ������������ ���������
    //������ ����� � �������
    friend bool BulletPlugAirplane(const Bullet &bul, const Airplane &plane);
    //����������� ��� ���������
    friend void AllDestroy(std::vector<Bullet> &bullet_vector_,
                std::vector<Bomb> &bullet_bomb_,
                std::vector<Airplane> &bullet_airplane_);

    //����������
    ~Airplane()
    {
        DeleteObject(p_main);
        DeleteObject(p_red);
        DeleteObject(p_orange);
        DeleteObject(p_green);
        DeleteObject(b_main);
    }
};

std::vector<Airplane> airplane_vector;

class Bomb{
private:
    int x1, y1;   //���������� �����(����� ������� ����)
    int x2, y2;   //������ ������
    int Yspeed, Xspeed;  //�������� �� �(�����/������) � �� Y(����)
    bool active;     //����� ���������� � ���������� �� ������
    int health;      //���������� ��������� ����������� ��� �����������
    HPEN p_main;
    HBRUSH b_main;
    HPEN p_green, p_orange, p_red;
public:
    Bomb()
    {
        active = false;
        p_main = CreatePen(PS_SOLID, 1, RGB(0,255,0));
        b_main = CreateSolidBrush(RGB(0,0,0));
        p_green = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
        p_orange = CreatePen(PS_SOLID, 2, RGB(255, 100, 0));
        p_red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    }

    void move_bomb(HDC hdc)
    {
        if(!pause)
        {
            y1 += Yspeed;
            x1 += Xspeed;
            y2 += Yspeed;
            x2 += Xspeed;
        }
        BITMAP mech_object;
        HDC memdc = CreateCompatibleDC(hdc);
        switch(health)
        {
        case 1: GetObject (bomb_red_texture, sizeof(BITMAP), &mech_object);
                SelectObject(memdc, bomb_red_texture);//SelectObject(hdc, p_red);
                break;
        case 2: GetObject (bomb_orange_texture, sizeof(BITMAP), &mech_object);
                SelectObject(memdc, bomb_orange_texture);//SelectObject(hdc, p_orange);
                break;
        case 3: GetObject (bomb_green_texture, sizeof(BITMAP), &mech_object);
                SelectObject(memdc, bomb_green_texture);//SelectObject(hdc, p_green);
                break;
        }
        //SelectObject(hdc, b_main);
        //Ellipse(hdc, x1, y1, x2, y2);
BitBlt(hdc, x1, y1, mech_object.bmWidth, mech_object.bmHeight, memdc, 0, 0, SRCCOPY);
        DeleteDC(memdc);
    }

    void set_bomb(const Airplane &plane)
    {
        x1 = (plane.x1 + plane.x2)/2 - 5;
        y1 = plane.y2 - 10;
        x2 = (plane.x1 + plane.x2)/2 + 5;
        y2 = plane.y2 + 10;
        Yspeed = 5;
        Xspeed = plane.speed/3;
        active = true;
        health = rand() % 3 + 1; //�� 1 �� 3
    }

    int SubHealth_Bomb()
    {
        health = health - 1;
        return health;
    }

    void destroy_bomb() //����������� ����� ��� ������������
    {
        active = false;
    }

    bool check_active()  //�������� ���������� �����
    {
        return active;
    }

    bool check_y_bomb()  //�������� �� ������������ ����� � ���������
    {
        return (y2 < max_Y_clientrect - 50);
    }

    //�������� ��������� ����� � ������
    friend bool BombPlugMachine(const Machine &mech_, const Bomb &bomb_);
    //������ ����� � �����
    friend bool BulletPlugBomb(const Bullet &bul, const Bomb &bomb_);
    //����������� ��� ���������
    friend void AllDestroy(std::vector<Bullet> &bullet_vector_,
                std::vector<Bomb> &bullet_bomb_,
                std::vector<Airplane> &bullet_airplane_);

    ~Bomb()
    {
        DeleteObject(p_main);
        DeleteObject(p_red);
        DeleteObject(p_orange);
        DeleteObject(p_green);
        DeleteObject(b_main);
    }
};

std::vector<Bomb> bomb_vector;

#endif // GAME_CLASS_H_INCLUDED
