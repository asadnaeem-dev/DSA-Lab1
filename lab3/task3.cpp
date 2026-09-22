#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        cout << "Inserted " << val << " at head.\n";
    }

    void insertAtThird(int val) {
        if (!head || !head->next) {
            cout << "List is too short for position 3.\n";
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head->next;
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "Inserted " << val << " at 3rd position.\n";
    }

    void displayList() const {
        if (!head) {
            cout << "List: NULL\n";
            return;
        }
        Node* temp = head;
        cout << "List: ";
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void deleteLast() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        if (!head->next) {
            delete head;
            head = nullptr;
            cout << "Deleted last node.\n";
            return;
        }
        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        cout << "Deleted last node.\n";
    }

    int countNodes() const {
        int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void reverseList() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;
        while (curr) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;
        cout << "List reversed.\n";
    }

    void searchValue(int val) const {
        Node* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->data == val) {
                cout << "Found " << val << " at position " << pos << ".\n";
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Value " << val << " not found.\n";
    }

    ~SinglyLinkedList() {
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

int main() {
    SinglyLinkedList list;
    int choice = 0, val = 0;

    do {
        cout << "\n1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Value: "; cin >> val;
                list.insertAtHead(val);
                break;
            case 2:
                cout << "Value: "; cin >> val;
                list.insertAtThird(val);
                break;
            case 3:
                list.displayList();
                break;
            case 4:
                list.deleteLast();
                break;
            case 5:
                cout << "Count: " << list.countNodes() << "\n";
                break;
            case 6:
                list.reverseList();
                break;
            case 7:
                cout << "Search: "; cin >> val;
                list.searchValue(val);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}
