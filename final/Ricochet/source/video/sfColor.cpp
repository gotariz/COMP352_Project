#include "sfColor.h"

void sfColor::setColor(int r, int g, int b, int a)
{
    red     = r > 255 ? 255 : r;
    green   = g > 255 ? 255 : g;
    blue    = b > 255 ? 255 : b;
    alpha   = a > 255 ? 255 : a;

    stop();
    reset();
}

void sfColor::setColor2(int r, int g, int b, int a)
{
    red2    = r > 255 ? 255 : r;
    green2  = g > 255 ? 255 : g;
    blue2   = b > 255 ? 255 : b;
    alpha2  = a > 255 ? 255 : a;

    stop();
    reset();
}

void sfColor::setRedTime(float seconds)
{
    red_time = seconds;
}

void sfColor::setGreenTime(float seconds)
{
    green_time = seconds;
}

void sfColor::setBlueTime(float seconds)
{
    blue_time = seconds;
}

void sfColor::setAlphaTime(float seconds)
{
    alpha_time = seconds;
}

void sfColor::setTime(float seconds)
{
    red_time    = seconds;
    green_time  = seconds;
    blue_time   = seconds;
    alpha_time  = seconds;
}

sf::Color sfColor::getColor()
{
    return sf::Color(red,green,blue,alpha);
}

sf::Color sfColor::getColor2()
{
    return sf::Color(red2,green2,blue2,alpha2);
}

sf::Color sfColor::getCurrentColor()
{
    //cout << current_red << "-" << current_green << "-" << current_blue << endl;
    return sf::Color(current_red,current_green,current_blue,current_alpha);
}


void sfColor::update(float time_delta)
{
    if (transitioning)
    {
        // transition red
        et_red += time_delta;
        et_red = et_red > red_time ? red_time : et_red;
        float r_delta = red - red2;
        current_red = red2 + (r_delta * (et_red / red_time));

        et_green += time_delta;
        et_green = et_green > green_time ? green_time : et_green;
        float g_delta = green - green2;
        current_green = green2 + (g_delta * (et_green / green_time));

        et_blue += time_delta;
        et_blue = et_blue > blue_time ? blue_time : et_blue;
        float b_delta = blue - blue2;
        current_blue = blue2 + (b_delta * (et_blue / blue_time));

        et_alpha += time_delta;
        et_alpha = et_alpha > alpha_time ? alpha_time : et_alpha;
        float a_delta = alpha - alpha2;
        current_alpha = alpha2 + (a_delta * (et_alpha / alpha_time));

        if (et_red == red_time &&
            et_green == green_time &&
            et_blue == blue_time &&
            et_alpha == alpha_time)
        {
            transitioning = false;
        }
    }

}

void sfColor::start()
{
    transitioning = true;
}

void sfColor::stop()
{
    transitioning = false;
}

void sfColor::reset()
{
    et_red      = 0;
    et_green    = 0;
    et_blue     = 0;
    et_alpha    = 0;

    current_red     = red;
    current_green   = green;
    current_blue    = blue;
    current_alpha   = alpha;
}

