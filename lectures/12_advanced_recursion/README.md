# Lecture 12 --- Advanced Recursion

Review Recursion vs. Iteration

- Binary Search
- “Rules” for writing recursive functions
- Advanced Recursion — problems that cannot be easily solved using iteration (for or while loops):  
  – Merge sort  

## 12.1 Review: Iteration vs. Recursion

- Every recursive function can also be written iteratively. Sometimes the rewrite is quite simple and straightforward. Sometimes it’s more work.
- Often writing recursive functions is more natural than writing iterative functions, especially for a first draft of
a problem implementation.
- You should learn how to recognize whether an implementation is recursive or iterative, and practice rewriting
one version as the other.
- Note: The order notation for the number of operations for the recursive and iterative versions of an algorithm
is usually the same.
- However in C, C++, Java, and some other languages, iterative functions are generally faster than their
corresponding recursive functions. This is due to the overhead of the function call mechanism.
- Compiler optimizations will sometimes (but not always!) reduce the performance hit by automatically eliminating
the recursive function calls. This is called tail call optimization.

## 12.2 Binary Search

- Suppose you have a std::vector&lt;T&gt; v (for a placeholder type T), sorted so that:
```cpp
v[0] <= v[1] <= v[2] <= ...
```
- Now suppose that you want to find if a particular value x is in the vector somewhere. How can you do this without looking at every value in the vector?
- The solution is a recursive algorithm called binary search, based on the idea of checking the middle item of the search interval within the vector and then looking either in the lower half or the upper half of the vector, depending on the result of the comparison.
```cpp
template <class T>
bool binsearch(const std::vector<T> &v, int low, int high, const T &x) {
	if (high == low) return x == v[low];
	int mid = (low+high) / 2;
	if (x <= v[mid])
		return binsearch(v, low, mid, x);
	else
		return binsearch(v, mid+1, high, x);
}

template <class T>
bool binsearch(const std::vector<T> &v, const T &x) {
	return binsearch(v, 0, v.size()-1, x);
}
```

- If we replaced the if-else structure inside the recursive binsearch function (above) with
```cpp
if ( x < v[mid] )
	return binsearch( v, low, mid-1, x );
else
	return binsearch( v, mid, high, x );
```
would the function still work correctly?

## 12.3 “Rules” for Writing Recursive Functions

- Here is an outline of five steps that are useful in writing and debugging recursive functions. Note: You don’t have
to do them in exactly this order...
1. Handle the base case(s).
2. Define the problem solution in terms of smaller instances of the problem. Use wishful thinking, i.e., if someone
else solves the problem of fact(4) I can extend that solution to solve fact(5). This defines the necessary
recursive calls. It is also the hardest part!
3. Figure out what work needs to be done before making the recursive call(s).
4. Figure out what work needs to be done after the recursive call(s) complete(s) to finish the computation. (What
are you going to do with the result of the recursive call?)
5. Assume the recursive calls work correctly, but make sure they are progressing toward the base case(s)!

## 12.4 Another Recursion Example: Merge Sort

- Idea:
  - 1) Split a vector in half,  
  - 2) Recursively sort each half, and  
  - 3) Merge the two sorted halves into a single sorted vector.  
- Suppose we have a vector called values having two halves that are each already sorted. In particular, the
values in subscript ranges [low..mid] (the lower interval) and [mid+1..high] (the upper interval) are each
in increasing order.
- Which values are candidates to be the first in the final sorted vector? Which values are candidates to be the
second?
- In a loop, the merging algorithm repeatedly chooses one value to copy to scratch. At each step, there are only
two possibilities: the first uncopied value from the lower interval and the first uncopied value from the upper
interval.
- The copying ends when one of the two intervals is exhausted. Then the remainder of the other interval is copied
into the scratch vector. Finally, the entire scratch vector is copied back.

## 12.5 Thinking About Merge Sort

- It exploits the power of recursion! We only need to think about  

  – Base case (intervals of size 1)  
  – Splitting the vector  
  – Merging the results
- We can insert cout statements into the algorithm and use this to understand how this is is happening.
- Can we analyze this algorithm and determine the order notation for the number of operations it will perform?
Count the number of pairwise comparisons that are required.

## 12.6 Merge Sort Exercises

- [Leetcode problem 912: Sort an Array](https://leetcode.com/problems/sort-an-array/). Solution: [p912_sortarray.cpp](../../leetcode/p912_sortarray.cpp)
- [Leetcode problem 148: Sort List](https://leetcode.com/problems/sort-list/). Solution: [p148_sortlist.cpp](../../leetcode/p148_sortlist.cpp)

## 12.7 Merge Sort Run Time Complexity

- Each time we divide the vector into two halves, the number of subproblems doubles, leading to a recursion tree structure.
- At each level, the vector size reduces by half. The division continues until we reach base cases where each sub-vector contains only one element. 
- The number of levels in the recursion tree corresponds to how many times we can divide n by 2 until we reach 1: log<sub>2</sub> n.
- At each level of recursion, we need to merge two sorted halves into one sorted vector. Merging two halves of size n requires O(n) operations.  The same amount of merging work happens at each level of recursion.
- Total Work Done: Since we have O(logn) levels in the recursion tree and each level requires O(n) merging work, the total time complexity is: O(nlogn).

## 12.8 Leetcode Exercises

- [Leetcode problem 704: Binary Search](https://leetcode.com/problems/binary-search/). Solution: [p704_binarysearch.v1.cpp](../../leetcode/p704_binarysearch.v1.cpp) or [p704_binarysearch.v2.cpp](../../leetcode/p704_binarysearch.v2.cpp)
