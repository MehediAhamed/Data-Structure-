#include <iostream>


using namespace std;

 int seg_tree[1000];
 int arr[1000];
 int lazy_tree[1000];

void segment_tree_build(int node, int b, int e)
{
    if (b == e)
    {
        seg_tree[node] = arr[b];
        return;
    }
    int left = 2 * node;
    int right = 2* node + 1;
    int mid = (b + e) / 2;
    segment_tree_build(left, b, mid);
    segment_tree_build(right, mid + 1, e);
    seg_tree[node] = min(seg_tree[left], seg_tree[right]);
    return;
}

void segment_tree_build_sum(int node, int begin, int end)
{
	if (begin == end)
	{
		seg_tree[node] = arr[begin];
		return;
	}
	else
	{
		int left = 2 * node;
		int right = 2 * node + 1;
		int mid = (begin + end) / 2;
		segment_tree_build(left, begin, mid);
		segment_tree_build(right, mid + 1, end);
        seg_tree[node] = seg_tree[left] + seg_tree[right];
	}
}


//complexity O(logN)
int query(int node, int i, int j, int b, int e)
{

    //no overlap
    if (b > j || e < i)
    {
        return INT_MAX;
    }

    //total overlap
    if (b >= i && e <= j)
    {
        return seg_tree[node];
    }
    

    //partial overlap-traverse left and right
    
    int left = 2 * node;
    int right = left + 1;
    int mid = (b + e) / 2;

    int l = query( left, i, j, b, mid);
    int r = query( right, i, j, mid + 1, e);

    return min(l, r);
}
int query_sum(int node, int begin, int end, int i, int j)
{
	if (begin > j || end < i)
        return 0;
	if (begin >= i && end <= j)
		return seg_tree[node];

	int left = 2 * node;
	int right = left + 1;
	int mid = (begin + end) / 2;
	int q1 = query_sum(left, begin, mid, i, j);
	int q2 = query_sum(right, mid + 1, end, i, j);
    return q1 + q2;
}

void update(int node, int begin, int end, int position, int value, string mode)
{
	if (begin == end)
	{
	    if(mode == "replace")
		{
		    seg_tree[node] = value;
            arr[position] = value;
		}
		else if(mode == "add")
        {
            seg_tree[node] += value;
            arr[position] += value;
        }
		return;
	}
	else
	{
		int left = 2 * node;
		int right = 2 * node + 1;
		int mid = (begin + end) / 2;
		if (position >= begin && position <= mid)
			update(left, begin, mid, position, value, mode);
		else
			update(right, mid + 1, end, position, value, mode);
		seg_tree[node] = seg_tree[left] + seg_tree[right];
	}
}

int lazy_update( int node,int val, int i, int j,  int b, int e)
{
    if (lazy_tree[node] != 0)
    {
        seg_tree[node] += lazy_tree[node];
        if (b != e)
        {
            lazy_tree[node * 2] = lazy_tree[node];
            lazy_tree[node * 2 + 1] = lazy_tree[node];
        }
        lazy_tree[node] = 0;
    }

    //no overlap
    if (b > j || e < i)
    {
        return seg_tree[node];
    }

    //total overlap
    if (b >= i && e <= j)
    {
        seg_tree[node] += val;
        if (b != e)
        {
            lazy_tree[node * 2] += val;
            lazy_tree[node * 2 + 1] += val;
        }
        return seg_tree[node];
    }

    int left = 2 * node;
    int right = 2* node + 1;
    int mid = (b + e) / 2;
    int l = lazy_update(left,val, i, j,  b, mid);
    int r = lazy_update(right,val, i, j,  mid + 1, e);
    
    seg_tree[node] = min(l, r);
    return seg_tree[node];
}

int lazy_query(int node, int i, int j, int b, int e)
{
    if (lazy_tree[node] != 0)
    {
        seg_tree[node] += lazy_tree[node];
        if (b != e)
        {
            lazy_tree[node * 2] = lazy_tree[node];
            lazy_tree[node * 2 + 1] = lazy_tree[node];
        }
        lazy_tree[node] = 0;
    }

    if (b > j || e < i)
    {
        return INT_MAX;
    }
    if (b >= i && e <= j)
    {
        return seg_tree[node];
    }
    int left = 2 * node;
    int right = left + 1;
    int mid = (b + e) / 2;

    int l = lazy_query( left, i, j, b, mid);
    int r = lazy_query(right, i, j, mid + 1, e);

    return min(l, r);
}

int main()
{
    int N, Q, i, j;
    cin >> N >> Q;

    

    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
    }

    segment_tree_build(1, 1, N);

    while (Q--)
    {
        int k, v;
        cin >> k >> v;
        cout << query( 1, k, v, 1, N) << "\n";
    }
}