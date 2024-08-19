#ifndef __Vector_HH__
#define __Vector_HH__

template <typename T> class Vector {
    private:
        unsigned int cap;
        unsigned int size;
        T* storage;
    public:
        Vector()
        {
            cap=2;
            size=0;
            storage=new T[cap];
        } 
        ~Vector()
        {
            delete [] storage;
        }
        void pop_back()
        {
            if(size==0)
            {
                std::cout<<"no hay elementos en el Vector"<<std::endl;
                return;
            }
            size--;
        }
        T& at(unsigned int i) const
        {
            return storage[i];
        }
        void push_back( T newElement)
        {
            if(size == cap)
            {
                resize();
            }
            storage[size]= newElement;
            size++;

        }
        void resize()
        {
            T* newStorage = new T[cap*2];
            for(unsigned int i = 0;i<size;i++)
            {
                newStorage[i] = storage[i];
            }
            delete [] storage;
            storage = newStorage;
            cap = cap*2;
        }
        void pushFront( T newElement)
        {
            if(size == cap)
            {
                std::cout<<"arreglo original insuficiente, redimensionando..."<<std::endl;
                resize();
            }
            for(unsigned int i = size;i > 0;i--)
            {
                storage[i] = storage[i-1];
            }
            storage[0] = newElement;
            size++;
        }
        void popFront()
        {
            if(size == 0)
            {
                std::cout<<"no hay elementos en el Vector"<<std::endl;
                return;
            }
            for(unsigned int i = 0;i<size-1;i++)
            {
                storage[i] = storage[i+1];
            }
            size--;
        }

        bool empty() const {return size == 0;}
        unsigned int getSize() const{return size;}
        
};
#endif