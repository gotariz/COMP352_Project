#ifndef GZ_POSITION_H_INCLUDED
#define GZ_POSITION_H_INCLUDED

namespace gz
{

template <class T>
class Position
{
public:
    /// x location
    T x;
    /// y location
    T y;

    ////////////////////////////////////////////////////////////
    /// \brief defualt constructor - Data is initialised to zero.
    ////////////////////////////////////////////////////////////
    Position() :
    x(0),
    y(0)
    {}

    ////////////////////////////////////////////////////////////
    /// \brief auto initialising constructor
    ///
    ///\param xPos   x position
    ///\param yPos   y position
    ////////////////////////////////////////////////////////////
    Position(T xPos, T yPos) :
    x(xPos),
    y(yPos)
    {}

    ////////////////////////////////////////////////////////////
    /// \brief defualt destructor
    ////////////////////////////////////////////////////////////
    ~Position(){};

    ////////////////////////////////////////////////////////////
    /// \brief sets the x and y position
    ///
    ///\param xPos   x position
    ///\param yPos   y position
    ////////////////////////////////////////////////////////////
    void set(T xPos, T yPos)
    {
        x = xPos;
        y = yPos;
    };
};

}

#endif // GZ_POSITION_H_INCLUDED
