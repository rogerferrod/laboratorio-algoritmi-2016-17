package edu.unito.tree;

import org.junit.*;
import static org.junit.Assert.*;
import java.util.ArrayList;
public class TreeTests {
  Tree tree;
  @Before
  public void setup() {
    tree = new Tree("root");
  }

  @Test
  public void testChildren() {
    tree.addTree(new Tree("figlio1"));
    tree.addTree(new Tree("figlio2"));
    tree.addTree(new Tree("figlio3"));
    ArrayList<String> list = tree.children();

    ArrayList<String> test = new ArrayList<>();
    test.add("figlio1");
    test.add("figlio2");
    test.add("figlio3");

    assertEquals(test, list);
  }
}
