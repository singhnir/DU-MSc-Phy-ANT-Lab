#include<stdio.h>
#include<math.h>
// function to solve AX=b for X
void gausspivot(int n,double A[n][n+1],double x[]){
    int i,j,k;
    for(i=0;i<n-1;i++){
        //Partial Pivoting
        for(k=i+1;k<n;k++){
            //If the diagonal element is less than the terms below it
            if(fabs(A[i][i])<fabs(A[k][i])){
                //Swap the rows in the matrix
                for(j=0;j<=n;j++){                
                    double temp;
                    temp=A[i][j];
                    A[i][j]=A[k][j];
                    A[k][j]=temp;
                }
            }
        }
        //Begin the Gauss Elimination
        for(k=i+1;k<n;k++){
            double term;
            term=A[k][i]/A[i][i];
            for(j=0;j<=n;j++){
                A[k][j]=A[k][j]-term*A[i][j];
            }
        }        
    }
    //Start with the back-substitution
    for(i=n-1;i>=0;i--){
        x[i]=A[i][n];
        for(j=i+1;j<n;j++){
            x[i]=x[i]-A[i][j]*x[j];
        }
        x[i]=x[i]/A[i][i];
    }  
    // printing the x array
    for(i=0;i<n;i++) {
        printf(" a[%d]= %.3lf\n",i,x[i]);
    }     
}
int main()
{
    int n,N=10;   // no of datapoints
    // n is order of matrix or n-1 is the order of polynomial
    printf("enter the order of augmented matrix:");
    scanf("%d",&n);
    int i,j,k;
    double x[]={1,2,3,4,5,6,7,8,9,10};
    double y[]={6.37,17.42,34.13,56.5,84.53,118.22,157.22,202.58,253.25,309.5};  
    double sigma[]={3.19,8.71,17.06,28.25,42.26,59.11,78.78,101.29,126.62,154.79}; 
    double A[n][n+1];
    // part A of augmented matrix [A:b] 
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            double weight,sum=0,w=0;
            for(k=0;k<N;k++) {
                weight=1/pow(sigma[k],2);
                sum+=pow(x[k],i+j)*weight;
                w+=weight;
            }
            A[i][j]=sum/w;
        }
    }
    // part b of augmented matrix [A:b]
    for(i=0;i<n;i++) {
        double weight,sum=0,w=0;
        for(k=0;k<N;k++) {
            weight=1/pow(sigma[k],2);
            sum=sum+(pow(x[k],i)*y[k]*weight);
            w+=weight;
        }
        A[i][n]=sum/w;
    }
    double a[n],yf[N]; //yf[N] is fitted values
    // finding the coefficients
    printf("The coefficients for order [%d] are:\n",n-1);
    gausspivot(n,A,a);

    FILE*fp=NULL;
    fp=fopen("4.txt","w");
    // defining the polynomial
    k=0;
    while(k<N) {   
        double sum=0;
        for (i=0;i<n;++i)
            sum += a[i]*pow(x[k],i);
        yf[k]=sum;
        fprintf(fp,"%.3lf\t%lf\n",x[k],yf[k]);
        k++;
    }
    // calculating the chi square
    double chi=0;
    for (i=0;i<N;++i)
        chi += 1/pow(sigma[i],2)*(yf[i]-y[i])*(yf[i]-y[i]);
    printf("Chi square for order [%d]:%lf\n",n-1,chi);
}