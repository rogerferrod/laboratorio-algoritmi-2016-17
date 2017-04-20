package edu.unito.tree;
import org.junit.*;
import java.util.ArrayList;

import static org.junit.Assert.*;
public class TreeTests {
  private Tree<String> tree;

  @Before
  public void setup() {
    tree = new Tree<>("root");
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
    tree.addTree(N,1);
    tree.addTree(M,2);
    //System.out.println(tree.toString());
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

    ArrayList<String> list = new ArrayList<>();
    list.add("figlio1");
    list.add("figlio2");
    list.add("figlio3");
    list.add("figlio4");
    assertEquals(list, tree.children());
  }

  @Test
  public void print(){
    Tree<String> B = new Tree<>("B");
    Tree<String> C = new Tree<>("C");
    Tree<String> D = new Tree<>("D");
    Tree<String> E = new Tree<>("E");
    Tree<String> F = new Tree<>("F");

    C.addTree(E);
    C.addTree(F);
    B.addTree(C);
    B.addTree(D);
    tree.addTree(B);
    System.out.println(tree.toString());
  }

}
