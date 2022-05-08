// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <string>
#include <iostream>

template <typename T>
class TPQueue {
  private:
 private:
    struct structItem {
     T data;
     structItem *next;
     structItem *prev;
    };
    TPQueue::structItem *create(const T &data) {
     structItem * item = new structItem;
     item->data = data;
     item->next = nullptr;
     item->prev = nullptr;
     return item;
    }
    structItem *head;
    structItem *tail;
    structItem *current;
 public:
    T pop() {
     if (head) {
       structItem *temp = head->next;
       if (temp)
         temp->prev = nullptr;
       T data = head->data;
       delete head;
       head = temp;
       return data;
     } else {
         throw std::string("Empty!");
       }
    }
    void push(const T& data) {
     structItem *temp = head;
     structItem *item = create(data);
     while (temp && temp->data.prior >= data.prior)
       temp = temp->next;
     if (!temp && head) {
       tail->next = item;
       tail->next->prev = tail;
       tail = item;
     } else if (!temp && !head) {
         head = tail = item;
       } else if (!temp->prev) {
           temp->prev = item;
           item->next = temp;
           head = item;
         } else {
             temp->prev->next = item;
             item->prev = temp->prev;
             item->next = temp;
             temp->prev = item;
           }
    }
};
