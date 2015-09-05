#ifndef GZ_SIZE_H_INCLUDED
#define GZ_SIZE_H_INCLUDED

namespace gz
{

template <class T>
class Size
{
public:
    /// width of the virtual sizeable object
    T w;
    /// height of the virtual sizeable object
    T h;

    ////////////////////////////////////////////////////////////
    /// \brief defualt constructor - Data is initialised to zero.
    ////////////////////////////////////////////////////////////
    Size() :
    w(0),
    h(0)
    {}

    ////////////////////////////////////////////////////////////
    /// \brief auto initialising constructor
    ///
    ///\param width    width of the virtual sizeable object
    ///\param height   height of the virtual sizeable object
    ////////////////////////////////////////////////////////////
    Size(T width, T height) :
    w(width),
    h(height)
    {}

    ////////////////////////////////////////////////////////////
    /// \brief defualt destructor
    ////////////////////////////////////////////////////////////
    ~Size(){};
};

}

#endif // GZ_SIZE_H_INCLUDED
