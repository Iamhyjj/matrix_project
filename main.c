#include<assert.h>
#include"matrix.h"
//#define DEBUG
void TestFreeMatrix(){
	matrix m=create_matrix(400,400);
	free_matrix(&m);
	#ifdef DEBUG
		printf("m.row=%d\n",m.row);
		printf("m.col=%d\n",m.col);
	#endif
	assert(m.row==0);
	assert(m.col==0);
	printf("%s passed\n",__func__);
}
void TestMatrixProductAbyB(){
	matrix A,B,product,ans;
	element_type A_entry[]={1,2,3,4};
	element_type B_entry[]={4,3,2,1};
	element_type ans_entry[]={8,5,20,13};
	A=create_matrix(2,2);
	B=create_matrix(2,2);
	ans=create_matrix(2,2);
	enter_matrix(A,A_entry,4);
	enter_matrix(B,B_entry,4);
	enter_matrix(ans,ans_entry,4);
	product=matrix_product(A,B);
	#ifdef DEBUG
		print_matrix(product);
		print_matrix(ans);
	#endif
	assert(equal_matrix(product,ans));
	free_matrix(&A);
	free_matrix(&B);
	free_matrix(&product);
	free_matrix(&ans);
	printf("%s passed\n",__func__);
}
void TestCreateMatrix(){
	int i,j,m=3,n=3;
	matrix test=create_matrix(m,n);
	#ifdef DEBUG
		printf("m=%d\n",m);
		printf("n=%d\n",n);
		printf("row=%d\n",test.row);
		printf("col=%d\n",test.col);
	#endif
	assert(m==test.row);
	assert(n==test.col);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			assert(test.mat[i][j]==0);
		}
	}
	printf("%s passed\n",__func__);
	free_matrix(&test);
}

void TestEnterMatrixrbyc(){
	int r=2,c=3,i,j,k=0;
	matrix m=create_matrix(r,c);
	element_type a[]={2,3,5,7,11,13};
	enter_matrix(m,a,sizeof(a)/sizeof(element_type));
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			assert(m.mat[i][j]==a[k++]);
		}
	}
	free_matrix(&m);
	printf("%s passed\n",__func__);
}
void TestAddMatrix(){
	matrix A,B,sum,ans;
	element_type A_entry[]={1,2,3,4};
	element_type B_entry[]={2,3,5,7};
	element_type ans_entry[]={3,5,8,11};
	A=create_matrix(2,2);
	B=create_matrix(2,2);
	ans=create_matrix(2,2);
	enter_matrix(A,A_entry,4);
	enter_matrix(B,B_entry,4);
	enter_matrix(ans,ans_entry,4);
	sum=AddMatrix(A,B);
	#ifdef DEBUG
		print_matrix(sum);
		print_matrix(ans);
	#endif
	assert(equal_matrix(sum,ans));
	free_matrix(&A);
	free_matrix(&B);
	free_matrix(&sum);
	free_matrix(&ans);
	printf("%s passed\n",__func__);
} 
void TestMixedOperation(){
	matrix A,B,C,result1,result2;
	A=create_matrix(2,2);
	B=create_matrix(2,2);
	C=create_matrix(2,2);
	element_type A_entries[]={1,2,3,4};
	element_type B_entries[]={3,4,5,6};
	element_type C_entries[]={7,8,9,10};
	enter_matrix(A,A_entries,4);
	enter_matrix(B,B_entries,4);
	enter_matrix(C,C_entries,4);
	result1=AddMatrix(matrix_product(A,B),matrix_product(A,C));
	result2=matrix_product(A,AddMatrix(B,C));
	assert(equal_matrix(result1,result2)); 
	printf("%s passed\n",__func__);
}
void TestMatrixPow(){
	int pow=2,order=3;
	element_type m_entries[]={1,2,3,3,2,1,1,1,1},ans_entries[]={10,9,8,10,11,12,5,5,5};
	matrix m=create_matrix(order,order);
	matrix err=create_matrix(order,order-1);
	matrix ans=create_matrix(order,order);
	matrix m_result,err_result;
	enter_matrix(m,m_entries,order*order);
	enter_matrix(err,m_entries,order*order);
	enter_matrix(ans,ans_entries,order*order);
	m_result=matrix_pow(m,pow);
	err_result=matrix_pow(err,pow);
	assert(err_result.row==0);
	assert(err_result.col==0);
	assert(m_result.row==order);
	assert(m_result.col==order);
	assert(equal_matrix(ans,m_result));
	printf("%s passed\n",__func__);
}
void TestRandomMatrix(){
	int row=3,col=3,lower=4,upper=5,i,j;
	matrix m=create_random_matrix(row,col,lower,upper);
	assert(m.row=row);
	assert(m.col=col);
	#ifdef DEBUG
		print_matrix(m);
		printf("m.row=%d\n",m.row);
		printf("m.col=%d\n",m.col);
	#endif
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			assert(m.mat[i][j]>=1&&m.mat[i][j]<=5);
		}
	}
	free_matrix(&m);
	printf("%s passed\n",__func__);
}
void TestCreateIdentityMatrix(){
	int i,j,n=3;
	matrix m=create_identity_matrix(n);
	assert(m.col==n&&m.row==n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				assert(m.mat[i][j]==1);
			}
			else{
				assert(m.mat[i][j]==0);
			}
		}
	}
	free_matrix(&m);
	printf("%s passed\n",__func__);
}
void TestTranspose(){
	matrix m,mt;
	m=create_matrix(2,3);
	mt=Transpose(m);
}
int main(int argc, char *argv[]) {
	TestCreateMatrix();
	return 0;
}
