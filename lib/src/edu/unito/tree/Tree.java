package edu.unito.tree;

import java.util.ArrayList;
import java.util.Iterator;

public class Tree<T> implements Iterable<T> {// implements Iterable<T> {
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

  private int numSibling(Tree<T> tree) {
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

  private int numChild(Tree<T> tree) {
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

  private ArrayList<Tree<T>> children(Tree<T> tree) {
    ArrayList<Tree<T>> list = new ArrayList<>();
    if (tree != null && tree.child != null) {
      list.add(tree.child);
      tree = tree.child;
      while (tree.sibling != null) {
        list.add(tree.sibling);
        tree = tree.sibling;
      }
    }
    return list;
  }

  public ArrayList<Tree<T>> children() {
    return children(this);
  }

  public int height(){
    return height(this);
  }

  private int height(Tree<T> tree){
    if (tree.child == null) return 0;

    tree = tree.child;
    int max = height(tree);
    while (tree.sibling != null) {
      int n = height(tree.sibling);
      if (n > max) max = n;
      tree = tree.sibling;
    }

    return max +1;
  }

  private boolean hasChild(Tree<T> tree) {
    return tree.child != null;
  }

  public boolean hasChild() {
    return hasChild(this);
  }

  private boolean hasNextSibling(Tree<T> tree) {
    return tree.sibling != null;
  }

  public boolean hasNextSibling() {
    return hasNextSibling(this);
  }

  public T getLabel() {
    return label;
  }

  public Tree<T> getParent() {
    return parent;
  }

  public Tree<T> getChild() {
    return child;
  }

  public Tree<T> getChild(int i) {
    return children().get(i);
  }

  public Tree<T> getSibling() {
    return sibling;
  }

/*  @Override
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
  }
*/

  public int degree() {
    return degree(this);
  }

  private int degree(Tree<T> tree) {
    ArrayList<Tree<T>> list = children(tree);
    int max = list.size();
    for (Tree<T> t: list) {
      int m = degree(t);
      if (m > max) max = m;
    }
    return max;
  }

  public int size() {
    return size(this);
  }

  private int size(Tree<T> tree) {
    if (tree.child == null) return 1;

    int iChild = 1;
    tree = tree.child;
    do {
      iChild += size(tree);
      tree = tree.sibling;
    } while (tree != null);

    return iChild;
  }

  public boolean isBinary() {
    return isBinary(this);
  }

  private boolean isBinary(Tree<T> tree) {
    if (numChild(tree) > 2) return false;
    if (tree.child == null) return true;

    boolean bChild = true;
    tree = tree.child;
    do {
      bChild = isBinary(tree);
      tree = tree.sibling;
    } while (tree != null && bChild);

    return bChild;
  }

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

  @Override
  public Iterator<T> iterator() {
      return new TreeIterator<T>(this);
  }

  /*@Override
  public Iterator<Tree<T>> iterator() {
    return iterator(this);
  }
  
  public Iterator<Tree<T>> iterator(Tree<T> tree) {
    return new TreeIterator<T>(tree);
  }*/

}
