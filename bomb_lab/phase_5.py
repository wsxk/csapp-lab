box = [109   ,  97  ,    100    , 117   ,  105 ,    101  ,   114 ,    115, 110   ,  102   ,  111   ,  116  ,   118  ,   98    ,  121  ,   108]
key ='flyers'
key_list =[]
for i in range(6):
    key_list.append(ord(key[i]))
flag =[]
for i in range(6):
    for j in range(32,255):
        a = (j&0xf)
        if box[a]==key_list[i]:   
            flag.append(j)
            
            break
print(bytes(flag))

        
    
