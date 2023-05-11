#include <iostream>
#include <string>
#include <graphics.h>
#include <cmath>

using namespace std;

class vector2
{
    public :
        int x, y;
        vector2(){}
        vector2(int x_, int y_)
        {
            x = x_; y = y_;
        }
};

class gameScreen
{
    private :
        int frameBuffer = 2;
        int activePage = 0;
        int visualPage = 1;
    public :
        void screenUpdate()
        {
            activePage++;
            if (activePage >= frameBuffer) activePage = 0;

            visualPage++;
            if (visualPage >= frameBuffer) visualPage = 0;

            setactivepage(activePage);
            setvisualpage(visualPage);

            cleardevice();
        }  
};

class C_Bar
{
    private :
        int color;
        int b_color;

        vector2 position;

        float xSize;
        float ySize;
        float percentage = 1;

    public :
        // C_Bar(){}
        C_Bar(int x_ = 0, int y_ = 0, float xSize_ = 200, float ySize_ = 20, int color_ = RED, int b_color_ = WHITE)
        {
            position.x = x_;
            position.y = y_;

            xSize = xSize_;
            ySize = ySize_;

            color = color_;
            b_color = b_color_;
        }

        void setPosition(int x_, int y_)
        {
            position.x = x_;
            position.y = y_;
        }

        void setColor(int color_)
        {
            color = color_;
        }

        void setSize(int x_ = 200, int y_ = 20)
        {
            xSize = x_;
            ySize = y_;
        }

        void setPercentage(float percentage_)
        {
            percentage = percentage_;
            if (percentage < 0) percentage = 0;
        }

        void update()
        {
            setfillstyle(SOLID_FILL, b_color);
            bar(position.x - 1, position.y - 1, position.x + (int)xSize + 1, position.y + (int)ySize + 1);

            setfillstyle(SOLID_FILL, color);
            bar(position.x, position.y, position.x + (int)(xSize * percentage), position.y + (int)(ySize));
        }
};

class Knight
{
    private :

        vector2 position;
        vector2 size;

        bool hadapKanan = 1;

        C_Bar hpBar;
        C_Bar staminaBar;

        int maxHealth = 100;
        int health = 100;

        int maxStamina = 100;
        int stamina = 100;

        float scale = 5.5;
        int frame = 0;
        int jumlahFrame = 10;
        int delayFrame = 3;

        string state;
   
        bool firstAttack; //Attack pertama kali setelah melakukan hal lain
        bool ready; //ready to attack
        bool attackFinish = 1; //attack finished
        bool doAttack;

        int attackCount;
        int frameCountAfterAttack;
        int range = 300;

        bool attackComplete;
    
    public :
        Knight(){}
        Knight(int x_ = 0, int y_ = 0, float scale_ = 5.5, int health_ = 100, int stamina_ = 100, int x_s = 120, int y_s = 80)
        {
            position.x = x_; position.y = y_; scale = scale_; health = health_; stamina = stamina_; size.x = x_s; size.y = y_s; 
            hpBar.setColor(RED);
            hpBar.setPercentage(1);
            hpBar.setSize(300);

            staminaBar.setColor(DARKGRAY);
            staminaBar.setPercentage(1);
            staminaBar.setSize(300);
        }
        void update()
        {
            attackComplete = 0;
            if (stamina <= 0)
            {
                ready = 0;
            }
            
            else if (stamina >= 100)
            {
                ready = 1;
            }

            if (attackFinish && GetAsyncKeyState(VK_SPACE) && !doAttack && ready)
            {
                doAttack = 1;
                attackCount++;
                if(attackCount > 2) attackCount = 1;
            }
            else
            {
                doAttack = 0;
            }

            if ((doAttack || !attackFinish))
            {
                stamina--;
                frameCountAfterAttack++;
                if(frameCountAfterAttack <= 0)
                {
                    frame = 0;
                }

                if(attackFinish || firstAttack)
                {
                    attackFinish = 0;
                    firstAttack = 0;
                    frame = 0;
                    frameCountAfterAttack = 0;
                }

                if(frameCountAfterAttack >= jumlahFrame * delayFrame)
                {
                    attackFinish = 1;
                }
                
                else
                {
                    state = "Attack" + to_string(attackCount);
                    //cout<<state<<endl;

                    if(attackCount == 1) jumlahFrame = 4;
                    else jumlahFrame = 6;
                }

            }

            if(attackFinish)
            {
                if (stamina < maxStamina) stamina++;
                firstAttack = 1;
                jumlahFrame = 10;
                if (GetAsyncKeyState('D'))
                {
                    hadapKanan = 1;
                    state = "Run";
                    position.x += 15;
                }

                else if (GetAsyncKeyState('A'))
                {
                    hadapKanan = 0;
                    state = "Run";
                    position.x -= 15;
                }

                else state = "Idle";
            }

            if (!hadapKanan)
            {
                state = state + to_string(0);
            }

            settextstyle(8, HORIZ_DIR, 4);
            outtextxy(position.x - size.x/2, position.y - 60, "Divine Knight");

            hpBar.setPosition(position.x - size.x/2, position.y - 20);
            hpBar.setPercentage((float)health / (float)maxHealth);
            hpBar.update();

            staminaBar.setPosition(position.x - size.x/2, position.y + 5);
            staminaBar.setPercentage((float)stamina / (float)maxStamina);
            staminaBar.update();

            frame++;
            if (frame > delayFrame * (jumlahFrame - 1)) frame = 0;

            string s = "Sprite\\Knight\\" + state + "\\" + to_string(frame / delayFrame) + ".gif";

            char* char_array = new char[s.length() + 1];

            strcpy(char_array, s.c_str());

            int ukuranx = (int)((float)size.x * scale);
            int ukurany = (int)((float)size.y * scale);

            readimagefile(char_array, position.x - size.x * scale / 2, position.y - size.y * scale / 2, (position.x - size.x / 2) + ukuranx, (position.y - size.y / 2) + ukurany);

            delete[] char_array;

            if(frameCountAfterAttack == jumlahFrame * delayFrame / 2)
            {
                attackComplete = 1;
            }

            // circle(position.x + size.x / 2, position.y+ 140 + size.y / 2, 100);

            // circle(position.x + 200 + size.x / 2, position.y+ 140 + size.y / 2, 100);
            // circle(position.x - 200 + size.x / 2, position.y+ 140 + size.y / 2, 100);
        }

        void damaged(int damage)
        {
            health -= damage;
        }

        bool is_attack()
        {
            return attackComplete;
        }

        vector2 getPosition()
        {
            return position; 
        }

        int get_range()
        {
            return range;
        }

        bool hadap_kanan()
        {
            return hadapKanan;
        }

        int get_health()
        {
            return health;
        }

};

class Mage
{
    private :

        vector2 position;
        vector2 size;

        bool hadapKanan = 0;

        C_Bar hpBar;
        C_Bar manaBar;

        int maxHealth = 100;
        int health = 100;

        int maxMana = 100;
        int mana = 100;

        float scale = 5.5;
        int frame = 0;
        int jumlahFrame = 10;
        int delayFrame = 3;

        string state;
 
        bool firstAttack;
        bool ready;
        bool attackFinish = 1;
        bool doAttack;
        bool attackComplete;

        int attackCount;
        int frameCountAfterAttack;
        int range = 500;
    
    public :
        Mage(){}
        Mage(int x_ = 0, int y_ = 0, float scale_ = 5.5, int health_ = 100, int mana_ = 100, int x_s = 250, int y_s = 250)
        {
            position.x = x_; position.y = y_; scale = scale_; health = health_; mana = mana_; size.x = x_s; size.y = y_s; 
            hpBar.setColor(RED);
            hpBar.setPercentage(1);
            hpBar.setSize(300);

            manaBar.setColor(BLUE);
            manaBar.setPercentage(1);
            manaBar.setSize(300);
        }
        void update()
        {
            attackComplete = 0;
            if (mana <= 0)
            {
                ready = 0;
            }
            
            else if (mana >= 100)
            {
                ready = 1;
            }

            if (attackFinish && GetAsyncKeyState(VK_SHIFT) && !doAttack && ready)
            {
                doAttack = 1;
                attackCount++;
                if(attackCount > 2) attackCount = 1;
            }
            else
            {
                doAttack = 0;
            }

            if ((doAttack || !attackFinish))
            {
                mana -= 2;
                frameCountAfterAttack++;
                if(frameCountAfterAttack <= 0)
                {
                    frame = 0;
                }

                if(attackFinish || firstAttack)
                {
                    attackFinish = 0;
                    firstAttack = 0;
                    frame = 0;
                    frameCountAfterAttack = 0;
                }

                if(frameCountAfterAttack >= jumlahFrame * delayFrame)
                {
                    attackFinish = 1;
                }
                
                else
                {
                    state = "Attack" + to_string(attackCount);
                    //cout<<state<<endl;
                }

            }

            if(attackFinish)
            {
                if (mana < maxMana) mana++;
                firstAttack = 1;
                jumlahFrame = 8;
                if (GetAsyncKeyState(VK_RIGHT))
                {
                    hadapKanan = 1;
                    state = "Run";
                    position.x += 10;
                }

                else if (GetAsyncKeyState(VK_LEFT))
                {
                    hadapKanan = 0;
                    state = "Run";
                    position.x -= 10;
                }

                else state = "Idle";
            }

            if (!hadapKanan)
            {
                state = state + to_string(0);
            }

            frame++;
            if (frame > delayFrame * (jumlahFrame - 1)) frame = 0;



            string s = "Sprite\\Mage\\" + state + "\\" + to_string(frame / delayFrame) + ".gif";
            cout<<s<<endl;

            char* char_array = new char[s.length() + 1];

            strcpy(char_array, s.c_str());

            int ukuranx = (int)((float)size.x * scale);
            int ukurany = (int)((float)size.y * scale);

            readimagefile(char_array, position.x - 100 - size.x * scale / 2, position.y - (size.y * (scale / 2)) - 34, (position.x - size.x / 2) + ukuranx, (position.y - size.y / 2) + ukurany);

            delete[] char_array;

            if(frameCountAfterAttack == jumlahFrame * delayFrame / 2)
            {
                attackComplete = 1;
            }

            // circle(position.x - 50 + size.x / 2, position.y + 50 + size.y / 2, 110);

            // circle(position.x - 400 + size.x / 2, position.y + 50 + size.y / 2, 110);
            // circle(position.x + 300 + size.x / 2, position.y + 50 + size.y / 2, 110);
            settextstyle(8, HORIZ_DIR, 4);
            outtextxy(position.x - size.x/2, position.y - 60, "Chaos Wizard");
            hpBar.setPosition(position.x - size.x/2, position.y - 20);
            hpBar.setPercentage((float)health / (float)maxHealth);
            hpBar.update();

            manaBar.setPosition(position.x - size.x/2, position.y + 5);
            manaBar.setPercentage((float)mana / (float)maxMana);
            manaBar.update();

        }

        void damaged(int damage)
        {
            health -= damage;
        }

        bool is_attack()
        {
            return attackComplete;
        }

        bool hadap_kanan()
        {
            return hadapKanan;
        }

        int get_range()
        {
            return range;
        }

        vector2 getPosition()
        {
            return position; 
        }

        int get_health()
        {
            return health;
        }

};


int main()
{
    gameScreen m_gameScreen;

    initwindow(1368, 720, "Dungeon Fighter");
    while(1)
    {

        settextjustify(LEFT_TEXT, CENTER_TEXT);

        Mage player1(getmaxx() - 200, 300, 3);
        Knight player2(80, 300, 4);

        setbkcolor(COLOR(61, 63, 65));

        while(1)
        {
            m_gameScreen.screenUpdate();

            player1.update();
            player2.update();

            if(player1.is_attack()&& !player1.hadap_kanan() && (player1.getPosition().x - player2.getPosition().x) <= player1.get_range() && (player1.getPosition().x - player2.getPosition().x) > 0)
            {
                player2.damaged(20);
            }
            else if(player1.is_attack()&& player1.hadap_kanan() && (player1.getPosition().x - player2.getPosition().x) >= -1 * player1.get_range() && (player1.getPosition().x - player2.getPosition().x) < 0)
            {
                player2.damaged(20);
            }

            if(player2.is_attack()&& !player2.hadap_kanan() && (player2.getPosition().x - player1.getPosition().x) <= player2.get_range() && (player2.getPosition().x - player1.getPosition().x) > 0)
            {
                player1.damaged(10);
            }
            else if(player2.is_attack()&& player2.hadap_kanan() && (player2.getPosition().x - player1.getPosition().x) >= -1 * player2.get_range() && (player2.getPosition().x - player1.getPosition().x) < 0)
            {
                player1.damaged(10);
            }
            
            if (player2.get_health() <= 0)
            {
                cleardevice();
                setbkcolor(BLACK);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                settextstyle(8, HORIZ_DIR, 20);
                outtextxy(getmaxx() / 2, getmaxy()/2, "Chaos Wizard Win");
                settextstyle(8, HORIZ_DIR, 6);
                outtextxy(getmaxx()/2, getmaxy()/2 + 200, "Press Enter to restart");
                
                if(GetAsyncKeyState(VK_RETURN))
                break;
            }

            if (player1.get_health() <= 0)
            {
                cleardevice();
                setbkcolor(BLACK);
                settextjustify(CENTER_TEXT, CENTER_TEXT);
                settextstyle(8, HORIZ_DIR, 20);
                outtextxy(getmaxx()/2, getmaxy()/2, "Divine Knight Win");
                settextstyle(8, HORIZ_DIR, 6);
                outtextxy(getmaxx()/2, getmaxy()/2 + 200, "Press Enter to restart");
                
                if(GetAsyncKeyState(VK_RETURN))
                break;
            }
            delay(5);
        }
    }


    closegraph();
    return 0;
}