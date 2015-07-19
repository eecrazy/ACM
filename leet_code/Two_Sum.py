class Solution:
    # @param {integer[]} nums
    # @param {integer} target
    # @return {integer[]}
    def twoSum(self, nums, target):
        ret=[]
        num_hash={}
        num=0
        ok=0
        if target % 2==0:
            half=target/2
            ok=1
        for i in nums:
            num+=1
            if ok==1 and half==i and i in num_hash:
                ret.append(num_hash[i])
                ret.append(num)
                return ret
            num_hash[i]=num
        for i in nums:
            val=target-i
            if val not in num_hash or num_hash[i]==num_hash[val]:
                continue
            if num_hash[i]<num_hash[val]:
                ret.append(num_hash[i])
                ret.append(num_hash[val])
                return ret
            else:
                ret.append(num_hash[val])
                ret.append(num_hash[i])
                return ret
