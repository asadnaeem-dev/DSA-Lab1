// Task 3: Iterative Tower of Hanoi
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

// Move the top disk between two pegs in the only legal direction.
void moveLegal(stack<int>& a, stack<int>& b, char na, char nb) {
    if (a.empty()) {                       // b -> a
        int d = b.top(); b.pop(); a.push(d);
        cout << "Move disk " << d << " from " << nb << " to " << na << "\n";
    } else if (b.empty()) {                // a -> b
        int d = a.top(); a.pop(); b.push(d);
        cout << "Move disk " << d << " from " << na << " to " << nb << "\n";
    } else if (a.top() < b.top()) {        // a -> b (smaller onto larger)
        int d = a.top(); a.pop(); b.push(d);
        cout << "Move disk " << d << " from " << na << " to " << nb << "\n";
    } else {                               // b -> a
        int d = b.top(); b.pop(); a.push(d);
        cout << "Move disk " << d << " from " << nb << " to " << na << "\n";
    }
}

void hanoiIterative(int n, char src, char aux, char dest) {
    stack<int> S, A, D;
    for (int i = n; i >= 1; i--) S.push(i);

    // For an even number of disks swap the roles of aux and dest
    if (n % 2 == 0) { swap(aux, dest); swap(A, D); }

    long long total = (1LL << n) - 1;
    for (long long i = 1; i <= total; i++) {
        if (i % 3 == 1)      moveLegal(S, D, src, dest);
        else if (i % 3 == 2) moveLegal(S, A, src, aux);
        else                 moveLegal(A, D, aux, dest);
    }
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;
    hanoiIterative(n, 'A', 'B', 'C');
    cout << "Total moves = " << ((1LL << n) - 1) << "\n";
}
