package edu.unito.tree;

import java.util.ArrayList;

public class Tree<T> {
  private T label;
  private Tree<T> parent;
  private Tree<T> child;
  private Tree<T> sibling;

  public Tree() {
    this.label = null;
    this.parent = null;
    this.child = null;
    this.sibling= null;
  }
  public Tree(T label) {
    this();
    this.label = label;
  }

  public Tree<T> addTree(Tree<T> tree) {
    return addTree(tree, numSibling(tree));
  }
  public Tree<T> addTree(Tree<T> tree, int i) {
    if (this.child == null) {
      if (i != 0) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      this.child = tree;
      tree.parent = this;
    } else {
      Tree<T> t = this.child;
      int count = 1;
      while (t.sibling != null && count < i) {
        t = t.sibling;
        count++;
      }
      if (count < i) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      tree.sibling = t.sibling;
      t.sibling = tree;
      tree.parent = this;
    }
    return this;
  }

  public int numSibling() {
    return numSibling(this);
  }
  public int numSibling(Tree<T> tree) {
    if (tree.parent == null) return 0;
    int count = 0;
    if (tree.parent.child != null) {
      tree = tree.parent.child;
      count++;
      while (tree.sibling != null) {
        tree = tree.sibling;
        count++;
      }
    }
    return count;
  }

  public int numChild() {
    return numChild(this);
  }
  public int numChild(Tree<T> tree) {
    if (tree.child == null) {
      return 0;
    } else {
      return numSibling(tree.child);
    }
  }

  public ArrayList<T> children() {
    return children(this);
  }
  public ArrayList<T> children(Tree<T> tree) {
    ArrayList<T> list = new ArrayList<>();
    if (tree != null && tree.child != null) {
      list.add(tree.child.label);
      tree = tree.child;
      while (tree.child != null) {
        list.add(tree.child.label);
        tree = tree.child;
      }
    }
    return list;
  }

}
