# Quick Sort

Quick sort is a highly efficient sorting algorithm and is based on partitioning of array of data into smaller arrays. A large array is partitioned into two arrays one of which holds values smaller than the specified value, say pivot, based on which the partition is made and another array holds values greater than the pivot value.

Quicksort partitions an array and then calls itself recursively twice to sort the two resulting subarrays.
This algorithm is quite efficient for large-sized data sets as its average and worst-case complexity are O(n2).

## Partition in Quick Sort

how to find the pivot in an array?

![Gif for  Pivot Selection](https://www.tutorialspoint.com/data_structures_algorithms/images/quick_sort_partition_animation.gif)

we choose a random value which is arr[end] and then we need to put it in it's final position and divide our array into two parts right to the pivot and left to the pivot the upper gif shows how we can choose this value

The pivot value divides the list into two parts. And recursively, we find the pivot for each sub-lists until all lists contains only one element.

## Quick Sort Pivot Algorithm

Based on our understanding of partitioning in quick sort, we will now try to write an algorithm for it, which is as follows.

- **Step 1**− Choose the highest index value as pivot
- **Step 2**− Take two variables to point left and right of the list excluding pivot
- **Step 3**− left points to the low index
- **Step 4**− right points to the high
- **Step 5**− while value at left is less than pivot move right
- **Step 6**− while value at right is greater than pivot move left
- **Step 7**− if both step 5 and step 6 does not match swap left and right
- **Step 8**− if left ≥ right, the point where they met is new pivot position

## Quick Sort Algorithm

Using pivot algorithm recursively, we end up with smaller possible partitions. Each partition is then processed for quick sort. We define recursive algorithm for quicksort as follows −

- **Step 1** − Make the right-most index value pivot
- **Step 2** − partition the array using pivot value
- **Step 3** − quicksort left partition recursively
- **Step 4** − quicksort right partition recursively

### some specs of Quick Sort

- time Complexity = O(n^2)
- space Complexity = S(3) ->(right, left, piveot) size

- in place sorting
- Stable Sorting
- non-adaptive sorting
