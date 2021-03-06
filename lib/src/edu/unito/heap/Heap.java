package edu.unito.heap;

import java.util.Comparator;

/**
 * The Heap class
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */
class Heap<T> {
  /**
   * Check if heap is a maxHeap.
   *
   * Iterative version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a maxHeap
   */
  static boolean isMaxHeap(Object[] heap, Comparator<Object> comparator) {
    if (heap == null) throw new NullPointerException("heap mustn't be null.");
    if (comparator == null) throw new NullPointerException("Comparator mustn't be null.");
    int size = heap.length;
    if (size == 0) throw new IllegalArgumentException("Empty heap is neither max nor min");
    int child;

    for (int i=0; i<size; ++i) {
      child = left(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) <= 0) {   //heap[i] <= heap[child]
          return false;
        }
      }
      child = right(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) <= 0) {   //heap[i] <= heap[child]
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
  static boolean isMaxHeap(Object[] heap, Comparator<Object> comparator, int pos) {
    if (heap == null) throw new NullPointerException("heap mustn't be null.");
    if (comparator == null) throw new NullPointerException("comparator mustn't be null.");
    int size = heap.length;
    int left, right;
    if (size == 0) throw new IllegalArgumentException("Empty heap is neither max nor min");

    left = left(pos, size);
    if (left != pos) {
      if (comparator.compare(heap[pos], heap[left]) <= 0) {   //heap[i] <= heap[child]
        return false;
      }
    }
    right = right(pos, size);
    if (right != pos) {
      if (comparator.compare(heap[pos], heap[right]) <= 0) {   //heap[i] <= heap[child]
        return false;
      }
    }
    return (left == pos || isMaxHeap(heap, comparator, left)) && (right == pos || isMaxHeap(heap, comparator, right));
    //return (left != pos ? isMaxHeap(heap, comparator, left) : true) && (right != pos ? isMaxHeap(heap, comparator, right) : true);
  }

  /**
   * Check if heap is a minHeap.
   *
   * Iterative version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a minHeap.
   */
  static boolean isMinHeap(Object[] heap, Comparator<Object> comparator) {
    if (heap == null) throw new NullPointerException("heap mustn't be null.");
    if (comparator == null) throw new NullPointerException("comparator mustn't be null.");
    int size = heap.length;
    int child;
    if (size == 0) throw new IllegalArgumentException("Empty heap is neither max nor min");

    for (int i=0; i<size; i++) {
      child = left(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) >= 0) {   //heap[i] >= heap[child]
          return false;
        }
      }
      child = right(i, size);
      if (child != i) {
        if (comparator.compare(heap[i], heap[child]) >= 0) {   //heap[i] >= heap[child]
          return false;
        }
      }
    }
    return true;
  }

  /**
   * Check if heap is a minHeap.
   *
   * Recursive version.
   *
   * @param heap Object's array representing the heap.
   * @param comparator Method to compare two heap elements.
   * @return true if <code>heap</code> is a minHeap.
   */
  static boolean isMinHeap(Object[] heap, Comparator<Object> comparator, int pos) {
    if (heap == null) throw new NullPointerException("heap mustn't be null.");
    if (comparator == null) throw new NullPointerException("comparator mustn't be null.");
    int size = heap.length;
    int left, right;
    if (size == 0) throw new IllegalArgumentException("Empty heap is neither max nor min");

    left = left(pos, size);
    if (left != pos) {
      if (comparator.compare(heap[pos], heap[left]) >= 0) {   //heap[i] >= heap[child]
        return false;
      }
    }
    right = right(pos, size);
    if (right != pos) {
      if (comparator.compare(heap[pos], heap[right]) >= 0) {   //heap[i] >= heap[child]
        return false;
      }
    }
    return (left == pos || isMinHeap(heap, comparator, left)) && (right == pos || isMinHeap(heap, comparator, right));
    //return (left != pos ? isMinHeap(heap, comparator, left) : true) && (right != pos ? isMinHeap(heap, comparator, right) : true);
  }

  /**
   * Returns the position of the left child of the node in position <code>pos</code>.
   *
   * @param pos The node position.
   * @param size The size of the heap.
   * @return The left child position or <code>pos</code> if the node haven't a left child.
   */
  private static int left(int pos, int size) {
    if (size > 2*pos+1)
      return 2*pos+1;
    else
      return pos;
  }

  /**
   * Returns the position of the right child of the node in position <code>pos</code>.
   *
   * @param pos THe node position.
   * @param size The size of the heap.
   * @return The right child position or <code>pos</code> if the node haven't a right child.
   */
  private static int right(int pos, int size) {
    if (size > 2*pos+2)
      return 2*pos+2;
    else
      return pos;
  }
}
