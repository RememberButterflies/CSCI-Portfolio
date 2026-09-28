/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2026.04.27
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #198 House Robber
 *          (https://leetcode.com/problems/house-robber/)
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

class Solution {
public:

    // DP arrays
    vector<int> max_can_rob = {};
    vector<int> max_no_rob = {};

    int get_max_can_rob(int i, int size, vector<int>& nums){
        if(i>=size){
            // out of bounds
            return 0;
        }

        // if already defined, return it
        if(max_can_rob[i] != -1){
            return max_can_rob[i];
        }

        /*
        result rob is (rob current house) + (max of (can rob 2 houses down) or (cannot rob next house))
        result no rob is (max of either rob or dont for the next house)
        */
        int result_rob = nums[i] + max(get_max_can_rob(i+2,size,nums),get_max_no_rob(i+1,size,nums));
        int result_no_rob = max(get_max_can_rob(i+1,size,nums),get_max_no_rob(i+1,size,nums));

        // populate array
        max_can_rob[i] = max(result_rob,result_no_rob);
        return max_can_rob[i];

    }

    int get_max_no_rob(int i, int size, vector<int>& nums){
        if(i>=size){
            // out of bounds
            return 0;
        }

        // if already defined, return it
        if(max_no_rob[i] != -1){
            return max_no_rob[i];
        }

        // same but dont get the can rob value
        int result_no_rob = max(get_max_can_rob(i+1,size,nums),get_max_no_rob(i+1,size,nums));
        // populate array
        max_no_rob[i] = result_no_rob;
        return max_no_rob[i]; 
    }


    int rob(vector<int>& nums) {
        /*
            use 2 DP arrays
            in first, each element in array shows the max you can get from robbing if only the house from then onward exist, and you may rob the first house, but do not have to
            in second, each element shows the max you can rob if only the houses from then onward exist, and you may not rob the first house

            use 2 helper functions to recursively populate these arrays. start from front, but call subsequent runs to get results, checking and updating DP
            then return max of first element of both arrays

            helpers do heavy lifting

            similar to maximum independent set question from csci 439 (algorithms) final
        */
        int size = nums.size();

        // prepopulate arrays
        for(int i=0; i<size; i++){
            max_can_rob.push_back(-1);
            max_no_rob.push_back(-1);
        }


        

        return max(get_max_can_rob(0,size,nums), get_max_no_rob(0,size,nums));
        
    }
};