/***********************************************************************
 * Implements a quicksort which uses type casting and interfaces and
 * several others which directly use the given types and compares
 * their performance.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

import java.io.*;
import java.util.Random;
import java.util.Arrays;

interface Cmp
{
    int cmp(Object x, Object y);
}

// Icmp: integer comparison
// Adapted from Kernighan & Pike's "Practice of Programming"
class Icmp implements Cmp
{
    public int cmp(Object o1, Object o2)
    {
        int i1 = ((Integer) o1).intValue();
        int i2 = ((Integer) o2).intValue();
        if (i1 < i2)
            return -1;
        else if (i1 == i2)
            return 0;
        else
            return 1;
    }
}

// Scmp: string comparison
// Adapted from Kernighan & Pike's "Practice of Programming"
class Scmp implements Cmp
{
    public int cmp(Object o1, Object o2)
    {
        String s1 = (String) o1;
        String s2 = (String) o2;
        return s1.compareTo(s2);
    }
}

// Implements quicksort and associated utility functions
class Quicksort
{
    // Quicksort.sort: quicksort v[left]..v[right]
    // Adapted from Kernighan & Pike's "Practice of Programming"
    static void sort(Object[] v, int left, int right, Cmp cmp)
    {
        int i, last;

        if (left >= right) // nothing to do 
            return;
        swap(v, left, rand(left, right));   // move pivot element
        last = left;                        // to v[left]
        for (i = left+1; i <= right; ++i)
            if (cmp.cmp(v[i], v[left]) < 0)
                swap(v, ++last, i);
        swap(v, left, last);
        sort(v, left, last-1, cmp);
        sort(v, last+1, right, cmp);
    }

    // Quicksort.integerSort: sort v[left]..v[right] into increasing order using 
    //                    Integers
    static void integerSort(Integer[] v, int left, int right)
    {
        int i, last;

        if (left >= right) // nothing to do 
            return;
        intSwap(v, left, rand(left, right));   // move pivot element
        last = left;                        // to v[left]
        for (i = left+1; i <= right; ++i)
            if (v[i] < v[left])
                intSwap(v, ++last, i);
        intSwap(v, left, last);
        integerSort(v, left, last-1);
        integerSort(v, last+1, right);
    }

    // Quicksort.stringSort: sort v[left]..v[right] into increasing order using 
    //                       Strings
    static void stringSort(String[] v, int left, int right)
    {
        int i, last;

        if (left >= right) // nothing to do 
            return;
        stringSwap(v, left, rand(left, right));   // move pivot element
        last = left;                              // to v[left]
        for (i = left+1; i <= right; ++i)
            if ((v[i].compareTo(v[left])) < 0)
                stringSwap(v, ++last, i);
        stringSwap(v, left, last);
        stringSort(v, left, last-1);
        stringSort(v, last+1, right);
    }

    // Quicksort.stringSwap: swap v[i] and v[j] using String
    static void stringSwap(String[] v, int i, int j)
    {
        String temp;
        
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    // Quicksort.intSwap: swap v[i] and v[j] using Integer
    static void intSwap(Integer[] v, int i, int j)
    {
        Integer temp;
        
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    // Quicksort.swap: swap v[i] and v[j]
    // Adapted from Kernighan & Pike's "Practice of Programming"
    static void swap(Object[] v, int i, int j)
    {
        Object temp;
        
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    static Random rgen = new Random();

    // Quicksort.rand: return random integer in [left, right]
    // Adapted from Kernighan & Pike's "Practice of Programming"
    static int rand(int left, int right)
    {
        return left + Math.abs(rgen.nextInt())%(right-left+1);
    }
}

class Ex2_2
{
    static Random rgen = new Random();

    static char[] chars = "abcdefghijklmnopqrstuvwxyz".toCharArray();

    static Icmp icmp = new Icmp();
    static Scmp scmp = new Scmp();

    // Adapted from http://stackoverflow.com/a/5683362
    public static String randomString(int length)
    {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; ++i)
        {
            char c = chars[rgen.nextInt(chars.length)];
            sb.append(c);
        }

        return sb.toString();
    }

    public static void main(String[] args)
    {
        System.out.println("Preparing to do tests...");

        final int test_len = 10;
        final int max_string_len = 10;
        final int num_attempts = 100;
        final int num_elements = 10000;
        final long NSEC_PER_SEC= 1000000000;
        
        Integer[] i1_test_array = new Integer[test_len];
        Integer[] i2_test_array = new Integer[test_len];
        String[] s1_test_array = new String[test_len];
        String[] s2_test_array = new String[test_len];

        for (int i = 0; i < test_len; ++i)
        {
            i1_test_array[i] = i2_test_array[i] = rgen.nextInt(test_len);
            s1_test_array[i] = s2_test_array[i] =
                randomString(rgen.nextInt(max_string_len));
        }

        System.out.println("Sanity test:");

        System.out.println("\tInteger Array: " + Arrays.toString(i1_test_array));
        Quicksort.sort(i1_test_array, 0, i1_test_array.length-1, icmp);
        System.out.println("\tGeneric Sort:  " + Arrays.toString(i1_test_array));
        Quicksort.integerSort(i2_test_array, 0, i2_test_array.length-1);
        System.out.println("\tSpecific Sort: " + Arrays.toString(i2_test_array));

        System.out.println("\tString Array:  " + Arrays.toString(s1_test_array));
        Quicksort.sort(s1_test_array, 0, s1_test_array.length-1, scmp);
        System.out.println("\tGeneric Sort:  " + Arrays.toString(s1_test_array));
        Quicksort.stringSort(s2_test_array, 0, s2_test_array.length-1);
        System.out.println("\tSpecific Sort: " + Arrays.toString(s2_test_array));

        Integer[] i_array1 = new Integer[num_elements];
        Integer[] i_array2 = new Integer[num_elements];
        String[] s_array1 = new String[num_elements];
        String[] s_array2 = new String[num_elements];

        Double i1_total_time, i2_total_time, s1_total_time, s2_total_time;
        i1_total_time = i2_total_time = s1_total_time = s2_total_time = 0.0;
        long start, end;

        for (int i = 0; i < num_attempts; ++i)
        {
            for (int j = 0; j < num_elements; ++j)
            {
                i_array1[j] = i_array2[j] = rgen.nextInt(test_len);
                s_array1[j] = s_array2[j] = randomString(rgen.nextInt(
                            max_string_len));
            }

            start = System.nanoTime();
            Quicksort.sort(i_array1, 0, i_array1.length-1, icmp);
            end = System.nanoTime();
            i1_total_time += ((double)end - (double)start) / NSEC_PER_SEC;

            start = System.nanoTime();
            Quicksort.sort(i_array2, 0, i_array2.length-1, icmp);
            end = System.nanoTime();
            i2_total_time += ((double)end - (double)start) / NSEC_PER_SEC;

            start = System.nanoTime();
            Quicksort.sort(s_array1, 0, s_array1.length-1, scmp);
            end = System.nanoTime();
            s1_total_time += ((double)end - (double)start) / NSEC_PER_SEC;

            start = System.nanoTime();
            Quicksort.sort(s_array2, 0, s_array2.length-1, scmp);
            end = System.nanoTime();
            s2_total_time += ((double)end - (double)start) / NSEC_PER_SEC;

        }
            
        double i1_avg_time, i2_avg_time, s1_avg_time, s2_avg_time;
        i1_avg_time = i1_total_time / num_attempts;
        i2_avg_time = i2_total_time / num_attempts;
        s1_avg_time = s1_total_time / num_attempts;
        s2_avg_time = s2_total_time / num_attempts;

        System.out.println("Testing complete, statistics (in seconds):");
        System.out.println("\tGeneric Integer Sort Total:     " + i1_total_time);
        System.out.println("\tSpecific Integer Sort Total:    " + i2_total_time);
        System.out.println("\tGeneric Integer Sort Average:   " + i1_avg_time);
        System.out.println("\tSpecific Integer Sort Average:  " + i2_avg_time);
        System.out.println("\tGeneric String Sort Total:      " + s1_total_time);
        System.out.println("\tSpecific String Sort Total:     " + s2_total_time);
        System.out.println("\tGeneric String Sort Average:    " + s1_avg_time);
        System.out.println("\tSpecific String Sort Average:   " + s2_avg_time);

    }
}


