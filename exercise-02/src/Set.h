#ifndef __LIST_SET_H__
#define __LIST_SET_H__

#include <stdio.h>

#include <stdexcept>

template <typename T>
class Set {
    // stores the set elements as a linked list
    struct List {
        T data;
        List *next;
    } *head;
    int capacity = 0;

    // copys an existing list
    List *deep_copy_list(List *new_head) {
        if (new_head) {
            auto tail = deep_copy_list(new_head->next);
            List *head = new List();
            head->data = new_head->data;
            head->next = tail;
            return (head);
        }

        return (nullptr);
    }

    // frees the list and sets the head to NULL
    void free_list() {
        while (head) {
            List *tmp = head->next;
            delete head;
            head = tmp;
        }
        return;
    }

   public:
    // constructor
    Set() : head(nullptr){};

    // destructor
    ~Set() {
        free_list();
    }

    // copy constructor
    Set(const Set &s) {
        head = deep_copy_list(s.head);
        capacity = s.capacity;
    }

    // copy assignment
    Set &operator=(const Set &s) {
        // free the existing set
        free_list();
        // copy the set passed in
        head = deep_copy_list(s.head);
        capacity = s.capacity;
        return (*this);
    }

    // size
    const int size() const {
        return capacity;
    }

    // operator[]
    T operator[](int index) const {
        if (index >= 0 && index < capacity) {
            List *tmp = head;
            for (int i = 0; i < index; i++) {
                tmp = tmp->next;
            }
            return tmp->data;
        }

        throw std::out_of_range("Index out of range");
    }

    // operator==
    T operator==(const Set<T> &other) const {
        if (size() != other.size()) {
            return false;
        } else {
            for (List *tmp = head; tmp; tmp = tmp->next) {
                if (!other.contains(tmp->data)) {
                    return false;
                }
            }
        }

        return true;
    }

    // add
    Set<T> add(const T &el) {
        if (!contains(el)) {
            List *new_elem = new List();
            new_elem->data = el;
            new_elem->next = head;
            head = new_elem;
            capacity++;
        }
        return *this;
    }

    // remove
    Set<T> remove(const T &el) {
        if (contains(el)) {
            if (head->data == el) {
                List *tmp = head->next;
                delete head;
                head = tmp;
            } else {
                for (List *tmp = head, *prev = nullptr; tmp; prev = tmp, tmp = tmp->next) {
                    if (tmp->data == el) {
                        if (tmp->next == nullptr) {
                            delete tmp;
                            prev->next = nullptr;
                            break;

                        } else {
                            List *tmp2 = tmp->next;
                            tmp->data = tmp->next->data;
                            tmp->next = tmp->next->next;
                            delete tmp2;
                            break;
                        }
                    }
                }
            }
            capacity--;
        }

        return *this;
    }

    // contains
    bool contains(const T &elem) const {
        for (List *tmp = head; tmp; tmp = tmp->next) {
            if (tmp->data == elem) {
                return true;
            }
        }
        return false;
    }
};
#endif
