#include <iostream>

template <class T>
class linked_list
{
    struct node
    {
        T dato;
        node * next = nullptr;
        node(const T & d, node * p = nullptr): dato(d), next(p){}
    };
    node * head = nullptr;
    node * tail = nullptr;
    int sz = 0;
public:
    linked_list() = default;
    ~linked_list() {
        while (!empty()) {
            pop_front();
        }
    }
    bool empty() const {return head == nullptr;}

    void push_back(const T   & d) {
        node * n = new node(d, nullptr);
        if (empty()) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        sz += 1;
    }
    void push_front(const T & d){head = new node(d, head); sz++;}

    void pop_front() {
        if (empty()) {return;}
        node * n = head;
        head = head->next;
        if (!head) { tail = nullptr; }
        delete n;
        sz -= 1;
    }
    T& front() const {
        return head->dato;
    }
    void pop_back() {
        if (empty()) {return;}
        node * curr = tail;
        while (curr->next!=tail) {
            curr = curr->next;
        }
        delete tail;
        tail = curr;
        tail->next = nullptr;
        sz -= 1;
    }
    T& back() const {
        return tail->dato;
    }
    node ** search(const T & d)
    {
        node ** n = &head;
        while(*n && (*n)->dato != d)
            n = &(*n)->next;
        return n;
    }
    node ** remove(node ** n)
    {
        node * nt = *n;
        *n = nt->next;
        if (nt == tail) {
            if (head == nullptr) {
                tail = nullptr;
            } else {
                node * temp = head;
                while (temp->next) temp = temp->next;
                tail = temp;
            }
        }
        sz -= 1;
        delete nt;
        return n;
    }
    void remove_all(const T & x)
    {
        node ** n = &head;
        tail = nullptr;

        while (*n) {
            if ((*n)->dato == x) {
                node * nt = *n;
                *n = nt->next;
                delete nt;
            } else {
                tail = *n;
                n = &(*n)->next;
            }
        }
    }
    int size() const {return sz;}
    node ** insert(node ** n, const T & d)
    {
        *n = new node(d, *n);
        return n;
    }
    void print() const {
        for (node * n = head; n; n = n->next) {
            std::cout << n->dato << (n->next ? " " : "");
        }
        std::cout << "\n";
    }
    friend std::ostream & operator << (std::ostream & os, const
    linked_list<T> & ll)
    {
        os << "head -> ";
        for(node * n = ll.head; n; n = n->next)
            os << n->dato << " -> ";
        return os;
    }
};
