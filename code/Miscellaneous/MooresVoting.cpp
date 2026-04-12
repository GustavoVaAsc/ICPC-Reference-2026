int majorityElement(vector<int>& nums) {
    int vote = 0, r = 0;
    for(int i=0; i<nums.size();i++){
        if(nums[i] == nums[r])
            vote++;
        else
            vote--;
        if(vote == 0){
            r = i;
            vote = 1;
        } 
    }

    int cnt = 0;
    int goal = (nums.size())/2;
    for(int i=0; i<nums.size(); i++){
        if(nums[i] == nums[r]){
            cnt++;
            if(cnt > goal){
                break;
            }
        }
    }

    return nums[r];
}