#ifndef __STACK_HH__
#define __STACK_HH__

template <typename T> class Stack {
    private:
        unsigned int cap;
        unsigned int size;
        T* storage;
    public:
        Stack()
        {
            cap=2;
            size=0;
            storage=new T[cap];
        } 
        Stack(unsigned int capacity): cap(capacity), size(0), storage(new T[capacity]){} 
        ~Stack()
        {
            delete [] storage;
        }
        void pop()
        {
            if(size==0)
            {
                std::cout<<"no hay elementos en el Stack"<<std::endl;
                return;
            }
            size--;
        }
        T& top() const
        {
            return storage[size-1];
        }
        void push( T newElement)
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
        bool empty() const {return size == 0;}
        unsigned int getSize() const {return size;}
};
 #endif       