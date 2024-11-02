package src;


import java.util.NoSuchElementException;

public class JavaSet<T> implements JavaContainer<T>{
    private int capacity;
    private int size;
    private T[] elements;

    /**
     * @param _capacity create this much space.
     *                  capacity must be bigger than 0 and only work on first parameter.
     *                  if there is not any parameter or parameter is wrong. Then create array with size of 10
     */
    @SuppressWarnings("unchecked")
    public JavaSet(int... _capacity) {
        // Constructor.
        capacity = (_capacity.length > 0 && _capacity[0] > 0) ? _capacity[0] : 10;
        size = 0;
        elements = (T[]) new Object[capacity];
    }

    /**
     * @param obj Add this obj to set container, if there is not existing copy of it.
     */
    @Override
    public void Add(T obj) {
        for (int i = 0; i < Size(); ++i) {
            if (elements[i] == obj) 
                return;
        }

        if (Size() == capacity) {
            resize();
        }
        elements[Size()] = obj;
        ++size;
    }

    /**
     * @param obj Find obj in set and removes it. If obj does not in the set then does nothing.
     */
    @Override
    public void Remove(T obj) {
        for (int i = 0; i < Size(); ++i) {
            if (elements[i] == obj) {
                System.arraycopy(elements, i + 1, elements, i, Size() - i - 1);
                --size;
                break;
            }
        }
    }
    @Override
    public int Size() {
        // Return size.
        return size;
    }

    /**
     * @return  Overridden toString method for JavaSet class.
     */
    @Override
    public String toString() {
        StringBuilder visual = new StringBuilder();
        visual.append("[");
        for (int i = 0; i < Size(); ++i) {
            visual.append(elements[i]);
            visual.append(", ");
        }
        visual.append("...]");
        return visual.toString();
    }

    /**
     * Overridden equals method for JavaVector class.
     * checks if
     * @param obj and @this is same
     * @return boolean value
     */
    @Override
    public boolean equals(Object obj) {
        // Return true if this and obj exactly same.
        if (this == obj) return true;
        // Return false if obj type is not a JavaSet.
        if (!(obj instanceof JavaSet<?> otherSet)) return false;

        // Return false if size's difference.
        if (Size() != otherSet.Size()) return false;

        // Checks pair for every element in the otherSet.
        for (int i = 0; i < this.Size(); ++i) {
            boolean isFound = false;
            for (int j = 0; j < otherSet.Size(); ++j) {
                if (this.elements[i].equals(otherSet.elements[j])) {
                    isFound = true;
                    break;
                }
            }
            if (!isFound) {
                return false;
            }
        }
        return true;
    }

    /**
     * Creates and
     * @return iterator for user to use.
     */
    @Override
    public Iterator<T> getIterator() {
        // Creates and returns iterator for user to use.
        return new JavaSetIterator();
    }
    
    private class JavaSetIterator implements Iterator<T> {
        private int currentIndex = 0;

        @Override
        public boolean hasNext() {
            return currentIndex < Size();
        }

        @Override
        public T next() {
            // If there is a next element then return the element.
            if (!hasNext()) {
                throw new NoSuchElementException();
            }
            return elements[currentIndex++];
        }
    }

    /**
     * This method expand the set capacity by 2 times when called.
     */
    private void resize() {
        capacity *= 2;
        @SuppressWarnings("unchecked")
        var newElements = (T[]) new Object[capacity];
        System.arraycopy(elements, 0, newElements, 0, Size());
        elements = newElements;
    }


}