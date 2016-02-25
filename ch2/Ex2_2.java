/***********************************************************************
 * Implements a quicksort which uses type casting and interfaces and
 * several others which directly use the given types and compares
 * their performance.
 *
 * Author: Nicholas Kachur <nick.e.kachur@gmail.com>
 ***********************************************************************/

import java.io.*;
import java.util.Random;

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
    public static void main(String[] args)
    {
        System.out.println("Preparing to do tests...");

        int[] = 
    }

}


