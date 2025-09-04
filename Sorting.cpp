
#include <iostream>
#include <cmath>
#include <chrono>
#include <cassert>
using namespace std;

template <typename T>
class my_vector;

template <typename T>
class SortingSystem
{
private:
    T *data;
    int size;
    void countSort(int e); // Radix Support
    void bucketSort(int);  // (9) Bucket Sort for int
    void quickSort(int low, int high, my_vector<T> arr);
    void displayData(int arr[]); // For count sort
    void displayData(int pivot); // For pivot
public:
    SortingSystem(int n); // Constructor
    ~SortingSystem();     // Destructor

    void insertionSort();                // (1) Insertion Sort
    void selectionSort();                // (2) Selection Sort
    void bubbleSort();                   // (3) Bubble Sort
    void shellSort();                    // (4) Shell Sort
    void mergeSort(int left, int right); // (5) Merge Sort
    void quickSort(int left, int right); // (6) Quick Sort
    void countSort();                    // (7) Count Sort
    void radixSort();                    // (8) Radix Sort
    void bucketSort();                   // (9) Bucket Sort

    void merge(int left, int mid, int right); // Merge Support
    int partition(int low, int high);         // Quick Support

    void displayData();
    void measureSortTime(void (SortingSystem::*sortFunc)());

    void showMenuInt();
    void showMenu();
};

template <typename T>
class my_vector
{
private:
    T *arr;
    int capacity;
    int size; // Renamed to lowercase 's' for consistency
    T *begin;
    T *end;

public:
    my_vector()
    {
        arr = new T[1];
        size = 0;
        capacity = 1;
        begin = arr;
        end = arr;
    }

    my_vector(int initSize)
    {
        assert(initSize > 0); // Correct use of assert
        initSize *= 2;
        arr = new T[initSize];
        size = initSize / 2;
        capacity = initSize;
        begin = arr;
        end = arr + size;
    }

    my_vector(int initSize, T value)
    {
        assert(initSize > 0); // Correct use of assert
        initSize *= 2;
        arr = new T[initSize];
        size = initSize / 2;
        capacity = initSize;
        begin = arr;
        end = arr + size;
        for (int i = 0; i < size; i++)
        {
            arr[i] = value; // Initialize with the given value
        }
    }

    void push_back(T value)
    {
        if (size == 0)
        {
            begin = arr;
            end = arr + 1;
        }
        if (size == capacity)
        {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = arr[i];
            }
            temp[size] = value;
            delete[] arr;
            arr = temp;
            temp = nullptr;
            size++;
        }
        else
        {
            arr[size] = value;
            size++;
        }
        end = arr + size;
    }

    void pop_back()
    {
        assert(size > 0); // Correct use of assert
        size--;
        if (size == 0)
        {
            begin = end = arr;
        }
        else
        {
            end = arr + size;
        }
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    T &operator[](int index)
    {
        assert(index >= 0 && index < size); // Correct use of assert
        return arr[index];
    }

    int my_size() const
    {
        return size;
    }

    //    ~my_vector() {
    //        delete[] data;
    //    }
};

// ------------------------------------------------------
// -----------------Implementation------------------------
// ------------------------------------------------------

// Constructor
template <typename T>
SortingSystem<T>::SortingSystem(int n)
{
    size = n;
    data = new T[size];
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter Data " << i + 1 << " :";
        cin >> data[i];
    }
}

// Destructor
template <typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] data;
}

// Show Data
template <typename T>
void SortingSystem<T>::displayData()
{
    for (int i = 0; i < size; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

// Show Data (quick sort)
template <typename T>
void SortingSystem<T>::displayData(int pivot)
{
    for (int i = 0; i < size; ++i)
    {
        if (i == pivot)
        {
            cout << "[" << data[i] << "] ";
        }
        else
        {
            cout << data[i] << " ";
        }
    }
    cout << endl;
}

// For count sort
template <>
void SortingSystem<int>::displayData(int arr[])
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// (1) Insertion Sort
template <typename T>
void SortingSystem<T>::insertionSort()
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        int temp = i - 1;
        while (temp >= 0 && data[i] < data[temp])
        {
            swap(data[temp], data[i]);
            temp--;
            i--;
        }
        cout << "iteration " << ++count << " :";
        this->displayData();
    }
}

// (2) Selection Sort
template <typename T>
void SortingSystem<T>::selectionSort()
{
    for (int i = 0, j, index; i < size - 1; ++i)
    {
        for (j = i + 1, index = i; j < size; ++j)
        {
            if (data[index] > data[j])
            {
                index = j;
            }
        }
        swap(data[index], data[i]);
        cout << "iteration " << i + 1 << " :";
        this->displayData();
    }
}

// (3) Bubble Sort
template <typename T>
void SortingSystem<T>::bubbleSort()
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (data[i] < data[j])
            {
                swap(data[i], data[j]);
            }
        }
        cout << "iteration " << i + 1 << " :";
        this->displayData();
    }
}

// (4) Shell Sort
template <typename T>
void SortingSystem<T>::shellSort()
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap, j; i < size; ++i)
        {
            T temp = data[i];
            for (j = i; j >= gap and data[j - gap] > temp; j -= gap)
            {
                data[j] = data[j - gap];
            }
            data[j] = temp;
            cout << "iteration " << i + 1 << " :";
            this->displayData();
        }
    }
}

// (5) Merge Sort
// Merge Function
template <typename T>
void SortingSystem<T>::merge(int left, int mid, int right)
{
    int size1, size2;
    size1 = mid - left + 1;
    size2 = right - mid;
    T *arr1 = new T[size1];
    T *arr2 = new T[size2];
    for (int i = 0; i < size1; ++i)
    {
        arr1[i] = data[left + i];
    }

    for (int j = 0; j < size2; ++j)
    {
        arr2[j] = data[mid + 1 + j];
    }
    int i, j, k;
    i = left;
    j = k = 0;
    while (j < size1 and k < size2)
    {
        if (arr1[j] < arr2[k])
        {
            data[i++] = arr1[j];
            j++;
        }
        else
        {
            data[i++] = arr2[k];
            k++;
        }
    }
    while (j < size1)
    {
        data[i++] = arr1[j++];
    }
    while (k < size2)
    {
        data[i++] = arr2[k++];
    }
    delete[] arr1;
    delete[] arr2;
}

template <typename T>
void SortingSystem<T>::mergeSort(int left, int right)
{
    static int count = 0;
    if (left >= right)
    {
        return;
    }
    else
    {
        int med = (left + right) / 2;
        mergeSort(left, med);
        mergeSort(med + 1, right);
        merge(left, med, right);
        cout << "iteration " << ++count << " :";
        this->displayData();
    }
}
// (6) Quick Sort
// Partition Function
template <typename T>
int SortingSystem<T>::partition(int left, int right)
{
    int pivot = left;
    int j = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (data[pivot] > data[i])
        {
            j++;
            swap(data[i], data[j]);
        }
    }
    swap(data[left], data[j]);
    return j;
}
template <typename T>
void SortingSystem<T>::quickSort(int left, int right)
{
    static int count = 0;
    if (right <= left)
    {
        return;
    }
    int j = partition(left, right);
    quickSort(left, j - 1);
    quickSort(j + 1, right);
    cout << "iteration " << ++count << " :";
    this->displayData(j);
}

// (7) Count Sort
template <>
void SortingSystem<int>::countSort()
{
    int counter = 0;
    int maxElement = data[0];
    for (int i = 1; i < size; ++i)
    {
        if (data[i] > maxElement)
        {
            maxElement = data[i];
        }
    }

    // Counting Array
    int *count = new int[maxElement + 1]();
    for (int i = 0; i < size; ++i)
    {
        count[data[i]]++;
    }
    for (int i = 1; i <= maxElement; ++i)
    {
        count[i] += count[i - 1];
    }

    // Output Array
    int *outData = new int[size];
    for (int i = size - 1; i >= 0; --i)
    {
        outData[--count[data[i]]] = data[i];
        cout << "iteration " << ++counter << " :";
        this->displayData(outData);
    }
    delete[] count;
    delete[] outData;
}

// [8] Radix Sort
// Count function for radix
template <>
void SortingSystem<int>::countSort(int exp)
{
    my_vector<int> prefix(10, 0);
    my_vector<int> sorted(size);
    for (int i = 0; i < size; i++)
    {
        prefix[(data[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++)
    {
        prefix[i] += prefix[i - 1];
    }
    for (int i = size - 1; i >= 0; i--)
    {
        int digit = (data[i] / exp) % 10;
        sorted[prefix[digit] - 1] = data[i];
        prefix[digit]--;
    }
    for (int i = 0; i < size; i++)
    {
        data[i] = sorted[i];
    }
}

template <>
void SortingSystem<int>::radixSort()
{
    int maxNum = INT_MIN;
    for (int i = 0; i < size; i++)
    {
        maxNum = max(maxNum, data[i]);
    }
    int max_num_of_digits = log10(maxNum) + 1;
    for (int i = 0; i < max_num_of_digits; i++)
    {
        countSort(pow(10, i));
        for (int j = 0; j < size; j++)
        {
            cout << data[j] << ' ';
        }
        cout << '\n';
    }
}

// Bucket Support
template <typename T>
void SortingSystem<T>::quickSort(int low, int high, my_vector<T> arr)
{
    if (high <= low)
    {
        return;
    }
    int pivot = low;
    int j = low;
    for (int i = low + 1; i <= high; i++)
    {
        if (arr[pivot] > arr[i])
        {
            j++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[low], arr[j]);
    quickSort(low, j - 1, arr);
    quickSort(j + 1, high, arr);
}
// [9] Bucket Sort
template <>
void SortingSystem<int>::bucketSort(int)
{
    int mx = INT_MIN, mn = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        mx = max(mx, data[i]);
        mn = min(mn, data[i]);
    }
    float range = float(mx) - mn;
    int number_of_bucket = ceil(sqrt(range)) + 1;
    float width_of_bucket = ceil(float(range) / number_of_bucket);
    my_vector<my_vector<int>> buckets(number_of_bucket);
    for (int i = 0; i < size; i++)
    {
        int index_of_bucket = (data[i] - mn) / width_of_bucket;
        if (index_of_bucket >= number_of_bucket)
        {
            index_of_bucket = number_of_bucket - 1;
        }
        buckets[index_of_bucket].push_back(data[i]);
    }
    for (int k = number_of_bucket - 1; k > -1; k--)
    {
        if (buckets[k].my_size())
        {

            quickSort(0, buckets[k].my_size() - 1, buckets[k]);
            for (int j = 0; j < number_of_bucket; j++)
            {
                if (buckets[j].my_size())
                {

                    for (int z = 0; z < buckets[j].my_size(); z++)
                    {
                        cout << buckets[j][z] << ' ';
                    }
                }
            }
            cout << '\n';
        }
    }
    int counter = 0;
    for (int i = 0; i < number_of_bucket; i++)
    {
        if (buckets[i].my_size())
        {
            for (int j = 0; j < buckets[i].my_size(); j++)
            {
                data[counter] = buckets[i][j];
                counter++;
            }
        }
    }
}

// [9] Bucket Sort
template <>
void SortingSystem<double>::bucketSort()
{
    double mx = INT_MIN, mn = INT_MAX;
    for (int i = 0; i < size; i++)
    {
        mx = max(mx, data[i]);
        mn = min(mn, data[i]);
    }
    float range = float(mx) - mn;
    int number_of_bucket = ceil(sqrt(range)) + 1;
    float width_of_bucket = ceil(float(range) / number_of_bucket);
    my_vector<my_vector<double>> buckets(number_of_bucket);
    for (int i = 0; i < size; i++)
    {
        int index_of_bucket = (data[i] - mn) / width_of_bucket;
        if (index_of_bucket >= number_of_bucket)
        {
            index_of_bucket = number_of_bucket - 1;
        }
        buckets[index_of_bucket].push_back(data[i]);
    }
    for (int k = number_of_bucket - 1; k > -1; k--)
    {
        if (buckets[k].my_size())
        {

            quickSort(0, buckets[k].my_size() - 1, buckets[k]);
            for (int j = 0; j < number_of_bucket; j++)
            {
                if (buckets[j].my_size())
                {
                    for (int z = 0; z < buckets[j].my_size(); z++)
                    {
                        cout << buckets[j][z] << ' ';
                    }
                }
            }
            cout << '\n';
        }
    }
    int counter = 0;
    for (int i = 0; i < number_of_bucket; i++)
    {
        if (buckets[i].my_size())
        {
            for (int j = 0; j < buckets[i].my_size(); j++)
            {
                data[counter] = buckets[i][j];
                counter++;
            }
        }
    }
}

// Menu
template <>
void SortingSystem<int>::showMenuInt()
{
    cout << "1) Insertion Sort\n"
            "2) Selection Sort\n"
            "3) Bubble Sort\n"
            "4) Shell Sort\n"
            "5) Merge Sort\n"
            "6) Quick Sort\n"
            "7) Count Sort\n"
            "8) Radix Sort\n"
            "9) Bucket Sort\n"
            "10) Exit\n"
            "Please Choose a sorting algorithm: ";
    int algo;
    cin >> algo;
    while (algo < 1 or algo > 10)
    {
        cout << "Invalid Choice!\n"
                "From 1 to 10 only!\n"
                "New Choice: ";
        cin >> algo;
    }

    cout << "Initial: ";
    this->displayData();
    // Switch for type of the data
    switch (algo)
    {
    case 1:
        this->insertionSort();
        break;
    case 2:
        this->selectionSort();
        break;
    case 3:
        this->bubbleSort();
        break;

    case 4:
        this->shellSort();
        break;
    case 5:
        this->mergeSort(0, size - 1);
        break;
    case 6:
        this->quickSort(0, size - 1);
        break;

    case 7:
        this->countSort();
        break;
    case 8:
        this->radixSort();
        break;
    case 9:
        this->bucketSort(10);
        break;
    default:
        exit(0);
    }
}

// Menu without radix and count
template <typename T>
void SortingSystem<T>::showMenu()
{
    cout << "1) Insertion Sort\n"
            "2) Selection Sort\n"
            "3) Bubble Sort\n"
            "4) Shell Sort\n"
            "5) Merge Sort\n"
            "6) Quick Sort\n"
            "7) Bucket Sort\n"
            "8) Exit\n"
            "Please Choose a sorting algorithm: ";
    int algo;
    cin >> algo;
    while (algo < 1 or algo > 8)
    {
        cout << "Invalid Choice!\n"
                "From 1 to 8 only!\n"
                "New Choice: ";
        cin >> algo;
    }
    cout << "Initial: ";
    this->displayData();
    // Switch for type of the data
    switch (algo)
    {
    case 1:
        this->insertionSort();
        break;
    case 2:
        this->selectionSort();
        break;
    case 3:
        this->bubbleSort();
        break;

    case 4:
        this->shellSort();
        break;
    case 5:
        this->mergeSort(0, size - 1);
        break;
    case 6:
        this->quickSort(0, size - 1);
        break;

    // case 7: this->bucketSort();    break;
    default:
        exit(0);
    }
}

// Time
template <typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)())
{
    auto start = chrono::high_resolution_clock::now();
    (this->*sortFunc)();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> time = end - start;
    cout << "Sorting Time: " << time.count() << endl;
}

void mainMenu()
{
    cout << "1) Int\n"
            "2) Double\n"
            "3) String\n"
            "4) Char\n"
            "Please choose sorting type: ";
    int type;
    cin >> type;

    while (type < 1 or type > 4)
    {
        cout << "Invalid Choice!\n"
                "From 1 to 4 only!\n"
                "New Choice: ";
        cin >> type;
    }

    cout << "Please Enter size of the data: ";
    int size;
    cin >> size;

    switch (type)
    {
    case 1:
    {
        SortingSystem<int> sorting(size);
        sorting.measureSortTime(&SortingSystem<int>::showMenuInt);
        break;
    }
    case 2:
    {
        SortingSystem<double> sorting(size);
        sorting.measureSortTime(&SortingSystem<double>::showMenu);
        break;
    }
    case 3:
    {
        SortingSystem<string> sorting(size);
        sorting.measureSortTime(&SortingSystem<string>::showMenu);
        break;
    }
    default:
    {
        SortingSystem<char> sorting(size);
        sorting.measureSortTime(&SortingSystem<char>::showMenu);
        break;
    }
    }
    cout << "1) Another Sorting\n"
            "2) Exit\n"
            "Choice: ";
    int choice;
    cin >> choice;
    while (choice < 1 or choice > 2)
    {
        cout << "invalid choice!\n"
                "Please 1 or 2: ";
        cin >> choice;
    }
    if (choice == 1)
    {
        mainMenu();
    }
    else
    {
        exit(0);
    }
}
int main()
{
    cout << "Welcome to Deadline Fighters' Sorting System!\n";
    mainMenu();
}
