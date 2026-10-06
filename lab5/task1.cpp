#include <iostream>
#include <string>
using namespace std;

struct Tab {
    int id;
    string title, url;
    Tab *next, *prev;
};

class TabManager {
    Tab *current;

    void show(Tab *t) {
        cout << "ID: " << t->id << " | Title: " << t->title << " | URL: " << t->url << endl;
    }

public:
    TabManager() : current(NULL) {}

    ~TabManager() {
        while (current) closeCurrent();
    }

    void openTab(int id, string title, string url) {
        Tab *n = new Tab{id, title, url, NULL, NULL};
        if (!current) {
            n->next = n->prev = n;
            current = n;
            return;
        }
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
    }

    void closeCurrent() {
        if (!current) {
            cout << "No tabs open." << endl;
            return;
        }
        Tab *d = current;
        if (d->next == d) {
            current = NULL;
        } else {
            d->prev->next = d->next;
            d->next->prev = d->prev;
            current = d->next;
        }
        delete d;
    }

    void moveNext() {
        if (!current) { cout << "No tabs open." << endl; return; }
        current = current->next;
    }

    void movePrev() {
        if (!current) { cout << "No tabs open." << endl; return; }
        current = current->prev;
    }

    void displayCurrent() {
        if (!current) { cout << "No tabs open." << endl; return; }
        show(current);
    }

    void displayForward() {
        if (!current) { cout << "No tabs open." << endl; return; }
        Tab *t = current;
        do {
            show(t);
            t = t->next;
        } while (t != current);
    }

    void displayBackward() {
        if (!current) { cout << "No tabs open." << endl; return; }
        Tab *t = current;
        do {
            show(t);
            t = t->prev;
        } while (t != current);
    }

    void search(int id) {
        if (!current) { cout << "No tabs open." << endl; return; }
        Tab *t = current;
        do {
            if (t->id == id) {
                show(t);
                return;
            }
            t = t->next;
        } while (t != current);
        cout << "Tab not found." << endl;
    }
};

int main() {
    TabManager m;
    int choice, id;
    string title, url;
    do {
        cout << "\n1 Open New Tab\n2 Close Current Tab\n3 Move Next\n4 Move Previous\n"
             << "5 Display Current Tab\n6 Display All Forward\n7 Display All Backward\n"
             << "8 Search Tab\n0 Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "ID: "; cin >> id;
            cout << "Title: "; cin >> ws; getline(cin, title);
            cout << "URL: "; getline(cin, url);
            m.openTab(id, title, url);
            break;
        case 2: m.closeCurrent(); break;
        case 3: m.moveNext(); break;
        case 4: m.movePrev(); break;
        case 5: m.displayCurrent(); break;
        case 6: m.displayForward(); break;
        case 7: m.displayBackward(); break;
        case 8:
            cout << "ID: "; cin >> id;
            m.search(id);
            break;
        }
    } while (choice != 0);
    return 0;
}
