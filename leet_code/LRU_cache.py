#coding:utf8

class LRUCache:
    # @param capacity, an integer
    def __init__(self, capacity):
        self.cache={}
        self.max_len=capacity
        self.pos={}
        self.a=[]

    # @return an integer
    def get(self, key):
        if key in self.cache:
            #记录最近一次使用key   
            self.a.remove(key)
            self.a.insert(0,key)         
            return self.cache[key]
        else:
            return -1

    # @param key, an integer
    # @param value, an integer
    # @return nothing
    def set(self, key, value):
        if key in self.cache:
            self.cache[key]=value
            self.a.remove(key)
            self.a.insert(0,key)
            #更新，记录最近一次使用key
        else:
            if len(self.cache)<self.max_len:
                #cache空间没有满，可以插入新的记录，并且记录key
                self.cache[key]=value
                self.a.insert(0,key)
            else:
                #cache空间已满，删除最近最久未使用的key,并删除之。
                #插入新的记录，并且记录key的使用
                b=self.a.pop()
                self.a.insert(0,key)
                if b in self.cache:
                    del self.cache[b]
                self.cache[key]=value

if __name__ == '__main__':
    lru=LRUCache(2)
    lru.set(2,1)
    lru.set(1,1)
    print lru.get(2)
    lru.set(4,2)
    print lru.get(1)
    print lru.get(2)









                