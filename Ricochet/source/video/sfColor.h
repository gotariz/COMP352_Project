#ifndef SFCOLOR_H
#define SFCOLOR_H

#include "dependencies.h"

class sfColor
{
    public:
        sfColor(){}
        virtual ~sfColor(){}

    public:

        void setColor(int r, int g, int b, int a);
        void setColor2(int r, int g, int b, int a);
        void setRedTime(float seconds);
        void setGreenTime(float seconds);
        void setBlueTime(float seconds);
        void setAlphaTime(float seconds);
        void setTime(float seconds);

        void update(float time_delta);

        void start();
        void stop();
        void reset();

        sf::Color getColor();
        sf::Color getColor2();
        sf::Color getCurrentColor();

    private:
        bool transitioning = false;

        float et_red    = 0;
        float et_green  = 0;
        float et_blue   = 0;
        float et_alpha  = 0;

        float red_time      = 0;
        float green_time    = 0;
        float blue_time     = 0;
        float alpha_time    = 0;

        float red   = 0;
        float green = 0;
        float blue  = 0;
        float alpha = 255;

        float red2   = 0;
        float green2 = 0;
        float blue2  = 0;
        float alpha2 = 255;

        float current_red   = 0;
        float current_green = 0;
        float current_blue  = 0;
        float current_alpha = 255;
};

#endif // SFCOLOR_H
