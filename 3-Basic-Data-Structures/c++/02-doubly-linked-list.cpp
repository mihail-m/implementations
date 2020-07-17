#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value;
    Node* prev;
    Node* next;

    Node() {
        value = 0;
        prev = nullptr;
        next = nullptr;
    }

    Node(int v, Node* n, Node* p) {
        value = v;
        next = n;
        prev = p;
    }
};

class doubly_linked_list {
    private:
        Node* first;
        Node* last;

        int _elements;

        Node* goToPos(int pos) {
            if (pos < _elements - pos) {
                int cnt = 0;
                Node* cur = first;
                while (cnt < pos) {
                    cur = cur->next;
                    cnt++;
                }

                return cur;
            }

            int cnt = _elements - 1;
            Node* cur = last;
            while (cnt > pos) {
                cur = cur->prev;
                cnt--;
            }
            return cur;
        }

    public:
        doubly_linked_list() {
            first = nullptr;
            last = nullptr;
            _elements = 0;
        }

        void insert_end(int num) {
            _elements++;

            if (last == nullptr) {
                first = new Node(num, nullptr, nullptr);
                last = first;
                return;
            }

            last->next = new Node(num, nullptr, last);
            last = last->next;
        }

        void insert_begin(int num) {
            _elements++;

            if (first == nullptr) {
                first = new Node(num, nullptr, nullptr);
                last = first;
                return;
            }

            first = new Node(num, first, nullptr);
        }

        void insert_pos(int num, int pos) {
            if (pos < 0 || pos > _elements) {
                throw invalid_argument("Possition out of bounds.");
            }

            if (pos >= _elements) {
                insert_end(num);
                return;
            }

            if (pos == 0) {
                insert_begin(num);
                return;
            }

            _elements++;

            Node* cur = goToPos(pos - 1);
            cur->next = new Node(num, cur->next, cur);
            cur->next->next->prev = cur->next;
        }

        void erase_begin() {
            if (first == nullptr) {
                return;
            }

            _elements--;

            Node* temp = first;
            first = first->next;
            first->prev = nullptr;
            delete temp;
        }

        void erase_end() {
            if (last == nullptr) {
                return;
            }

            _elements--;

            last = last->prev;
            delete last->next;
            last->next = nullptr;
        }

        void erase_pos(int pos) {
            if (pos < 0 || pos >= _elements) {
                throw invalid_argument("Possition out of bounds.");
            }

            if (pos == 0) {
                erase_begin();
                return;
            }

            if (pos == _elements - 1) {
                erase_end();
                return;
            }

            _elements--;

            Node* cur = goToPos(pos - 1);

            Node* temp = cur->next;
            cur->next = temp->next;
            cur->next->prev = cur;
            delete temp;
        }

        void reverse() {
            if (_elements == 2) {
                swap(first->value, first->next->value);
                return;
            }

            Node* forward = first;
            Node* backward = last;

            int cnt = 0;
            while (cnt < _elements / 2) {
                swap(forward->value, backward->value);
                forward = forward->next;
                backward = backward->prev;
                cnt++;
            }
        }

        int get_begin() {
            return first->value;
        }

        int get_end() {
            return last->value;
        }

        int get(int pos) {
            if (pos >= _elements || pos < 0) {
                throw invalid_argument("Possition out of bounds.");
            }

            return goToPos(pos)->value;
        }

        int elements() {
            return _elements;
        }

        void print() {
            Node* cur = first;
            while (cur != nullptr) {
                cout << cur->value << " ";
                cur = cur->next;
            }
            cout << "\n";
        }

        void free() {
            if (first == nullptr) {
                return;
            }

            Node* temp = first;
            Node* cur = first->next;

            while (cur != nullptr) {
                delete temp;

                temp = cur;
                cur = cur->next;
            }

            delete temp;
            _elements = 0;
        }
};

void test() {
    doubly_linked_list l;

    for (int i = 0; i < 5; i++) {
        l.insert_end(i);
    }

    l.print();
    l.reverse();
    l.print();
    l.free();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    test();

    return 0;
}
