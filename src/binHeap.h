#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;

// Predložak klase koji implementira maximalnu hrpu.
template <typename T>
class MaxHeap{
public:
    using size_type = typename std::vector<T>::size_type;
	// Konstruktor
    MaxHeap() = default;
    // Parametrizirani konstruktor koji preuzima elemente iz raspona [begin, end).
    template <typename RAIT>
    MaxHeap(RAIT begin, RAIT end);
	// Gurni novi element na hrpu.
    void push(T);
	// Ukloni vodeći (maksimalni) element sa hrpe.
    void pop();
	// Vrati vodeći element hrpe.
    T top() const;
    // Je li hrpa prazna?
    bool empty() const;
	// Broj elemenata u hrpi.
    size_type size() const;
    // Ispiši sortirane vijednosti u vektor vec.
	// MaxHeap ostaje prazan nakon sortiranja.
    void sort(std::vector<T> & vec);
protected:
  std::vector<T> mData;
  // Eventualne dodatne metode stavljati u ovu sekciju.
};


template <typename T>
template <typename RAIT>
MaxHeap<T>::MaxHeap(RAIT begin, RAIT end){
  //kopiranje u spremnik
  while (begin != end) {
    mData.push_back(*begin);
    begin++;
  }
  if (mData.size() < 2)
    return;
  for (int i = (mData.size() - 2) / 2; i >= 0; --i) {
    int trenutni = i;
    //slijedi kopiran dio od pop
    //ako ima oba djeteta
    while (mData.size() > 2 * trenutni + 2) {
      //ako je manji od barem jednog djeteta
      if (mData[trenutni] < mData[2 * trenutni + 1] ||
          mData[trenutni] < mData[2 * trenutni + 2]) {
            //ako je lijevi >= desni
            if (mData[2 * trenutni + 1] >= mData[2 * trenutni + 2]){
              iter_swap(mData.begin() + trenutni,
                        mData.begin() + 2 * trenutni + 1);
              trenutni = 2 * trenutni + 1;
            }
            //ako je desni > lijevi
            else {
              iter_swap(mData.begin() + trenutni,
                        mData.begin() + 2 * trenutni + 2);
              trenutni = 2 * trenutni + 2;
            }
      }
      //inace je na pravom mjestu
      else
        break;
    }
    //ako ima jedno dijete i manji je od njega
    if (mData.size() == 2 * trenutni + 2 &&
        mData[trenutni] < mData[2 * trenutni + 1])
      iter_swap(mData.begin() + trenutni,
                mData.begin() + 2 * trenutni + 1);
  }
}

template <typename T>
void MaxHeap<T>::push(T elem){
  mData.push_back(elem);
  int pozicija = mData.size() - 1;
  int roditelj = (pozicija - 1) / 2;

  while(mData[pozicija] > mData[roditelj] && pozicija > 0) {
    iter_swap(mData.begin() + pozicija, mData.begin() + roditelj);
    pozicija = roditelj;
    roditelj = (pozicija - 1) / 2;
  }
}

template <typename T>
void MaxHeap<T>::pop(){
  //ako je prazan ne radi nista
  if (mData.size() == 0)
    return;
  //ako ima jedan element izbaci ga i ne radi nista
  if(mData.size() == 1){
    mData.pop_back();
    return;
  }
  //inace zamijeni prvi i zadnji i izbaci zadnji
  iter_swap(mData.begin(), mData.end() - 1);
  mData.pop_back();
  //usporedjivanje prvog sa djecom ako postoje
  int trenutni = 0;
  //ako ima oba djeteta
  while (mData.size() > 2 * trenutni + 2) {
    //ako je manji od barem jednog djeteta
    if (mData[trenutni] < mData[2 * trenutni + 1] ||
        mData[trenutni] < mData[2 * trenutni + 2]) {
          //ako je lijevi >= desni
          if (mData[2 * trenutni + 1] >= mData[2 * trenutni + 2]){
            iter_swap(mData.begin() + trenutni,
                      mData.begin() + 2 * trenutni + 1);
            trenutni = 2 * trenutni + 1;
          }
          //ako je desni > lijevi
          else {
            iter_swap(mData.begin() + trenutni,
                      mData.begin() + 2 * trenutni + 2);
            trenutni = 2 * trenutni + 2;
          }
    }
    //inace je na pravom mjestu
    else
      return;
  }
  //ako ima jedno dijete i manji je od njega
  if (mData.size() == 2 * trenutni + 2 &&
      mData[trenutni] < mData[2 * trenutni + 1])
    iter_swap(mData.begin() + trenutni,
              mData.begin() + 2 * trenutni + 1);
  return;
}

template <typename T>
T MaxHeap<T>::top() const{
  return mData[0];
}

template <typename T>
bool MaxHeap<T>::empty() const {
  if (mData.size() == 0)
    return true;
  return false;
}

template <typename T>
typename MaxHeap<T>::size_type MaxHeap<T>::size() const {
  return mData.size();
}

template <typename T>
void MaxHeap<T>::sort(std::vector<T> & vec){
  int velicina = size() - 1;
  while (!empty()) {
    vec[velicina] = top();
    pop();
    --velicina;
  }
}

#endif
