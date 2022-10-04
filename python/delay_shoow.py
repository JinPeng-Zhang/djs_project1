import  os
import  matplotlib.pyplot as plt
path = "../delay"
list = os.listdir(path)
print(list)
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

for file_name  in  list:
    file = open(path+'/'+file_name,'r')
    delay = []
    for  i in file.readlines():
        t = tim()
        t.get_time(i)
        t.get_delay()
        delay.append(t.delay)
        print(t.delay)
    plt.plot(delay)
    plt.show()
