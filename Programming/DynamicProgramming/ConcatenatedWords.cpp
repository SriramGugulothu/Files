class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string>set;
        for(string word :words){
            set.insert(word);
        } // Store each word for faster checking
        vector<string>res; // For storing the result.
        for(string word : words){
            int n = word.length();
            vector<int>dp(n+1,0); // dp array for each word. if dp[i] = 1 means some combination word represents till 'i' 
            bool flag = false;
            for(int i=0;i<n;i++){ // Traverse each position
                if(i==0 || dp[i-1]==1){ // I have realised that till my prev position some comb can represent the word, can I build some more combination on top of this?
                    for(int j=i;j<n;j++){
                        string temp = word.substr(i,j-i+1);
                        if(set.find(temp)!=set.end()){
                            dp[j] = 1; // If I can form combination I will mark it 1 for further usage.
                            if(j==n-1 && i != 0){ // If it is comnined by more than 1 word lets add it to result
                                res.push_back(word);
                                flag  = true;
                                break;
                            }
                        }
                    }
                }
                if(flag == true){
                break;
               }
            }
        }
        return res;
    }
};