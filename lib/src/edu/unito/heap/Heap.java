package edu.unito.heap;

import java.util.ArrayList;
import java.util.Comparator;

/**
 * The Heap class
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
      //System.out.println("-i: "+i+"  left: "+left(i)+"  right: "+right(i));
      child = left(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) < 1) {   //heap.get(i) <= heap.get(child)
          return false;
        }
      }
      child = right(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) < 1) {     //heap.get(i) <= heap.get(child)
          return false;
        }
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
        if (comparator.compare(heap.get(i), heap.get(child)) > 1) {   //heap.get(i) <= heap.get(child)
          return false;
        }
      }
      child = right(i);
      if (child != i) {
        if (comparator.compare(heap.get(i), heap.get(child)) > 1) {     //heap.get(i) <= heap.get(child)
          return false;
        }
      }
    }
    return true;
  }

  @Override
  public String toString() {
    return heap.toString();
  }

  /**
   * Check if heap is a maxHeap.
   *
   * Iterative version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a maxHeap
   */
  public static boolean isMaxHeap(Object[] heap, Comparator<Object> comparator) {
    int size = heap.length;
    int child;
    for (int i=0; i<size; i++) {
      System.out.println("-i: "+i+"  left: "+left(i, size)+"  right: "+right(i, size));
      child = left(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) < 0) {   //heap[i] <= heap[child]
          return false;
        }
      }
      child = right(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) < 0) {   //heap[i] <= heap[child]
          return false;
        }
      }
    }
    return true;
  }

  /**
   * Check if heap is a maxHeap.
   *
   * Recursive version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a maxHeap
   */
  public static boolean isMaxHeap(Object[] heap, Comparator<Object> comparator, int pos) {
    int size = heap.length;
    int left, right;
    System.out.println("-i: "+pos+"  left: "+left(pos, size)+"  right: "+right(pos, size));

    left = left(pos, size);
    if (left != pos) {
      if (comparator.compare(heap[pos], heap[left]) < 0) {   //heap[i] <= heap[child]
        return false;
      }
    }
    right = right(pos, size);
    if (right != pos) {
      if (comparator.compare(heap[pos], heap[right]) < 0) {   //heap[i] <= heap[child]
        return false;
      }
    }
    return (left == pos || isMaxHeap(heap, comparator, left)) && (right == pos || isMaxHeap(heap, comparator, right));
    //return (left != pos ? isMaxHeap(heap, comparator, left) : true) && (right != pos ? isMaxHeap(heap, comparator, right) : true);
  }

  /**
   * Check if heap is a maxHeap.
   *
   * Iterative version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a maxHeap
   */
  public static boolean isMinHeap(Object[] heap, Comparator<Object> comparator) {
    int size = heap.length;
    int child;
    for (int i=0; i<size; i++) {
      System.out.println("-i: "+i+"  left: "+left(i, size)+"  right: "+right(i, size));
      child = left(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) > 0) {   //heap[i] >= heap[child]
          return false;
        }
      }
      child = right(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) > 0) {   //heap[i] >= heap[child]
          return false;
        }
      }
    }
    return true;
  }

  /**
   * Check if heap is a maxHeap.
   *
   * Recursive version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a maxHeap
   */
  public static boolean isMinHeap(Object[] heap, Comparator<Object> comparator, int pos) {
    int size = heap.length;
    int left, right;
    System.out.println("-i: "+pos+"  left: "+left(pos, size)+"  right: "+right(pos, size));

    left = left(pos, size);
    if (left != pos) {
      if (comparator.compare(heap[pos], heap[left]) > 0) {   //heap[i] >= heap[child]
        return false;
      }
    }
    right = right(pos, size);
    if (right != pos) {
      if (comparator.compare(heap[pos], heap[right]) > 0) {   //heap[i] >= heap[child]
        return false;
      }
    }
    return (left == pos || isMinHeap(heap, comparator, left)) && (right == pos || isMinHeap(heap, comparator, right));
    //return (left != pos ? isMinHeap(heap, comparator, left) : true) && (right != pos ? isMinHeap(heap, comparator, right) : true);
  }

  private static int left(int pos, int size) {
    if (size > 2*pos+1)
      return 2*pos+1;
    else
      return pos;
  }

  private static int right(int pos, int size) {
    if (size > 2*pos+2)
      return 2*pos+2;
    else
      return pos;
  }
}
