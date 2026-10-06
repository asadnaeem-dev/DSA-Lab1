#include <iostream>
#include <string>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity, passengers;
    Coach *next, *prev;
};

class Train {
    Coach *head, *current;

    void show(Coach *c) {
        cout << "Coach: " << c->number << " | Type: " << c->type << " | Capacity: " << c->capacity
             << " | Passengers: " << c->passengers << " | Empty: " << c->capacity - c->passengers << endl;
    }

    Coach *find(int num) {
        if (!head) return NULL;
        Coach *t = head;
        do {
            if (t->number == num) return t;
            t = t->next;
        } while (t != head);
        return NULL;
    }

    void removeNode(Coach *c) {
        if (c->next == c) {
            head = current = NULL;
        } else {
            c->prev->next = c->next;
            c->next->prev = c->prev;
            if (head == c) head = c->next;
            if (current == c) current = c->next;
        }
        delete c;
    }

public:
    Train() : head(NULL), current(NULL) {}

    ~Train() {
        while (head) removeNode(head);
    }

    void addCoach(int num, string type, int cap, int pass) {
        Coach *n = new Coach{num, type, cap, pass, NULL, NULL};
        if (!head) {
            n->next = n->prev = n;
            head = current = n;
            return;
        }
        Coach *tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = n;
        head->prev = n;
    }

    void insertCoach(int after, int num, string type, int cap, int pass) {
        Coach *p = find(after);
        if (!p) { cout << "Coach " << after << " not found." << endl; return; }
        Coach *n = new Coach{num, type, cap, pass, NULL, NULL};
        n->next = p->next;
        n->prev = p;
        p->next->prev = n;
        p->next = n;
    }

    void removeCoach(int num) {
        Coach *c = find(num);
        if (!c) { cout << "Coach not found." << endl; return; }
        removeNode(c);
    }

    void moveForward() {
        if (!current) { cout << "Train is empty." << endl; return; }
        current = current->next;
    }

    void moveBackward() {
        if (!current) { cout << "Train is empty." << endl; return; }
        current = current->prev;
    }

    void displayClockwise() {
        if (!head) { cout << "Train is empty." << endl; return; }
        Coach *t = head;
        do {
            show(t);
            t = t->next;
        } while (t != head);
    }

    void displayAnticlockwise() {
        if (!head) { cout << "Train is empty." << endl; return; }
        Coach *t = head->prev;
        do {
            show(t);
            t = t->prev;
        } while (t != head->prev);
    }

    void search(int num) {
        Coach *c = find(num);
        if (c) show(c);
        else cout << "Coach not found." << endl;
    }

    void maxAvailable() {
        if (!head) { cout << "Train is empty." << endl; return; }
        Coach *best = head, *t = head->next;
        while (t != head) {
            if (t->capacity - t->passengers > best->capacity - best->passengers) best = t;
            t = t->next;
        }
        show(best);
    }

    void displayCurrent() {
        if (!current) { cout << "Train is empty." << endl; return; }
        show(current);
    }

    void reverseTrain() {
        if (!head) { cout << "Train is empty." << endl; return; }
        Coach *t = head;
        do {
            Coach *nx = t->next;
            Coach *tmp = t->next;
            t->next = t->prev;
            t->prev = tmp;
            t = nx;
        } while (t != head);
        head = head->next;
    }
};

void readCoach(int &num, string &type, int &cap, int &pass) {
    cout << "Coach Number: "; cin >> num;
    cout << "Coach Type: "; cin >> ws; getline(cin, type);
    cout << "Capacity: "; cin >> cap;
    cout << "Current Passengers: "; cin >> pass;
}

int main() {
    Train tr;
    int n, num, cap, pass, after, choice;
    string type;

    cout << "Number of coaches: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Coach " << i + 1 << endl;
        readCoach(num, type, cap, pass);
        tr.addCoach(num, type, cap, pass);
    }

    do {
        cout << "\n1 Add Coach\n2 Insert Coach\n3 Remove Coach\n4 Move Forward\n5 Move Backward\n"
             << "6 Display Clockwise\n7 Display Anti-clockwise\n8 Search Coach\n"
             << "9 Max Available Capacity\n10 Display Current\n11 Reverse Train\n0 Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            readCoach(num, type, cap, pass);
            tr.addCoach(num, type, cap, pass);
            break;
        case 2:
            cout << "Insert after coach number: "; cin >> after;
            readCoach(num, type, cap, pass);
            tr.insertCoach(after, num, type, cap, pass);
            break;
        case 3:
            cout << "Coach number: "; cin >> num;
            tr.removeCoach(num);
            break;
        case 4: tr.moveForward(); break;
        case 5: tr.moveBackward(); break;
        case 6: tr.displayClockwise(); break;
        case 7: tr.displayAnticlockwise(); break;
        case 8:
            cout << "Coach number: "; cin >> num;
            tr.search(num);
            break;
        case 9: tr.maxAvailable(); break;
        case 10: tr.displayCurrent(); break;
        case 11: tr.reverseTrain(); break;
        }
    } while (choice != 0);
    return 0;
}
