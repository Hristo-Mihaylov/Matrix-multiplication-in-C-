#include <iostream>
#include "Matrix.h"
using namespace std;

int main(int argc, char** argv)
{

    if (argc != 5)
    {
        cout<<"Invalid number of arguments!"<<endl;
        return -1;
    }


    if (argv[2][0] == '+' || argv[2][0] == 'x')
    {

    }
    else
    {
        cout<<"Invalid operation argument!"<<endl;
        return -1;
    }

    Matrix m;
    m.fill_from_file(argv[1]);

    if (argv[2][0] == '+')
    {
        if (atoi(argv[3]))
        {
            m.add(atoi(argv[3]));
            m.store_in_file(argv[4]);
        }
        else
        {
            Matrix n;
            n.fill_from_file(argv[3]);
            m.add(&n);
            m.store_in_file(argv[4]);
        }
    }
    else
    {
        if (atoi(argv[3]))
        {
            m.mult(atoi(argv[3]));
            m.store_in_file(argv[4]);
        }
        else
        {
            Matrix n;
            n.fill_from_file(argv[3]);
            m.mult(&n);
            m.store_in_file(argv[4]);
        }
    }



    //*****************************************************************************************
    // Experiment area.

    // Matrix m;
    // Matrix n;
    // char fname[] = "input1.txt";
    // char gname[] = "input2.txt";
    // char name[] = "output.txt";
    // m.fill_from_file(fname);
    // cout<<m.rows()<<endl<<m.columns()<<endl;
    // n.fill_from_file(gname);
    // cout<<n.rows()<<endl<<n.columns()<<endl;
    // for (int i=0; i<m.columns(); i++){
    // 	cout<<m.index(m.rows()-2,i)<<" ";
    // }


    // m.mult(&n);
    // // m.add(4);
    // // m.print();
    // // n.print();
    // m.store_in_file(name);

    // End of experiment area.
    //*****************************************************************************************


    return 0;
}
