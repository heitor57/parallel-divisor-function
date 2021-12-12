#!/usr/bin/python3
import random
from sys import argv
import os
import os.path

os.makedirs(os.path.dirname(argv[1]), exist_ok=True)

with open(argv[1], "w") as f:
    n = int(argv[2])
    for i in range(n):
        f.write("%d\n" % random.randint(2, 2000000000))
