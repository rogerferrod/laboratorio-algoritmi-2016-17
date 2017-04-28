package edu.unito.tree;

import org.junit.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;


import static org.junit.Assert.*;

public class TreeTests {
  private Tree<String> tree;
  private ArrayList<String> list;

  @Before
  public void setup() {
    tree = new Tree<>("root");
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
    list.add("root");
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
    //System.out.println(tree.toString());
  }

  @Test(expected = IllegalArgumentException.class)
  public void testAddTreeCyclic() {
    tree.addTree(tree);
  }

  @Test(expected = IndexOutOfBoundsException.class)
  public void testAddTreeWrongPosition() {
    tree.addTree(new Tree<>("A"), 1);
  }

  @Test
  public void testNumSiblingEmpty() {
    assertEquals(0, tree.numSibling());
  }

  @Test
  public void testNumSibling() {
    Tree<String> c1 = new Tree<>("figlio1");
    Tree<String> c2 = new Tree<>("figlio2");
    Tree<String> c3 = new Tree<>("figlio3");

    tree.addTree(c1);
    tree.addTree(c2);
    tree.addTree(c3);

    assertEquals(0, tree.numSibling());
    assertEquals(3, c1.numSibling());
    assertEquals(3, c2.numSibling());
    assertEquals(3, c3.numSibling());
  }

  @Test
  public void testNumChildEmpty() {
    assertEquals(0, tree.numChild());
  }

  @Test
  public void testNumChild() {
    Tree<String> c1 = new Tree<>("figlio1");
    Tree<String> c2 = new Tree<>("figlio2");
    Tree<String> c3 = new Tree<>("figlio3");
    Tree<String> c4 = new Tree<>("figlio4");

    tree.addTree(c1);
    tree.addTree(c2);
    c3.addTree(c4);
    tree.addTree(c3);


    assertEquals(3, tree.numChild());
    assertEquals(0, c1.numChild());
    assertEquals(0, c2.numChild());
    assertEquals(1, c3.numChild());
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
    assertEquals(3, tree.getChild().degree());
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
    assertEquals(6, tree.getChild().size());
  }

  @Test
  public void testIsBinary() {
    buildFixture();
    assertEquals(false, tree.isBinary());
    assertEquals(true, tree.getChild().getChild(1).isBinary());
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


  /*@Test
  public void testGetAllSimple() {
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");

    tree.addTree(B);
    tree.addTree(C);

    ArrayList<Tree<String>> list = new ArrayList<>();
    list.add(tree);
    list.add(B);
    list.add(C);

    ArrayList<Tree<String>> t = tree.getAll();

    assertEquals(list, t);
  }*/

  @Test
  public void testSortedGetAll() {
    buildFixture();

    ArrayList<String> t = tree.getAll();

    Comparator<String> comparator = new Comparator<String>() {
      @Override
      public int compare(String t1, String t2) {
        return t1.compareTo(t2);
      }
    };

    list.sort(comparator);
    t.sort(comparator);

    assertEquals(list, t);
  }

  @Test
  public void testToString() {
    buildFixture();
    assertEquals("(root(B(D,(E(H,(I)),(F))),(C(G(J,(K,(L,(M))))))))", tree.toString());
    //System.out.println(tree.toString());
  }

}