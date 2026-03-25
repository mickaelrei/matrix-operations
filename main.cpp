#include <iostream>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

template <size_t N, typename T>
Matrix<2*N, 1, T> calculateVelocityChanges(Matrix<2*N, 1, T> v, Matrix<N, 1, T> m, Matrix<2*N, 1, T> n, float e = 1.0f) {
    Matrix<2*N, 2*N, T> invM;
    Matrix<2*N, N, T> Z;

    // Montar matrizes M^(-1) e Z
    size_t a = 0;
    size_t b = 1;
    for (size_t i = 0; i < N; i++) {
        float mInv = 1.0f / m.data[i][0];
        invM.data[2*i][2*i] = mInv;
        invM.data[2*i + 1][2*i + 1] = mInv;

        Z.data[2*a][i] = -n.data[2*i][0];
        Z.data[2*a + 1][i] = -n.data[2*i + 1][0];
        Z.data[2*b][i] = n.data[2*i][0];
        Z.data[2*b + 1][i] = n.data[2*i + 1][0];

        b += 1;
        if (b == N - 1) {
            a += 1;
            b = a + 1;
        }
    }

    auto uImp = Z.transpose() * v;

    auto A = Z.transpose() * invM * Z;
    auto J = solveGaussJordan(A, -(1.0f + e) * uImp);

    return invM * Z * J;
}

template <size_t N>
Matrix<2*N, 1, float> velocityHelper(std::array<glm::vec2, N> p, std::array<glm::vec2, N> v, std::array<float, N> m, float e = 1.0f) {
    Matrix<2*N, 1, float> vm;
    Matrix<N, 1, float> mm;
    Matrix<2*N, 1, float> n;

    // Monta matrizes de velocidade, massa e normais a partir dos arrays
    size_t a = 0;
    size_t b = 1;
    for (size_t i = 0; i < N; i++) {
        vm.data[2*i][0] = v[i].x;
        vm.data[2*i + 1][0] = v[i].y;

        mm.data[i][0] = m[i];

        auto norm = glm::normalize(p[b] - p[a]);
        n.data[2*i][0] = norm.x;
        n.data[2*i + 1][0] = norm.y;

        b += 1;
        if (b == N - 1) {
            a += 1;
            b = a + 1;
        }
    }

    return calculateVelocityChanges(vm, mm, n, e);
}

int main(int argc, char **argv) {
    float d = 5.0f;

    // Caso especifico com colisao simultanea de 3 bolas

    // Massas
    float m0 = 13;
    float m1 = 11;
    float m2 = 7;

    // Posicoes
    glm::vec2 p0{0.0f, 0.0f};
    glm::vec2 p1{d, 0.0f};
    glm::vec2 p2{d*std::cos(M_PIf / 3), d*std::sin(M_PIf / 3)};

    // Angulo das velocidades
    auto av0 = M_PIf / 4.0f;
    auto av1 = 3.0f * M_PIf / 4.0f;
    auto av2 = 3.0f * M_PIf / 2.0f;

    // Velocidades
    auto v0 = 5.0f * glm::vec2{std::cos(av0), std::sin(av0)};
    auto v1 = 3.0f * glm::vec2{std::cos(av1), std::sin(av1)};
    auto v2 = 2.0f * glm::vec2{std::cos(av2), std::sin(av2)};

    // Arrays de posicao, velocidade e massa
    std::array<glm::vec2, 3> ps{p0, p1, p2};
    std::array<glm::vec2, 3> vs{v0, v1, v2};
    std::array<float, 3> ms{m0, m1, m2};

    auto dv = velocityHelper(ps, vs, ms);

    // Calcula novas velocidades com o resultado do sistema linear
    auto nv0 = v0 + glm::vec2{dv.data[0][0], dv.data[1][0]};
    auto nv1 = v1 + glm::vec2{dv.data[2][0], dv.data[3][0]};
    auto nv2 = v2 + glm::vec2{dv.data[4][0], dv.data[5][0]};

    // Verifica conservacao de energia do sistema
    float k = 0.5f * (m0 * glm::length2(v0) + m1 * glm::length2(v1) + m2 * glm::length2(v2));
    float nk = 0.5f * (m0 * glm::length2(nv0) + m1 * glm::length2(nv1) + m2 * glm::length2(nv2));

    printf("k = %.5f | nk = %.5f\n", k, nk);
}