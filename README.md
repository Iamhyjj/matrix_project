# User Guide for matrix.h
## 1 What is a matrix type?
matrix type in this file is defined as follow:  
typedef double element_type;  
typedef struct matrix{  
  element_type** mat;  
  int row;  
  int col;  
}matrix;  
The default type of elements in the matrix are double  

### ***Before started, there's something you should know:
The result of ANY invalid matrix operation will be an empty matrix,namely:  
    m.row=0,m.col=0,m.mat=NULL;  
invalid matrix operations include but not limited to:  
(1)Add two matrixes of different sizes  
(2)multiply two matrixes that cannot be multiplied  
(3)calculate the power of/calculate the inversed matrix of a non-square matrix  
...

## 2 Basic matrix operations:
### (1)matrix create_matrix(int row,int coloumn):
   You can create a matrix(rowxcoloumn) by using function create_matrix  
   The function will return a matrix type variant whose elements are all 0  
for example:  
   matrix m=create_matrix(2,3);  
and you will get a matrix type variant m:  
   m.row=2;  
   m.col=3;  
   m.mat is showed as follow:  
       0.0  0.0  0.0  
       0.0  0.0  0.0  
### (2)create_identity_matrix(int order)  
   You can create an identity matrix of order n by using function create_identity_matrix()  
for example:  
    int n=3;  
    matrix m=create_idenity_matrix(n);  
m.mat is showed as follow:  
    1.0  0.0  0.0  
    0.0  1.0  0.0  
    0.0  0.0  1.0  

### (3)free_matrix(matrix m)  
   If you no longer need a matrix, you'd better free it in time to avoid memory leakage  
   You can simply do this by using free_matrix function  
for example:  
   free_matrix(m);  
(4)print_matrix(matrix m)  
   If you want to see every element in a matrix, you can use the function print_matrix  
for example:  
if the matrix m.mat=[1,2,3,4,5,6]  
   print_matrix(m);  
the result will be:  
      1.0  2.0  3.0  
      4.0  5.0  6,0  

## 3 assign value to elements in matrix
### (1)input_matrix(matrix m)
   You can manually input a matrix by using input_matrix()  
for example:  
   matrix m=create_matrix(3,3);  
   input_matrix(m);  
The result will be:  
Please input the matrix:  
1 2 3 4 5 6 7 8 9(here is your input)  
(or you can input like this:)  
1 2 3  
4 5 6  
7 8 9  
and m.mat will be:  
   1.0  2.0  3.0  
   4.0  5.0  6.0  
   7.0  8.0  9.0  
### (2)enter_matrix(matrix m,element_type* entries,int len)  
