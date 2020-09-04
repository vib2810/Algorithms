int Solution::solve(string A, string B) 
{
    int ans=INT_MIN;
    for(int i=0; i<A.length(); i++)
    {
        //starting point (i,0) 
        //filling diagonally
        int len=A.length()-i;
        int *dp=new int[len];
        if(A[i]==B[0]) dp[0]=1;
        else dp[0]=0;
        if(dp[0]>ans) ans=dp[0];
        //  cout<<dp[0]<<" "<<(i)<<" "<<0<<endl;
        for(int j=1; j<len; j++)
        {

            if(A[i+j]==B[j]) dp[j]=dp[j-1]+1;
            else dp[j]=0;
            if(ans<dp[j]) 
            {
                cout<<dp[j]<<" "<<(i+j)<<" "<<j<<endl;
                ans=dp[j];
            }
        }
    }
    for(int i=1; i<B.length(); i++)
    {
        //starting point (0,i) 
        //filling diagonally
        int len=B.length()-i;
        int *dp=new int[len];
        if(A[0]==B[i]) dp[0]=1;
        else dp[0]=0;
        if(dp[0]>ans) ans=dp[0];
        for(int j=1; j<len; j++)
        {
            if(A[j]==B[i+j]) dp[j]=dp[j-1]+1;
            else dp[j]=0;
            if(ans<dp[j]) 
            {
                ans=dp[j];
                cout<<dp[j]<<" "<<(j)<<" "<<(i+j)<<endl;
            }
        }
    }
    return ans;
}
