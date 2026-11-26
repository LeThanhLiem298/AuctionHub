
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Bid {
    string bidderId;
    double amount;
    long long timestamp;
    int auctionId;
};


void printBids(const vector<Bid>& v, size_t limit = 10) {
    for (size_t i = 0; i < min(v.size(), limit); i++)
        cout << "[" << v[i].bidderId << "] $"
             << v[i].amount << " @ "
             << v[i].timestamp << "\n";

    if (v.size() > limit)
        cout << "... (" << v.size() << " total)\n";
}

bool loadBids(const string& path, vector<Bid>& out) {
    ifstream f(path);

    if (!f)
        return false;

    Bid b;

    while (f >> b.bidderId >> b.amount
             >> b.timestamp >> b.auctionId) {
        out.push_back(b);
    }

    return true;
}
bool lessBid(const Bid& a, const Bid& b) {
    if (a.amount == b.amount)
        return a.timestamp < b.timestamp;

    return a.amount < b.amount;
}


void insertionSort(vector<Bid>& v) {
    int n = v.size();

    for (int i = 1; i < n; i++) {
        Bid key = v[i];
        int j = i - 1;

        while (j >= 0 &&
              (v[j].amount > key.amount ||
              (v[j].amount == key.amount &&
               v[j].timestamp > key.timestamp))) {

            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = key;
    }
}


void selectionSort(vector<Bid>& v) {
    int n = v.size();

    for (int i = 0; i < n - 1; i++) {
        int maxIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (v[j].amount > v[maxIndex].amount) {
                maxIndex = j;
            }
        }

        if (maxIndex != i) {
            swap(v[i], v[maxIndex]);
        }
    }
}


void interchangeSort(vector<Bid>& v) {
    int n = v.size();
    int swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[i].amount > v[j].amount) {
                swap(v[i], v[j]);
                swaps++;
            }
        }
    }

    cout << "Total swaps: " << swaps << "\n";
}

bool bubbleSortEarlyStop(vector<Bid>& v) {
    int n = v.size();
    bool initiallySorted = true;

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (v[j].amount > v[j + 1].amount) {
                swap(v[j], v[j + 1]);
                swapped = true;
                initiallySorted = false;
            }
        }

        if (!swapped)
            break;
    }

    return initiallySorted;
}

int partition(vector<Bid>& v, int lo, int hi) {
    int mid = lo + (hi - lo) / 2;

    if (lessBid(v[mid], v[lo]))
        swap(v[mid], v[lo]);

    if (lessBid(v[hi], v[lo]))
        swap(v[hi], v[lo]);

    if (lessBid(v[hi], v[mid]))
        swap(v[hi], v[mid]);

    swap(v[mid], v[hi]);

    Bid pivot = v[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (!lessBid(pivot, v[j])) {
            i++;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[hi]);

    return i + 1;
}

void quickSort(vector<Bid>& v, int lo, int hi) {
    if (lo < hi) {
        int p = partition(v, lo, hi);

        quickSort(v, lo, p - 1);
        quickSort(v, p + 1, hi);
    }
}

void quickSortWrapper(vector<Bid>& v) {
    if (!v.empty())
        quickSort(v, 0, (int)v.size() - 1);
}





int main() {
    vector<Bid> v;

    if (!loadBids("test_data/small.txt", v)) {
        cout << "Cannot open small.txt\n";
        return 1;
    }

    // Task A
    cout << "\nTASK A - Insertion Sort\n";

    vector<Bid> a = v;
    insertionSort(a);
    printBids(a);

    // Task B
    cout << "\nTASK B - Selection Sort (Top 3)\n";

    vector<Bid> b = v;
    selectionSort(b);
    printBids(b, 3);

    // Task C
    cout << "\nTASK C - Interchange Sort\n";

    vector<Bid> c = v;
    interchangeSort(c);
    printBids(c);

    // Task D
    cout << "\nTASK D - Bubble Sort Early Stop\n";

    vector<Bid> d1 = a;
    vector<Bid> d2 = b;

    cout << "Sorted input: ";
    if (bubbleSortEarlyStop(d1))
        cout << "STABLE\n";
    else
        cout << "UNSTABLE\n";

    cout << "Reversed input: ";
    if (bubbleSortEarlyStop(d2))
        cout << "STABLE\n";
    else
        cout << "UNSTABLE\n";

    // Task E
    cout << "\nTASK E - Quick Sort\n";

    vector<Bid> large;

    if (!loadBids("test_data/large.txt", large)) {
        cout << "Cannot open large.txt\n";
        return 1;
    }

    auto start = steady_clock::now();

    quickSortWrapper(large);

    auto end = steady_clock::now();

    double ms =
        duration<double, milli>(end - start).count();

    cout << "Number of bids: " << large.size() << "\n";
    cout << "Runtime: " << ms << " ms\n";

    if (is_sorted(large.begin(), large.end(), lessBid))
        cout << "Sorted: YES\n";
    else
        cout << "Sorted: NO\n";

    return 0;
}
