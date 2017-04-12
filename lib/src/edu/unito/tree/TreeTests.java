package edu.unito.tree;

import org.junit.*;
public class TreeTests {
  Tree tree;
  @Before
  public void setup() {
    tree = new Tree("albero");
  }

  @Test
  public void testChildren() {
    tree.addTree(new Tree("figlio1"));
    tree.addTree(new Tree("figlio2"));
    tree.addTree(new Tree("figlio3"));
    tree.children();
  }
}
