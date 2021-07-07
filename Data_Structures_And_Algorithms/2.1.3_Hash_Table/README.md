# Hash Table

Hash Table is a data structure which stores data in an associative manner.

## Hashing

Hashing is a technique to convert a range of key values into a range of indexes of an array. We're going to use modulo operator (%) to get a range of key values. Consider an example of hash table of size 20, and the following items are to be stored. Item are in the (key,value) format.

![HASH Table UML Diagram](https://www.tutorialspoint.com/data_structures_algorithms/images/hash_function.jpg)

| Sr. No. |  Key  | Hash         | Array Index |
| ------- | :---: | ------------ | :---------: |
| 1       |   1   | 1 % 20 = 1   |      1      |
| 2       |   2   | 2 % 20 = 2   |      2      |
| 3       |  42   | 42 % 20 = 2  |      2      |
| 4       |   4   | 4 % 20 = 4   |      4      |
| 5       |  12   | 12 % 20 = 12 |     12      |
| 6       |  14   | 14 % 20 = 14 |     14      |
| 7       |  17   | 17 % 20 = 17 |     17      |
| 8       |  13   | 13 % 20 = 13 |     13      |
| 9       |  37   | 37 % 20 = 17 |     17      |

----------

## Linear Probing

As we can see, it may happen that the hashing technique is used to create an already used index of the array. In such a case, we can search the next empty location in the array by looking into the next cell until we find an empty cell. This technique is called linear probing.

| Sr. No. |  Key  | Hash         | Array Index | After Linear Probing, Array Index |
| ------- | :---: | ------------ | :---------: | :-------------------------------: |
| 1       |   1   | 1 % 20 = 1   |      1      |                 1                 |
| 2       |   2   | 2 % 20 = 2   |      2      |                 2                 |
| 3       |  42   | 42 % 20 = 2  |      2      |                 3                 |
| 4       |   4   | 4 % 20 = 4   |      4      |                 4                 |
| 5       |  12   | 12 % 20 = 12 |     12      |                12                 |
| 6       |  14   | 14 % 20 = 14 |     14      |                14                 |
| 7       |  17   | 17 % 20 = 17 |     17      |                17                 |
| 8       |  13   | 13 % 20 = 13 |     13      |                13                 |
| 9       |  37   | 37 % 20 = 17 |     17      |                18                 |

## Basic Operations we are gona build

Following are the basic primary operations of a hash table.

- **Search** − Searches an element in a hash table.

- **Insert** − inserts an element in a hash table.

- **delete** − Deletes an element from a hash table.
