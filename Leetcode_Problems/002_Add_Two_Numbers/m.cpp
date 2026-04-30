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
 *      Leetcode #2 Add Two Numbers
 *          (https://leetcode.com/problems/add-two-numbers/)
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


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // make a new ListNode* pointers for; the head of new list, the current
        // spot in newlist, the current spots in l1 and l2 and an integer for a
        // carry value and one for the current sum, and 2 for the curr's vals
        ListNode* resultHead = nullptr;        
        ListNode* currResult = nullptr;
        ListNode* currA = l1;
        ListNode* currB = l2;
        int carry = 0;
        int sum = 0;
        int A = 0;
        int B = 0;

        // iterate through both lists together
        // add currA->val + currB->val = sum. check if sum >= 10, if so set
        // carry =1 and sum = sum-10, else carry = 0. set currResult->val = sum.
        // if only 1 of either currA or currB == nullptr, then 0 will be used
        // for its value instead if both are nullptr, end is reached, check if
        // carry =1, and make new node with it. end is reached, return
        // resultHead

        // initialize step
        // get curr vals
        if (currA == nullptr) {
            A = 0;
        } else {
            A = currA->val;
            currA = currA->next;
        }
        if (currB == nullptr) {
            B = 0;
        } else {
            B = currB->val;
            currB = currB->next;
        }

        // get sum, carry, adjust sum
        sum = A + B;
        if (sum >= 10) {
            carry = 1;
            sum = sum - 10;
        } else {
            carry = 0;
        }

        // assign
        resultHead = new ListNode(sum);
        if (resultHead == nullptr) {
            return nullptr;
        }
        currResult = resultHead;

        // 2nd onward
        while ((currA != nullptr) || (currB != nullptr)) {

            // get curr vals
            if (currA == nullptr) {
                A = 0;
            } else {
                A = currA->val;
                currA = currA->next;
            }
            if (currB == nullptr) {
                B = 0;
            } else {
                B = currB->val;
                currB = currB->next;
            }

            // get sum, carry, adjust sum
            sum = A + B + carry;
            if (sum >= 10) {
                carry = 1;
                sum = sum - 10;
            } else {
                carry = 0;
            }

            // set next node, adjust
            ListNode* currResultNext = new ListNode(sum);
            if (currResultNext == nullptr) {
                return nullptr;
            }
            currResult->next = currResultNext;
            currResult = currResult->next;
        }

        // check if carry == 1
        if (carry == 1) {
            ListNode* currResultLast = new ListNode(1);
            if (currResultLast == nullptr) {
                return nullptr;
            }
            currResult->next = currResultLast;
        }

        // return head of result
        return resultHead;
    }
};
