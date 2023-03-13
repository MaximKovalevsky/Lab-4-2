// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

template<typename T>

class Matrix
{
private:
    T** matrix;
    int row;
    int column;
public:
    Matrix(int newRow, int newColumn)// конструктор для создания матрицы
    {
        this->row = newRow;
        this->column = newColumn;
        matrix = (T**) new T * [row];//создаем динамический массив для матрицы
        for (int i = 0; i < row; i++)
            matrix[i] = (T*)new T[column];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                matrix[i][j] = 0;
    }

    Matrix(const Matrix& newMatrix)//конструктор копирования
    {
        this->row = newMatrix.row;
        this->column = newMatrix.column;
        matrix = (T**) new T * [row];
        for (int i = 0; i < row; i++)
            matrix[i] = (T*)new T[column];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                matrix[i][j] = newMatrix.matrix[i][j];
    }

    Matrix operator=(const Matrix& newMatrix)//конструктор присваивания копированием
    {
        if (this->column > 0) //сначала освобождаем память
        {
            for (int i = 0; i < row; i++)
                delete[] matrix[i];
        }

        if (this->row > 0)
            delete[] matrix;

        this->row = newMatrix.row;
        this->column = newMatrix.column;
        matrix = (T**) new T * [row];
        for (int i = 0; i < row; i++)
            matrix[i] = (T*) new T[column];
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                matrix[i][j] = newMatrix.matrix[i][j];

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix& newMatrix)//оператор вывода
    {
        for (int i = 0; i < newMatrix.row; i++)
        {
            for (int j = 0; j < newMatrix.column; j++)
                out << newMatrix.matrix[i][j] << "\t";
            out << std::endl;
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, const Matrix& newMatrix)//оператор ввода
    {
        for (int i = 0; i < newMatrix.row; i++)
            for (int j = 0; j < newMatrix.column; j++)
                in >> newMatrix.matrix[i][j];
        return in;
    }

    T getMatrix(int i, int j)//метод для вывода определенного элемента матрицы
    {
        if ((this->row > 0) && (this->column > 0))
            return matrix[i][j];
        else
            return 0;
    }

    void setMatrix(int i, int j, T a)//метод для изменения элементов матрицы
    {
        if ((i < 0) || (i >= this->row))
            return;
        if ((j < 0) || (j >= this->column))
            return;
        matrix[i][j] = a;
    }

    Matrix operator++(T)//оператор ++
    {
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                matrix[i][j] += 1;
        return *this;
    }

    Matrix operator+(Matrix& newMatrix)//оператор +
    {
        Matrix<int> tmp(row, column);
        if ((row == newMatrix.row) and (column == newMatrix.column))
        {
            for (int i = 0; i < row; i++)
                for (int j = 0; j < column; j++)
                    tmp.matrix[i][j] = matrix[i][j] + newMatrix.matrix[i][j];
        }
        else
            std::cout << "Для сложения матриц их размерность должна быть одинаковой. " << '\n';
        return tmp;
    }

    Matrix operator+=(Matrix newMatrix)//оператор +=
    {
        if ((this->row == newMatrix.row) and (this->column == newMatrix.column))
        {
            for (int i = 0; i < row; i++)
                for (int j = 0; j < column; j++)
                    matrix[i][j] = matrix[i][j] + newMatrix.matrix[i][j];
        }
        else
            std::cout << "Для сложения матриц их размерность должна быть одинаковой. " << '\n';
        return *this;
    }

    Matrix operator*(Matrix& newMatrix)//оператор *
    {
        int sameMax = 0;
        int sameMin = 0;

        if (this->column == newMatrix.row)
        {
            sameMax = std::max(column, row);
            sameMin = std::min(column, row);
        }
        if ((this->row == 1) || (newMatrix.row == 1))
            sameMax = 1;
        Matrix<int> tmp(sameMax, sameMax);
        if ((this->column == newMatrix.row))
        {
            for (int i = 0; i < sameMax; i++)
            {
                for (int j = 0; j < sameMax; j++)
                {
                    for (int a = 0; a < sameMin; a++)
                    {
                        tmp.matrix[i][j] += matrix[i][a] * newMatrix.matrix[a][j];
                    }
                }
            }
        }
        else
        {
            std::cout << "Для умножения матриц у них должно быть общее количество строк или столбцов. " << '\n';
            return *this;
        }
        return tmp;

    }

    Matrix operator*=(const Matrix& newMatrix) //оператор *= (не верный - создает новую матрицу вместо перезаписи в старую матрицу M)
    {
        //нужно скопировать содержимое матрицы M в другую, увеличить размерноcть матрицы M
        int sameMax = 0;
        int sameMin = 0;

        if (this->column == newMatrix.row)
        {
            sameMax = std::max(column, row);
            sameMin = std::min(column, row);
        }
        if ((this->row == 1) || (newMatrix.row == 1))
            sameMax = 1;
        Matrix<int> tmp(sameMax, sameMax);
        if ((this->column == newMatrix.row))
        {
            for (int i = 0; i < sameMax; i++)
            {
                for (int j = 0; j < sameMax; j++)
                {
                    for (int a = 0; a < sameMin; a++)
                    {
                        tmp.matrix[i][j] += matrix[i][a] * newMatrix.matrix[a][j];
                    }
                }
            }
        }

        else
        {
            std::cout << "Для умножения матриц у них должно быть общее количество строк или столбцов. " << '\n';
            return *this;
        }
        //matrix = (T**)malloc(sameMax * sameMax * sizeof(T));//вариант по увелечению размера матрицы

        return tmp;


    }

    int determ(Matrix newMatrix) //метод для вычисления определителя
    {
        int det = 0;//величина определителя
        int n = std::max(row, column);//порядок определителя
        Matrix<int> temp(row, column);
        if (this->row == this->column)
        {
            if (n == 1)
            {
                return newMatrix.matrix[0][0];
            }
            else if (n == 2)
            {
                det = (newMatrix.matrix[0][0] * newMatrix.matrix[1][1] - newMatrix.matrix[0][1] * newMatrix.matrix[1][0]);
                return det;
            }
            else
            {
                det = (newMatrix.matrix[0][0] * newMatrix.matrix[1][1] * newMatrix.matrix[2][2] + newMatrix.matrix[1][0] * newMatrix.matrix[2][1] * newMatrix.matrix[0][2] + newMatrix.matrix[0][1] * newMatrix.matrix[1][2] * newMatrix.matrix[2][0]) - (newMatrix.matrix[0][2] * newMatrix.matrix[1][1] * newMatrix.matrix[2][0] + newMatrix.matrix[2][1] * newMatrix.matrix[1][2] * newMatrix.matrix[0][0] + newMatrix.matrix[1][0] * newMatrix.matrix[0][1] * newMatrix.matrix[2][2]);
                return det;
            }

        }
        else//если в определителе количество строк не равно количеству столбцов
        {
            std::cout << "Определитель не ровный" << '\n';
            return 0;
        }
    }

    T& operator()(int newRow, int newColumn)//оператор () - по просьбе Полковского Олега Александровича
    {
        return this->matrix[newRow][newColumn];
    }


    ~Matrix()//деструктор
    {
        if (column > 0)
        {
            for (int i = 0; i < row; i++)
                delete[] matrix[i];
        }

        if (row > 0)
            delete[] matrix;
    }
};



int main()
{
    setlocale(LC_ALL, "rus");
    Matrix<int> M(2, 1);
    Matrix<int> M1(2, 1);
    std::cout << "Вводим первую матрицу: " << '\n';
    std::cin >> M;
    std::cout << "Вводим вторую матрицу: " << '\n';
    std::cin >> M1;
    std::cout << "Копируем вторую матрицу в первую: " << '\n';
    std::cout << (M = M1) << '\n';
    std::cout << "Вывдем первый символ в первой матрице: " << M.getMatrix(0, 0) << '\n';
    std::cout << "Поменяем последний символ в первой матрице. ";
    M.setMatrix(1, 1, 111);
    std::cout << "Снова выведем первую матрицу: " << '\n';
    std::cout << M;
    std::cout << "Увеличим все элементы первой матрицы на 1: " << '\n';
    M++;
    std::cout << M;
    std::cout << "Сложим первую и вторую матрицу: " << '\n' << (M + M1);
    std::cout << "Произведем операцию += " << '\n' << (M += M1);
    std::cout << "Перемножим матрицы: " << '\n' << (M * M1);
    std::cout << "Произведем операцию *= " << '\n' << (M *= M1);
    std::cout << "Вычислим детерминант первой матрицы:  " << M.determ(M) << '\n';
    std::cout << M(0, 0) << std::endl;//номер первого символа в матрице - 0
}

