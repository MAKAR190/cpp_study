#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>

using Point = std::vector<double>;
using namespace std;

Point generate_point(size_t dimensions, std::mt19937 &gen, std::normal_distribution<double> &dist) {
    Point point(dimensions);
    generate(point.begin(), point.end(), [&]() { return dist(gen); });
    return point;
}

bool is_dominated(const Point &p1, const Point &p2) {
    return inner_product(p1.begin(), p1.end(), p2.begin(), true, logical_and<>(), less_equal<>());
}

double euclidean_distance(const Point &p1, const Point &p2) {
    return sqrt(inner_product(p1.begin(), p1.end(), p2.begin(), 0.0, plus<>(), [](double a, double b) {
        return (a - b) * (a - b);
    }));
}

void remove_dominated_points(vector<Point> &points) {
    vector<Point> non_dominated_points;
    for (const auto &p1 : points) {
        bool is_dominated_point = false;
        for (const auto &p2 : points) {
            if (p1 != p2 && is_dominated(p1, p2)) {
                is_dominated_point = true;
                break;
            }
        }
        if (!is_dominated_point) {
            non_dominated_points.push_back(p1);
        }
    }
    points = non_dominated_points;
}

vector<double> compute_densities(const vector<Point> &points) {
    size_t k = points.size();
    if (k == 0) return {};

    size_t sqrt_k = static_cast<size_t>(sqrt(k));
    vector<double> densities;

    transform(points.begin(), points.end(), back_inserter(densities), [&](const Point &p1) {
        vector<double> distances;
        transform(points.begin(), points.end(), back_inserter(distances), [&](const Point &p2) {
            return p1 != p2 ? euclidean_distance(p1, p2) : numeric_limits<double>::max();
        });
        nth_element(distances.begin(), distances.begin() + min(sqrt_k, distances.size() - 1), distances.end());
        return distances[sqrt_k];
    });

    return densities;
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(5.0, sqrt(10.0));

    size_t n = 5;
    size_t num_points = 150;
    vector<Point> P1(num_points);
    generate(P1.begin(), P1.end(), [&]() { return generate_point(n, gen, dist); });

    vector<Point> A;
    copy_if(P1.begin(), P1.end(), back_inserter(A), [&](const Point &p1) {
        return none_of(P1.begin(), P1.end(), [&](const Point &p2) {
            return p1 != p2 && is_dominated(p1, p2);
        });
    });

    vector<Point> P2(num_points);
    generate(P2.begin(), P2.end(), [&]() { return generate_point(n, gen, dist); });

    vector<Point> B;
    copy_if(P2.begin(), P2.end(), back_inserter(B), [&](const Point &p1) {
        return none_of(P2.begin(), P2.end(), [&](const Point &p2) {
            return p1 != p2 && is_dominated(p1, p2);
        });
    });

    A.insert(A.end(), B.begin(), B.end());

    remove_dominated_points(A);

    vector<double> densities = compute_densities(A);

    for (size_t i = 0; i < A.size(); ++i) {
        cout << "Point: ";
        copy(A[i].begin(), A[i].end(), ostream_iterator<double>(cout, " "));
        cout << " | Gestosc: " << densities[i] << endl;
    }

    return 0;
}
