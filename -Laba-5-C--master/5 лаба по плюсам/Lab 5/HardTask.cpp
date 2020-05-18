#include "Stdafx.h"

/*
Файл состоит из k компонент структуры, где каждая 
компонента содержит две матрицы: первая размерности 
m × n, вторая размерности m × l. Получить k сумму 
соответствующих матриц и записать их во второй файл.
Вывести на экран содержимое первого и второго файлов
*/
using namespace std;

struct Matrix;
void CheckDigit(unsigned& anydigit);
void DisplayMatrix(int* Pointer, unsigned n, unsigned m);
int* InitMatrix(unsigned l, unsigned n, unsigned m);
int* FreeMemory(unsigned n, unsigned m);
int BlockWriteFile(const char* FileName, Matrix* MassiveMat, unsigned count_matrix, unsigned row, unsigned col);
void DisplayFile(const char* FileName, int count_matrix, unsigned n, unsigned m);
void WorkFunc(Matrix* masmat, string FileNameSec, int count_komponent, int row,
    int col);

struct Matrix
{
	int* mat1; // m x n    |
                       // | n == l
	int* mat2; // m x l    |
};

void hard()
{
	system("cls");
	printf("\nHard level task: \n");
    unsigned count_komponent,
        row, col;
    printf("\nВведите k(количество компонент структуры): "); CheckDigit(count_komponent);
    printf("\nВведите размерность матриц(m x n): \n\tколичество строк: "); CheckDigit(row); 
    printf("\tКоличество столбцов: "); CheckDigit(col);
    Matrix* MassiveMat = new Matrix[count_komponent];
    std::string filename = "firstfile.txt";
    //printf("\nВведите название 1-го файла: "); cin>> filename;
    BlockWriteFile(filename.c_str(), MassiveMat, count_komponent, row, col);

    DisplayFile(filename.c_str(), count_komponent, row, col);

    cout << "\nСумыы соответсвующих компонет структуры записаные в файл: \n";
    string secfilename = "secondfile.txt";
    WorkFunc(MassiveMat, secfilename, count_komponent, row, col);
    ifstream f_in; f_in.open(secfilename, ios::in);
    int* Pointer = FreeMemory(row, col);
    int Sector = 0;
    for (size_t j = 0; j < count_komponent; j++)
    {
        int i = 0, q = 0;
        while (f_in >> Pointer[i] && i < (row * col)-1) { i++; }
        printf("\n %d's  first component matrix \n", (Sector + 1));
        DisplayMatrix(Pointer, row, col);
     /*   while (f_in >> Pointer[q] && q < row * col) { q++; }
        printf("\n %d's  second component matrix \n", (Sector + 1));
        DisplayMatrix(Pointer, row, col);*/
        Sector++;
    }
}
void WorkFunc(Matrix* masmat,string FileNameSec, int count_komponent, int row, int col)
{
    int* result_mat = new int[row*col];
    ofstream f_out; f_out.open(FileNameSec, ios::out);
    for (int q = 0; q < count_komponent; ++q)
    {
        for (int i = 0; i < row * col; ++i)
        {
            f_out << (masmat[q].mat1[i] + masmat[q].mat2[i])<<" ";
        }
        f_out << "\n";

    }
    f_out.close();
}

void CheckDigit(unsigned& anydigit)
{
    while (true)
    {
        std::cin >> anydigit;
        if (!isalpha(anydigit) && !isspace(anydigit))
                     break;
       if (cin.bad() || cin.fail())
       {
            cin.clear();
          cin.ignore(cin.rdbuf()->in_avail());
        }
        std::cout << "\nНекоректный ввод числового значения, повторите ввод!!!\n";
    }
}

void DisplayMatrix(int* Pointer, unsigned n, unsigned m)
{
    unsigned i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%4d", *(Pointer + i * m + j));
        }
        printf("\n");
    }
}

int* InitMatrix(unsigned l, unsigned n, unsigned m)
{
    unsigned i;
    int* Pointer = (int*)malloc(n * m * sizeof(int));
    for (i = 0; i < n * m; i++) { Pointer[i] = rand()%10; }
    return Pointer;
}

int* FreeMemory(unsigned n, unsigned m)
{
    int* Pointer = (int*)malloc(n * m * sizeof(int));
    return Pointer;
}

int BlockWriteFile(const char* FileName,Matrix* MassiveMat, unsigned count_matrix, unsigned row, unsigned col)
{
    int BufSize = sizeof(int) * row * col,
        counter_matrix = 0;
   
    //Matrix* matrix = new Matrix[count_matrix];
    unsigned i;

    ofstream f_out;
    f_out.open(FileName, ios::out);

    if (!f_out.is_open())
    {
        printf("Can't open file to write.");
        getchar();
        abort();
    }

    for (i = 0; i < count_matrix; i++)
    {
        MassiveMat[i].mat1 = InitMatrix(i, row, col);
        MassiveMat[i].mat2 = InitMatrix(i, row, col);
        for (size_t j = 0; j < row*col; j++)
        {
            f_out << MassiveMat[i].mat1[j]<< " ";
        }
       f_out << "\n";
        for (size_t j = 0; j < row * col; j++)
        {
            f_out << MassiveMat[i].mat2[j] << " ";
        }       
       f_out << "\n";
    }
    f_out.close();
    return counter_matrix;
}

void DisplayFile(const char* FileName, int count_matrix, unsigned n, unsigned m)
{
    int BufSize = sizeof(int) * n * m, Sector = 0;
    int* Pointer = FreeMemory(n, m);

    ifstream f_in;
    f_in.open(FileName, ios::in);

    if (!f_in.is_open()) { printf("\nCan't open file to read."); getchar(); abort(); }

    for (size_t j = 0; j < count_matrix; j++)
    {
        int i = 0, q = 0;
        while (f_in >> Pointer[i] && i < (n*m)-1) {  i++; }
        printf("\n %d's  first component matrix \n", (Sector + 1));
        DisplayMatrix(Pointer, n, m);
        while (f_in >> Pointer[q] && q < (n * m) - 1) { q++; }
        printf("\n %d's  second component matrix \n", (Sector + 1));
        DisplayMatrix(Pointer, n, m);       
        Sector++;
    }
}


