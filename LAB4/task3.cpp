#include <iostream>
#include <string>
using namespace std;

struct Node {
    int bit;
    Node *next, *prev;
    Node(int b) : bit(b), next(NULL), prev(NULL) {}
};

class Binary {
public:
    Node *head, *tail;
    int size;

    Binary() : head(NULL), tail(NULL), size(0) {}
    Binary(const Binary &o) : head(NULL), tail(NULL), size(0) {
        for (Node *p = o.head; p; p = p->next) pushBack(p->bit);
    }
    Binary &operator=(const Binary &o) {
        if (this != &o) {
            clear();
            for (Node *p = o.head; p; p = p->next) pushBack(p->bit);
        }
        return *this;
    }
    ~Binary() { clear(); }

    void clear() {
        while (head) {
            Node *t = head;
            head = head->next;
            delete t;
        }
        tail = NULL;
        size = 0;
    }

    void pushBack(int b) {
        Node *n = new Node(b);
        if (!tail) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
        size++;
    }

    void pushFront(int b) {
        Node *n = new Node(b);
        if (!head) head = tail = n;
        else { head->prev = n; n->next = head; head = n; }
        size++;
    }

    void popFront() {
        Node *t = head;
        head = head->next;
        if (head) head->prev = NULL; else tail = NULL;
        delete t;
        size--;
    }

    void pad() {
        while (size % 8 != 0 || size == 0) pushFront(0);
    }

    bool store(const string &s) {
        clear();
        if (s.empty()) return false;
        for (char c : s) {
            if (c != '0' && c != '1') { clear(); return false; }
            pushBack(c - '0');
        }
        pad();
        return true;
    }

    void print() const {
        int i = 0;
        for (Node *p = head; p; p = p->next, i++) {
            if (i && i % 8 == 0) cout << " ";
            cout << p->bit;
        }
        cout << endl;
    }

    void onesComplement() {
        for (Node *p = head; p; p = p->next) p->bit ^= 1;
    }

    unsigned long long toDecimal() const {
        unsigned long long v = 0;
        for (Node *p = head; p; p = p->next) v = v * 2 + p->bit;
        return v;
    }
};

Binary add(const Binary &a, const Binary &b) {
    Binary r;
    Node *p = a.tail, *q = b.tail;
    int carry = 0;
    while (p || q || carry) {
        int s = carry + (p ? p->bit : 0) + (q ? q->bit : 0);
        r.pushFront(s & 1);
        carry = s >> 1;
        if (p) p = p->prev;
        if (q) q = q->prev;
    }
    r.pad();
    return r;
}

Binary twosComplement(const Binary &a) {
    Binary c(a), one;
    c.onesComplement();
    one.store("1");
    Binary r = add(c, one);
    while (r.size > a.size) r.popFront();
    return r;
}

Binary multiply(const Binary &a, const Binary &b) {
    Binary result, shifted(a);
    result.store("0");
    for (Node *q = b.tail; q; q = q->prev) {
        if (q->bit) result = add(result, shifted);
        shifted.pushBack(0);
    }
    result.pad();
    return result;
}

int main() {
    Binary a, b;
    string s;
    int ch;
    do {
        cout << "\n1.Store Number A 2.Store Number B 3.1's Complement of A 4.2's Complement of A\n"
                "5.Add A+B 6.Multiply A*B 7.Decimal of A 8.Decimal of B 0.Exit\nChoice: ";
        cin >> ch;
        if (ch == 1 || ch == 2) {
            cout << "Enter bits: ";
            cin >> s;
            Binary &t = (ch == 1) ? a : b;
            if (t.store(s)) t.print(); else cout << "Invalid binary input\n";
        } else if (ch == 3) {
            if (!a.head) { cout << "A not stored\n"; continue; }
            Binary c(a);
            c.onesComplement();
            c.print();
        } else if (ch == 4) {
            if (!a.head) { cout << "A not stored\n"; continue; }
            twosComplement(a).print();
        } else if (ch == 5 || ch == 6) {
            if (!a.head || !b.head) { cout << "Store both numbers first\n"; continue; }
            Binary r = (ch == 5) ? add(a, b) : multiply(a, b);
            r.print();
            cout << "Decimal: " << r.toDecimal() << endl;
        } else if (ch == 7 || ch == 8) {
            Binary &t = (ch == 7) ? a : b;
            if (!t.head) { cout << "Number not stored\n"; continue; }
            cout << t.toDecimal() << endl;
        }
    } while (ch != 0);
    return 0;
}
