/**
 * @file    m.cpp
 * @author  Patrick McGrath
 * @version 1.0.0
 * @date    2025.07.09
 *
 * @brief   File contains solution for;
 * 
 * 
 * 
 * 
 *      Leetcode #701 Insert Into a Binary Search Tree
 *          (https://leetcode.com/problems/insert-into-a-binary-search-tree/)
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
    TreeNode* insertIntoBST(TreeNode* root, int val) {

        // node for val
        TreeNode* result = new TreeNode(val);

        // check for empty root, return val's node if so
        if (root == nullptr){
            return result;
        }

        // root not null, find leaf to be result's parent
        // and do linking
        TreeNode* parent = root;
        while (1){
            if (val < parent->val){
                if (parent->left == nullptr){
                    parent->left = result;
                    return root;
                } else {
                    parent = parent->left;
                }
            } else {
                if (parent->right == nullptr){
                    parent->right = result;
                    return root;
                } else {
                    parent = parent->right;
                }
            }
        }

        // some error
        return nullptr;
    }

};