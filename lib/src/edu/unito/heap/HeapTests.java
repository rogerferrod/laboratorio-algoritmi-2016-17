package edu.unito.heap;

import org.junit.*;

import java.util.ArrayList;
import java.util.Comparator;


import static org.junit.Assert.*;

/**
 * A series of tests for the public method of Heap
 * implemented with JUnit
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */

public class HeapTests {

  private Comparator<Object> comparatorObjects = new Comparator<Object>() {
    @Override
    public int compare(Object t1, Object t2) {
      Integer i1 = (Integer)t1;
      Integer i2 = (Integer)t2;
      return i1.compareTo(i2);
    }
  };

  @Test
  public void testStaticIsMaxHeapIterative() {
    assertEquals(true, Heap.isMaxHeap(new Integer[]{4,3,2,1}, comparatorObjects));
  }

  @Test(expected = NullPointerException.class)
  public void testStaticIsMaxHeapIterativeNull() {
    assertEquals(true, Heap.isMaxHeap(null, comparatorObjects));
  }

  @Test(expected = IllegalArgumentException.class)
  public void testStaticIsMaxHeapIterativeEmpty() {
    assertEquals(true, Heap.isMaxHeap(new Integer[]{}, comparatorObjects));
  }

  @Test
  public void testStaticIsMaxHeapRecursive() {
    assertEquals(true, Heap.isMaxHeap(new Integer[]{4,3,2,1}, comparatorObjects, 0));
  }

  @Test
  public void testStaticIsMinHeapIterative() {
    assertEquals(true, Heap.isMinHeap(new Integer[]{1,3,5,6,8,7}, comparatorObjects));
  }

  @Test
  public void testStaticIsMinHeapRecursive() {
    assertEquals(true, Heap.isMinHeap(new Integer[]{1,3,5,6,8,7}, comparatorObjects, 0));
  }
}