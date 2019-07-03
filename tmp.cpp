#include<iostream>
#include<string.h>
using namespace std;
typedef long long ll;
#define MAX 100005
int n,q;
int a[MAX];
ll bit0[MAX],bit1[MAX];
void updata(ll *b,int i,int val)
{
    while(i<=n)
    {
        b[i]+=val;
        i+=i&-i;
    }
}
ll query(ll *b,int i)
{
    ll res=0;
    while(i>0)
    {
        res+=b[i];
        i-=i&-i;
    }
    return res;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin>>n>>q)
    {
        memset(bit0,0,sizeof(bit0));
        memset(bit1,0,sizeof(bit1));
        for(int i=1;i<=n;i++)
        {
           cin>>a[i];
           updata(bit0,i,a[i]);
        }
        while(q--)
        {
            int l,r,x;
            char ch;
            cin>>ch;
            cin>>l>>r;
            if(ch=='C')
            {
                cin>>x;
                updata(bit0,l,-x*(l-1));
                updata(bit1,l,x);
                updata(bit0,r+1,x*r);
                updata(bit1,r+1,-x);
            }
            else
            {
                ll sum=0;
                sum+=query(bit0,r)+query(bit1,r)*r;
                sum-=query(bit0,l-1)+query(bit1,l-1)*(l-1);
                cout<<sum<<endl;
            }
        }
    }
}