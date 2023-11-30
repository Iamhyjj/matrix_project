#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#define MAX_MATRIX_SIZE 500
#define EPS 1e-10
//NOTE:The result of any invalid operation will be an empty matrix(row=col=0,mat=NULL)
typedef double element_type;       //The type of elements in the matrix is double,change the type here (print_matrix and input_matrix need adjusting accordingly)
typedef struct matrix{
	element_type** mat;
	int row;
	int col;
}matrix;

//The initial value of every element in the matrix is 0 
matrix create_matrix(int row,int col){
	int i;
	matrix result;
	if(row>MAX_MATRIX_SIZE||col>MAX_MATRIX_SIZE){
		printf("Create matrix error:the number of rows(coloumns) of the matrix should be no more than %d\n ",MAX_MATRIX_SIZE);
		result.row=result.col=0;
		result.mat=NULL;
		return result;
	}
	if(row<=0||col<=0){
		result.col=result.row=0;
		result.mat=NULL;
		return result;
	}
	else{
		result.row=row;
		result.col=col;
	}
	result.mat=(element_type**)malloc(row*sizeof(element_type*));
	if(result.mat==NULL){
		printf("Create matrix error\n");
		result.row=result.col=0;
		return result;
	} 
	for(i=0;i<row;i++){
		result.mat[i]=(element_type*)calloc(col,sizeof(element_type));
		if(result.mat[i]==NULL){
			printf("Create matrix error\n");
			result.row=(i-1>0)?(i-1):0;
			return result;
		}
	}
	return result;
}

//create a random matrix(rxc) whose elements(int type) are between two bounds 
//still needs improving
matrix create_random_matrix(int r,int c,int lower_bound,element_type upper_bound){
	matrix result=create_matrix(r,c);
	int i,j,len=upper_bound-lower_bound+1;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			result.mat[i][j]=lower_bound+rand()%len;
		}
	}
	return result;
}

matrix create_identity_matrix(int order){
	matrix ret=create_matrix(order,order);
	int i;
	for(i=0;i<order;i++){
		ret.mat[i][i]=1;
	}
	return ret;
}

void input_matrix(matrix m){
	int j,i;
	printf("Please input the matrix:\n");
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col;j++){
			scanf("%lf",&m.mat[i][j]);
		}
	}
}
//The value of every element in the entry array will be given to the matrix
//if the length of the entry array is longer than row*col,then the excess elements in the array will be ignored
//if the length of the entry array is shorter than row*col,then the remaining elements in the matrix will stay unchanged
void enter_matrix(matrix m,element_type* entries,int len){
	int i,j,k=0;
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col;j++){
			m.mat[i][j]=entries[k++];
		}
	}
}

//This sector still needs improving
void print_matrix(matrix m){
	if(m.col==0||m.row==0){
		printf("This is an empty matrix\n");
	}
	else{
	int j,i;
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col;j++){
			printf("%8.2lf",m.mat[i][j]+EPS);
			}
		printf("\n");
	}
	}
}

//two matrixes are equal only if:1The sizes of two matrixes are equal 2 EVERY element in them are equal
int equal_matrix(matrix a,matrix b){
	if(a.row!=b.row||a.col!=b.col){
		return 0;
	}
	else{
		int i,j;
		for(i=0;i<a.row;i++){
			for(j=0;j<a.col;j++){
				if(fabs(a.mat[i][j]-b.mat[i][j])>EPS){
					return 0;
				}
			}
		}
	}
	return 1;
}

void free_matrix(matrix* m){
	int i;
	for(i=0;i<(*m).row;i++){
		free((*m).mat[i]);
	}
	free((*m).mat);
	(*m).row=0;
	(*m).col=0;
}


void SwapRow(matrix m,int r1,int r2){
	element_type* temp;
	temp=m.mat[r1];
	m.mat[r1]=m.mat[r2];
	m.mat[r2]=temp;
}

//r1+kr2
void RowPlus(matrix m,int r1, int r2, double k){
	int i;
	for(i=0;i<m.col;i++){
		m.mat[r1][i]+=k*m.mat[r2][i];
	}	
}
void MultiplyRow(matrix m,int r, double k){
	int i;
	for(i=0;i<m.col;i++){
		m.mat[r][i]*=k;
	}
}

matrix Transpose(matrix m){
	int i,j;
	matrix result=create_matrix(m.col,m.row);
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col;j++){
			result.mat[j][i]=m.mat[i][j];
		}
	}
	return result;
}

matrix AddMatrix(matrix m1,matrix m2){
	matrix result;
	int i,j;
	if(m1.col==m2.col&&m1.row==m2.row){
		result=create_matrix(m1.row,m1.col);
		for(i=0;i<m1.row;i++){
			for(j=0;j<m1.col;j++){
				result.mat[i][j]=m1.mat[i][j]+m2.mat[i][j];
			}
		}
	}
	else{
		result=create_matrix(0,0);
	}
	return result;
}

void ScalarMultiplation(matrix m,double k){
	int i,j;
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col;j++){
			m.mat[i][j]*=k;
		}
	}
}

matrix matrix_product(matrix a,matrix b){
	int rowa,rowb,cola,colb,i,j,k;
	rowa=a.row;
	rowb=b.row;
	cola=a.col;
	colb=b.col;
	matrix result;
	if(cola!=rowb){
		result=create_matrix(0,0);
	}
	else{
		result=create_matrix(rowa,colb);
		for(i=0;i<rowa;i++){
			for(j=0;j<colb;j++){
				for(k=0;k<cola;k++){
					result.mat[i][j]+=a.mat[i][k]*b.mat[k][j];
				}
			}
		}
	}
	return result;
}

//n must be no less than 0, or the result will be an empty matrix
matrix matrix_pow(matrix m,int n){
	if(m.row==0||m.col==0||m.row!=m.col||n<0){
		return create_matrix(0,0);
	}
	else{
		if(n==1){
			return m;
		}
		if(n==2){
			return matrix_product(m,m);
		}
		return n%2?matrix_product(m,matrix_pow(matrix_pow(m,(n-1)/2),2)):matrix_pow(matrix_pow(m,n/2),2);
	}
}

matrix GJ_elimination(matrix original_m){
	int i,j;
	matrix m=create_matrix(original_m.row,original_m.col);
	for(i=0;i<original_m.row;i++){
		for(j=0;j<original_m.col;j++){
			m.mat[i][j]=original_m.mat[i][j];
		}
	}
	for(i=0;i<m.row&&i<m.col;i++){
		j=i;
		while(m.mat[i][i]==0&&j<m.row){
			if(m.mat[j][i]){
				SwapRow(m,i,j);      //make mat[i][i]!=0
				MultiplyRow(m,i,-1);//To hold the value of Det(m) 
			}
			j++;
		}
		if(j==m.row){
			continue;                //every element in coloumn number i is 0,move to next coloumn
		}
		for(j=0;j<m.row;j++){
			if(j!=i&&m.mat[j][i]){
				RowPlus(m,j,i,-(m.mat[j][i]/m.mat[i][i]));
			}
		}
	}
	return m;
}

matrix standardize(matrix m){
	int i,j;
	matrix result=GJ_elimination(m);
	for(i=0;i<m.row&&i<m.col;i++){
		if(result.mat[i][i]){
		MultiplyRow(result,i,1/result.mat[i][i]);
		}
	}
	return result;
}

int Rank(matrix m){
	matrix temp=standardize(m);
	int i,result=0;
	for(i=0;i<m.row&&i<m.col;i++){
		if(temp.mat[i][i]){
			result++;
		}
	}
	free_matrix(&temp);
	return result;
}

double Det(matrix m){
	double result=1;
	if(m.row!=m.col){
		return 0;
	}
	else{
		int i;
		matrix temp;
		temp=GJ_elimination(m);
		for(i=0;i<temp.row;i++){
			result*=temp.mat[i][i];
		}
		free_matrix(&temp);
	}
	return result;
}

//(m,E)-->(E,m^-1)
matrix Inverse(matrix m){
	matrix result,temp=create_matrix(0,0);
	int i,j;
	if(m.row!=m.col){
		result=create_matrix(0,0);
	}
	else if(Rank(m)<m.row){
		result=create_matrix(0,0);
	}
	else{
		temp=create_matrix(m.row,2*m.row);
		result=create_matrix(m.row,m.col);
		for(i=0;i<m.row;i++){
			for(j=0;j<m.col;j++){
				temp.mat[i][j]=m.mat[i][j];
			}
		}
		for(;j<temp.col;j++){
			temp.mat[j-m.col][j]=1;
		}
		temp=standardize(temp);
		for(i=0;i<temp.row;i++){
			for(j=m.col;j<temp.col;j++){
				result.mat[i][j-m.col]=temp.mat[i][j];
			}
		}
		return result;
	}
	free_matrix(&temp);
	return result;
}

matrix Solve(matrix m){
	int i,j;
	matrix coefficient_matrix=create_matrix(m.row,m.col-1),temp,result;
	result=create_matrix(0,0);
	temp=create_matrix(0,0);
	int rm=Rank(m);
	for(i=0;i<m.row;i++){
		for(j=0;j<m.col-1;j++){
			coefficient_matrix.mat[i][j]=m.mat[i][j];
		}
	}
	if(rm>Rank(coefficient_matrix)){
		;
	}    							//No solution
	else if(rm==m.row){
		result=create_matrix(m.row,1);
		temp=standardize(m);
		for(i=0;i<m.row;i++){
			result.mat[i][0]=temp.mat[i][temp.col-1];
		}
	}
	else{
		//result=create_matrix(m.row,m.row+1);
		//for(i=0;i<m.row-rm;i++){
		//	for(j=0;j<result.row;j++){
		//		result.mat[j][i]=                  //UNFINISHED HERE
		//	}
		//}
		;	
	}								//General solution+Particular solution
	free_matrix(&coefficient_matrix);	
	free_matrix(&temp);
	return result;
}

