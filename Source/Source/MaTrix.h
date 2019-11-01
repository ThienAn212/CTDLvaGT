#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#define EPSILON 0.00001
using namespace std;

class MaTrix
{
    public:
        int n;
        double **a;
    public:
        MaTrix();
        MaTrix(int n);
        MaTrix(int n,double **a);
        MaTrix(const MaTrix &a);

        // nhập ma trận 
        // argument nếu có sẽ là tên file và sẽ đọc từ file, không có thì mặc định là nhập từ bàn phím
        void input(string filename="");  
        // in ma trận
        // argument nếu có sẽ là tên file và sẽ in ra file, không có thì mặc định là in ra màn hình
        void printMaTrix(string filename="");

        MaTrix& operator =(const MaTrix &a);
        MaTrix& operator*(const MaTrix &a);

        //định thức của ma trận
        double det();
        
        //tạo ma trận mới mà dòng I,cột J đã bị xóa đi trong this
        MaTrix& deleteIJ(int I,int J);
        
        //định thức của ma trận sau khi xóa dòng i, cột j
        double A(int i,int j);

        // tạo ra ma trận nghịch đảo 
        MaTrix& inverse();

        //tạo ra ma trận mới mà dòng i, dòng j đổi chổ với nhau
        MaTrix& swapIJ(int i,int j);

        //tạo ra ma trận mới mà giá trị (dòng j) = (dòng j) + k*(dòng i) 
        MaTrix& addkItoJ(int I,int J,double k);

        //hạng của ma trận
        int rank();

        //tạo ra ma trận mới mà thay đổi các giá trị cột j thành các giá trị mảng b theo thứ tự
        MaTrix& changeJ(int J, double *b);
        
        //giải hệ phương trình tuyến tính
        double * solve(int nb,double *B);

        void clear();
        ~MaTrix();
}; 