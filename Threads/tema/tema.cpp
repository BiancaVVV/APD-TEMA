#include <iostream>
#include <thread>
#include <vector>
using namespace std;

#define THREAD_MAX 5
#define SIZE 20

int elements[SIZE] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40 };
int ok = 0;

void ThreadSearch(int start, int end, int key) {
    for (int index = start; index < end; index++) {
        if (elements[index] == key)
        {
            cout << "Element was found at the position  " << index << endl;
            ok = 1;
        }
    }
}

int main() {


    vector<thread> threads;
    int key;
    cout << "Element to find is: ";
    cin >> key;

    //5 threads are created, each calling the ThreadSearch function on a different range of the vector
    for (int i = 0; i < THREAD_MAX; i++) {
        threads.push_back(thread(ThreadSearch, i * (SIZE / 5), (i + 1) * (SIZE / 5), key));
    }

    //t waits for each thread to join
    for (auto& t : threads) {
        t.join();
    }

    if (ok == 0)
        cout << "Not found... :(" << endl;

    return 0;
}