
package src;

import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        // Example driver code for JavaSet and JavaVector classes. And Examples for each method.

        // Test for JavaSet Class

        JavaSet<Integer> mySet = new JavaSet<>();
        // Adding elements
        mySet.Add(1);
        mySet.Add(2);
        mySet.Add(3);
        // Adding already existing element for checking
        mySet.Add(2);
        // Printing set before changes
        System.out.println("\n\nSet before using remove:");
        System.out.println("Set1 size: " +mySet.Size());
        System.out.println("Set1 elements: " +mySet);

        var set_it = mySet.getIterator();
        // Iterating through set and printing elements
        System.out.print("\nPrinting elements of set1 using iterator: ");
        while (set_it.hasNext()) {
            System.out.print(set_it.next() + " ");
        }
        System.out.println();

        // Removing Integer 2 and printing changes
        mySet.Remove(2);
        System.out.println("\nSet after removing Integer '2':");
        System.out.println("Set1 size: " +mySet.Size());
        System.out.println("Set1 elements: " +mySet);

        // Testing Constructor with parameter and testing the equals' method.
        JavaSet<Integer> mySet2 = new JavaSet<>(1);
        mySet2.Add(1);
        mySet2.Add(3);
        System.out.println("\nSet2 elements: " +mySet2);
        System.out.println("Equality of set1 and set2: "+mySet2.equals(mySet));

        // Test for JavaVector Class

        JavaVector<String> myVector = new JavaVector<>();
        // Adding elements
        myVector.Add("semih");
        myVector.Add("sari");
        myVector.Add("koca");
        // Adding already existing element for checking
        myVector.Add("sari");
        // Printing vector before changes
        System.out.println("\n\nVector before using remove:");
        System.out.println("Vector1 size: " +myVector.Size());
        System.out.println("Vector1 elements: " +myVector);

        var vector_it = myVector.getIterator();
        // Iterating through vector and printing elements
        System.out.print("\nPrinting elements of vector1 using iterator: ");
        while (vector_it.hasNext()) {
            System.out.print(vector_it.next() + " ");
        }
        System.out.println();

        // Removing String sari and printing changes
        myVector.Remove("sari");
        System.out.println("\nVector after removing String 'sari':");
        System.out.println("Vector1 size: " +myVector.Size());
        System.out.println("Vector1 elements: " +myVector);

        // Testing Constructor with parameter and testing the equals' method.
        JavaVector<String> myVector2 = new JavaVector<>(1);
        myVector2.Add("semih");
        myVector2.Add("sari");
        myVector2.Add("semih");
        System.out.println("\nVector2 elements: " +myVector2);
        System.out.println("Equality of Vector1 and Vector2: "+myVector2.equals(myVector));

        // Write set1 and vector2 to txt file.
        String file1 = "files/set.txt";
        String file2 = "files/vector.txt";
        writeJavaContainerToFile(mySet, file1);
        writeJavaContainerToFile(myVector, file2);

    }
    private static <T> void writeJavaContainerToFile(JavaContainer<T> container, String fileName) {
        // Create file with the address and name.
        try (FileWriter writer = new FileWriter(fileName)) {
            // Get iterator of the given container.
            var it = container.getIterator();
            // Using that iterator to write to file. call each element's toString method.
            while (it.hasNext()) {
                writer.write(it.next().toString() + "\n");
            }
        // catch if there is any error doing this try block. Like error at creating file to the address.
        } catch (IOException exep) {
            System.err.println("Erron in operatin on file: "+ fileName + "\nTerminating...");
        }
    }
}
