#ifndef GZ_CIRCLE_H_INCLUDED
#define GZ_CIRCLE_H_INCLUDED

namespace gz
{
/// const value of PI to 5 decimal places
static const double PI = 3.14159;

////////////////////////////////////////////////////////////
/// \brief A location in 2D space with a radius
////////////////////////////////////////////////////////////
template <class T>
class Circle
{
    public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T x;
        T y;
        T r;

        ////////////////////////////////////////////////////////////
        /// \brief defualt constructor - Data is initialised to zero.
        ////////////////////////////////////////////////////////////
        Circle() :
        x(0),
        y(0),
        r(0)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief auto initialising constructor
        ///
        ///\param x     x location of the cirlce
        ///\param y     y location of the circle
        ///\param r     radius of the circle
        ////////////////////////////////////////////////////////////
        Circle(T px, T py, T pr) :
        x(px),
        y(px),
        r(pr)
        {}

        ////////////////////////////////////////////////////////////
        /// \brief defualt destructor
        ////////////////////////////////////////////////////////////
        virtual ~Circle(){}

        ////////////////////////////////////////////////////////////
        /// \brief get the circumference of the circle
        ///
        /// \return the distance around the edge of the circle
        ////////////////////////////////////////////////////////////
        double getCircumference()
        {
            return (PI * (2 * (double)r));
        }
};

}

#endif // GZ_CIRCLE_H_INCLUDED
