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
  public void testNumSiblingEmpty() {
    assertEquals(0, tree.numSibling());
  }

  @Test
  public void testNumSibling() {
    Tree<String> f1 = new Tree<>("figlio1");
    Tree<String> f2 = new Tree<>("figlio2");
    Tree<String> f3 = new Tree<>("figlio3");

    tree.addTree(f1);
    tree.addTree(f2);
    tree.addTree(f3);

    assertEquals(0, tree.numSibling());
    assertEquals(3, f1.numSibling());
    assertEquals(3, f2.numSibling());
    assertEquals(3, f3.numSibling());
  }

  @Test
  public void testNumChildEmpty() {
    assertEquals(0, tree.numChild());
  }

  @Test
  public void testNumChild() {
    Tree<String> f1 = new Tree<>("figlio1");
    Tree<String> f2 = new Tree<>("figlio2");
    Tree<String> f3 = new Tree<>("figlio3");

    tree.addTree(f1);
    tree.addTree(f2);
    tree.addTree(f3);

    assertEquals(3, tree.numChild());
    assertEquals(0, f1.numChild());
    assertEquals(0, f2.numChild());
    assertEquals(0, f3.numChild());
  }

  @Test
  public void testChildrenEmpty() {
    Tree<String> f1 = new Tree<>("figlio1");
    Tree<String> f2 = new Tree<>("figlio2");
    Tree<String> f3 = new Tree<>("figlio3");
    Tree<String> f4 = new Tree<>("figlio4");

    tree.addTree(f1);
    tree.addTree(f2);
    tree.addTree(f3);
    tree.addTree(f4);

    ArrayList<String> list = new ArrayList<>();
    list.add("figlio1");
    list.add("figlio2");
    list.add("figlio3");
    list.add("figlio4");
    assertEquals(list, tree.children());
  }

}
