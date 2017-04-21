import java.util.Iterator;

public class TreeIterable implements Iterable<Integer> {
    private int start, end;

    public TreeIterable(int start, int end) {
        this.start = start;
        this.end = end;
    }

    public Iterator<Integer> iterator() {
        return new RangeIterator();
    }

    // Inner class example
    private class TreeIterator implements
                    Iterator<Integer> {
        private int cursor;

        public RangeIterator() {
            this.cursor = Range.this.start;
        }

        public boolean hasNext() {
            return this.cursor < Range.this.end;
        }

        public Integer next() {
            if(this.hasNext()) {
                int current = cursor;
                cursor ++;
                return current;
            }
            throw new NoSuchElementException();
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }
}