#ifndef MATRIX_H_7QJYTZ6X
#define MATRIX_H_7QJYTZ6X

typedef std::pair<std::size_t, std::size_t> Coord;

template <typename T>
class Matrix : public std::vector<std::vector<T>>{
    public:
        using std::vector<std::vector<T>>::vector;
        T &at(std::size_t x, std::size_t y) { return (*this)[y][x]; }
        T &at(const Coord &c) { return at(c.first, c.second); }
};


#endif /* end of include guard: MATRIX_H_7QJYTZ6X */