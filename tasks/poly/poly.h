#pragma once
#include <map>
#include <vector>
#include <iostream>
#include <math.h>

class Poly {
public:
    Poly();
    Poly(const Poly& poly);
    Poly(const std::vector<int64_t>& vec);
    Poly(const std::vector<std::pair<int64_t, int64_t>>& vec);
    int64_t operator()(const int64_t& numb) const;
    bool operator==(const Poly& poly) const;
    bool operator!=(const Poly& poly) const;
    Poly operator-() const;
    Poly operator+(const Poly& poly);
    Poly operator-(const Poly& poly);
    Poly& operator+=(const Poly& poly);
    Poly& operator-=(const Poly& poly);
    Poly operator*(const Poly& poly);
    friend std::ostream& operator<<(std::ostream& os, const Poly& dt);

private:
    std::map<int64_t, int64_t, std::greater<int64_t>> coef_;
};
