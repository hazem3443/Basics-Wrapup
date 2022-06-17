def swapCount(s):
     
    chars = s
    countLeft = 0
    countRight = 0
    swap = 0
    imbalance = 0
    
    br_open ,br_close = 0,0
    for i in range(len(chars)):
        if chars[i] == '(':
            br_open +=1
            countLeft += 1
            if imbalance > 0:
                swap += imbalance
                imbalance -= 1
        elif chars[i] == ')':
            br_close +=1
            countRight += 1
            imbalance = (countRight - countLeft)

    if((br_close - br_open)!=0):
        return -1
 
    return swap
 
# Driver code
# s = "(()))("
# print(swapCount(s))
 
# s = "()())"
# print(swapCount(s))

# s = ")()(()(" 
# print(swapCount(s))#1

# # s = "))()(()(" 
# # print(swapCount(s))#1



def BalancedStringBySwapping(s) :
	unbalancedPair = 0;
	for i in range(len(s)) :
		if (unbalancedPair > 0 and s[i] == ')') :
		
			unbalancedPair -= 1;
		elif (s[i] == '(') :
		
			unbalancedPair += 1;

	return (unbalancedPair + 1) // 2;

# s = "]][][[][";
# print(BalancedStringBySwapping(s));

s = ")()(())("
print(swapCount(s))
 
s = "()())"
print(swapCount(s))

s = ")()(()(" 
print(swapCount(s))#1

s = "))()(()(" 
print(swapCount(s))#1