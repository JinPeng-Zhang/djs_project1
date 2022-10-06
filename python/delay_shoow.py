import  os
import  matplotlib.pyplot as plt
import numpy as np
path = "../delay"
list = os.listdir(path)
cnt = 0

class tim():
    def __init__(self):
        self.second = []
        self.msecond = []
        self.delay = int
    def get_time(self,str):
        str =  str.split('|')
        self.second.append(str[0].split(':')[0])
        self.second.append(str[2].split(':')[0])
        self.msecond.append(str[0].split(':')[1])
        self.msecond.append(str[2].split(':')[1].split('\n')[0])
    def get_delay(self):
        self.delay = (int(self.second[1])-int(self.second[0]))*1000 + \
                     (int(self.msecond[1])-int(self.msecond[0]))

num = 0

for file_name  in  list:
    num += 1
    file = open(path+'/'+file_name,'r')
    delay = []
    for  i in file.readlines():
        t = tim()
        t.get_time(i)
        t.get_delay()
        delay.append(t.delay)

    plt.plot(range(len(delay)),delay)
    plt.plot(range(len(delay)),np.full(30,sum(delay)/len(delay),dtype=float))
    print(f"{file_name}:average is {(float)(sum(delay)/len(delay))} ms")
    plt.legend(('30times','average'))
    plt.xlabel("number of times")
    plt.ylabel("time/ms")
    plt.show()
