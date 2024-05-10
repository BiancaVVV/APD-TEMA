#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx;

// Funcția care va fi rulată de fiecare thread pentru a efectua căutarea binară
void binary_search(const std::vector<int>& arr, int target, int left, int right, int& result) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            // Dacă găsim elementul, actualizăm rezultatul și ieșim din thread
            std::lock_guard<std::mutex> guard(mtx);
            result = mid;
            return;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
}

// Funcția principală care inițiază thread-urile și gestionează rezultatul
int parallel_binary_search(const std::vector<int>& arr, int target, int num_threads) {
    int n = arr.size();
    int result = -1;

    // Vectorul de thread-uri
    std::vector<std::thread> threads;

    // Impărțim intervalul de căutare între thread-uri
    int chunk_size = n / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int left = i * chunk_size;
        int right = (i == num_threads - 1) ? (n - 1) : (left + chunk_size - 1);
        threads.emplace_back(binary_search, std::cref(arr), target, left, right, std::ref(result));
    }

    // Așteptăm ca toate thread-urile să se încheie
    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

int main() {
    std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int target = 9;
    int num_threads = 8; // Numărul de thread-uri

    int result = parallel_binary_search(arr, target, num_threads);

    if (result != -1) {
        std::cout << "Elementul " << target << " a fost găsit la poziția " << result << std::endl;
    }
    else {
        std::cout << "Elementul " << target << " nu a fost găsit în vector." << std::endl;
    }

    return 0;
}
