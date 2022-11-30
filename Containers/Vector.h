#pragma once

#include <stdexcept>

namespace containers
{

    template<typename T>
    class Vector
    {
    private:
        T* elem;
        int sz;
    public:
        /**
         * \brief constructor
         * \param s size for the new vector
         */
        explicit Vector(int s)
        {
            if(s<0)
                throw std::length_error{"Vector constructor: negative size"};
            elem =new T[s];
            sz= s;
        }

        /**
         * \brief copy constructor
         * \param v vector to copy from
         */
        Vector(const Vector& v) : elem{new T[v.sz]}, sz{v.sz}
        {
            for(int i = 0; i < v.sz; i++)
                elem[i] = v[i];
        }

        /**
         * \brief move constructor
         * \param v vector to move from
         */
        Vector(Vector&& v) : elem{v.elem}, sz{v.sz}
        {
            v.elem = nullptr;
            v.sz = 0;
        }

 
        
        /**
         * \brief [] operator definition
         * \param i index for array lookup
         * \return element at index in vector
         */
        T& operator[](int i)
        {
            return elem[i];
        }

        /**
         * \brief const [] operator definition
         * \param i index for array lookup
         * \return element at index in the vector
         */
        const T& operator[](int i) const
        {
            return elem[i];
        }

        /**
         * \brief 
         * \param v vector to copy from
         * \return reference to this vector
         */
        Vector& operator=(const Vector& v)
        {
            T* p = new T[v.sz];
            for(int i = 0; i < v.sz; i++)
                p[i] = v[i];
            delete[] elem;
            elem = p;
            sz = v.sz;
            return *this;
        }


        Vector& operator=(Vector&& v)
        {
            
        }

        /**
         * \brief size getter
         * \return size of the vector
         */
        int size() const
        {
            return sz;
        }

    };
    
}
