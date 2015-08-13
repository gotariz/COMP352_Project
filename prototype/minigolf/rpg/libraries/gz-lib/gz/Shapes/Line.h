#ifndef GZ_LINE_H
#define GZ_LINE_H

#include "point.h"

namespace gz
{

////////////////////////////////////////////////////////////
/// \brief 2 locations in 2D space
////////////////////////////////////////////////////////////
template <class T>
class Line
{
    public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        /// x location of the first point
        T x1;
        /// y location of the first point
        T y1;
        /// x location of the second point
        T x2;
        /// y location of the second point
        T y2;

        ////////////////////////////////////////////////////////////
        /// \brief defualt constructor - Data is initialised to zero.
        ////////////////////////////////////////////////////////////
        Line() :
        x1(0),
        y1(0),
        x2(0),
        y2(0)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief auto initialising constructor
        ///
        ///\param x1    The x location of the first point
        ///\param y1    The y location of the first point
        ///\param x2    The x location of the second point
        ///\param y2    The y location of the second point
        ////////////////////////////////////////////////////////////
        Line(T px1, T py1, T px2, T py2) :
        x1(px1),
        y1(py1),
        x2(px2),
        y2(py2)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief defualt destructor
        ////////////////////////////////////////////////////////////
        virtual ~Line();

        ////////////////////////////////////////////////////////////
        /// \brief get the location of the start of the line
        ///
        /// \return the first x and y as a gz::Point
        ////////////////////////////////////////////////////////////
        Point<T> getFirstPoint()
        {
            return Point<T>(x1,y1);
        }

        ////////////////////////////////////////////////////////////
        /// \brief get the location of the end of the line
        ///
        /// \return the second x and y as a gz::Point
        ////////////////////////////////////////////////////////////
        Point<T> getSecondPoint()
        {
            return Point<T>(x2,y2);
        }
};

}

#endif // GZ_LINE_H
