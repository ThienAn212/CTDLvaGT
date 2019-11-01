#include"Map.h"
#include"Header.h"
#include"MaTrix.h"

using namespace std;

MaTrix inputMatrix()
{
    int chose;
    bool check = false;
    MaTrix a;
    while (!check)
    {
        system("cls");
        cout << "Input Matrix: " << endl;
        cout << "1. file." << endl;
        cout << "2. keyboard." << endl;
        cout << "-1. EXIT." << endl;
        cout << "Your choice: ";
        cin >> chose;
        string filename;
        switch (chose)
        {
        case -1:
            return *(new MaTrix());
        case 1:
            cout << "filename: ";
            cin >> filename;
            a.input(filename);
            check = true;
            break;
        case 2:
            a.input();
            check = true;
            break;
        default:
            check = false;
        }
        if (check)
            break;
    }
    return a;
}

void MatrixOption()
{
    MaTrix a=inputMatrix();
    if (a.n==0) return;
    while (1)
    {
        system("cls");
        int option;
        cout << "FEATURE: " << endl;
        cout << "1. det." << endl;
        cout << "2. inverse." << endl;
        cout << "3. multiply with another Matrix." << endl;
        cout << "4. rank." << endl;
        cout << "5. solve." << endl;
        cout << "-1. EXIT" << endl;
        cout<<"Your option: ";
        cin>>option;
        switch (option)
        {
        case -1:
            return;
        case 1:
            cout<<"dinh thuc cua ma tran la: "<<a.det()<<endl;
            break;
        case 2: 
            cout<<"nghich dao cua ma tran la: "<<endl;
            a.inverse().printMaTrix();
            break;
        case 3:
        {
            MaTrix b=inputMatrix();
            if (b.n==0) return;
            MaTrix res=a*b;
            system("cls");
            cout<<"ket qua khi nhan 2 ma tran: "<<endl;
            a.printMaTrix();
            cout<<"va: "<<endl;
            b.printMaTrix();
            cout<<"la: "<<endl;
            res.printMaTrix();
        }
        break;
        case 4:
            cout<<"hang cua ma tran la: "<<a.rank()<<endl;
            break;
        case 5:
        {
            double *b=new double[a.n];
            double *res;
            cout<<"nhap mang he so tu do (n so): "<<endl;
            for(int i=0;i<a.n;++i)
                cin>>b[i];
            res=a.solve(a.n,b);
            cout<<"Loi giai: "<<endl;
            for(int i=0;i<a.n;++i)
            {
                cout<<"x [ "<<i+1<<" ] = "<<res[i]<<endl;
            }
        }
            break;
        default:
            break;
        }
        system("pause");
    }
}

int main()
{

    while (true)
    {
        system("cls");
        cout << "1. BOOL FUNCTION." << endl;
        cout << "2. VECTOR." << endl;
        cout << "3. MATRIX." << endl;
        cout << "-1. EXIT." << endl;
        cout << "-------------------------" << endl;
        int option1;
        cout << "your option: ";
        cin >> option1;
        switch (option1)
        {
        case -1:
            return 0;
        case 1:
			Bool();
            break;
        case 2:
			Vector();
            break;
        case 3:
            MatrixOption();
            break;
        default:
            cout << "Unsupported feature!!" << endl;
        }
    }
    return 0;
}


