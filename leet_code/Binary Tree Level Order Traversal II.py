#coding:utf8
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param {TreeNode} root
    # @return {integer[][]}
	def levelOrderBottom(self,root):
	    if root==None:
	        return []
	    ret=[]
	    now=[root]
	    while(len(now)!=0):
	        ret.append([i.val for i in now])
	        new_list=[]
	        for i in now:
	            if i.left!=None:
	                new_list.append(i.left)
	            if i.right!=None:
	                new_list.append(i.right)
	        now=new_list
	    return ret[::-1]

if __name__ == '__main__':
	root=TreeNode(3)
	root.left=TreeNode(9)
	root.left.right=TreeNode(45)
	root.right=TreeNode(20)
	root.right.left=TreeNode(15)
	root.right.right=TreeNode(7)
	a=Solution()
	print a.levelOrderBottom(root)
