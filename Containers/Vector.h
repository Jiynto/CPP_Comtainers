#pragma once

#include <complex>
#include <stdexcept>
#include <vector>

namespace containers
{

    template<class T>
    class Const_Vector_Iterator
    {
    public:
        using value_type = T;

        Const_Vector_Iterator(){ _data = new value_type*; }
        Const_Vector_Iterator(T* t): _data(t) {}
        
        Const_Vector_Iterator(Const_Vector_Iterator& iter)
        {
            _data = iter._data;
        }

        Const_Vector_Iterator& operator=(Const_Vector_Iterator const& iter)
        {
            if(this == iter) return *this;
            _data = iter._data;
            return *this;
        }

        constexpr ~Const_Vector_Iterator()
        {
            delete _data;
        }

        Const_Vector_Iterator operator+(int i)
        {
            return Const_Vector_Iterator(_data + i);
        }

        Const_Vector_Iterator operator-(int i)
        {
            return Const_Vector_Iterator(_data - i);
        }

        
        constexpr value_type& operator*() const
        {
            return *_data;
        }

        constexpr value_type* operator->() const
        {
            return _data;
        }

        constexpr bool operator==(const Const_Vector_Iterator<T>& rhs) const
        {
            return compare(rhs);
        }

        bool operator!=(const Const_Vector_Iterator<T>& rhs) const
        {
            return !compare(rhs);
        }

        Const_Vector_Iterator& operator++()
        {
            increment();
            return *this;
        }

        
        Const_Vector_Iterator operator++(int)
        {
            auto temp = *this;
            increment();
            return temp;
        }

        Const_Vector_Iterator operator--()
        {
            decrement();
            return *this;
        }

        Const_Vector_Iterator operator--(int)
        {
            auto temp = *this;
            decrement();
            return temp;
        }

    
        
    protected:
        T* _data;

        void increment() { ++_data; }
        void decrement() { --_data; }
        bool compare(const Const_Vector_Iterator<T>& rhs) const { return _data == rhs._data; }
    };



    
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
        
        
        constexpr Vector<T>::iterator begin() noexcept
        {
            return sz ? &elem[0] : nullptr;
        }
        
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
