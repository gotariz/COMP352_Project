#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

namespace gz
{

    ////////////////////////////////////////////////////////////
    /// \brief A Colour represented by RGB Values between 0 and 255
    ////////////////////////////////////////////////////////////
    class Color
    {
	public:
	
        /// red color value
        unsigned int r;
        /// green color value
        unsigned int g;
        /// blue color value
        unsigned int b;

        ////////////////////////////////////////////////////////////
        /// \brief  default constructor - Data is initialised to zero
        ////////////////////////////////////////////////////////////
        Color() :
        r(0),
        g(0),
        b(0)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief  auto initialised constructor with individual
        ///         RGB values
        ///
        /// \param red      red value
        /// \param green    green value
        /// \param blue     blue value
        ////////////////////////////////////////////////////////////
        Color(int red, int green, int blue) :
        r(red),
        g(green),
        b(blue)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief  auto initialised constructor with a integer RGB
        ///         value
        ///
        /// \param rgb      integer color value
        ////////////////////////////////////////////////////////////
        Color(int rgb)
        {
            r = (rgb >> 16 & 0xFF);
            g = (rgb >> 8 & 0xFF);
            b = (rgb & 0xFF);
        }

        ////////////////////////////////////////////////////////////
        /// \brief  auto initialised constructor with a string
        ///         representing the hex RGB value
        ///
        /// \param rgb      integer color value
        ////////////////////////////////////////////////////////////
        Color(std::string hexColor)
        {
            int rgb;
            std::stringstream ss;
            ss << std::hex << hexColor;
            ss >> rgb;

            r = (rgb >> 16 & 0xFF);
            g = (rgb >> 8 & 0xFF);
            b = (rgb & 0xFF);
        }

    };
}

#endif // COLOR_H_INCLUDED
