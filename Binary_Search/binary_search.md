```C++
int binary_search(int left, int right)
{
	int mid;
	while(left+1<right){
		mid = (left + right) >> 1;
		if(check(mid))
			left = mid;
		else
			right=mid;
	}
	if(check(right))
		return right;
	else
		return left;
}
```

```C++
int bsc(int l,int r)
{
    int md;
    while(l+1<r)
    {
        md = (l+r) >> 1;
        (chck(md) ? l : r) = md;
    }
    return chck(r) ? r s: l;
}
```

