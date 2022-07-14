/*
Array Challenge
Have the function ArrayChallenge(arr) take the array of integers stored in arr, and determine if any two numbers (excluding the first element) in the array can sum up to the first element in the array. For example: if arr is [7, 3, 5, 2, -4, 8, 11], then there are actually two pairs that sum to the number 7: [5, 2] and [-4, 11]. Your program should return all pairs, with the numbers separated by a comma, in the order the first number appears in the array. Pairs should be separated by a space. So for the example above, your program would return: 5,2 -4,11

If there are no two numbers that sum to the first element in the array, return -1
Examples
Input: [17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7]
Output: 6,11 10,7 15,2
Input: [7, 6, 4, 1, 7, -2, 3, 12]
Output: 6,1 4,3

Solution


function ArrayChallenge(arr) { 

  // code goes here  
  var sum = []
  for (var i = 1; i < arr.length; i++) {
    for (var j = i + 1; j < arr.length; j++) {
      if (arr[i] + arr[j] === arr[0]) {
        sum.push([arr[i], arr[j]].join());
      }
    }
  }
  return sum.length > 0 ? sum.join(" ") : -1;
}
   
// keep this function call here 
console.log(ArrayChallenge(readline()));

*/

/** SQL problem
 * 
 * SQL Challenge
Your table: maintable_GT86K

MySQL version: 8.0.23

In this MySQL challenge, your query should return the vendor information along with the values from the table cb_vendorinformation. You should combine the values of the two tables based on the GroupID column. The final query should consolidate the rows to be grouped by FirstName, and a Count column should be added at the end that adds up the number of times that person shows up in the table. The output table should be sorted by the Count column in ascending order and then sorted by CompanyName in alphabetical order. Your output should look like the following table.
 

SOLUTION
---------

SELECT * 
FROM (SELECT Ta.GroupID,Ta.FirstName,Ta.LastName, Ta.Job ,Ta.ExternalID, cv.CompanyName
  FROM (
    select FirstName, LastName, Job, GroupID, ExternalID, count(*) "Count"
    from maintable_GT86K
    where VendorID in(
      SELECT ma.VendorID
      FROM maintable_GT86K ma
      GROUP By 1)
  Group by 1
  ) Ta INNER JOIN cb_vendorinformation cv
  ON cv.GroupID = Ta.GroupID
  ORDER By 6) final
INNER JOIN (
  SELECT FirstName, Count(*) "Count"
  from maintable_GT86K 
    INNER JOIN cb_vendorinformation
    ON maintable_GT86K.GroupID = cb_vendorinformation.GroupID
  Group by 1
  ORDER By 2) lastT
on lastT.FirstName = final.FirstName
order By 8 ASC,6

*/