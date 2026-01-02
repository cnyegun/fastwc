# Optimization found
1. use stat <filename> for fast O(1) `wc -c`
2. use a lookup table to check for spaces
3. use a buffer fread() instead of fgetc(). 2048 * 2048 seems good
4. remove if branch, check for whitespace using a variable
5. remove for loop, use two direct pointer for traversing inside the buffer
6. 
