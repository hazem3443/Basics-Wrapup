# Merge Sort

Merge sort is a sorting technique based on divide and conquer technique.
Merge sort first divides the array into equal halves and then combines them in a sorted manner.

**worst time Complexity** = Ο(n log n)

we divide the list into two parts iteratively till we reach the union part which is not dividable then merge them after comparisons into new sorted smaller list

## algorithms steps

- **Step 1** − if it is only one element in the list it is already sorted, return.
- **Step 2** − divide the list recursively into two halves until it can no more be divided.
- **Step 3** − merge the smaller lists into new list in sorted order.

from these steps we notice that there is two functions Divide recursively(iteratively) and merge parts with sorting operation

**Divide** Algorithm

```psudo
Divide(arr,len){
    if len =1: 
        return x
    
    mid = len/2;
    l1 = divide(arr,mid);
    l2 = divide(arr+mid,len-mid);

    return merge(l1,l2);
}
```

**merge** algorithms ascendingly

```psudo
merge(l1,l2){
    i,j,cur = 0;
    l3 = [];
    while (i < l1_len && j < l2_len){
        if(l1[i] < l2[j]){
            l3[cur++] = l1[i++]
        }else{
            l3[cur++] = l2[j++]
        }
    }
    while (i < l1_len ) l3[cur++] = l1[i++]
    while (j < l2_len) l3[cur++] = l2[j++]

    return l3;
}
```

- not In-place sorting algorithm
    can be in place if we use **swap** function while checking instead of l3 assigning
- Stable Sorting
- Adaptive algorithm
