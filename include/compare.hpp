#include <algorithm>

template<typename T>
void bubbleSort(T* data, int size) {
    int preSize = size - 1;
    for (int i = 0; i < preSize; ++i) {
        for (int j = i; j < size; ++j) {
            if (data[i] > data[j]) {
                std::swap(data[i], data[j]);
            }
        }
    }
}

template<typename T>
void quickSort(T* data, int size) {

}
