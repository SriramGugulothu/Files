 /* Burst ballons -1 */
#include <iostream>
#include<vector>
#include<climits>
using namespace std;
int fun(vector<int>ballons,int i,int j,int count,vector<vector<int>>&dp){
    if(i>j){
        return 0;
    }
    if(dp[i][j] != -1){
    	return dp[i][j];
	}
    int maxi = INT_MIN;
    for(int k = i;k<=j;k++){
        int val = 0;
        if(count==0){
            val = ballons[k];
        }
        else{
            val = ballons[i-1]*ballons[j+1];
        }
        int temp = fun(ballons,i,k-1,count+1,dp) + fun(ballons,k+1,j,count+1,dp);
        maxi = max(maxi,temp+val);
    }
    return dp[i][j] = maxi;
}
int main() { 
    int n;
    cin>>n;
    vector<int>ballons(n+2);
    ballons[0] = 1;
    ballons[n+1] =1;
    for(int i=1;i<=n;i++){
        cin>>ballons[i];
    }    
    int count = 0;
    vector<vector<int>>dp(n+3,vector<int>(n+3,-1));
   cout<<fun(ballons,1,n,count,dp);
}
