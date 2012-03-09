#include <iostream>
#include "PageSet.h"
#include "Page.h"
#include "Set.h"
#include "UnitTest.h"

typedef int Size;


PageSet::PageSet () : Set<Page>::Set() {}


PageSet::~PageSet () {
  free();
}


PageSet::PageSet (const PageSet & psCopy) {
  copy(psCopy);
}


PageSet & PageSet::operator = (const PageSet & psCopy) {
  free();
  return copy(psCopy);
}


bool PageSet::isEmpty() {
  return Set<Page>::IsEmpty();
}


PageSet & PageSet::copy (const PageSet & psCopy) {
  Set<Page>::copy(psCopy);
  return *this;
}


void PageSet::free () {
  Set<Page>::free();
}


bool PageSet::Test (ostream & os) {
  bool success = true;

  PageSet set;
  PageSet set2;
  TEST(set.IsEmpty() == true);

  Page myPage(
      "http://jobs.com/monster/happy.txt"
    , "../intel.html"
    , "My cool description"
  );
  set.Insert(myPage);
  set.Insert(myPage);
  set.Insert(myPage);

  TEST(set.GetSize() == 1);

  set2 = set;
  Page nextPage(
      "file:///home/eric/school/Web-Crawler/Makefile"
    , "./.././././../Downloads/myweb.html"
    , "A downloaded website"
  );
  set2.Insert(nextPage);
  set2.Insert(nextPage);
  set2.Insert(nextPage);

  TEST(set.GetSize() == 1);
  TEST(set2.GetSize() == 2);

  TEST(set.Contains(myPage) == true); 
  TEST(set.Contains(nextPage) == false); 

  Page unusedPage;
  TEST(set2.Contains(myPage) == true);
  TEST(set2.Contains(nextPage) == true);
  TEST(set2.Contains(unusedPage) == false);

  set.Remove(myPage);

  TEST(set.IsEmpty() == true);

  set.Remove(myPage);
  set.Remove(myPage);
  set.Remove(nextPage);
  set.Remove(nextPage);

  return success;
}


bool PageSet::Contains (const Page & val) const {
  return Set<Page>::Contains(val); 
}


bool PageSet::Insert (const Page & v) {
  return Set<Page>::Insert(v);
}


void PageSet::traverse (BSTNode<Page>* node, ostream & stream) {
  if (NULL == node) {
    return;
  }

  if (NULL != node->GetLeft()) {
    traverse(node->GetLeft(), stream);
  }

  if (NULL != node->GetRight()) {
    traverse(node->GetRight(), stream);
  }

  stream << node->GetValue(); 
}

BSTNode<Page>* PageSet::GetRoot () const {
  return BST<Page>::GetRoot();
}

ostream & operator << (ostream & stream, PageSet & set) {
  set.traverse(set.GetRoot(), stream);
  return stream;
}


