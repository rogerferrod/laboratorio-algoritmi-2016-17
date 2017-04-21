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

  public int numSibling() {
    return numSibling(this);
  }

  public int numChild(Tree<T> tree) {
    if (tree.child == null) {
      return 0;
    } else {
      return numSibling(tree.child);
    }
  }

  public int numChild() {
    return numChild(this);
  }

  public Tree<T> addTree(Tree<T> tree, int i) {
    if (tree == this) {
      throw new IllegalArgumentException("Can't add this as child of this");
    } else if (this.child == null) {
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

  public Tree<T> addTree(Tree<T> tree) {
    return addTree(tree, numChild(this));
  }

  public ArrayList<T> children(Tree<T> tree) {
    ArrayList<T> list = new ArrayList<>();
    if (tree != null && tree.child != null) {
      list.add(tree.child.label);
      tree = tree.child;
      while (tree.sibling != null) {
        list.add(tree.sibling.label);
        tree = tree.sibling;
      }
    }
    return list;
  }

  public ArrayList<T> children() {
    return children(this);
  }

  /*@Override
  public String toString() {
    String s = "L: "+label.toString()+" - ";
    s += "P: ";
    if (parent == null) {
      s += "null";
    } else {
      s += parent.label.toString();
    }
    s += " - C: ";
    if (child == null) {
      s += "null";
    } else {
      s += child.label.toString();
    }
    s += " - S: ";
    if (sibling == null) {
      s += "null";
    } else {
      s += sibling.label.toString();
    }

    return s;
  }*/

  @Override
  public String toString() {
    String s = "";
    s += "(" + label;
    if(child != null){
      s += child.toString();
    }
    if(sibling != null){
      s += "," + sibling.toString();
    }
    s += ")";
    return s;
  }
}
