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
  private Comparator<Object> comparatorObjects = new Comparator<Object>() {
    @Override
    public int compare(Object t1, Object t2) {
      Integer i1 = (Integer)t1;
      Integer i2 = (Integer)t2;
      return i1.compareTo(i2);
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
    buildFixture();

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
    buildFixture();

    assertEquals(true, heap.isMaxHeap());
  }

  @Test
  public void testStaticIsMaxHeap() {
    System.out.println("iter");
    assertEquals(true, Heap.isMaxHeap(new Integer[]{4,3,2,1,}, comparatorObjects));

    buildFixture();
    System.out.println(heap);
    assertEquals(true, Heap.isMaxHeap(heap.toList().toArray(), comparatorObjects));
  }

  @Test
  public void testStaticIsMaxHeapRecursive() {
    System.out.println("ric");
    assertEquals(true, Heap.isMaxHeap(new Integer[]{4,3,2,1,}, comparatorObjects, 0));

    buildFixture();
    System.out.println(heap);
    assertEquals(true, Heap.isMaxHeap(heap.toList().toArray(), comparatorObjects, 0));
  }
}