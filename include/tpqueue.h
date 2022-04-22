// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>

template<typename T>
class TPQueue {
// реализация шаблона очереди с приоритетом на связанном списке
 private:
    struct ITEM {
        T value;
        ITEM* next, * prev;
    };
    ITEM* head, * tail, * current;
    TPQueue::ITEM* create(const T& value) {
        ITEM* item = new ITEM;
        item->value = value;
        item->next = nullptr;
        item->prev = nullptr;
        return item;
    };
 public:
    TPQueue() {
        head = tail = current = nullptr;
    }
  
    ~TPQueue() {
        while (head)
            pop();
    }
  
    T getNext() {
        if (head && tail) {
            if (!current)
                current = head;
            else if (current->next)
                current = current->next;
            else
                throw std::string("Out of limit!");
            return current->value;
        } else {
            throw std::string("Out of limit!");
        }
    }
  
    T pop() {
        if (head && tail) {
            ITEM* temp = head->next;
            if (temp)
                temp->prev = nullptr;
            T value = head->value;
            delete head;
            head = temp;
            if (!head)
                tail = nullptr;
            return value;
        } else {
            throw std::string("Out of limit!");
        }
    }
    
    void push(const T& value) {
        ITEM* temp = head;
        ITEM* item = create(value);
        while (temp && temp->value.prior >= value.prior)
            temp = temp->next;
        if (!temp && head) {
            tail->next = item;
            item->prev = tail;
            tail = item;
        } else if (!temp && !head) {
            head = tail = item;
        } else if (!temp->prev) {
            head->prev = item;
            item->next = head;
            head = item;
        } else {
            temp->prev->next = item;
            item->prev = temp->prev;
            item->next = temp;
            temp->prev = item;
        }
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
