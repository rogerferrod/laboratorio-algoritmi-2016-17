package edu.unito.heap;

import org.junit.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;


import static org.junit.Assert.*;

/**
 * A series of tests for the public method of Heap
 * implemented with JUnit
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */

public class HeapTests {
  private Heap<Integer> heap;

  private Comparator<Integer> comparator = new Comparator<Integer>() {
    @Override
    public int compare(Integer t1, Integer t2) {
      return t1.compareTo(t2);
    }
  };

  @Before
  public void setup() {
    heap = new Heap<>(comparator);
  }

  public void buildFixture() {
    for (int i = 1; i < 8; i++)
      heap.add(i);
  }

  @Test
  public void testAdd() {
    for (int i=1; i<8; i++) {
      heap.add(i);
    }
    ArrayList<Integer> list = new ArrayList<>();
    list.add(7);
    list.add(4);
    list.add(6);
    list.add(1);
    list.add(3);
    list.add(2);
    list.add(5);

    assertEquals(list, heap.toList());
  }

  @Test
  public void testIsMaxHeap() {
    for (int i=1; i<8; i++) {
      heap.add(i);
    }
    assertEquals(true, heap.isMaxHeap());
  }
}