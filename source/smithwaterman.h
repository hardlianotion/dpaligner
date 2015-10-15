#include <vector>
#include <string>


struct ScoreMatrix {
    typedef std::vector<long>::const_iterator iterator;
    
    ScoreMatrix(const std::vector<long>& data, size_t rows, size_t columns)
        : data_(data), rows_(rows), columns_(columns) {}
    
    ScoreMatrix(size_t rows, size_t columns)
        : data_(rows*columns,0), rows_(rows), columns_(columns) {}
    
    ScoreMatrix() = delete;
    
    const long operator()(const size_t row, const size_t col) const {
        return data_.at(row * columns_ + col);
    }
    
   long& operator()(const size_t row, const size_t col) {
        return data_.at(row * columns_ + col);
    }

    const size_t rows() const {
        return rows_;
    }

    const size_t columns() const {
        return columns_;
    }

    const std::vector<long>& data() const {
        return data_;
    }

    const std::pair<iterator, iterator> range() const {
        return std::make_pair(data_.cend() - (columns() ), data_.end());
    }
    
    std::pair<size_t, size_t> find(const iterator ptr) const {
        ptrdiff_t difference = std::distance(data_.cbegin(), ptr);
        
        if(difference < 0) {
            throw std::logic_error("Argument ptr is not consistent with score matrix data.");
        }

        size_t i =  static_cast<size_t>(difference / columns());
        size_t j = difference % columns();

        return std::make_pair(i,j);
    }

private:
    std::vector<long> data_;
    const size_t rows_;
    const size_t columns_;
};

const ScoreMatrix createScoreMatrix(const std::string& lhs, const std::string& rhs); 
long score(const ScoreMatrix& scores);
long score(const char lhs, const char rhs);
long score(const std::string& lhs, const std::string& rhs);
std::string cigarize(const std::string& path); 
std::pair<std::string, std::pair<size_t, size_t>> match(const ScoreMatrix& scores);
std::string match(const std::string& lhs, const std::string& rhs);

