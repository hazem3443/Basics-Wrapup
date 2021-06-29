# Interpolation Search

Interpolation search is an improved variant of binary search. This search algorithm works on the probing position of the required value.For this algorithm to work properly, the data collection should be in a sorted form and equally distributed.

Binary search has a huge advantage of time complexity over linear search.
Linear search has worst-case complexity of Ο(n) whereas binary search has Ο(log n).

$mid = lo + \frac{(hi - lo)}{(list[hi] - list[lo])} *(data - list[lo])$

this Search looks make a percent of the position of the required value in the array and compare over each iteration.

__Time Complexity = Ο(log (log n))__(worst case)
__Time Complexity = Ο(log n)__(Best case)
__Space Complexity = S(3)__
