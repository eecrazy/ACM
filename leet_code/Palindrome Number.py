#coding:utf8
def isPalindrome(x):
	x=str(x)
	l=len(x)
	if(l<=1):
		return True
	if(l%2==0):
		if x[0:l/2]==x[-1:l/2-1:-1]:
			return True
		else:
			return False
	else:
		if x[0:l/2]==x[-1:l/2:-1]:
			return True
		else:
			return False

if __name__ == '__main__':
	print isPalindrome(123212)