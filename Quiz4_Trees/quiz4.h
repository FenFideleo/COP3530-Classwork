/*  COP3530
    Student: Erik Meurrens

    Quiz 4: Trees (Sum of a Level)

*/

#include <iostream>
#include <queue>
using std::cout;
using std::endl;

 class TreeNode 
 {
     public:
       int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 };

TreeNode* insert(TreeNode* root, int data) 
{
      if (root == nullptr)
        return new TreeNode(data);
      if (root->val < data)
        root->right = insert(root->right, data);
      else 
        root->left = insert(root->left, data);
      return root;
}

int sumOfLevel(TreeNode* root, int level) 
{
    int sum = 0;
    unsigned int currLevel = 0;
    std::queue<TreeNode*> q({ root });

    while (!q.empty()) {
        if (currLevel == level) {
            sum += q.front()->val;
            q.pop();
            continue;
        }
        else {
            currLevel++;
        }

        for (int i = q.size(); i > 0; i--) {
            if (q.front()->left)
                q.push(q.front()->left);
            if (q.front()->right)
                q.push(q.front()->right);
            q.pop();
        }

    }

    if (sum == 0)
        return -1;
    else
        return sum;
}
