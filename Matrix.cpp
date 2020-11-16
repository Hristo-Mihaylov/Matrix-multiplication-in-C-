#include <iostream>
#include <stdlib.h>
#include "Matrix.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


using namespace std;

Matrix::Matrix()
{

}

int Matrix::rows()
{
    return _matrix.size();
}

int Matrix::columns()
{
    return _matrix[0].size();
}


int Matrix::fill_from_file(char *path)
{
    int fd = open(path, O_RDONLY, S_IRWXU);

    if(fd == -1)
    {
        printf("Error with open\n");
        return -1;
    }

    char buff[2];
    int val=0;
    vector<int> vect = {};
    _matrix.push_back(vect);
    while (read(fd, buff, 1) == 1)
    {
        if (buff[0] == '\n')
        {
            _matrix[_matrix.size()-1].push_back(val);
            _matrix.push_back(vect);
            val=0;

        }
        else if (buff[0] == ' ')
        {
            _matrix[_matrix.size()-1].push_back(val);
            val=0;

        }
        else
        {
            val = 10*val + atoi(buff);
        }


    }
    if (_matrix.back().empty())
    {
        _matrix.pop_back();
    }
    close(fd);


    return 0;
}


int Matrix::store_in_file(char *path)
{

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    if(fd == -1)
    {
        printf("Error with open\n");
        return -1;
    }
    for (int i=0; i<rows(); i++)
    {
        for (int j=0; j<columns(); j++)
        {
            char buff[64];
            sprintf(buff, "%d", _matrix[i][j]);
            write(fd, buff, strlen(buff));
            if (j == columns()-1)
            {
                write(fd, "\n", 1);
            }
            else
            {
                write(fd, " ", 1);
            }
        }
    }
    close(fd);

    return 0;
}


void Matrix::print()
{
    for (int i=0; i<_matrix.size(); i++)
    {
        for (int j=0; j<_matrix[i].size(); j++)
        {
            cout<<_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}


int Matrix::index(int row, int column)
{
    return _matrix[row][column];
}

int Matrix::add(Matrix *m)
{
    for (int i=0; i<_matrix.size(); i++)
    {
        for (int j=0; j<_matrix[i].size(); j++)
        {
            _matrix[i][j] = _matrix[i][j] + m->index(i, j);
        }
    }
    return 0;
}


int Matrix::add(int val)
{
    for (int i=0; i<_matrix.size(); i++)
    {
        for (int j=0; j<_matrix[i].size(); j++)
        {
            _matrix[i][j] = _matrix[i][j] + val;
        }
    }
    return 0;
}


int Matrix::mult(Matrix *m)
{
    vector<vector<int>> vect = {{}};
    for (int i=0; i<rows(); i++)
    {
        for (int j=0; j<m->columns(); j++)
        {
            vect[i].push_back(0);
        }
        if (i != rows()-1)
        {
            vect.push_back({});
        }
    }

    for (int i=0; i<rows(); i++)
    {
        for (int j=0; j<m->columns(); j++)
        {
            for (int k=0; k<m->rows(); k++)
            {
                vect[i][j] = vect[i][j] + _matrix[i][k]*(m->index(k, j));
            }
        }
    }

    for (int i=0; i<rows(); i++)
    {
        _matrix[i].clear();
    }

    _matrix.clear();

    for (int i=0; i<vect.size(); i++)
    {
        _matrix.push_back({});
        for (int j=0; j<vect[0].size(); j++)
        {
            _matrix[i].push_back(vect[i][j]);
        }
    }

    return 0;
}


int Matrix::mult(int val)
{
    for (int i=0; i<_matrix.size(); i++)
    {
        for (int j=0; j<_matrix[i].size(); j++)
        {
            _matrix[i][j] = _matrix[i][j] * val;
        }
    }
    return 0;
}

