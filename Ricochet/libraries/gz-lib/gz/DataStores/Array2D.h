#ifndef ARRAY2D_H
#define ARRAY2D_H


#include <iostream>
#include <vector>

namespace gz
{

    template <class T>
    class Array2D
    {
        public:
            Array2D(){}
            virtual ~Array2D(){}

        public: // functions

            void createArray(unsigned rows, unsigned cols);
            void initialise(T a);
            void set(unsigned row, unsigned col, T a);
            T get(unsigned row, unsigned col);

            unsigned getRows(){return m_rows;}
            unsigned getCols(){return m_cols;}

        private:
            unsigned m_rows;
            unsigned m_cols;

            std::vector<T> collection;

    };


    ////////////////////////////////////////////////////
    // Implementations
    ////////////////////////////////////////////////////
    template <class T>
    void Array2D<T>::createArray(unsigned rows, unsigned cols)
    {
        m_rows = rows;
        m_cols = cols;
        collection = std::vector<T>(rows * cols);
    }

    template <class T>
    void Array2D<T>::initialise(T a)
    {
        for (unsigned i = 0; i < collection.size(); ++i)
        {
            collection.at(i) = a;
            //std::cout << "index " << i << " = " << collection.at(i) << std::endl;
        }
    }

    template <class T>
    T Array2D<T>::get(unsigned row, unsigned col)
    {
        int index = (row * m_cols) + col;
        return collection.at(index);
    }

    template <class T>
    void Array2D<T>::set(unsigned row, unsigned col, T a)
    {
        int index = (row * m_cols) + col;
        collection.at(index) = a;
    }

}

#endif // ARRAY2D_H
