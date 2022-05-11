#include "poly.h"

Poly::Poly() {
    coef_[0] = 0;
};

Poly::Poly(const Poly& poly) {
    coef_ = poly.coef_;
}

Poly::Poly(const std::vector<int64_t>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != 0) {
            coef_[i] = vec[i];
        }
    }
}

Poly::Poly(const std::vector<std::pair<int64_t, int64_t>>& vec) {
    for (auto& i : vec) {
        if (i.second != 0) {
            coef_[i.first] = i.second;
        }
    }
}

int64_t Poly::operator()(const int64_t& numb) const {
    int64_t ans = 0;
    for (auto& i : coef_) {
        ans = ans + i.second * powl(numb, i.first);
    }
    return ans;
}

bool Poly::operator==(const Poly& poly) const {
    if (coef_ == poly.coef_) {
        return true;
    }
    return false;
}
bool Poly::operator!=(const Poly& poly) const {
    return !(*this == poly);
}

Poly Poly::operator-() const {
    Poly new_poly;
    new_poly.coef_ = coef_;
    for (auto& i : coef_) {
        new_poly.coef_.at(i.first) = -i.second;
    }
    return new_poly;
}

Poly Poly::operator+(const Poly& poly) {
    Poly new_poly = *this;
    for (auto& i : poly.coef_) {
        if (new_poly.coef_.contains(i.first)) {
            new_poly.coef_.at(i.first) += i.second;
        } else {
            new_poly.coef_[i.first] = i.second;
        }
        if (new_poly.coef_.at(i.first) == 0 && i.first != 0) {
            new_poly.coef_.erase(i.first);
        }
    }
    return new_poly;
}

Poly Poly::operator-(const Poly& poly) {
    return (*this + -poly);
}

Poly& Poly::operator+=(const Poly& poly) {
    *this = *this + poly;
    return *this;
}

Poly& Poly::operator-=(const Poly& poly) {
    *this = *this - poly;
    return *this;
}

Poly Poly::operator*(const Poly& poly) {
    Poly new_poly;
    for (auto& i : coef_) {
        for (auto& j : poly.coef_) {
            new_poly.coef_[i.first + j.first] += i.second * j.second;
        }
    }
    return new_poly;
}

std::ostream& operator<<(std::ostream& os, const Poly& dt) {
    os << "y = ";
    bool is_first = true;
    for (auto& i : dt.coef_) {
        if (!is_first) {
            os << " + ";
        }
        if (i.first == 0) {
            os << dt.coef_.at(i.first);
        } else {
            os << i.second << "x^" << i.first;
        }
        is_first = false;
    }
    return os;
}
