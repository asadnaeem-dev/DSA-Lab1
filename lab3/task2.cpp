#include <iostream>
#include <string>

using namespace std;

class StringPool {
private:
    string** stringPool;
    int currentSize;
    int maxSize;

public:
    // setup pool
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string*[maxSize];
        for (int i = 0; i < maxSize; i++) {
            stringPool[i] = nullptr;
        }
    }

    // add item
    void addString(const string& val) {
        if (currentSize >= maxSize) {
            cout << "Pool is full." << endl;
            return;
        }
        stringPool[currentSize] = new string(val);
        currentSize++;
        cout << "Added: " << val << endl;
    }

    // remove item
    string* removeString() {
        if (currentSize == 0) {
            cout << "Pool is empty." << endl;
            return nullptr;
        }
        currentSize--;
        string* removed = stringPool[currentSize];
        stringPool[currentSize] = nullptr;
        return removed;
    }

    // show pool
    void displayStatus() const {
        cout << "\n--- Pool Status ---" << endl;
        cout << "Current size: " << currentSize << "/" << maxSize << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << "[" << i << "] " << *stringPool[i] << endl;
        }
        if (currentSize == 0) {
            cout << "(Empty)" << endl;
        }
        cout << "-------------------\n" << endl;
    }

    // cleanup pool
    ~StringPool() {
        for (int i = 0; i < currentSize; i++) {
            delete stringPool[i];
        }
        delete[] stringPool;
    }
};

int main() {
    StringPool pool;

    // fill pool
    pool.addString("Alpha");
    pool.addString("Beta");
    pool.addString("Gamma");
    pool.displayStatus();

    // remove unallocated
    cout << "Removing element without deallocating..." << endl;
    string* leakedItem = pool.removeString();

    if (leakedItem != nullptr) {
        cout << "Removed: " << *leakedItem << endl;
    }

    pool.displayStatus();

    // fix leak
    cout << "Fixing leak and clearing pointer..." << endl;
    if (leakedItem != nullptr) {
        delete leakedItem;
        leakedItem = nullptr;
    }

    return 0;
}
