#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BacktrackingLab {
public:
    // 1. Generar todos los subconjuntos
    static void subconjuntos(size_t i, const std::string& alph, std::vector<bool>& chosen) {
        if (i == alph.size()) {
            for (size_t k = 0; k < alph.size(); ++k)
                if (chosen[k]) std::cout << alph[k];
            std::cout << "\n";
            return;
        }
        chosen[i] = false; subconjuntos(i + 1, alph, chosen); // Opción 1: No incluir
        chosen[i] = true;  subconjuntos(i + 1, alph, chosen); // Opción 2: Incluir
    }

    // 2. Generar Permutaciones
    static void permutaciones(int n, std::vector<int>& p, std::vector<bool>& used) {
        if (p.size() == static_cast<size_t>(n)) {
            for (int x : p) std::cout << x << " ";
            std::cout << "\n";
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                used[i] = true;  p.push_back(i + 1); // HACER
                permutaciones(n, p, used);           // EXPLORAR
                p.pop_back();    used[i] = false;    // DESHACER
            }
        }
    }

    // 3. Generar Combinaciones (k de n)
    static void combinaciones(int n, int k, int start, std::vector<int>& c) {
        if (c.size() == static_cast<size_t>(k)) {
            for (int x : c) std::cout << x << " ";
            std::cout << "\n";
            return;
        }
        // Poda: si no quedan suficientes elementos disponibles, se corta la rama
        for (int i = start; i < n; ++i) {
            if (n - i < k - static_cast<int>(c.size())) break; 
            c.push_back(i + 1);
            combinaciones(n, k, i + 1, c);
            c.pop_back();
        }
    }

    // 4. Problema de N-Reinas: contarReinas(fila)
    struct NQueensSolver {
        int n;
        std::vector<bool> cols, diag1, diag2; // diag1: f - c + n - 1, diag2: f + c

        NQueensSolver(int size) : n(size), cols(size, false), diag1(2 * size - 1, false), diag2(2 * size - 1, false) {}

        int contarReinas(int f) {
            if (f == n) return 1; // Solución encontrada
            int total = 0;
            for (int c = 0; c < n; ++c) {
                if (!cols[c] && !diag1[f - c + n - 1] && !diag2[f + c]) {
                    cols[c] = diag1[f - c + n - 1] = diag2[f + c] = true; // HACER
                    total += contarReinas(f + 1);                         // EXPLORAR
                    cols[c] = diag1[f - c + n - 1] = diag2[f + c] = false;// DESHACER
                }
            }
            return total;
        }
    };

    // 5. Suma de Subconjuntos con Poda
    static void sumaSubconjuntos(const std::vector<int>& A, int N, size_t idx, int sumaActual, std::vector<int>& actual) {
        if (sumaActual == N) {
            std::cout << "{ ";
            for (int x : actual) std::cout << x << " ";
            std::cout << "}\n";
            return;
        }
        for (size_t i = idx; i < A.size(); ++i) {
            // PODA: si al agregar A[i] superamos N, como A está ordenado, los siguientes también fallarán
            if (sumaActual + A[i] > N) break;

            actual.push_back(A[i]);
            sumaSubconjuntos(A, N, i + 1, sumaActual + A[i], actual);
            actual.pop_back();
        }
    }
};

