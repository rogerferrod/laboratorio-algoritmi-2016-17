package edu.unito.tree;

import java.util.ArrayList;
import java.util.List;
import java.util.Comparator;
import java.util.Iterator;

public class Tree<T> implements Iterable<T> {
  private T label;
  private Tree<T> parent;
  private Tree<T> left;
  private Tree<T> right;

  /**
   * Empty constructor
   * Initialize a new tree with no label, parent, children and siblings.
   */
  public Tree() {
    this.label = null;
    this.parent = null;
    this.left = null;
    this.right = null;
  }

  /**
   * Basic constructor
   * Initialize a new tree with a label but without parent, children and siblings.
   *
   * @param label Node label
   */
  public Tree(T label) {
    this();
    this.label = label;
  }

  //getter
  public T getLabel() {
    return label;
  }

  //getter
  public Tree<T> getParent() {
    return parent;
  }

  //getter
  public Tree<T> getSibling() {
    return right;
  }

  //getter
  public Tree<T> getChild() {
    return left;
  }

  public Tree<T> getChild(int i) {
    return children().get(i);
  }

  public Tree<T> addTree(Tree<T> tree, int i) {
    if (tree == null)
      throw new IllegalArgumentException("Can't add null as child");
    if (tree == this) {
      throw new IllegalArgumentException("Can't add this as child of this");
    } else if (this.left == null) {
      if (i != 0) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      this.left = tree;
      tree.parent = this;
    } else {
      Tree<T> t = this.left;
      int count = 1;
      while (t.right != null && count < i) {
        t = t.right;
        count++;
      }
      if (count < i) throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      tree.right = t.right;
      t.right = tree;
      tree.parent = this;
    }
    return this;
  }

  /**
   * Aggiunge un albero binario di ricerca
   * che può essere null
   * @param tree
   * @param i
   * @return
   */
  public Tree<T> addBRTree(Tree<T> tree, int i) {
    if (tree == this) {
      throw new IllegalArgumentException("Can't add this as child of this");
    }
    if (i == 0) {
      this.left = tree;
    } else if (i == 1) {
      this.right = tree;
    }
    return this;
  }

  public Tree<T> addTree(Tree<T> tree) {
    return addTree(tree, numChild(this));
  }

  private int numSibling(Tree<T> tree) {
    if (tree.parent == null) return 0;
    int count = 0;
    if (tree.parent.left != null) {
      tree = tree.parent.left;
      count++;
      while (tree.right != null) {
        tree = tree.right;
        count++;
      }
    }
    return count;
  }

  public int numSibling() {
    return numSibling(this);
  }

  private int numChild(Tree<T> tree) {
    if (tree.left == null) {
      return 0;
    } else {
      return numSibling(tree.left);
    }
  }

  public int numChild() {
    return numChild(this);
  }

  public int height() {
    return height(this);
  }

  private int height(Tree<T> tree) {
    if (tree.left == null) return 0;

    tree = tree.left;
    int max = height(tree);
    while (tree.right != null) {
      int n = height(tree.right);
      if (n > max) max = n;
      tree = tree.right;
    }

    return max + 1;
  }

  public int degree() {
    return degree(this);
  }

  private int degree(Tree<T> tree) {
    ArrayList<Tree<T>> list = children(tree);
    int max = list.size();
    for (Tree<T> t : list) {
      int m = degree(t);
      if (m > max) max = m;
    }
    return max;
  }

  public int size() {
    return size(this);
  }

  private int size(Tree<T> tree) {
    if (tree.left == null) return 1;

    int iChild = 1;
    tree = tree.left;
    do {
      iChild += size(tree);
      tree = tree.right;
    } while (tree != null);

    return iChild;
  }

  private ArrayList<Tree<T>> children(Tree<T> tree) {
    ArrayList<Tree<T>> list = new ArrayList<>();
    if (tree != null && tree.left != null) {
      list.add(tree.left);
      tree = tree.left;
      while (tree.right != null) {
        list.add(tree.right);
        tree = tree.right;
      }
    }
    return list;
  }

  public ArrayList<Tree<T>> children() {
    return children(this);
  }

  public boolean isBinary() {
    return isBinary(this);
  }

  private boolean isBinary(Tree<T> tree) {
    if (numChild(tree) > 2) return false;
    if (tree.left == null) return true;

    boolean bChild = true;
    tree = tree.left;
    do {
      bChild = isBinary(tree);
      tree = tree.right;
    } while (tree != null && bChild);

    return bChild;
  }

  public ArrayList<T> getAll() {
    return getAll(this);
  }

  private ArrayList<T> getAll(Tree<T> tree) {
    Iterator<T> it = tree.iterator(tree);
    ArrayList<T> list = new ArrayList<>();
    while (it.hasNext()) {
      list.add(it.next());
    }
    return list;
  }

  public Tree<T> toBinaryRTree(Comparator<T> compare) {
    return toBinaryRTree(this, compare);
  }

  private Tree<T> toBinaryRTree(Tree<T> tree, Comparator<T> compare) {
    ArrayList<T> list = tree.getAll();
    list.sort(compare);
    return buildBRT(list, 0, list.size()-1);
  }

  private Tree<T> buildBRT(List<T> list, int begin, int end) {
    if (end - begin < 0) return null;

    Tree<T> root;
    root = new Tree<>(list.get(begin+(end - begin)/2));

    Tree<T> BRTleft = buildBRT(list, begin, begin+(end - begin)/2-1);
    root.addBRTree(BRTleft, 0);

    Tree<T> BRTright = buildBRT(list, begin+(end - begin)/2+1, end);
    root.addBRTree(BRTright, 1);

    return root;
  }

  @Override
  public String toString() {
    String s = "";
    s += "(" + label;
    if (left != null) {
      s += left.toString();
    }
    if (right != null) {
      s += "," + right.toString();
    }
    s += ")";
    return s;
  }

  @Override
  public Iterator<T> iterator() {
    return new TreeIterator<T>(this);
  }

  private Iterator<T> iterator(Tree<T> tree) {
    return new TreeIterator<T>(tree);
  }
  
  @Override @SuppressWarnings("unchecked")  /* da rimettere i wornings */
  public boolean equals(Object obj){
	return obj instanceof Tree && getAll(this).equals(getAll((Tree<T>)obj));
  }
  
  @Override
  public int hashCode() {
	return 0;
  }


}
