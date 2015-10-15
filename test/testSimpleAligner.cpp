#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <smithwaterman.h>

using namespace std;

TEST_CASE("Score matrix has expected properties.") {
    SECTION("Indexation works as expected.") {
        vector<long> implData = {0,1,2,3,4,5,6,7,8,9,10,11};
        ScoreMatrix mx(implData,3,4);
        long datum = 0;
        for(size_t i = 0; i < mx.rows(); ++i) {
            for(size_t j = 0; j < mx.columns(); ++j) {
                CHECK(mx(i,j) == datum);
                ++datum;
            }
        }
        mx(1,2) = 55;
        mx(2,1) = 33;
        const auto& mxData = mx.data();
        CHECK(mxData[9] == 33);
        CHECK(mxData[6] == 55);
    }
    SECTION("Scores are calculated correctly.") {
        const auto scores = createScoreMatrix("TA", "ATAG");

        CHECK(scores.rows() == 3);
        CHECK(scores.columns() == 5);
        CHECK(scores(0, 1) == 0);
        CHECK(scores(0, 3) == 0);
        CHECK(scores(1, 0) == 0);
        CHECK(scores(2, 0) == 0);
        CHECK(scores(1, 1) == 0);
        CHECK(scores(1, 2) == 2);
        CHECK(scores(1, 3) == 1);
        CHECK(scores(1, 4) == 0);
        CHECK(scores(2, 1) == 2);
        CHECK(scores(2, 2) == 1);
        CHECK(scores(2, 3) == 4);
        CHECK(scores(2, 4) == 3);
    }
}

TEST_CASE("Score function properties are correct.") {
    INFO("Score is >= 0, with identity only if there is no possible match between strings.")
    CHECK(score("ATGAC", "") == 0);
    CHECK(score("ATAT", "GCGC") == 0);
    CHECK(score("ATAGAC", "TA") > 0);

    INFO("Score of identical words is greater than comparisons between subsets.");
    CHECK(score("ACTGATTAC", "ACTGATTAC") == 18);
    CHECK(score("ACTTAC", "TGATTAC") < 18);

    INFO("Score function is symmetric in its arguments.");
    CHECK(score("TACG", "ATTG") == score("ATTG", "TACG"));

    INFO("Score is derived from the score matrix.");
    const ScoreMatrix scores = createScoreMatrix("TAG", "CAGATAG"); 
    CHECK(score("TAG", "CAGATAG") == score(scores));
}

TEST_CASE("Cigarize correctly summarizes match route string.") {
    string route = "====DDIIII";
    string cigar = cigarize(route);
    INFO("cigarize reverses the route string.");
    CHECK(cigar == "4=2D4I");
}    

TEST_CASE("Match picks out the matched substring when passed a ScoreMatrix.") {
    SECTION("Perfect match.") {
        const auto scores = createScoreMatrix("TTG", "ATTGAC");
        auto result = match(scores);
        CHECK(result.second.first == 1lu);
        CHECK(result.second.second == 4lu);
    }

    SECTION("Deletion match.") {
        const auto scores = createScoreMatrix("TTG", "ATTAGAC");
        auto result = match(scores);
        CHECK(result.second.first == 1lu);
        CHECK(result.second.second == 5lu);
    }

    SECTION("Insertion match.") {
        const auto scores = createScoreMatrix("TTG", "ATGAC");
        auto result = match(scores);
        CHECK(result.second.first == 1lu);
        CHECK(result.second.second == 3lu);
    }

}

TEST_CASE("Match function gives correct cigar string as solution.") {
    SECTION("Perfect match.") {
        string result = match("ATTGAC", "TTG");
        CHECK(result == "3=");
    }

    SECTION("Deletion match.") {
        string result = match("ATTAGAC", "TTG");
        CHECK(result == "2=1D1=");
    }

    SECTION("Insertion match.") {
        string result = match("ATGAC", "TTG");
        CHECK(result == "1=1I1=");
    }

}


