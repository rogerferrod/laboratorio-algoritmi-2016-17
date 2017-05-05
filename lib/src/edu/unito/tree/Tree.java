package edu.unito.tree;

import java.util.ArrayList;
import java.util.List;
import java.util.Comparator;
import java.util.Iterator;

/**
 * The class Tree is used to collect all of the tree types, and acts as a generic k-Tree
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */

public class Tree<T> implements Iterable<T> {
  private T label;
  private Tree<T> parent;
  private Tree<T> left;
  private Tree<T> right;


  /**
   * Empty constructor
   * <p>
   * Create a new Tree with no label and children
   */
  public Tree() {
    this.label = null;
    this.parent = null;
    this.left = null;
    this.right = null;
  }

  /**
   * Basic constructor
   * Initialize a new tree with a given label
   *
   * @param  label the label of the node
   */
  public Tree(T label) {
    this();
    this.label = label;
    this.parent = null;
    this.left = null;
    this.right = null;
  }

  /**
   * Return the label of this node
   *
   * @return  label
   */
  public T getLabel() {
    return label;
  }

  /**
   * Return the left subtree of this node if exist, otherwise null
   *
   * @return  left subtree
   */
  public Tree<T> getLeft(){
    return left;
  }

  /**
   * Return the right subtree of this node if exist, otherwise null
   *
   * @return  right subtree
   */
  public Tree<T> getRight(){
    return right;
  }

  /**
   * Return the parent of this node if exist, otherwise null
   *
   * @return  parent
   */
  public Tree<T> getParent() {
    return parent;
  }

  /**
   * Add a subtree to the current node as child and return the new tree
   * <p>
   * The parameter cannot be null and must be different to the node itself
   * actually the method cannot prevent the creation of cycle in the tree
   *
   * @param   tree the new subtree
   * @return  the new tree with changes
   */
  public Tree<T> addTree(Tree<T> tree) {
  return addTree(tree, numChild(this));
  }

  /**
   * Add a subtree to the current node as child number i and return the new tree
   * <p>
   * The parameter cannot be null and must be different to the node itself
   * actually the method cannot prevent the creation of cycle in the tree
   *
   * @param    tree the new subtree
   * @param    i the index position at which to add the new subtree
   * @return    the new tree with changes
   */
  public Tree<T> addTree(Tree<T> tree, int i) {
    if (tree == null)
      throw new IllegalArgumentException("Cannot add empty subtree");

    if (tree == this) /* in realtà è più complesso di cosi ma vabbe */
      throw new IllegalArgumentException("Cannot create a cycle");

    if (this.left == null) {
      if (i != 0){
        throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      }
      this.left = tree;
      tree.parent = this;
    }
    else {
      Tree<T> t = this.left;
      int count = 1;
      while (t.right != null && count < i) {
        t = t.right;
        count++;
      }
      if (count < i) {
        throw new IndexOutOfBoundsException("Child index is too big for the list of sons");
      }
      tree.right = t.right;
      t.right = tree;
      tree.parent = this;
    }
    return this;
  }


  /**
   * Finds the height of the tree
   *
   * @return  the height
   */
  public int height() {
    return height(this);
  }

  /**
   * Finds the maximum degree of the tree
   *
   * @return  the maximum degree
   */
  public int degree() {
    return degree(this);
  }

  /**
   * Returns the number of nodes the tree contains
   *
   * @return  the size
   */
  public int size() {
    return size(this);
  }

  /**
   * Returns a list of children for the current node
   *
   * @return  the children of the node
   */
  public ArrayList<Tree<T>> children() {
    return children(this);
  }

  /**
   * Return true is the tree is a binary tree, false otherwise
   *
   * @return true if the tree is a binary tree
   */
  public boolean isBinary() {
    return isBinary(this);
  }

  /**
   * Returns the tree as a list
   *
   * @return  list of all elements in the tree
   */
  public ArrayList<T> getAll() {
    return getAll(this);
  }

  /**
   * Returns the Binary Search Tree rappresentation of the tree
   *
   * @param compare the Comparator used to order the tree
   * @return  the binary search tree
   */
  public Tree<T> toBinarySearchTree(Comparator<T> compare) {
    return toBinarySearchTree(this, compare);
  }

  /**
   * Converts tree to string in Penn Treebank format.
   *
   * @return  the tree as string
   */
  @Override
  public String toString() {
    String str = "";
    str += "(" + label.toString();
    if (left != null) {
      str += left.toString();
    }
    if (right != null) {
      str += "," + right.toString();
    }
    str += ")";
    return str;
  }

  /**
   * Returns an iterator over all the nodes of the tree with left preorder
   *
   * @return  the iterator over the nodes of the tree
   */
  @Override
  public Iterator<T> iterator() {
    return new TreeIterator<T>(this);
  }

  /**
   * Implements equality for Tree's.
   * <p> Two Tree objects are equal if they have equal value()s, the same number of children, and their children are pairwise equal.
   *
   * @param obj the tree to compare with
   * @return  true is the two trees are equal, false otherwise
   */
  @Override
  @SuppressWarnings("unchecked")  /* da rimettere i warnings */
  public boolean equals(Object obj){
    boolean equal = true;
    if(obj instanceof Tree){ /* x instanceof y is false if x is null*/
      Tree<T> tree = (Tree<T>)obj;
      equal = label.equals(tree.getLabel());
      if (left != null) {
        equal &= left.equals(tree.getLeft());
      }
      if (right != null) {
        equal &= right.equals(tree.getRight());
      }
      return equal;
    }
    return false;
  }

  /**
   * Implements a hashCode for Tree's
   *
   * @return  the hash code
   */
  @Override
  public int hashCode() {
    throw new UnsupportedOperationException("Operation not supported");
  }


  /**
   * returns the next sibling of the node
   *
   * @return    the right sibling
   */
  private Tree<T> getSibling() {
    return right;
  }

  /**
   * returns the child of the node
   *
   * @return    the child
   */
  private Tree<T> getChild() {
    return left;
  }

  /**
   * returns the child in the position i
   *
   * @param i index position of the child
   * @return    the child
   */
  private Tree<T> getChild(int i) {
    return children().get(i);
  }

  /**
   * finds the number of siblings of the tree
   *
   * @param tree the tree
   * @return    the number of siblings
   */
  private int numSibling(Tree<T> tree) {
    if (tree.parent == null)
      return 0;

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

  /**
   * finds the number of siblings of the current node
   *
   * @return    the number of siblings
   */
  private int numSibling() {
    return numSibling(this);
  }

  /**
   * finds the number of children of the tree
   *
   * @param tree the tree
   * @return    the number of children
   */
  private int numChild(Tree<T> tree) {
    if (tree.left == null)
      return 0;

    return numSibling(tree.left);

  }

  /**
   * finds the number of siblings of the current node
   *
   * @return    the number of children
   */
  private int numChild() {
    return numChild(this);
  }

  /**
   * finds the height of the tree
   *
   * @param tree the tree
   * @return    the height
   */
  private int height(Tree<T> tree) {
    if (tree.left == null)
      return 0;

    tree = tree.left;
    int max = height(tree);

    while (tree.right != null) {
      int n = height(tree.right);
      if (n > max){
        max = n;
      }
      tree = tree.right;
    }
    return max + 1;
  }

  /**
   * finds the degree of the tree
   *
   * @param tree the tree
   * @return    the degree
   */
  private int degree(Tree<T> tree) {
    ArrayList<Tree<T>> list = children(tree);
    int max = list.size();

    for (Tree<T> t : list) {
      int m = degree(t);
      if (m > max){
        max = m;
      }
    }
    return max;
  }

  /**
   * finds the size of the tree
   *
   * @param tree the tree
   * @return    the size
   */
  private int size(Tree<T> tree) {
    if (tree.left == null)
      return 1;

    int iChild = 1;
    tree = tree.left;

    do {
      iChild += size(tree);
      tree = tree.right;
    } while (tree != null);

    return iChild;
  }

  /**
   * Returns a list of children for the tree
   *
   *  @param tree the tree
   * @return  the children of the node
   */
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

  /**
   * Return true is the tree is a binary tree, false otherwise
   *
   * @param tree the tree
   * @return true if the tree is a binary tree
   */
  private boolean isBinary(Tree<T> tree) {
    if (numChild(tree) > 2)
      return false;
    if (tree.left == null)
      return true;

    boolean bChild = true;
    tree = tree.left;
    do {
      bChild = isBinary(tree);
      tree = tree.right;
    } while (tree != null && bChild);

    return bChild;
  }

  /**
   * Returns the tree as a list
   *
   * @param tree the tree
   * @return  list of all elements in the tree
   */
  private ArrayList<T> getAll(Tree<T> tree) {
    Iterator<T> it = tree.iterator(tree);
    ArrayList<T> list = new ArrayList<>();
    while (it.hasNext()) {
      list.add(it.next());
    }
    return list;
  }

  /**
   * Returns the Binary Search Tree rappresentation of the tree
   *
   * @param tree the tree
   * @param compare the Comparator used to order the tree
   * @return  the binary search tree
   */
  private Tree<T> toBinarySearchTree(Tree<T> tree, Comparator<T> compare) {
    ArrayList<T> list = tree.getAll();
    list.sort(compare);
    return buildBST(list);
  }

  /**
   * Converts a sorted list into a Binary Search Tree
   * begin and end are the index of sublist considered in the recursive call
   *
   * @param list the sorted list
   * //@param begin index of the first element to be considered in the list
   * //@param end index of the last element to be considered in the list
   * @return  the binary search tree
   */
  private Tree<T> buildBST(List<T> list) {
    if (list.size() == 0)
      return null;

    Tree<T> root;
    root = new Tree<>(list.get(list.size()/2));


    Tree<T> BSTLeft = buildBST(list.subList(0, list.size()/2));
    if (BSTLeft != null)
      root.addTree(BSTLeft);

    Tree<T> BSTRight = buildBST(list.subList(list.size()/2+1, list.size()));
    if (BSTRight != null)
      root.addTree(BSTRight);

    return root;
  }

  /**
   * Returns an iterator for the tree
   *
   * @param tree the tree
   * @return  the iterator over the nodes of the tree
   */
  private Iterator<T> iterator(Tree<T> tree) {
    return new TreeIterator<T>(tree);
  }

}

