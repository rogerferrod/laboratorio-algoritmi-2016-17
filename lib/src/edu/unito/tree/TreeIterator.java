package edu.unito.tree;

import java.util.Iterator;
import java.util.Stack;
import java.util.NoSuchElementException;

public class TreeIterator<T> implements Iterator<T> {

    /*private Tree<T> current;

    public TreeIterator(Tree<T> tree) {
        this.current = tree;
    }

    public boolean hasNext() {
        return current.getChild() != null || current.getSibling() != null;
    }

    public T next() {
    	Tree<T> tNext;
        if(this.hasNext()) {
            if(current.getChild() != null){
            	tNext = current.getChild();ù
            	current = current.next();
            }
        }
        throw new NoSuchElementException();
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }*/
	
	private Stack<Tree<T>> stack = new Stack<Tree<T>>();

	/* Iteratore di profondità */
    public TreeIterator(Tree<T> tree) {
        if (tree != null) {
            stack.push(tree);
        }
    }

    public boolean hasNext() {
        return !stack.empty();
    }

    public T next() { /* Tree<T> */
        if (!hasNext()){
            throw new NoSuchElementException ("Tree no such elements");
        }
        Tree<T> result = stack.pop();
        /* push per ogni figlio */
        if (result.getChild() != null) {
            stack.push(result.getChild());
        }
        if (result.getSibling() != null) {
            stack.push(result.getSibling());
        }        
        return result.getLabel();
    }

    public void remove() {
        throw new UnsupportedOperationException("Operation not supported");
    }

}
