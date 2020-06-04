# intal.h - C library for integers of arbitrary length (intal).
## Introduction
An intal is a nonnegative integer of arbitrary length, but in my implementation it supports up to 1000 decimal digits. The integer is stored as a null-terminated string of ASCII characters. An intal is represented as a string of decimal digits ('0' thru '9') that are stored in the big-endian style. That is, the most significant digit is at the head of the string. An integer 25, for example, is stored in a string s as '2' at s[0], '5' at s[1], and null char at s[2].  

The difference between this method of storing numbers and regular integers is the limit of storage. All integer datatypes have a limit within which the numbers must be present to store it in those datatypes. Intal is more like a custom datatype which can store data limitlessly and can include special characters with special meanings in order to maintain compression. Eg : We could use '1e07' as exponential raised to the power seven and have an internal conversion of it.
## Applications
A common application is public-key cryptography, whose algorithms commonly employ arithmetic with integers having hundreds of digits. Integers of arbitrary length can also be used to avoid overflow, which is an inherent limitation of fixed-precision arithmetic. Similar to a 5-digit odometer's display which changes from 99999 to 00000, a fixed-precision integer may exhibit wraparound if numbers grow too large to represent at the fixed level of precision.
## Implementation
1. intal_add: Used the basic school addition technique by adding character stored in intals from backward untill all the characters from the smaller intal has been added to larger intal. After each individual sum of character result is stored as sum%10, while propagating sum/10 as carry till we iterate all characters of larger intal.

2. intal_compare: Used length as a comparison metric for intals of unequal length and returned 1 if first one was longer or -1 if second was longer. For the cases where both were equal in length, took difference for each i where 0 < i < len(intal)-1 and returned 1 if first one was greater, -1 if second one was greater. If intals pass all the above cases, return 0.

3. intal_diff: Used compare function to set the first one as greater one for convenience. Started subtracting from backwards position wise and stored the result while propagating the carry if we get a negative result at any point. Return the result after removing the zeros from the begining if any present.

4. intal_multiply: We start from last digit of second number multiply it with first number. Then we multiply second digit of second number with first number, and so on. We add all these multiplications but before adding, we put i-th multiplication shifted. Finally we remove any trailing zeros if any and then we return the result.

5. intal_mod: Used an O(logn) approach to find modulus which has the following steps:
    1. Make a copy of intal1 and intal2 in temp1 and temp2.
    2. Multiply temp2 untill it is greater than temp1.
    3. Take difference of temp2 and temp1 and store it to temp1.
    4. If temp1 is still greater than intal2, assign intal2 to temp2 and goto step 2.
    5. temp1 is the result of intal1 % intal2, we remove any zeros in the begining and then return temp1 as result.

6. intal_gcd: Used euclid's method for gcd(a, b). In this method, gcd(a, b) = gcd(b, a%b) is done repeatedly until the second parameter, b equals 0. I used the modulus operator from intal_mod for a%b.

7. intal_pow: Used the idea -> a^n = (a^2)^n/2 if 'n' is even and a^n = (a^2)^n/2 * a in case 'n' is odd. Iterate through the number 'n' as many times depending on the condition calculated above and multiply the value of intal1 to the result variable which contains an initial value of "1" and we use the intal_multiply(intal1, ans) and repeatedly store it in ans only.

8. intal_fibonacci: Used the iterative method of generating fiboanacci numbers by setting initial values a = "0", b = "1" and returned 'a' and 'b' for n == 0 and n == 1 respectively. If 'n' >= 2 use a variable to hold sum of 'a' and 'b' using c = intal_add(a,b) and move 'a' and 'b' till we reach the nth fibonacci number.

9. intal_factorial: Used the basic definition of factorial for this. Iterated from n to 1 and kept multiplying the results into a result intal using intal_multiply and reducing value of the intal iterator by one for each iteration using intal_diff until it reached 1.

10. intal_bincoeff: Used the Pascal's identity C(n,k) = C(n-1,k) + C(n-1,k-1) and created a DP table of size k+1 and iterated through all the n's from 1 to n and calculated value of nCk while iterating inwards from min(i,k) to 1 and using Pascal's identity here. Used intal_add(C(n-1,k) , C(n-1,k-1)) to perform this addition.

11. intal_max: Set the first value of the array as maximum and iterated through the entire array while comparing the first value with the others using intal_compare and updated the maximum value as we find a new maximum. Returned index of the maximum value once we iterated the entire array.

12. intal_min: Set the first value of the array as minimum and iterated through the entire array while comparing the first value with the others using intal_compare and updated the minimum value as we find a new minimum. Returned index of the minimum value once we iterate the entire array.

13. intal_search: Used linear search to iterate through the entire while comparing arr[i] with key and returned the index whenever the result of intal_compare(arr[i], key) == 0. If none of the elements match, returned -1.

14. intal_binsearch: Used the regular iterative method of binary search on the array and compared the key to the arr[mid] element using the intal_compare method and returned the offset if it gave result as 0. If result was 1 looked for key in left half of array. If -1 looked in right half . Returned -1 if none of the keys match the array elements.

15. intal_sort: Used quicksort to maintain the conditions specified in the questions. Created a quicksort function chooses pivot as the first element of the array while keeping in mind  the start and end index given and then puts all elements smaller than pivot to the left side and larger elements to the right side. Then swaps the pivot with the first largest element on the right side. Recurssive calls to quicksort is made to select each element s pivot and sort the entire array.

16. intal_coin_row_problem: We maintain a DP table of size n+1 strings where each element in DP table tells us the maximum amount if there were i coins and set the DP[0]='0' as there is no way to select coins if there aren't any and DP[1] = arr[0] if there is just a coin and DP[2] = max(arr[0],arr[1]). Then for each i from 3 to n, we calculate DP[i] by recurrence, DP[i] = max(DP[i-2]+arr[i],DP[i-1]). To implement the max function, we use intal_compare and return what is necassary. Finally the result is stored in DP[n] which is returned.  
## Future Work:
1. We could add the functionality of division which could be useful.
2. Bitwise operations like AND, OR, NOT, XOR
3. Factorization of intals