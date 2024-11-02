package src;


import java.util.NoSuchElementException;


public class JavaVector<T> implements JavaContainer<T>{
    private int capacity;
    private int size;
    private T[] elements;
    /**
     * @param _capacity create this much space.
     *                  capacity must be bigger than 0 and only work on first parameter.
     *                  if there is not any parameter or parameter is wrong. Then create array with size of 10
     */
    @SuppressWarnings("unchecked")
    public JavaVector(int... _capacity) {
        // Constructor
        capacity = (_capacity.length > 0 && _capacity[0] > 0) ? _capacity[0] : 10;
        size = 0; 
        elements = (T[]) new Object[capacity]; 
    }
    /**
     * @param obj Add this obj to vector container.
     */
    @Override
    public void Add(T obj) {
        if (Size() == capacity) {
            resize();
        }
        // Add new element.
        elements[Size()] = obj;
        ++size;
    }
    /**
     * Search for obj.
     * @param obj
     * If there is any removes that element and copies of it.
     */
    @Override
    public void Remove(T obj) {
        for (int i = 0; i < Size(); ++i) {
            if (elements[i] == obj) {
                System.arraycopy(elements, i + 1, elements, i, Size() - i - 1);
                --size;
            }
        }
    }
    @Override
    public int Size() {
        // Returns size.
        return size;
    }
    /**
     * @return  Overridden toString method for JavaVector class.
     */
    @Override
    public String toString() {
        // Overridden toString for JavaVector class.
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
     * Checks pair for every element of this vector also in the otherVector.
     * Placement does not matter, but quantity matters.
     * checks if
     * @param obj and @this is same
     * @return boolean value
     *
     */
    @Override
    public boolean equals(Object obj) {
        // Return true if this and obj exactly same.
        if (this == obj) return true;
        // Return false if obj type is not a JavaVector.
        if (!(obj instanceof JavaVector<?> otherVector)) return false;

        // Return false if size's difference.
        if (Size() != otherVector.Size()) return false;

        // Checks pair for every element of this vector also in the otherVector. Placement does not matter, but quantity matters.
        for (int i = 0; i < this.Size(); ++i) {
            boolean isFound = false;
            for (int j = 0; j < otherVector.Size(); ++j) {
                if (this.elements[i].equals(otherVector.elements[j])) {
                    isFound = true;

                    int countThis = 1;
                    int countOther = 1;

                    for (int k = i + 1; k < this.Size() && this.elements[i].equals(this.elements[k]); ++k) {
                        ++countThis;
                    }
                    for (int k = j + 1; k < otherVector.Size() && otherVector.elements[j].equals(otherVector.elements[k]); ++k) {
                        ++countOther;
                    }

                    if (countThis != countOther) {
                        return false;
                    }
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
     * This method expand the vector capacity by 2 times when called.
     */
    private void resize() {
        capacity *= 2;
        @SuppressWarnings("unchecked")
        var newElements = (T[]) new Object[capacity];
        System.arraycopy(elements, 0, newElements, 0, Size());
        elements = newElements;
    }


}