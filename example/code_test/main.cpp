#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>

struct Vec3 {
    std::array<double, 3> v{};

    Vec3() = default;

    Vec3(double x, double y, double z) : v{x, y, z} {
    }

    double operator[](int i) const {
        return v[i];
    }

    double& operator[](int i) {
        return v[i];
    }

    Vec3 operator+(const Vec3& o) const {
        return {v[0] + o[0], v[1] + o[1], v[2] + o[2]};
    }

    Vec3 operator-(const Vec3& o) const {
        return {v[0] - o[0], v[1] - o[1], v[2] - o[2]};
    }

    Vec3 operator*(double t) const {
        return {v[0] * t, v[1] * t, v[2] * t};
    }
};

inline double dot(const Vec3& a, const Vec3& b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline double length(const Vec3& a) {
    return std::sqrt(dot(a, a));
}

inline double clamp01(double x) {
    return std::clamp(x, 0.0, 1.0);
}

struct Bridge {
    double distance;
    double param_p;
    double param_q;
    Vec3   point_on_p;
    Vec3   point_on_q;
};

Bridge minimum(const Vec3& p0, const Vec3& p1, const Vec3& q0, const Vec3& q1) {
    constexpr double EPSILON = 1e-10;

    const Vec3 d1      = p1 - p0;
    const Vec3 d2      = q1 - q0;
    const Vec3 gap_vec = p0 - q0;

    const double p_sqr     = dot(d1, d1);
    const double q_sqr     = dot(d2, d2);
    const double q_dir_gap = dot(d2, gap_vec);

    double param_p = 0.0;
    double param_q = 0.0;

    if (p_sqr <= EPSILON && q_sqr <= EPSILON) {
        param_p = 0.0;
        param_q = 0.0;
    }
    else if (p_sqr <= EPSILON) {
        param_p = 0.0;
        param_q = clamp01(q_dir_gap / q_sqr);
    }
    else {
        const double p_dir_gap = dot(d1, gap_vec);

        if (q_sqr <= EPSILON) {
            param_q = 0.0;
            param_p = clamp01(-p_dir_gap / p_sqr);
        }

        else {
            const double align = dot(d1, d2);
            const double d     = p_sqr * q_sqr - align * align;

            if (EPSILON < d) {
                param_p = clamp01((align * q_dir_gap - p_dir_gap * q_sqr) / d);
            }
            else {
                param_p = 0.0;
            }

            param_q = (align * param_p + q_dir_gap) / q_sqr;

            if (param_q < 0.0) {
                param_q = 0.0;
                param_p = clamp01(-p_dir_gap / p_sqr);
            }
            else if (1.0 < param_q) {
                param_q = 1.0;
                param_p = clamp01((align - p_dir_gap) / p_sqr);
            }
        }
    }

    const Vec3 point_on_p = p0 + d1 * param_p;
    const Vec3 point_on_q = q0 + d2 * param_q;
    const Vec3 bridge     = point_on_p - point_on_q;

    return {length(bridge), param_p, param_q, point_on_p, point_on_q};
}

int main() {
    auto run = [](const std::string& name, Vec3 p0, Vec3 p1, Vec3 q0, Vec3 q1) {
        Bridge bridge = minimum(p0, p1, q0, q1);
        std::cout << name << "\n"
                  << "  distance   : " << static_cast<int>(std::ceil(bridge.distance)) << "\n"
                  << "  s          : " << bridge.param_p << "\n"
                  << "  t          : " << bridge.param_q << "\n"
                  << "  Point On P : (" << bridge.point_on_p[0] << ", " << bridge.point_on_p[1] << ", " << bridge.point_on_p[2] << ")\n"
                  << "  Point On Q : (" << bridge.point_on_q[0] << ", " << bridge.point_on_q[1] << ", " << bridge.point_on_q[2] << ")\n\n";
    };

    run("Test 1", {350, 150, 350}, {0, 0, 0}, {10, -6, 30}, {56, 21, 120});             // distance: 20
    run("Test 2", {700, -940, -854}, {-390, 619, 340}, {3, 970, -17}, {111, 222, 333}); // distance: 310
    run("Test 3", {0, 0, 0}, {0, 10000, 10000}, {0, 5000, 5000}, {5000, 5000, 5000});   // distance: 0
}