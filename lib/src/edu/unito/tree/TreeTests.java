package edu.unito.tree;

import org.junit.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;


import static org.junit.Assert.*;

/**
 * A series of tests for the public method of Tree implemented with JUnit.
 *
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */
public class TreeTests {
  private Tree<String> tree;
  private ArrayList<String> list;

  private Comparator<String> comparator = new Comparator<String>() {
    @Override
    public int compare(String t1, String t2) {
      return t1.compareTo(t2);
    }
  };

  @Before
  public void setup() {
    tree = new Tree<>("A");
  }

  public void buildFixture() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");
    Tree<String> G = new Tree<>("G");
    Tree<String> H = new Tree<>("H");
    Tree<String> I = new Tree<>("I");
    Tree<String> J = new Tree<>("J");
    Tree<String> K = new Tree<>("K");
    Tree<String> L = new Tree<>("L");
    Tree<String> M = new Tree<>("M");

    tree.addTree(B);
    tree.addTree(C);
    B.addTree(D);
    B.addTree(E);
    B.addTree(F);
    E.addTree(H);
    E.addTree(I);
    C.addTree(G);
    G.addTree(J);
    G.addTree(K);
    G.addTree(L);
    G.addTree(M);

    list = new ArrayList<String>();
    list.add("A");
    list.add("B");
    list.add("D");
    list.add("E");
    list.add("H");
    list.add("I");
    list.add("F");
    list.add("C");
    list.add("G");
    list.add("J");
    list.add("K");
    list.add("L");
    list.add("M");
  }

  @Test
  public void testAddTree() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");
    Tree<String> N = new Tree<>("N");
    Tree<String> M = new Tree<>("M");

    C.addTree(E);
    C.addTree(F);
    B.addTree(C);
    B.addTree(D);
    tree.addTree(B);
    tree.addTree(N, 1);
    tree.addTree(M, 2);
  }

  @Test(expected = IllegalArgumentException.class)
  public void testAddTreeCyclic() {
    tree.addTree(tree);

    /*Tree<String> tree2 = new Tree<>("A");
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    D.addTree(B);
    C.addTree(D);
    B.addTree(C);
    tree2.addTree(B);*/
  }

  @Test
  public void testAddTreePosition() {
    Tree<String> tree2 = new Tree<>("A");
    tree2.addTree(new Tree<>("B"), 0);
    tree2.addTree(new Tree<>("C"), 1);
    tree2.addTree(new Tree<>("D"), 2);
    tree2.addTree(new Tree<>("E"), 3);

    tree.addTree(new Tree<>("B"), 0);
    tree.addTree(new Tree<>("D"), 1);
    tree.addTree(new Tree<>("E"), 2);
    tree.addTree(new Tree<>("C"), 1);

    assertEquals(tree, tree2);
  }

  @Test(expected = IndexOutOfBoundsException.class)
  public void testAddTreeWrongPosition() {
    tree.addTree(new Tree<>("A"), 1);
  }

  @Test
  public void testChildren() {
    Tree<String> c1 = new Tree<>("figlio1");
    Tree<String> c2 = new Tree<>("figlio2");
    Tree<String> c3 = new Tree<>("figlio3");
    Tree<String> c4 = new Tree<>("figlio4");

    tree.addTree(c1);
    tree.addTree(c2);
    tree.addTree(c3);
    tree.addTree(c4);

    ArrayList<Tree<String>> list = new ArrayList<>();
    list.add(c1);
    list.add(c2);
    list.add(c3);
    list.add(c4);

    assertEquals(list, tree.children());
  }

  @Test
  public void testDegree() {
    buildFixture();
    assertEquals(4, tree.degree());
    assertEquals(3, tree.getLeft().degree());
  }

  @Test
  public void testDegreeEmpty() {
    assertEquals(0, tree.degree());
  }

  @Test
  public void testHeight() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");
    Tree<String> G = new Tree<>("F");
    Tree<String> H = new Tree<>("F");
    Tree<String> I = new Tree<>("F");

    H.addTree(I);
    D.addTree(G);
    E.addTree(H);
    B.addTree(D);
    B.addTree(E);
    C.addTree(F);
    tree.addTree(C);
    tree.addTree(B);

    assertEquals(4, tree.height());
    assertEquals(2, E.height());
    assertEquals(0, G.height());
  }

  @Test
  public void testSize() {
    buildFixture();
    assertEquals(13, tree.size());
    assertEquals(6, tree.getLeft().size());
  }

  @Test
  public void testIsBinary() {
    buildFixture();
    assertEquals(false, tree.isBinary());
    //aggiungerne un altro...
  }

  @Test
  public void testIterator() {
    buildFixture();
    Iterator<String> it = tree.iterator();
    ArrayList<String> result = new ArrayList<>();
    while (it.hasNext()) {
      result.add(it.next());
    }
    assertEquals(list, result);
  }

  @Test
  public void testGetAll() {
    buildFixture();
    assertEquals(list, tree.getAll());
  }

  @Test
  public void testSortedGetAll() {
    buildFixture();

    ArrayList<String> t = tree.getAll();

    list.sort(comparator);
    t.sort(comparator);

    assertEquals(list, t);
  }

  @Test
  public void testToBinarySearchTree() {
    buildFixture();

    Tree<String> A = new Tree<>("A");
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");
    Tree<String> G = new Tree<>("G");
    Tree<String> H = new Tree<>("H");
    Tree<String> I = new Tree<>("I");
    Tree<String> J = new Tree<>("J");
    Tree<String> K = new Tree<>("K");
    Tree<String> L = new Tree<>("L");
    Tree<String> M = new Tree<>("M");

    Tree<String> brt = G;
    brt.addTree(D, 0);
    brt.addTree(K, 1);

    D.addTree(B, 0);
    D.addTree(F, 1);

    B.addTree(A, 0);
    B.addTree(C, 1);

    F.addTree(E, 0);

    K.addTree(I, 0);
    K.addTree(M, 1);

    I.addTree(H, 0);
    I.addTree(J, 1);

    M.addTree(L, 0);

    assertEquals(brt, tree.toBinarySearchTree(comparator));
  }

  @Test
  public void testEquals(){
    Tree<String> tree1 = new Tree<>("a");
    Tree<String> tree2 = new Tree<>("a");
    Tree<String> b1 = new Tree<>("b");
    Tree<String> b2 = new Tree<>("b");
    Tree<String> c1 = new Tree<>("c");
    Tree<String> c2 = new Tree<>("c");

    b1.addTree(c1);
    tree1.addTree(b1);

    tree2.addTree(b2);
    tree2.addTree(c2);

    assertNotEquals(tree1, tree2);
  }

  @Test
  public void testToString() {
    buildFixture();
    assertEquals("(A(B(D,(E(H,(I)),(F))),(C(G(J,(K,(L,(M))))))))", tree.toString());
  }

  @Test
  public void testFindLabelNull() {
    assertEquals(null, tree.find((String)null));
  }

  @Test
  public void testFindLabel() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");

    tree.addTree(B);
    tree.addTree(C);

    B.addTree(D);
    B.addTree(E);

    C.addTree(F);

    assertEquals(tree, tree.find("A"));
    assertEquals(B, tree.find("B"));
    assertEquals(C, tree.find("C"));
    assertEquals(D, tree.find("D"));
    assertEquals(E, tree.find("E"));
    assertEquals(F, tree.find("F"));
  }

  @Test
  public void testFindLabelNotFound() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");

    tree.addTree(B);
    tree.addTree(C);

    B.addTree(D);
    B.addTree(E);

    C.addTree(F);

    assertEquals(null, tree.find("FF"));
  }
}