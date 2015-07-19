# Definition for singly-linked list.
class ListNode:
   def __init__(self, x):
       self.val = x
       self.next = None

def addTwoNumbers( l1, l2):
    # if l1==None and l2==None:
    #     return None
        ret=ListNode(0)
        cur=ret
        num=0
        while l1!=None and l2!=None:
            sum=l1.val+l2.val+num
            cur.next=ListNode(sum%10)
            num=sum/10
            l1=l1.next
            l2=l2.next
            cur=cur.next
        while l1!=None:
            sum=l1.val+num
            cur.next=ListNode(sum%10)
            num=sum/10
            l1=l1.next
            cur=cur.next
        while l2!=None:
            sum=l2.val+num
            cur.next=ListNode(sum%10)
            num=sum/10
            l2=l2.next
            cur=cur.next
        if num!=0:
            cur.next=ListNode(num)
        return ret.next


if __name__ == '__main__':
    l1=ListNode(4)
    l1.next=ListNode(5)
    l2=ListNode(7)
    l2.next=ListNode(9)
    print l1.val,l2.val
    print l1.next.val,l2.next.val
    a=addTwoNumbers(l1,l2)
    print a.val    
    print a.next.val
    print a.next.next.val