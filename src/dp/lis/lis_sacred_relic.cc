/*
change  #1 into 'if (a[c[mid]]<=key)'
and
        #2 into 'if (a[i]<a[c[1]])'
and
        #3 into 'else if (a[i]>=a[c[sz]])'

to solve unstrictly increasing subsequent
*/

#define N 3000

int prev[N],subseq[N],subseq_size;

template <class T>
void backtrack(const T a[],int t,int d)
{
    if (d<1) return;
    backtrack(a,prev[t],d-1);
    subseq[subseq_size++]=a[t];
}

template <class T>
int bsearch(const T a[],const int c[],int sz,const T &key)
{
    int l=1,r=sz;
    while (l<r)
    {
        int mid=(l+r)>>1;
        if (a[c[mid]]<key) l=mid+1;//#1
        else r=mid;
    }
    return l;
}

template <class T>
int LIS(const T a[],int n)//array of index from i(1?) to n
{
    int j,sz=1;
    int *c=new int[n+1]; // c[t]: index (into a) of the tail of the official lis of size t; a[c[]] is ordered;
    int *dp=new int[n+1]; // dp[t]: length of the lis that end at a[t]

    c[1]=1;
    dp[1]=1;

    for (int i=2;i<=n;i++) // iterating through a
    {
        // j: length of the lis that end at a[i]
        // sz: length of longest lis found so far
        if (a[i]<=a[c[1]])         j=1;//#2 ; if current a[i] is so small that it's impossible to append to any existing lis
        else if (a[i]>a[c[sz]])    j=++sz;//#3 ; if current a[i] is so big that it can append to the longest lis so far and make the longest lis longer
        else                       j=bsearch(a,c,sz,a[i]); // find where to insert.

        c[j]=i;
        dp[i]=j;
        prev[i]=c[j-1];
    }

    backtrack(a,c[sz],sz);
    delete[] c;
    delete[] dp;
    return sz;
}