#include <iostream>
using namespace std;

struct Person {
    int id;
    Person *next;
    Person(int i) : id(i), next(NULL) {}
};

Person *createCircle(int n) {
    Person *head = new Person(1), *tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Person(i);
        tail = tail->next;
    }
    tail->next = head;
    return head;
}

int main() {
    int n, k;
    cout << "Number of people (N): ";
    cin >> n;
    cout << "Step count (k): ";
    cin >> k;
    if (n < 1 || k < 1) { cout << "Invalid input\n"; return 1; }

    Person *cur = createCircle(n);
    Person *prev = cur;
    while (prev->next != cur) prev = prev->next;

    cout << "Elimination order: ";
    while (cur->next != cur) {
        for (int i = 1; i < k; i++) {
            prev = cur;
            cur = cur->next;
        }
        cout << cur->id << " ";
        prev->next = cur->next;
        delete cur;
        cur = prev->next;
    }
    cout << "\nSurvivor: " << cur->id << endl;
    delete cur;
    return 0;
}
