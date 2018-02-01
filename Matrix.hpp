#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <vector>
#include <memory>
#include <utility>

template<typename T>
class Matrix
{
public:
    typedef typename std::vector<T>::size_type size_type;

    Matrix();
    Matrix(size_type rows, size_type cols);
    Matrix(size_type rows, size_type cols, const T& val);
    Matrix(std::initializer_list<std::initializer_list<T>> il);

    size_type size() const { return m_data->size(); };
    std::pair<size_type, size_type> dimension() const { return std::pair<size_type, size_type>(m_rows, m_cols);}

    T& operator[](size_type id) const;
    T& operator()(size_type row, size_type col) const;

private:
    std::shared_ptr<std::vector<T>> m_data;
    size_type m_rows = 0;
    size_type m_cols = 0;

    ///Friend(s)
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
    {
        // (Provisoire)
        os << "Global size : " << matrix.size() << '\n'
           << "Total Rows  : " << matrix.m_rows << '\n'
           << "Total Cols  : " << matrix.m_cols << '\n'
           << '\n';

        for(size_type i=0; i<matrix.m_rows; ++i){
            for(size_type j=0; j<matrix.m_cols; ++j){
                os << const_cast<Matrix<T>&>(matrix)(i, j) << ' ';
            }
            os << '\n';
        }

        os << "--------------------------------";

        return os;
    }
};

//////////////////////////////////////////////////////////////////
/////// CONSTRUCTOR(S)
template<typename T>
Matrix<T>::Matrix() :
    m_data{std::make_shared<std::vector<T>>(std::vector<T>())}
{

}
template<typename T>
Matrix<T>::Matrix(size_type rows, size_type cols) :
    m_data{std::make_shared<std::vector<T>>(std::vector<T>(rows*cols))},
    m_rows{rows}, m_cols{cols}
{

}
template<typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const T& val) :
    m_data{std::make_shared<std::vector<T>>(std::vector<T>(rows*cols, val))},
    m_rows{rows}, m_cols{cols}
{

}
template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> il) :
    Matrix(il.size(), (il.size() > 0 ? il.begin()->size() : 0))
{
    // TO DO : Gérer le cas où il y aurait des lignes n'ayant pas le même nombre de colonnes
    //         assert ? exception ?

    std::size_t i{0};
    for(const auto& line : il){
        std::size_t j{0};
        for(const auto& val : line){
            (*m_data)[(i*m_cols)+j] = val;
            ++j;
        }
        ++i;
    }
}
//////////////////////////////////////////////////////////////////
/////// FUNCTION(S)

//////////////////////////////////////////////////////////////////
/////// OPERATOR(S)
template<typename T>
T& Matrix<T>::operator[](size_type id) const
{
    return (*m_data)[id];
}

template<typename T>
T& Matrix<T>::operator()(size_type row, size_type col) const
{
    return (*m_data)[(row*m_cols)+col];
}

#endif // MATRIX_HPP_INCLUDED
