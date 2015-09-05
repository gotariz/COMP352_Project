#ifndef GZ_RECT_H_INCLUDED
#define GZ_RECT_H_INCLUDED

namespace gz
{

////////////////////////////////////////////////////////////
/// \brief A location in 2D space with a width and height
////////////////////////////////////////////////////////////
template <class T>
class Rect
{
    public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        /// x co-ordinate of the rectangle
        T x;
        /// y co-ordinate of the rectangle
        T y;
        /// width of the rectangle
        T w;
        /// height of the rectangle
        T h;

        ////////////////////////////////////////////////////////////
        /// \brief defualt constructor - Data is initialised to zero.
        ////////////////////////////////////////////////////////////
        Rect() :
        x(0),
        y(0),
        w(0),
        h(0)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief auto initialising constructor
        ///
        ///\param x     x location of the rectangle
        ///\param y     y location of the rectangle
        ///\param w     width of the rectangle
        ///\param h     height of the rectangle
        ////////////////////////////////////////////////////////////
        Rect(T px, T py, T pw, T ph) :
        x(px),
        y(py),
        w(pw),
        h(ph)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief defualt destructor
        ////////////////////////////////////////////////////////////
        virtual ~Rect(){}

        ////////////////////////////////////////////////////////////
        /// \brief get the right x position of the Rect
        ///        Forumla = (x + w - 1) gives the last col "INDEX"
        ///
        /// \return the x position of the right size of the Rect
        ////////////////////////////////////////////////////////////
        T getX2()
        {
            return (x + w - 1);
        }

        ////////////////////////////////////////////////////////////
        /// \brief get the bottom y position of the Rect.
        ///        Forumla = (y + h - 1) gives the last row "INDEX"
        ///
        /// \return the y position of the bottom of the Rect
        ////////////////////////////////////////////////////////////
        T getY2()
        {
            return (y + h - 1);
        }
};

}

#endif // GZ_RECT_H_INCLUDED
