# Theoretical Analysis of Blocked Matrix Multiplication vs Naive Matrix Multiplication

Traditionally, we have the naive matrix multiplication algorithm that has a run time of O(n^3).

Let us calculate the cache misses incurred to find the product of matrices A & B of size n x n, using the naive way:

- Read/Scan the entire row of A – O(N/b) cache misses  **[ b is the number of data items read/written in a single read/write operation ]**
- Read/Scan the column of B – O(N) cache misses.
- Cache misses per element of C = O(N) + O(N/b) =
O(N).
- Overall cache misses = O(n^3) as we need to compute n^2 elements.
****

Now in the blocked matrix multiplication approach, we divide the rows & columns into blocks of size s.

And to get the product, we compute one block of the resultant matrix at every discrete step of computation. To get a better idea, the following is the pseudo code:				

```jsx
MatrixMultiply(A, B, C, n) 
Begin
	for i = 1 to n/s do
		for j = 1 to n/s do
			for k = 1 to n/s do
				Cij = Cij + Mul(Aik, Bkj, s)
			end-for 
		end-for
	end-for 
End.
```

Let us calculate the cache misses incurred to find the product of matrices A & B of size n x n, using the above method:

- To compute an s x s sub matrix of C, we need to bring in O(s^2) elements into the cache which results in O(s^2/b) cache misses.
- For the entire C matrix, the number of cache misses = O(s2/b)x(n/s)^3 = O(n^3/sb).

**IMPORTANT** : If we choose a block size such that a block of matrix A, B and C can simultaneously fit in the L1 cache, then the number of cache misses reduces significantly and run time improves drastically.

# Experimental Analysis of Blocked Matrix Multiplication vs Naive Matrix Multiplication

**Experiment** : Plot the run times for the two methods of matrix multiplication for different sizes of n x n matrices.

After taking into consideration my L1 cache size & running a few experiments, I found out that a block size of 16 would be efficient. 

Hence my experiments start with a matrix of size 16 x 16 first and increases in powers of 2 until 4096 x 4096.

→ Essentially the following list is the list of n’s that were used in this experiment: 

[16,32,64,128,256,512,1024,2048,4096]

The following are the run times in nanoseconds for blocked multiplication for each corresponding n :

**[14208,169709,1665000,6997000,38342458,287440916,2272035875,24221793667,206576047292]**

The following are the run times in nanoseconds for naive multiplication for each corresponding n :

**[13667,167458,1528167,6089083,37305625,293018917,2570162084,48415577291,1105041955417]**

## Plot obtained:
<img width="420" alt="Untitled" src="https://user-images.githubusercontent.com/102587700/227623099-2a384594-700e-4286-949d-402a2bc50333.png">

# Observation

Comparing the run times for the naive and blocked multiplication methods, it can be seen that the blocked method outperforms the naive method as the size of the matrices increases. This is expected since the blocked method reduces the number of higher level memory accesses required, thereby reducing the total number of operations required to perform the multiplication. 

We also see that the run time for the blocked method increases at a slower rate than the naive method as the matrix size increases. This is likely due to the fact that the blocked method is better able to utilize the cache hierarchy and reduce the number of cache misses compared to the naive method.

Overall, the results of this experiment suggest that the blocked method is a more efficient approach for matrix multiplication, particularly for larger matrix sizes.
