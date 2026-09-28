/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.07.05
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #4 Median of Two Sorted Arrays
 *          (https://leetcode.com/problems/median-of-two-sorted-arrays/)
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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {

        // variables
        /*
            m, n = sizes of nums1 and nums2
            midpoint = the middle node in merged list, or if even, the one after the middle point
            v = merged array, upto midpoint
            iv, im, in = current element of arrays
            done1, done2 = whether nums1 or nums2 is now empty
            curr1, curr2 = the current elements of nums1, nums2
            result = result

        */
        int m = nums1.size();
        int n = nums2.size();
        int midpoint = ((m+n)/2);
        bool odd = true;
        if ((m+n)%2 == 0){
            // evens need to one further
            odd = false;
            midpoint++;
        }
        vector<int>v;
        int iv = 0;
        int im = 0;
        int curr1;
        int in = 0;
        int curr2;
        bool done1 = false;
        if (m == 0){
            done1 = true;
        }
        bool done2 = false;
        if (n == 0){
            done2 = true;
        }
        double result = 0;


        // while the size of the merged array is less than the midpoint desired,
        while (iv <= midpoint){
            // check if nums1 or nums2 is done
            // and if not, get its current value
            if ((im < m) && (!done1)){
                curr1 = nums1[im];
                done1 = false;
            } else {
                done1 = true;              
            }
            if ((in < n) && (!done2)){
                curr2 = nums2[in];
                done2 = false;
            } else {
                done2 = true;
            }

            // check if either done1 or done2 is true, 
            // if so, populate from the other array until midpoint
            // if neither is done, populate from the smaller one
            // increment the appropriate index, and ultimately the merged size
            if (done1){
                //v[iv] = curr2;
                v.push_back(curr2);
                in++;
            } else if (done2){
                //v[iv] = curr1;
                v.push_back(curr1);
                im++;
            } else if (curr1 <= curr2){
                //v[iv] = curr1;
                v.push_back(curr1);
                im++;
            } else {
                //v[iv] = curr2;
                v.push_back(curr2);
                in++;
            }
            iv++;
        }

    // if m+n is odd, return midpoint, else return average of midpoint and its prev
    // iv is also over incremented by previous loop and also odd/even check. it is undone here
    if (odd){
        // odd
        iv = iv-1;
        result = v[iv];
    } else {
        // even
        iv = iv-2;   // it was incremented earlier
        result = (v[iv] + v[iv-1])/2.0;
    }

    // return result
    return result;
    }
};