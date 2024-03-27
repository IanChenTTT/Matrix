#ifndef MATRIX_H_
#define MATRIX_H_
class Matrix
{
private:
    double **mat;
    unsigned int col;
    unsigned int row;
    double **createMat(int row, int col)
    {
        double **temp = new double *[row];
        for (int i = 0; i < row; i++)
            temp[i] = new double[col];
        return temp;
    }
    void clear()
    {
        int i;
        for (i = 0; i < row; i++)
            delete mat[i];
        delete[] mat;
        this->col = 0;
        this->row = 0;
    }
    void init(int row, int col)
    {
        this->col = col;
        this->row = row;
        this->mat = createMat(row, col);
    }

public:
    /**
     *  Must have col and row in contructor
     *  this refer to current OBJ
     *  this is a pointer
     */
    Matrix(int row, int col)
    {
        init(row, col);
    }
    Matrix(const Matrix &other)
    {
        init(other.row, other.col);
        for (unsigned int i = 0; i < row; ++i)
        {
            for (unsigned int j = 0; j < col; ++j)
            {
                mat[i][j] = other.mat[i][j];
            }
        }
    }
    /*
     * Transpose this Matrix not modify data,
     * create new Matrix
     */
    Matrix transpose()
    {
        double **temp = createMat(col, row);
        for (int y = 0; y < this->row; y++)
            for (int x = 0; x < this->col; x++)
                std::swap(this->mat[y][x], temp[x][y]);
        Matrix tempMat(this->col, this->row);
        tempMat.mat = temp;
        return tempMat;
    }
    void add(Matrix *&other)
    {
        if (this->row != other->row || this->col != other->col)
            throw std::logic_error("mat was not compatible");
        int y;
        int x;
        for (y = 0; y < this->row; y++)
            for (x = 0; x < this->col; x++)
                this->mat[y][x] += other->mat[y][x];
    }
    void sub(Matrix *&other)
    {
        if (this->row != other->row || this->col != other->col)
            throw std::logic_error("mat was not compatible");
        int y;
        int x;
        for (y = 0; y < this->row; y++)
            for (x = 0; x < this->col; x++)
                this->mat[y][x] -= other->mat[y][x];
    }
    Matrix mulMat(Matrix *&other) // pass by val
    {
        if (this->col != other->row)
            throw std::logic_error("row and col are not matcH" + std::to_string(this->col + other->row));
        Matrix temp(this->row, other->col);
        int y;
        int x;
        int x1;
        /*
         * STEP
         * 1. loop all the element in temp (ans) cols in rows
         * 2. each element =
         *  sum of each element in(this col*other row ele)
         * 3. [M*N]*[N*X]= M*X
         */
        for (y = 0; y < temp.row; y++)
        {
            for (x = 0; x < temp.col; x++)
            {
                for (x1 = 0; x1 < this->col; x1++)
                    temp.mat[y][x] += this->mat[y][x1] * other->mat[x1][x];
            }
        }
        return temp;
    }
    Matrix mulMat(Matrix other) // pass by val;
    {
        if (this->col != other.row)
            throw std::logic_error("row and col are not matcH" + std::to_string(this->col + other.row));
        Matrix temp(this->row, other.col);
        int y;
        int x;
        int x1;
        /*
         * STEP
         * 1. loop all the element in temp (ans) cols in rows
         * 2. each element =
         *  sum of each element in(this col*other row ele)
         * 3. [M*N]*[N*X]= M*X
         */
        for (y = 0; y < temp.row; y++)
        {
            for (x = 0; x < temp.col; x++)
            {
                for (x1 = 0; x1 < this->col; x1++)
                    temp.mat[y][x] += this->mat[y][x1] * other.mat[x1][x];
            }
        }
        return temp;
    }
    void multNum(double val)
    {
        int y;
        int x;
        for (y = 0; y < this->row; y++)
            for (x = 0; x < this->col; x++)
                this->mat[y][x] *= val;
    }
    /*
     * Assume we have two 1 x n vector
     */
    int matDot(Matrix *&other)
    {
        // Dont care if vector is Matrix format
        if (this->row != other->row || this->col != 1 || other->col != 1)
            throw std::logic_error("mat was not compatible");
        Matrix temp = other->transpose();
        int x = this->row;
        int ans = 0;
        while (--x)
            ans += temp.mat[0][x] * this->mat[x][0];
        return ans;
    }
    bool set(int row, int col, double val)
    {
        if ((row < 0) || (row >= this->row) ||
            (col < 0) || (col >= this->col))
        {
            throw std::logic_error("row is:" + std::to_string(row) + "col is: " + std::to_string(col));
            return false;
        }
        this->mat[row][col] = val;
        return true;
    }
    void show()
    {
        int y;
        int x;
        for (y = 0; y < row; y++)
        {
            for (x = 0; x < col; x++)
                std::cout << std::setw(5) << this->mat[y][x];
            std::cout << std::endl;
        }
    }
    ~Matrix()
    {
        clear();
    }
    /** OPERATOR OVERLOADING
     *  CIN >> M
     *  M*M
     *  M=M
     *  M+=M
     */

    Matrix &operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;
        if (row != other.row || col != other.col)
        {
            clear();
            init(other.row, other.col);
        }
        int i;
        int j;
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                this->mat[i][j] = other.mat[i][j];
        return *this;
    }
    Matrix &operator*=(Matrix &other)
    {
        Matrix temp = this->mulMat(other);
        *this = temp;
        return *this;
    }
    void operator*=(double v)
    {
        int i;
        int j;
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                this->mat[i][j] *= v;
    }

    double &operator()(unsigned int row, unsigned int col)
    {
        return this->mat[row][col];
    }
    friend std::istream &operator>>(std::istream &input, Matrix &me)
    {
        int y;
        int x;
        for (y = 0; y < me.row; y++)
            for (x = 0; x < me.col; x++)
                input >> me.mat[y][x];
        return input;
    }
    friend std::ostream &operator<<(std::ostream &output, const Matrix &me)
    {
        int y;
        int x;
        for (y = 0; y < me.row; y++)
        {
            for (x = 0; x < me.col; x++)
                output << std::setw(4) << me.mat[y][x];
            output << std::endl;
        }

        return output;
    }
};
/*
 * MEMBER:
 * -row:int
 * -col:int
 * -Mat:double**
 * FUNC:
 * +add()
 * +sub()
 * +mul()
 * +sew(int row,int col,double val):bool
 * +show():void
 * */
#endif
