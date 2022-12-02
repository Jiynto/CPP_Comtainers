#pragma once

#include <complex>
#include <stdexcept>
#include <vector>

namespace containers
{

    template<class T>
    class Const_Vector_Iterator
    {

    protected:
        T* _data;

        void increment() { ++_data; }
        void decrement() { --_data; }
        bool compare(const Const_Vector_Iterator<T>& rhs) const { return _data == rhs._data; }

        
    public:
        using value_type = T;

        /**
         * \brief default constructor
         */
        Const_Vector_Iterator(){ _data = new value_type*; }

        /**
         * \brief constructor
         * \param t starting value of the iterator
         */
        explicit Const_Vector_Iterator(T* t): _data(t) {}

        /**
         * \brief copy constructor
         * \param iter this iterator with copied values
         */
        Const_Vector_Iterator(Const_Vector_Iterator<T>& iter)
        {
            _data = iter._data;
        }

        /**
         * \brief copy assignment operator overload
         * \param iter the right hand iterator
         * \return this iterator with copied values. 
         */
        Const_Vector_Iterator<T>& operator=(Const_Vector_Iterator<T> const& iter)
        {
            if(this == iter) return *this;
            _data = iter._data;
            return *this;
        }

        /**
         * \brief Destructor
         */
        constexpr ~Const_Vector_Iterator()
        {
            delete _data;
        }

        /**
         * \brief addition operator
         * \param i int to add to the iterator
         * \return a new iterator with the added value
         */
        Const_Vector_Iterator operator+(int const i)
        {
            return Const_Vector_Iterator(_data + i);
        }

        /**
         * \brief subtraction operator
         * \param i int to subtract from the iterator
         * \return a new iterator with the subtracted value
         */
        Const_Vector_Iterator operator-(int const i)
        {
            return Const_Vector_Iterator(_data - i);
        }

        /**
         * \brief less than operator
         * \param rhs right hand side of expression
         * \return true if lhs is less than rhs, else false
         */
        constexpr bool operator<(Const_Vector_Iterator<T> const& rhs) const
        {
            return _data < rhs._data;
        }

        /**
         * \brief greater than operator
         * \param rhs right hand side of expression
         * \return true if lhs is greater than rhs, else false
         */
        constexpr bool operator>(Const_Vector_Iterator<T> const& rhs) const
        {
            return _data > rhs._data;
        }
        
        /**
         * \brief less than or equal operator
         * \param rhs right hand side of expression
         * \return true if lhs is less than or equal to rhs, else false
         */
        constexpr bool operator<=(Const_Vector_Iterator<T> const& rhs) const
        {
            return _data < rhs._data || compare(rhs);
        }

        /**
         * \brief greater than or equal operator
         * \param rhs right hand side of expression
         * \return true if lhs is greater than or equal to rhs, else false
         */
        constexpr bool operator>=(Const_Vector_Iterator<T> const& rhs) const
        {
            return _data > rhs._data || compare(rhs);
        }

        /**
         * \brief compound addition assignment operator
         * \param i int to be added to pointer
         * \return this iterator after addition.
         */
        Const_Vector_Iterator operator+=(int const& i)
        {
            _data += i;
            return *this;
        }

        /**
         * \brief compound subtraction assignment operator
         * \param i int to be subtracted to pointer
         * \return this iterator after subtraction.
         */
        Const_Vector_Iterator operator-=(int const& i)
        {
            _data -= i;
            return *this;
        }

        /**
         * \brief dereference operator
         * \return dereferenced pointer to current element
         */
        constexpr value_type& operator*() const
        {
            return *_data;
        }

        /**
         * \brief dereference operator
         * \return pointer to current element
         */
        constexpr value_type* operator->() const
        {
            return _data;
        }

        /**
         * \brief equality comparison operator
         * \param rhs right hand side of the expression
         * \return true if left and right are the same, otherwise false
         */
        constexpr bool operator==(const Const_Vector_Iterator<T>& rhs) const
        {
            return compare(rhs);
        }

        /**
         * \brief inequality comparison operator
         * \param rhs right hand side of the expression
         * \return true if left does not equal right, else false
         */
        bool operator!=(const Const_Vector_Iterator<T>& rhs) const
        {
            return !compare(rhs);
        }

        /**
         * \brief postfix incrementation
         * \return the incremented iterator
         */
        Const_Vector_Iterator& operator++()
        {
            increment();
            return *this;
        }


        /**
         * \brief prefix incrementation
         * \return the iterator pre incrementation
         */
        Const_Vector_Iterator operator++(int)
        {
            auto temp = *this;
            increment();
            return temp;
        }

        /**
         * \brief postfix decrementation
         * \return the decremented iterator 
         */
        Const_Vector_Iterator operator--()
        {
            decrement();
            return *this;
        }

        /**
         * \brief prefix decrementation
         * \return the iterator pre decrementation
         */
        Const_Vector_Iterator operator--(int)
        {
            auto temp = *this;
            decrement();
            return temp;
        }

        /**
         * \brief returns the element found at this plus offset
         * \param i an offset to the current position
         * \return the element found at that offset
         */
        value_type& operator[](int const i)
        {
            return *(_data + i);
        }
    
        

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
