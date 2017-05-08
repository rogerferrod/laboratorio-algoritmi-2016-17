package edu.unito.heap;

import java.util.ArrayList;

/**
 * The class Heap is used to ...
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */
public class Heap<T> {
  private ArrayList<T> heap;

  public Heap() {
    this(0);
  }

  public Heap(int size) {
    heap = new ArrayList<>(size);
  }
}
