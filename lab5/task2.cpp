#include <iostream>
#include <string>
using namespace std;

struct Photo {
    int id;
    string name, date, location;
    Photo *next, *prev;
};

class Album {
    Photo *head, *current;

    void show(Photo *p) {
        cout << "ID: " << p->id << " | Name: " << p->name << " | Date: " << p->date
             << " | Location: " << p->location << endl;
    }

    void removeNode(Photo *p) {
        if (p->next == p) {
            head = current = NULL;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            if (head == p) head = p->next;
            if (current == p) current = p->next;
        }
        delete p;
    }

    Photo *find(int id) {
        if (!head) return NULL;
        Photo *t = head;
        do {
            if (t->id == id) return t;
            t = t->next;
        } while (t != head);
        return NULL;
    }

public:
    Album() : head(NULL), current(NULL) {}

    ~Album() {
        while (head) removeNode(head);
    }

    void addPhoto(int id, string name, string date, string loc) {
        Photo *n = new Photo{id, name, date, loc, NULL, NULL};
        if (!head) {
            n->next = n->prev = n;
            head = current = n;
            return;
        }
        Photo *tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = n;
        head->prev = n;
    }

    void insertAfterCurrent(int id, string name, string date, string loc) {
        if (!current) {
            addPhoto(id, name, date, loc);
            return;
        }
        Photo *n = new Photo{id, name, date, loc, NULL, NULL};
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
    }

    void removeById(int id) {
        Photo *p = find(id);
        if (!p) { cout << "Photo not found." << endl; return; }
        removeNode(p);
    }

    void removeCurrent() {
        if (!current) { cout << "Album is empty." << endl; return; }
        removeNode(current);
    }

    void moveNext() {
        if (!current) { cout << "Album is empty." << endl; return; }
        current = current->next;
    }

    void movePrev() {
        if (!current) { cout << "Album is empty." << endl; return; }
        current = current->prev;
    }

    void displayForward() {
        if (!current) { cout << "Album is empty." << endl; return; }
        Photo *t = current;
        do {
            show(t);
            t = t->next;
        } while (t != current);
    }

    void displayBackward() {
        if (!current) { cout << "Album is empty." << endl; return; }
        Photo *t = current;
        do {
            show(t);
            t = t->prev;
        } while (t != current);
    }

    void search(int id) {
        Photo *p = find(id);
        if (p) show(p);
        else cout << "Photo not found." << endl;
    }

    void count() {
        int c = 0;
        if (head) {
            Photo *t = head;
            do {
                c++;
                t = t->next;
            } while (t != head);
        }
        cout << "Total photos: " << c << endl;
    }
};

void readPhoto(int &id, string &name, string &date, string &loc) {
    cout << "ID: "; cin >> id;
    cout << "Name: "; cin >> ws; getline(cin, name);
    cout << "Date Taken: "; getline(cin, date);
    cout << "Location: "; getline(cin, loc);
}

int main() {
    Album a;
    int n, id, choice;
    string name, date, loc;

    cout << "Number of photos: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Photo " << i + 1 << endl;
        readPhoto(id, name, date, loc);
        a.addPhoto(id, name, date, loc);
    }

    do {
        cout << "\n1 Add Photo\n2 Insert After Current\n3 Remove By ID\n4 Remove Current\n"
             << "5 Move Next\n6 Move Previous\n7 Display Forward\n8 Display Backward\n"
             << "9 Search\n10 Count\n0 Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            readPhoto(id, name, date, loc);
            a.addPhoto(id, name, date, loc);
            break;
        case 2:
            readPhoto(id, name, date, loc);
            a.insertAfterCurrent(id, name, date, loc);
            break;
        case 3:
            cout << "ID: "; cin >> id;
            a.removeById(id);
            break;
        case 4: a.removeCurrent(); break;
        case 5: a.moveNext(); break;
        case 6: a.movePrev(); break;
        case 7: a.displayForward(); break;
        case 8: a.displayBackward(); break;
        case 9:
            cout << "ID: "; cin >> id;
            a.search(id);
            break;
        case 10: a.count(); break;
        }
    } while (choice != 0);
    return 0;
}
