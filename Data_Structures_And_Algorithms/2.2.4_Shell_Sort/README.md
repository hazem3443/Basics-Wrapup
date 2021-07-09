# Shell Sort

Shell sort is a highly efficient sorting algorithm and is based on insertion sort algorithm. This algorithm avoids large shifts as in case of insertion sort, if the smaller value is to the far right and has to be moved to the far left.

This algorithm is quite efficient for medium-sized data sets as its average and worst-case complexity of this algorithm depends on the gap sequence the best known is Ο(n), where n is the number of items. And the worst case space complexity is O(n).

How Shell Sort Works?

this sorting technique uses insertion sort like function to sort an array
first it reduces the gap between the unsorted elements with shell technique using **Knuth's Formula** algorithm

```psudo
h = h * 3 + 1
where −
   h is interval with initial value 1
```

then loop over that interval or loop (**interval**) times insertionly starting from interval index and into the
 inner loop subtract the interval from the inner cursor

 ```psedo
 Shell_Sort(){
    /* calculate interval*/
   while (interval < len /3){
      interval = interval * 3 + 1
   }

   while (interval > 0){
      for (int i = interval; i < len; i++){
         for (int j = i; j > interval - 1 && x[j - interval] > valueToInsert; j -= interval){
            swapByReference(x + j, x + j - interval);
         }
      }
      /* calculate new interval*/
      interval = (interval -1) /3;
   }
 }
 ```

- In-Place sorting algorithm
- stable sorting
- adaptive sorting algorithm

**Time Complexity** O(n)  
**Space Complexity** S(4)
