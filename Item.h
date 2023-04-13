//
// Created by Michał on 23.03.2023.
//

#ifndef PROCESORCSS_ITEM_H
#define PROCESORCSS_ITEM_H
template<class T>
class Item {
public:
    explicit Item(const T& value) : value(value) {
    }
    Item * getNextItem(){
        return this->nextItem;

    }
    Item * getPreviousItem(){
        return this->previousItem;

    }
    void setNextItem(Item * next){
        this->nextItem = next;

    }
    void setPreviousItem(Item * previous){
        this->previousItem = previous;

    }
    T getValue() const{
        return value;

    }
    void setValue(const T& newValue){
        this->value = newValue;

    }
private:
    T value;
    Item * nextItem{

    };
    Item * previousItem{

    };

};
#endif //PROCESORCSS_ITEM_H
