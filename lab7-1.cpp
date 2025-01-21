#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>
#include <functional>

using Point = std::vector<double>;
using namespace std;

std::mt19937 rng(std::random_device{}());
std::normal_distribution<double> normal_dist(5.0, 10.0);

double random_normal() {
    return normal_dist(rng);
}

Point generate_point(int n) {
    Point point(n);
    generate(point.begin(), point.end(), random_normal);
    return point;
}

bool is_dominated(const Point &p1, const Point &p2) {
    return inner_product(p1.begin(), p1.end(), p2.begin(), true, logical_and<>(), less_equal<>());
}

double euclidean_distance(const Point &p1, const Point &p2) {
    return sqrt(std::inner_product(p1.begin(), p1.end(), p2.begin(), 0.0, plus<>(), [](double a, double b) {
        return (a - b) * (a - b);
    }));
}

int main() {
    int n, num_points;
    cout << "Podaj wymiar przestrzeni (n): ";
    cin >> n;
    cout << "Podaj liczbe punktow (> 100): ";
    cin >> num_points;

    if (num_points <= 100) {
        cerr << "Liczba punktow musi byc wieksza niz 100!" << endl;
        return 1;
    }

    vector<Point> P(num_points);
    generate(P.begin(), P.end(), [&]() { return generate_point(n); });

    vector<Point> A;
    copy_if(P.begin(), P.end(), back_inserter(A), [&](const Point &p1) {
        return none_of(P.begin(), P.end(), [&](const Point &p2) {
            return p1 != p2 && is_dominated(p1, p2);
        });
    });

    vector<Point> B = A;

    vector<double> densities(A.size());
    transform(A.begin(), A.end(), densities.begin(), [&](const Point &p1) {
        vector<double> distances;
        transform(B.begin(), B.end(), back_inserter(distances), [&](const Point &p2) {
            return p1 == p2 ? numeric_limits<double>::max() : euclidean_distance(p1, p2);
        });
        sort(distances.begin(), distances.end());
        size_t k_sqrt = sqrt(A.size());
        return distances[k_sqrt - 1];
    });

    for_each(A.begin(), A.end(), [&](const Point &point) {
        copy(point.begin(), point.end(), ostream_iterator<double>(cout, " "));
        cout << endl;
    });

    cout << "Wspolczynniki gestosci:" << endl;
    copy(densities.begin(), densities.end(), ostream_iterator<double>(cout, " "));
    cout << endl;

    return 0;
}
