import  os
path = "../delay"
list = os.listdir(path)
print(list)
cnt = 0
for file_name  in  list:
    file = open(path+'/'+file_name,'r')
    for  i in file.readlines():
        print(i)
        cnt = cnt +1
        print(cnt)
        pass