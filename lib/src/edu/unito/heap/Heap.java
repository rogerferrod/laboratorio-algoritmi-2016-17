package edu.unito.heap;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;

/**
 * The class Heap is used to ...
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */
public class Heap<T> {
  private ArrayList<T> heap;
  private Comparator<T> comparator;

  public Heap(Comparator<T> comparator) {
    this(comparator, 0);
  }

  public Heap(Comparator<T> comparator, int size) {
    this.comparator = comparator;
    heap = new ArrayList<>(size);
  }

  public int parent(int pos) {
    return pos == 0 ? 0 : (pos+1)/2-1;
  }

  public int left(int pos) {
    if (heap.size() > 2*pos+1)
      return 2*pos+1;
    else
      return pos;
  }

  public int right(int pos) {
    if (heap.size() > 2*pos+2)
      return 2*pos+2;
    else
      return pos;
  }

  public void add(T elem) {
    heap.add(elem);
    int p = heap.size()-1;

    while (p > 0 && comparator.compare(heap.get(p), heap.get(parent(p))) >= 0) {
      T tmp = heap.get(p);
      heap.set(p, heap.get(parent(p)));
      heap.set(parent(p), tmp);
      p = parent(p);
    }
  }

  public ArrayList<T> toList() {
    return heap;
  }

  public boolean isMaxHeap() {
    int size = heap.size();
    int child;
    for (int i=0; i<size; i++) {
      System.out.println("-i: "+i+"  left: "+left(i)+"  right: "+right(i));
      child = left(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) < 1)   //heap.get(i) <= heap.get(child)
          return false;
      }
      child = right(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) < 1)     //heap.get(i) <= heap.get(child)
          return false;
      }
    }
    return true;
  }

  public boolean isMinHeap() {
    int size = heap.size();
    int child;
    for (int i=0; i<size; i++) {
      child = left(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) > 1)   //heap.get(i) <= heap.get(child)
          return false;
      }
      child = right(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) > 1)     //heap.get(i) <= heap.get(child)
          return false;
      }
    }
    return true;
  }

  public static boolean isMaxHeap(Object[] heap, Comparator comparator) {
    return false;
  }

  @Override
  public String toString() {
    return heap.toString();
  }
}
