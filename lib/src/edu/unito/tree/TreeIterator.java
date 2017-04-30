package edu.unito.tree;

import java.util.Iterator;
import java.util.Stack;
import java.util.NoSuchElementException;


/**
 * The implementation of an Iterator for the Tree
 * the traversing of the Tree is Depth-first search with left preorder
 * @author Riccardo Ferrero Regis
 * @author Roger Ferrod
 * @author Luca Chironna
 */

public class TreeIterator<T> implements Iterator<T> {
  private Stack<Tree<T>> stack = new Stack<>();

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
