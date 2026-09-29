#include <iostream>
#include <string>
using namespace std;

struct Song {
    int id;
    string name;
    int min, sec;
    Song *next, *prev;
    Song(int i, string n, int m, int s) : id(i), name(n), min(m), sec(s), next(NULL), prev(NULL) {}
};

class Playlist {
    Song *head, *tail, *current;

public:
    Playlist() : head(NULL), tail(NULL), current(NULL) {}
    ~Playlist() {
        while (head) {
            Song *t = head;
            head = head->next;
            delete t;
        }
    }

    Song *find(int id) {
        for (Song *p = head; p; p = p->next)
            if (p->id == id) return p;
        return NULL;
    }

    void show(Song *s) {
        cout << "ID: " << s->id << " | " << s->name << " | " << s->min << ":" << (s->sec < 10 ? "0" : "") << s->sec << endl;
    }

    void add(int id, string name, int m, int s) {
        if (find(id)) { cout << "ID already exists\n"; return; }
        Song *n = new Song(id, name, m, s);
        if (!head) head = tail = current = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        cout << "Song added\n";
    }

    void remove(int id) {
        Song *p = find(id);
        if (!p) { cout << "Song not found\n"; return; }
        if (p->prev) p->prev->next = p->next; else head = p->next;
        if (p->next) p->next->prev = p->prev; else tail = p->prev;
        if (current == p) current = p->next ? p->next : p->prev;
        delete p;
        cout << "Song deleted\n";
    }

    void forward() {
        if (!head) { cout << "Playlist empty\n"; return; }
        for (Song *p = head; p; p = p->next) show(p);
    }

    void backward() {
        if (!tail) { cout << "Playlist empty\n"; return; }
        for (Song *p = tail; p; p = p->prev) show(p);
    }

    void search(int id) {
        Song *p = find(id);
        if (p) show(p); else cout << "Song not found\n";
    }

    void playCurrent() {
        if (!current) { cout << "Playlist empty\n"; return; }
        cout << "Now playing: ";
        show(current);
    }

    void next() {
        if (!current) { cout << "Playlist empty\n"; return; }
        if (!current->next) { cout << "Already at last song\n"; return; }
        current = current->next;
        playCurrent();
    }

    void previous() {
        if (!current) { cout << "Playlist empty\n"; return; }
        if (!current->prev) { cout << "Already at first song\n"; return; }
        current = current->prev;
        playCurrent();
    }

    void reverse() {
        Song *p = head;
        while (p) {
            Song *t = p->next;
            p->next = p->prev;
            p->prev = t;
            p = t;
        }
        Song *t = head;
        head = tail;
        tail = t;
        cout << "Playlist reversed\n";
    }
};

int main() {
    Playlist pl;
    int ch;
    do {
        cout << "\n1.Add 2.Delete 3.Display Forward 4.Display Backward 5.Search\n"
                "6.Play Current 7.Next 8.Previous 9.Reverse 0.Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            int id, m, s;
            string name;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Duration (min sec): "; cin >> m >> s;
            pl.add(id, name, m, s);
        } else if (ch == 2) {
            int id; cout << "ID: "; cin >> id; pl.remove(id);
        } else if (ch == 3) pl.forward();
        else if (ch == 4) pl.backward();
        else if (ch == 5) {
            int id; cout << "ID: "; cin >> id; pl.search(id);
        } else if (ch == 6) pl.playCurrent();
        else if (ch == 7) pl.next();
        else if (ch == 8) pl.previous();
        else if (ch == 9) pl.reverse();
    } while (ch != 0);
    return 0;
}
