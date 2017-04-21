/*
package edu.unito.tree;

import java.util.Iterator;

class TreeIterator<T> implements Iterator<T> {

    private Tree<T> cursor;

    public TreeIterator(Tree<T> tree) {
        this.cursor = tree;
    }

    public boolean hasNext() {
        return cursor.hasChild() || cursor.hasNextSibling();
    }

    public T next() {
        if(this.hasNext()) {
            Tree<T> current = cursor;
            cursor ++;
            return current;
        }
        throw new NoSuchElementException();
    }

    public void remove() {
        throw new UnsupportedOperationException();
    }

}
*/