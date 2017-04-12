package edu.unito.tree;

import java.util.ArrayList;
public class Tree {
  String label;
  Tree parent;
  Tree child;
  Tree sibling;

  public Tree() {
    this.label = null;
    this.parent = null;
    this.child = null;
    this.sibling= null;
  }
  public Tree(String label) {
    this();
    this.label = label;
  }
  public Tree addTree(Tree tree, int i) {
    if (this.child == null) {
      if (i != 0) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      this.child = tree;
    } else {
      Tree t = this.child;
      int count = 1;
      while (t.sibling != null && count < i) {
        t = t.sibling;
        count++;
      }
      if (count < i) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      tree.sibling = t.sibling;
      t.sibling = tree;
    }
    return this;
  }
  public Tree addTree(Tree tree) {
    return addTree(tree, numSibling(tree));
  }
  public int numSibling(Tree tree) {
    int count = 0;
    if (tree.child != null) {
      tree = tree.child;
      while (tree.sibling != null) {
        tree = tree.sibling;
        count++;
      }
    }
    return count;
  }
  public int numChild(Tree tree) {
    int count = 0;
    if (tree.child != null) {
      count = 1 + numSibling(tree.child);
    }
    return count;
  }
  public ArrayList<Tree> children() {
    return children(this);
  }
  public ArrayList<Tree> children(Tree tree) {
    ArrayList<Tree> list = new ArrayList<>();
    if (tree.child != null) {
      list.add(tree.child);
      tree = tree.child;
      while (tree.sibling != null) {
        list.add(tree.sibling);
        tree = tree.sibling;
      }
    }

    return list;
  }
}
