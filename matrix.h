#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include <iomanip>

using namespace std;

template <typename T>
class Matrix {
protected:
    //Node<T> *root;
    unsigned rows, columns;

    vector<Node<T>*> vect_row;
    vector<Node<T>*> vect_col;

public:
    Matrix(unsigned rows, unsigned columns){
        this->rows = rows;
        this->columns = columns;

        for(int i=0; i < this->rows; ++i) {
            if (vect_row.size() > 0) vect_row.clear();
            vect_row.push_back(nullptr);
        }
        for(int j=0 ; j< this->columns ; ++j){
            if(vect_col.size()>0) vect_col.clear();
            vect_col.push_back(nullptr);
        }
    }

    Matrix(const Matrix &copy_matrix){
        this->rows = copy_matrix.rows;
        this->columns = copy_matrix.columns;

        for(int i=0; i < this->rows; ++i) {
            if (vect_row.size() > 0) vect_row.clear();
            vect_row.push_back(nullptr);
        }
        for(int j=0 ; j< this->columns ; ++j){
            if(vect_col.size()>0) vect_col.clear();
            vect_col.push_back(nullptr);
        }

        for(int i=0 ; i < this->rows ; ++i) {
            for(int j=0 ; j < this->columns ; ++j) {
                auto temp_val = copy_matrix(i, j);
                if (!temp_val)
                    continue;

                set(i,j,temp_val);
            }
        }
    }

    void set(unsigned fil, unsigned col, T number){
        auto newNode = new Node<T>();
        auto **dirx = new Node<T>*;
        dirx = nullptr;
        auto **diry = new Node<T>*;
        diry= nullptr;
        bool checkinrow = 0;
        bool checkincol = 0;

        for (dirx = &vect_col[col]; *dirx != NULL; dirx = &(*dirx)->next){
            if (fil == (*dirx)->pos_X) {
                checkinrow = 1;
                break;
            } else if (fil < (*dirx)->pos_X) {
                *dirx = (*dirx)->next;
                checkinrow = 0;
            }
        }
        for (diry = &vect_row[fil] ;  *diry != NULL ; diry = &(*diry)->down){
            if (col == (*diry)->pos_Y) {
                checkincol = 1;
                break;
            } else if (col < (*diry)->pos_Y) {
                *diry = (*diry)->down;
                checkincol = 0;
            }
        }

        if(checkincol){
            if(number){
                (*dirx)->number = number;
                (*diry)->number = number;
            }
            else{
                *dirx = (*dirx)->next;
                *diry = (*diry)->down;
            }

        }
        else{
            if(!number)
                return;
            newNode->pos_Y = col;
            newNode->pos_X = fil;
            newNode->number = number;
            newNode->down = *diry;
            newNode->next = *dirx;
            *diry = newNode;
            *dirx = newNode;
        }

    }
    T get(unsigned fil, unsigned col) const{
        auto col_temp = vect_row[fil];
        auto row_temp = col_temp;
        if(!col_temp) return 0;
        while(row_temp){
            if(row_temp->pos_Y == col) return row_temp->number;
            row_temp = row_temp->down;
        }
    }
    T operator()(unsigned fil, unsigned col) const{
        return  get(fil,col);
    };

    Matrix<T> operator*(T scalar) const{
        Matrix<T> matriz(this->rows, this->columns);

        for(auto colum : vect_row){
            if(!colum)
                continue;
            while(colum){
                matriz.set(colum->pos_X, colum->pos_Y , colum->number * scalar);
                colum = colum->down;
            }
        }

        return matriz;
    };

    Matrix<T> operator*(Matrix<T> other) const{
        Matrix<T> matriz(this->rows, this->columns);
        if(this->rows != other.rows ) return throw out_of_range("Las matrizes no se pueden multiplicar");
        for(int i : matriz.rows){
            for(int j:matriz.columns){
                T temp=0;
                for(int k : this->columns){
                    temp += get(i,k)*other(k,j);
                }
            }
        }

        return other;
    };

    Matrix<T> operator+(Matrix<T> other) const{
        Matrix<T> matriz(this->rows, this->columns);
        if(this->rows != other.rows and this->columns != other.columns) throw  out_of_range("No son del mismo tamano");
        for(auto tempRow : vect_row){
            if(!tempRow) continue;
            while(tempRow){
                matriz.set(tempRow->pos_X, tempRow->pos_Y , tempRow->number + other(tempRow->pos_X, tempRow->pos_Y));
                tempRow = tempRow->down;
            }
        }
        return  matriz;
    };



    Matrix<T> operator-(Matrix<T> other) const{
        Matrix<T> matriz(this->rows, this->columns);
        if(this->rows != other.rows and this->columns != other.columns)  throw  out_of_range("No son del mismo tamano");
        for(auto tempRow : vect_row){
            if(!tempRow) continue;
            while(tempRow){
                matriz.set(tempRow->pos_X, tempRow->pos_Y , tempRow->number - other(tempRow->pos_X, tempRow->pos_Y));
                tempRow = tempRow->down;
            }
        }
        return  matriz;
    };

    Matrix<T> transpose() const{
        Matrix<T> matriz(this->rows, this->columns);
        for( int i=0 ; i < this->rows ; ++i) {
            if(this->vect_row[i]){
                auto temp_col = vect_row[i];
                while (temp_col){
                    matriz.set(temp_col->pos_Y, temp_col->pos_X, temp_col->number);
                }
            }
        }

        return matriz;
    };

    void print() const{
        for( int i=0 ; i < this->rows ; ++i) {
            if( !this->vect_row[i] ) {
                for(int j=0 ; j < this->columns ; ++j) {
                    cout<<setw(3)<<0<<" ";
                }
                cout << endl;
            }  else {
                auto temp_col = vect_row[i];
                int col_pos = temp_col->pos_Y;
                for(int j=0 ; j < temp_col->pos_Y ; ++j) {
                    cout<<setw(3)<<0<<" ";
                }

                while(temp_col) {
                    for(int j=0 ; j < temp_col->pos_Y - col_pos -1 ; ++j) {
                        cout<<setw(3)<<0<<" ";
                    }
                    cout << setw(3) << temp_col->number << " ";
                    col_pos = temp_col->pos_Y;
                    temp_col = temp_col->down;
                }
                for(int j=0 ; j < columns-col_pos-1 ; ++j) {
                    cout<<setw(3)<<0<<" ";
                }
                cout << endl;
            }
        }
    };

    ~Matrix(){
        for(auto temp : vect_col ) {
            if(temp){
                temp->killnext();
                break;
            }
        }
        for(auto temp_fil : vect_row) {
            if (temp_fil) {
                temp_fil->killdown();
                break;
            }
        }

        vect_row.clear();
        vect_col.clear();
    };
};

#endif //SPARSE_MATRIX_MATRIX_H