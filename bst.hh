#ifndef __BST_HH__
#define __BST_HH__

template <typename T> class BST {
private:
class Node {
        private: 
            T data;
            Node* left;
            Node* right;
        public:
            Node(): data(), left(nullptr), right(nullptr) {}
            Node(const T& val)
            {
                data = val;
                left = nullptr;
                right = nullptr;
            }
            const T& getData()
            {
                return data;
            }

            Node* getLeft() const
            {
                return left;
            }
            Node* getRight() const
            {
                return right;
            }

            bool hasLeft() const 
            {
                return left != nullptr;
            }
            bool hasRight() const
            {
                return right != nullptr;
            }
            void setLeft(Node* n)
            {
                left = n;
            }
            void setRight(Node* n)
            {
                right = n;
            }
            
            
        };
    Node* root;
    unsigned int size;
public:
    BST() : root(nullptr), size(0) {}
    ~BST()
    {}
    bool empty() const {return root == nullptr;}
    unsigned int getSize() const {return size;}
    void insert(const T& newElement)
        {
            if(empty())
            {
                root =new Node(newElement);
                size++;
            }
            else
            {
                insert(newElement, root);
            }
        }
private:
        void insert(const T& newElement, Node* n)
        {
            if (n->getData() == newElement)
            {
                return;
            }
            if (n->getData() < newElement)
                {
                    if(n->hasLeft())
                    {
                        insert(newElement,n->getLeft());
                    }
                    else{
                    Node* newNode = new Node(newElement);
                    n->setLeft(newNode);
                    size++;}
                }
            else
            {
                if(n->hasRight())
                {
                    insert(newElement,n->getRight());
                }
                else{
                Node* newNode = new Node(newElement);
                n->setRight(newNode);
                size++;
                }
            }
    }
public:
        bool find(const T& element) const 
        {
            if(empty())
                return false;
            else 
            {
                return find(element, root);
            }
        }
    private:
        bool find(const T& element, Node* n) const 
        {
            if(n->getData()== element)
            {
                return true;
            }
            if(n->getData() < element)
            {
                if(n->hasLeft())
                {
                    return find(element, n->getLeft());
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if(n->hasRight())
                {
                    return find(element, n->getRight());
                }
                else
                {
                    return false;
                }
            }
        }
};
#endif