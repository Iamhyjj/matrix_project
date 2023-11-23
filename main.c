#include <stdio.h>
#include<assert.h>
#include <stdlib.h>
//#define DEBUG
void TestMatrixProductAbyB(){
	matrix A,B,product,ans;
	element_type A_entry[]={1,2,3,4};
	element_type B_entry[]={4,3,2,1};
	element_type ans_entry[]={8,5,20,13};
	A=create_matrix(2,2);
	B=create_matrix(2,2);
	ans=create_matrix(2,2);
	EnterMatrix(A,A_entry,4);
	EnterMatrix(B,B_entry,4);
	EnterMatrix(ans,ans_entry,4);
	product=matrix_product(A,B);
	#ifdef DEBUG
		print_matrix(product);
		print_matrix(ans);
	#endif
	assert(equal_matrix(product,ans));
	free_matrix(A);
	free_matrix(B);
	free_matrix(product);
	free_matrix(ans);
	printf("%s passed\n",__func__);
}
void TestCreateMatrix(){
	int m=3,n=3;
	matrix test=create_matrix(3,3);
	#ifdef DEBUG
		printf("m=%d\n",m);
		printf("n=%d\n",n);
		printf("row=%d\n",test.row);
		printf("col=%d\n",test.col);
	#endif
	assert(m==test.row);
	assert(n==test.col);
	assert(test.mat!=NULL);
	printf("%s passed\n",__func__);
	free_matrix(test);
}

void TestEnterMatrixrbyc(){
	int r=2,c=3,i,j,k=0;
	matrix m=create_matrix(r,c);
	element_type a[]={2,3,5,7,11,13};
	EnterMatrix(m,a,sizeof(a)/sizeof(element_type));
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			assert(m.mat[i][j]==a[k++]);
		}
	}
	printf("%s passed\n",__func__);
}
void TestAddMatrix2by3(){
	int A_entries[]={1,2,3,4,5,6};
	
	int B_entries[]={1,2,3,4,5,6};
} 
void TestMixedOperation(){
	;
}
int main(int argc, char *argv[]) {
	TestEnterMatrixrbyc();
	TestMatrixProductAbyB();
	return 0;
}
