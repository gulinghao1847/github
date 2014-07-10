/*
merge sort
*/
/*
recursive implementation is trivial
*/
/*
iterative implementation
*/
/*
My thoughts: We need to imitate the recursion function. But a problem is: the size of the array is unknown, so we don't how many loops we need to do in our problem. I think that is a tricky part in this problem. That is why I can't do this iteratively. 
But after searching for the Internet, I know that we do could imitate this. By using the function
*/
void mergeSort(vector<int>& NumberArray){
	//how many steps?
	/*That is the hardest part. two steps:
	1.how many levels do we need to do merge sort? just treat merge sort as a tree, the height of the tree = height
	2. In each step, how many merge do we need to do?
	So, there are two loops here, and the time complexity of this is just the same as 
	*/
	//first loop: how many loops? since N(i + 1) = N(i) * 2;
}
