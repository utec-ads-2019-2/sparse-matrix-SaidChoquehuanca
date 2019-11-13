#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    int pos_X,pos_Y;
public:
    Node<T> *next, *down;
    T number;
    explicit Node(){
        next = nullptr;
        down = nullptr;
        pos_X = 0;
        pos_Y = 0;
    };


    void killnext(){
        if(this->next){
            this->next->killnext();
        }
        delete this;
    }

    void killdown(){
        if(this->down){
            this->down->killdown();
        }
        delete this;
    }

    friend class Matrix<T>;

};

#endif //SPARSE_MATRIX_NODE_H
