#include <iostream>
#include <vector>
using namespace std;
void findSubsets(vector<int>& nums, vector<int>& current, int index, int target, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    if (index >= nums.size() || target < 0) {
        return;
    }
    current.push_back(nums[index]);
    findSubsets(nums, current, index + 1, target - nums[index], result);
    current.pop_back();
    findSubsets(nums, current, index + 1, target, result);
}
int main() {
    vector<int> nums = {1, 2, 5, 6, 8};
    int target = 9;
    vector<vector<int>> result;
    vector<int> current;
    findSubsets(nums, current, 0, target, result);
    if (result.empty()) {
        cout << "No subset found that sums to " << target << "." << endl;
    } else {
        cout << "Subsets that sum to " << target << ":" << endl;
        for (const auto& subset : result) {
            cout << "{ ";
            for (int num : subset) {
                cout << num << " ";}
            cout << "}" << endl;}}
    return 0;
}
