#coding:utf8

def lengthOfLongestSubstring(s):
        l=len(s)
        ret=0
        my_hash={}
        i=0
        index=0
        if l==1:
            return 1
        while index<l:
            if s[index] in my_hash:
                if index-i>ret:
                    ret=index-i
                temp=i
                i=my_hash[s[index]]+1
                for y in xrange(temp,i):
                    del my_hash[s[y]]
            else:
                my_hash[s[index]]=index
                index+=1

        if index-i>ret:
            ret=index-i
        return ret

if __name__ == '__main__':
    print lengthOfLongestSubstring("ohomm")