#pragma once

#include <complex>
#include <stdexcept>
#include <vector>

namespace containers
{



    
    


    
    //TODO: implement comparisons
    //TODO: implement Element concept
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
        Vector(const Vector<T>& v) : elem{new T[v.sz]}, sz{v.sz}
        {
            for(int i = 0; i < v.sz; i++)
                elem[i] = v[i];
        }

        /**
         * \brief move constructor
         * \param v vector to move from
         */
        Vector(Vector<T>&& v) noexcept: elem{v.elem}, sz{v.sz}
        {
            v.elem = nullptr;
            v.sz = 0;
        }

        

 
        
        /**
         * \brief [] operator definition
         * \param i index for array lookup
         * \return element at index in vector
         */
        constexpr T& operator[](int i)
        {
            return elem[i];
        }

        constexpr const T& operator[](int i) const
        {
            return elem[i];
        }

        /**
         * \brief returns specified element of the array, and performs bounds checks.
         * \param i index of the vector
         * \return element at index in vector
         */
        constexpr T& at(int i)
        {
            if(i < 0 || i >= sz)
            {
                throw std::out_of_range{"index out of bounds."};
            }
            return elem[i];
        }

        constexpr const T& at(int i) const
        {
            if(i < 0 || i >= sz)
            {
                throw std::out_of_range{"index out of bounds."};
            }
            return elem[i];
        }

        /**
         * \brief gets the first element of the vector.
         * \return the first element of the vector.
         */
        constexpr T& front()
        {
            return elem[0];
        }

        constexpr const T& front() const
        {
            return elem[0];
        }

        /**
         * \brief gets the last element of the vector.
         * \return the last element of the vector.
         */
        constexpr T& back() 
        {
            return elem[0] + sz;
        }

        constexpr const T& back() const
        {
            return elem[0] + sz;
        }


        /**
         * \brief returns a pointer to the underlying array in memory.
         * \return A pointer to the start of the array in memory.
         */
        constexpr T* data() noexcept
        {
            if(sz == 0) return nullptr;
            return elem;
        }
        
        const constexpr T* data() const noexcept 
        {
            if(sz == 0) return nullptr;
            return elem;
        }
        
        /**
         * \brief copy operator
         * \param v vector to copy from
         * \return reference to this vector
         */
        Vector& operator=(const Vector<T>& v)
        {
            T* p = new T[v.sz];
            for(int i = 0; i < v.sz; i++)
                p[i] = v[i];
            delete[] elem;
            elem = p;
            sz = v.sz;
            return *this;
        }

        /**
         * \brief move operator
         * \param v vector to move from
         * \return reference to this vector
         */
        Vector& operator=(Vector<T>&& v) noexcept
        {
            elem = v.elem;
            sz = v.sz;

            v.elem = nullptr;
            v.sz = 0;

            return *this;
        }


    
        /**
         * \brief returns an iterator pointing to the start of the vector (though not actually rn).
         * \return iterator pointing to start of the vector.
         */
        
        /*
        constexpr std::iterator<T> begin() noexcept
        {
            return sz ? &elem[0] : nullptr;
        }
        */
        /**
         * \brief returns iterator pointing to the end of the vector (though not actually rn).
         * \return iterator pointing to the end of the vector.
         */
        
        /*
        T* end()
        {
            return sz ? elem[0]+sz : nullptr;
        }
        */
        
        

        /**
         * \brief destructor
         */
        constexpr ~Vector()
        {
            
            
            delete [] elem;
            sz = 0;
        }

        /**
         * \brief size getter
         * \return size of the vector
         */
        constexpr int size() const
        {
            return sz;
        }

    };
    
}
