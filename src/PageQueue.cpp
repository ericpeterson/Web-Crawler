#include "PageQueue.h"
#include "Page.h"
#include "Queue.h"
#include "UnitTest.h"

typedef int Size;


PageQueue::PageQueue () : Queue<Page>::Queue() {}


PageQueue::~PageQueue () {
  free();
}


PageQueue::PageQueue (const PageQueue & pqCopy) {
  copy(pqCopy);
}


PageQueue & PageQueue::operator = (const PageQueue & pqCopy) {
  free();
  return copy(pqCopy);
}


Size PageQueue::getSize () const {
  return Queue<Page>::size(); 
}


bool PageQueue::isEmpty () const {
  return Queue<Page>::empty();
}


Page PageQueue::dequeue () {
  return Queue<Page>::pop();
}


void PageQueue::enqueue (const Page & newPage) {
  Queue<Page>::push(newPage);
}


PageQueue & PageQueue::copy (const PageQueue & pqCopy) {
  Queue<Page>::copy(pqCopy);
  return *this;
}


void PageQueue::free () {
  Queue<Page>::free();
}


bool PageQueue::Test (ostream & os) {
  bool success = true;
  return success;
}
