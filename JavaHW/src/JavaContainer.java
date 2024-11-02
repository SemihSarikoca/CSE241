package src;

public interface JavaContainer<T> {
    /**
     * @param obj Add this obj to container
     */
    void Add(T obj);

    /**
     * @param obj find and remove this obj from container
     */
    void Remove(T obj);

    /**
     *
     * @return size of the container
     */
    int Size();
    Iterator<T> getIterator();
    interface Iterator<T> {
        boolean hasNext();
        T next();
    }
    
}