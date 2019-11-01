#include "MaTrix.h"
#define _CRT_SECURE_NO_WARNINGS

char *convertTo(string s) //string convert to char *
{
    char *res = new char[s.length()+4];
    for (int i = 0; i <= s.length(); ++i)
    {
        res[i] = s[i];
    }
    return res;
}

MaTrix::MaTrix()
{
    this->a = NULL;
    this->n = 0;
}

MaTrix::MaTrix(int N)
{
    this->n=N;
    a=new double*[n];
    for(int i=0;i<n;++i)
    {
        a[i]=new double[n];
    }
}

MaTrix::MaTrix(int N, double **A)
{
    this->n = N;
    this->a = new double *[N];
    for (int i = 0; i < N; ++i)
    {
        a[i] = new double[N];
        for (int j = 0; j < N; ++j)
        {
            a[i][j] = A[i][j];
        }
    }
}

MaTrix::MaTrix(const MaTrix &A)
{
    //cout<<"1"<<endl;
    n = A.n;
    a = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            a[i][j] = A.a[i][j];
        }
    }
}

void MaTrix::input(string filename) //O(n^2)
{
    FILE *fi;
    if  (filename.length()==0){
        fi=stdin;
    }
    else{
        fi=fopen(convertTo(filename),"r");
    }
    
    this->clear();

    fscanf(fi,"%d",&n);
    a = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            fscanf(fi,"%lf",&a[i][j]);
        }
    }

    if (filename.length()!=0) fclose(fi);
}



void MaTrix::printMaTrix(string filename) //O(n^2)
{
    FILE *f;
    if (filename.length() != 0){
        f = fopen(convertTo(filename), "w");
    }
    else{
        f = stdout;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fprintf(f, "%.2lf ", a[i][j]);
        }
        fprintf(f,"\n");
    }

    if (filename.length()!=0) fclose(f);
}

MaTrix &MaTrix::operator=(const MaTrix &A) //O(n^2)
{
    this->clear();
    
    n = A.n;
    a = new double *[n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; ++j)
        {
            a[i][j] = A.a[i][j];
        }
    }
    return *this;
}

MaTrix& MaTrix::operator*(const MaTrix &A) //O(n^3)
{
    if (n!=A.n) {
        cout<<"khong the nhan"<<endl;
        return *(new MaTrix());
    }

    MaTrix *res=new MaTrix(n);
    
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)
        {
            double sum=0;
            for(int k=0;k<n;++k){
                sum+=a[i][k]*A.a[k][j];
            }
            res->a[i][j]=sum;
        }
    }

    return *res;
}


double MaTrix::det() //O(n2)
{
    if (n==0) return 0;
    if (n==1) return a[0][0];
    if (n==2) return a[0][0]*a[1][1]-a[0][1]*a[1][0];
    double res=0;
    
    //  
    for(int j=0;j<n;++j)
    {
        double tich=1;
        int i=0;
        for(int k=0;k<n;++k)
        {
            tich*=a[(i+k)%n][(j+k)%n];
        }
        res+=tich;
    }

    //
    for(int j=0;j<n;++j)
    {
        double tich=1;
        int i=0;
        for(int k=0;k<n;++k)
        {
            tich*=a[(i+k)%n][(j-k+n)%n];
        }
        res-=tich;
    }
    return res;
}

MaTrix& MaTrix::deleteIJ(int I,int J) //O(n2)
{
    if (!(I<n&&J<n&&I>=0&&J>=0)) 
    {
        cout<<"dong hoac cot khong hop le"<<endl;
        return *(new MaTrix());
    } 

    MaTrix *res= new MaTrix(n-1);
    int x=0,y=0;
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            if (i!=I && j!=J)
            {
                res->a[x][y]=a[i][j];
                ++y;
                if (y==res->n)
                {
                    ++x;
                    y=0;
                }
            }
        }
    }
    return *res;
}

double MaTrix::A(int i,int j) //O(n2)
{
    MaTrix a=(this->deleteIJ(i,j));
    return a.det();
}

MaTrix& MaTrix::inverse()//O(n^4)
{
    double detThis=this->det();
    if (abs(detThis-0)<EPSILON) {
        cout<<"Ma Tran khong kha nghich"<<endl;
        return *(new MaTrix());
    }

    MaTrix *res=new MaTrix(n);
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<n;++j)
        {
            res->a[i][j]=(pow(-1,i+j)*this->A(j,i))/detThis;
        }
    }
    return *res;
}

MaTrix& MaTrix::swapIJ(int i,int j) //O(n)
{
    double temp;
    MaTrix *res=new MaTrix(*this);
    for(int k=0;k<res->n;++k)
    {
        temp=res->a[i][k];
        res->a[i][k]=res->a[j][k];
        res->a[j][k]=temp;
    }
    return *res;
}

MaTrix& MaTrix::addkItoJ(int I,int J,double K) //O(n)
{
    MaTrix *res=new MaTrix(*this);
    for(int k=0;k<res->n;++k)
    {
        res->a[J][k]+=K*a[I][k];
    }
    return *res;
}

int MaTrix::rank()
{
    MaTrix *test=new MaTrix(*this);
    for(int i=0;i<n-1;++i)
    {
        
        if (abs(test->a[i][i]-0)<EPSILON)
        {
            int k=0;
            for(int j=i+1;j<n;++j)
            {
                if (abs(test->a[j][i]-0)>EPSILON) 
                {
                    k=j;
                    break;
                }
            }
            if (k==0) return i+1;
            *test=test->swapIJ(k,i);
        }

        for(int j=i+1;j<n;++j)
        {
            *test=test->addkItoJ(i,j,-test->a[j][i]/test->a[i][i]);
        }
        
    }
    if (abs(test->a[n-1][n-1]-0)>EPSILON) return n;
    else return n-1;
}

MaTrix& MaTrix::changeJ(int J,double * b)
{
    MaTrix *res=new MaTrix(*this);
    for(int i=0;i<n;++i)
    {
        res->a[i][J]=b[i];
    }
    return *res;
}

double *MaTrix::solve(int nb,double *b)
{
    if (nb!=n) 
    {
        cout<<"mang he so tu do khong phu hop de giai"<<endl;
        return NULL;
    }
    double detA=this->det();
    if (detA!=0) cout<<"he phuong trinh co nghiem duy nhat"<<endl;
    else 
    {
        cout<<"he phuong trinh hoac vo nghiem hoac vo so nghiem"<<endl;
        return NULL;
    }

    MaTrix A;
    double *res=new double[n];
    for(int j=0;j<n;++j)
    {
        A=this->changeJ(j,b);
        res[j]=A.det()/detA;
    }
    return res;
}


MaTrix::~MaTrix()
{
    //cout<<"-1"<<endl;
    this->clear();
}

void MaTrix::clear()
{
    if (n == 0)
        return;
    for (int i = 0; i < n; ++i)
    {
        delete[] a[i];
    }
    delete[] a;
    n = 0;
}
