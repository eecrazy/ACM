#coding:utf8

#这道题要求log(m+n),我的解法好像是   (m+n)log(m+n)的，因为用到了排序
def findMedianSortedArrays(nums1, nums2):
        m=len(nums1)
        n=len(nums2)
        c=m+n
        yu=(m+n)%2
        if m==0:
            if yu==1:
                return float(nums2[n/2])
            else:
                return float(nums2[n/2]+nums2[n/2-1])/2
        if n==0:
            if yu==1:
                return float(nums1[m/2])
            else:
                return float(nums1[m/2]+nums1[m/2-1])/2
        nums1.extend(nums2)
        nums1.sort()
        if yu==1:
            return float(nums1[c/2])
        else:
            return float(nums1[c/2]+nums1[c/2-1])/2


if __name__ == '__main__':
    nums1=[1,4,455,13,24,2,5,25,5]
    nums2=[2,3]
    print findMedianSortedArrays(nums1,nums2)