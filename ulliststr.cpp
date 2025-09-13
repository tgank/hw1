#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_back(const std::string& val){ //focus on looking at the tail block only

  if(tail_ == nullptr){
    //empty --> setting of tail
    tail_ = new Item();
    head_ = tail_; //make sure logic is corect
    tail_ -> val[tail_ -> first] = val; //val will now be in the beg of node making it exclusively tail
    tail_ -> last++;
  }
  else if(tail_ -> last < ARRSIZE){   
    //array in tail_ node still has room
      tail_ -> val[tail_ -> last] = val;
      tail_ -> last++;
  }
  else{
    //array FULL in tail_ so need NEW tail_ AKA tail_ -> last >= ARRSIZE
    Item* back = new Item;
    back -> next = nullptr;
    back -> prev = tail_;
    tail_ -> next = back;
    back -> val[back -> first] = val;
    tail_ = back;
    tail_ -> last++;
  }

  size_ ++;
  return;
}

void ULListStr::pop_back(){
  if(tail_ == nullptr){
    return;
  }
  if(tail_ -> last > tail_ -> first){
    //get rid of last
    tail_->last--;
    tail_->val[tail_->last].clear();
  }

  if (tail_ && tail_->last == tail_->first) { // tail and @ last val in array
    Item* old = tail_;
    if (head_ == tail_) {
      //last item
      head_ = tail_ = nullptr;
    } 
    else {
      //move tail
      tail_ = tail_->prev;
      tail_->next = nullptr;
    }
    delete old;
  }

  size_ --;
  return;

}

void ULListStr::push_front(const std::string& val){ //focus on looking at the head block only

  if(head_ == nullptr){
    //empty --> setting of head
    head_ = new Item;
    head_ -> prev = nullptr;
    head_ -> next = nullptr;
    tail_ = head_;
    head_ -> first = ARRSIZE-1;
    head_ -> last = ARRSIZE;
    head_ -> val[head_ -> first] = val; //val will now be in the beg of node making it exclusively tail
  }
  else if(head_ -> first > 0){   
    //array in head_ node still has room
      head_ -> first--;
      head_ -> val[head_ -> first] = val;
  }
  else{
    //array FULL in head_ so need NEW head_ AKA head_ -> first <= 0 ARRSIZE
    Item* front = new Item;
    front -> next = head_;
    front -> prev = nullptr;
    head_ -> prev = front;
    front -> first = ARRSIZE-1;
    front -> last = ARRSIZE;
    front -> val[front -> first] = val;
    head_ = front;
  }

  size_ ++;
  return;
}

void ULListStr::pop_front(){
  
  if(size_ == 0){
    return;
  }

  else if(head_ -> first == head_ -> last -1){
    //delete current head_ because last val is being popped
    Item* temp = head_;

    if(head_ == tail_){
      //only 1 node
      head_ = nullptr;
      tail_ = nullptr;
    }
    else{
      //move head_ to next node
      head_ = head_ -> next;
      head_ -> prev = nullptr;
    }

    delete temp;
    
  }
  else{
    //popping anywhere that isn't first
    head_ -> first++;
  }

  size_ --;
  return;
}

std::string const & ULListStr::back() const{
  
  if(size_ == 0){
    throw std::invalid_argument("List is empty");
  }
  return tail_ -> val[(tail_ -> last) - 1];
}

std::string const & ULListStr::front() const{
  if(size_ == 0){
    throw std::invalid_argument("List is empty");
  }
  return head_ -> val[head_ -> first];
}
  
std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc >= size_){
    return NULL;
  }
  else{
    size_t cntr = 0;
    size_t loc_in_arr = head_ -> first;

    Item* temp = head_;

    while(cntr != loc){
      if(loc_in_arr < temp -> last -1){
        loc_in_arr++;
      }
      else{
        temp = temp -> next;
        loc_in_arr = temp -> first;
      }
      cntr++;
    }

    //after exiting while loop will be at loc
    return &(temp -> val[loc_in_arr]);

  }
}



void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
