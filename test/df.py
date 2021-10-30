import eulerlib
import arith_lib

import sys
numbers = []
for line in open(sys.argv[1],'r'):
    numbers+=[int(line)]

# div= eulerlib.Divisors(max(numbers))

# result = list(map(div.phi,numbers))
result = list(map(lambda x: len(arith_lib.divisors(x)),numbers))
str_result= '\n'.join([str(int(i)) for i in result])
with open(sys.argv[2],'r') as fout:
    for i, line in enumerate(fout):
        number = int(line)
        if number == result[i]:
            pass
        else:
            print("Different",number,result[i],'line',i+1)
            raise SystemExit
print("Equal")
    # fout.write(str_result)
