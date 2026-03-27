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
    // auto J = solveGaussJordan(A, -(1.0f + e) * uImp);
    auto J = solveGaussSeidel(A, -(1.0f + e) * uImp);

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

    // Caso especifico com colisao simultanea de 4 bolas

    // Massas
    float m0 = 13;
    float m1 = 11;
    float m2 = 7;
    float m3 = 17;

    // Posicoes
    glm::vec2 p0{d, d};
    glm::vec2 p1{-d, d};
    glm::vec2 p2{-d, -d};
    glm::vec2 p3{d, -d};

    // Angulo das velocidades
    auto av0 = 5.0f * M_PIf / 4.0f;
    auto av1 = 7.0f * M_PIf / 4.0f;
    auto av2 = 1.0f * M_PIf / 4.0f;
    auto av3 = 3.0f * M_PIf / 4.0f;

    // Velocidades
    auto v0 = 5.0f * glm::vec2{std::cos(av0), std::sin(av0)};
    auto v1 = 3.0f * glm::vec2{std::cos(av1), std::sin(av1)};
    auto v2 = 2.0f * glm::vec2{std::cos(av2), std::sin(av2)};
    auto v3 = 7.0f * glm::vec2{std::cos(av3), std::sin(av3)};

    // Arrays de posicao, velocidade e massa
    std::array<glm::vec2, 4> ps{p0, p1, p2, p3};
    std::array<glm::vec2, 4> vs{v0, v1, v2, v3};
    std::array<float, 4> ms{m0, m1, m2, m3};

    // Chama helper pra transformar arrays em matrizes de input da resolução
    auto dv = velocityHelper(ps, vs, ms);

    // Calcula novas velocidades com o resultado do sistema linear
    std::array<glm::vec2, 4> nvs;
    for (size_t i = 0; i < 4; i++) {
        nvs[i] = vs[i] + glm::vec2{dv.data[2*i][0], dv.data[2*i+1][0]};
    }

    // Verifica conservacao de energia do sistema
    float k = 0.0f;
    float nk = 0.0f;
    for (size_t i = 0; i < 4; i++) {
        k += 0.5f * ms[i] * glm::length2(vs[i]);
        nk += 0.5f * ms[i] * glm::length2(nvs[i]);
    }

    printf("k = %.5f | nk = %.5f\n", k, nk);
}