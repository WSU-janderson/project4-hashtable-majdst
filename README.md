[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---

insert(key, value)--> Best Case: O(1) (Constant Time)--> The best case happens when the "home" bucket is either 'ESS'
 or 'EAR'. We can insert the item in one step.
Worst Case: O(N) (Linear Time)--> The worst case happens when all keys hash to the same home bucket. Have to probe through all N items in the table to find an empty spot or a duplicate.

---
remove(key)--> Best Case: O(1) --> The key to remove is found right in its "home" bucket--> one check, mark it as `EAR`, and return.
O(N)-->The key is not in the table--> have to probe through all N occupied buckets before hit an `ESS` bucket and can finally stop searching.


---

contains(key)--> Best Case: O(1)-->The key is found in its "home" bucket--> Worst: O(N-->Same as remove. 

---

get(key)--> Best Case: O(1)--> The best case is finding the key in its "home" bucket-->Worst Case: O(N)--> Identical to contains-->have to search a chain of N colliding keys.
