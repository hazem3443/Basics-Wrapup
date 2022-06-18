# General C++ Test

### Description

Design a templated, dynamically-growing array. The interface should at least have these procedures:

- `push_back`</br>
	Add an element to the end of the array
- `operator[]`</br>
	Access specified element with bounds checking
- `remove_if`</br>
	Take a predicate and _remove all elements_ which satisfy that predicate (i.e. when predicate is true)

Implementation should not have memory leaks. Feel free to add more capabilities to the interface if you need to.

### Pseudo Usage
```c++
// Assume array is of type Item_Type and empty
// content: {}

array.push_back(item_0);
array.push_back(item_1);
array.push_back(item_2);
array.push_back(item_3);
// content: {item_0, item_1, item_2, item_3}

auto item = arr[2];
// item now contains item_2

// remove any element that is not item_3
arr.remove_if(
	[](Item_Type item) {
		return item != item_3;
	}
);
// content: {item_3}
```

### Submission
A single C++ file (`test.cpp`) that contains the implementation of the array and a `main` function that demonstrates the usage of its interface.
