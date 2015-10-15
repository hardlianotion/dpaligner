#include <string>
#include <smithwaterman.h>

using namespace std;

const ScoreMatrix createScoreMatrix(const string& lhs, const string& rhs) {
    if(lhs.size() > rhs.size()) {
        throw runtime_error("At the moment, it is an error for lhs to be larger than rhs.");
    }
    
    ScoreMatrix result(lhs.size() + 1, rhs.size() + 1);     
    for(size_t i = 1; i < result.rows(); ++i) {
        for(size_t j = 1; j < result.columns(); ++j) {
            result(i, j) = max({
                             0l,
                             score(lhs[i-1], rhs[j-1]) + result(i - 1, j - 1),
                             result(i - 1, j) - 1, 
                             result(i, j - 1) - 1}); 
        }
    }
    return result;
}

long score(const char lhs, const char rhs) {
    return lhs == rhs ? 2 : -1;
}

long score(const ScoreMatrix& scores) {
    const auto ends = scores.range();
    return *max_element(ends.first, ends.second);
}

long score(const string& lhs, const string& rhs){
    string localLhs = lhs, localRhs = rhs;
    if (lhs.size() > rhs.size()){
        localLhs = rhs;
        localRhs = lhs;
    }
    const auto scores = createScoreMatrix(localLhs, localRhs);
    return score(scores);
}

pair<string, pair<size_t, size_t>> match(const ScoreMatrix& scores) {
    const auto ends = scores.range();
    const auto pathEnd = scores.find(max_element(ends.first, ends.second));
    
    size_t i = pathEnd.first;
    size_t j = pathEnd.second;
    string result;
    while(j > 0 && i > 0 && scores(i,j) > 0) {
        size_t maxElt = max({scores(i - 1,j - 1), scores(i - 1, j), scores(i, j - 1)});
        if(maxElt == scores(i - 1,j - 1)) {
            if (maxElt < scores(i, j)) {
                result.insert(0, 1, '=');
            } else {
                result.insert(0, 1, 'X');
            }
            --i; --j;
        } else if (maxElt == scores(i - 1,j)) {
            result.insert(0, 1, 'I');
            --i;
        } else {
            result.insert(0, 1, 'D');
            --j;
        }
    }
    return make_pair(result, make_pair(j,  pathEnd.second));
}

string cigarize(const string& path) {
    string result;
    size_t collector = 1;
    char previous = path[0];
    for(const auto letter: path.substr(1)) {
        if(letter != previous) {
            result += to_string(collector);
            result.push_back(previous);
            collector = 1;
        } else {
            ++collector;
        }
        previous = letter;
    }
    
    result += to_string(collector);
    result.push_back(previous);
    return result;
}

string match(const string& lhs, const string& rhs) {
    ScoreMatrix scores = lhs.size() > rhs.size() ? 
                            createScoreMatrix(rhs, lhs): createScoreMatrix(lhs, rhs); 
    const auto result = match(scores);
    return cigarize(result.first);
}

