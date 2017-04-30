package edu.unito.tree;

import java.util.Iterator;
import java.util.Stack;
import java.util.NoSuchElementException;

public class TreeIterator<T> implements Iterator<T> {
  private Stack<Tree<T>> stack = new Stack<>();

  /* Iteratore di profondità con preordire sinistro*/
  public TreeIterator(Tree<T> tree) {
    if (tree != null) {
      stack.push(tree);
    }
  }

  public boolean hasNext() {
    return !stack.empty();
  }

  public T next() {
    if (!hasNext()) {
      throw new NoSuchElementException("Tree no such elements");
    }
    Tree<T> result = stack.pop();
    if (result.getRight() != null) {
      stack.push(result.getRight());
    }
    if (result.getLeft() != null) {
      stack.push(result.getLeft());
    }
    return result.getLabel();
  }

  public void remove() {
    throw new UnsupportedOperationException("Operation not supported");
  }

}
