

#ifndef PROCESORCSS_LIST_H
#define PROCESORCSS_LIST_H
#include "Item.h"
#include <iostream>

using namespace std;

template<class T>
class List {
public:
    List(){
        this->length = 0;
        this->first = nullptr;
        this->last = nullptr;

    }
    void append(T value){
        auto * item =  new Item<T>(value);
        if(length == 0){
            first = item;
            last = first;
            first->setPreviousItem(last);
            first->setNextItem(first);
        }
        else{
            last->setNextItem(item);
            item->setPreviousItem(last);
            last = item;
            last->setNextItem(first);
            first->setPreviousItem(last);
        }
        length++;
    }
    Item<T> pop(){
        if(length == 0){
            throw std::runtime_error("List is empty!");

        }
        else if(length == 1){
            Item<T> Item = *last;
            delete first;
            length--;
            return Item;


        }
        else{
            Item<T> item = *last;
            last = last->getPreviousItem();
            delete last->getNextItem();
            last->setNextItem(nullptr);
            length--;
            return item;
        }
    }
    Item<T> pop(int index){
        if(index < 0 || index >= length ){
            throw std::runtime_error("Index out of range!");

        }
        else if(length == 0){
            throw std::runtime_error("List is empty!");

        }
        else if(index == length - 1){
            return pop();

        }
        else if(index == 0){
            Item<T> Item = *first;
            first = first->getNextItem();
            delete first->getPreviousItem();
            first->setPreviousItem(nullptr);
            length--;
            return Item;

        }
        else if(length == 1){
            Item<T> Item = *last;
            delete first;
            length--;
            return Item;
        }
        else{
            Item<T> item = *getItem(index);
            Item<T> * previous = item.getPreviousItem();
            Item<T> * next = item.getNextItem();
            previous->setNextItem(next);
            next->setPreviousItem(previous);
            length--;
            return item;
        }

    }
    Item<T> * getItem(int index){
        if(length == 0){
            throw std::runtime_error("List is empty!");
        }
        else{
            Item<T> * currentItem = first;
            int i = 0;
            while(i != index && i < length){
                currentItem = currentItem->getNextItem();
                i++;

            }
            if(i < length){
                return currentItem;
            }
            else{
                throw std::runtime_error("There is not such Item in the list!");
            }
        }
    }
    T get(int index){
        return getItem(index)->getValue();
    }
    void replace(int index, T value){
        if(index < 0 || index >= length ){
            throw std::runtime_error("Index out of range!");
        }
        else{
            this->getItem(index)->setValue(value);
        }
    }
    void insert(int index, T value){
        if(index < 0 || index >= length ){
            throw std::runtime_error("Index out of range!");
        }
        if(index == length - 1){
            append(value);
        }
        else{
            Item<T> * current = this->getItem(index);
            Item<T> * previous = current->getPreviousItem();
            auto * item = new Item<T>(value);
            previous->setNextItem(item);
            item->setPreviousItem(previous);
            item->setNextItem(current);
            current->setPreviousItem(item);
            length++;
        }
    }
    int index(const T& element) const{
        for (int i = 0; i < size(); ++i) {
            if(this[i] == element){
                return i;
            }
        }
        return -1;
    }
    int size() const{
        return length;
    }
    void swap(int i1, int i2){
        T temp = get(i1);
        replace(i1, get(i2));
        replace(i2, temp);
    }
    ~List(){
        while(length){
            pop();
        }
    }
    bool compare(List<T> * other){
        if(this->size() != other->size()){
            return false;
        }
        else{
            for (int i = 0; i < this->size(); ++i) {
                if(this->get(i) != other->get(i)){
                    return false;
                }
            }
            return true;
        }
    }
private:
    Item<T> * first;
    Item<T> * last;
    int length{};
};



#endif //PROCESORCSS_LIST_H
