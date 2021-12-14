
import tabulate
import numpy as np

time = [[0.069453  , 0.013431 , 0.011433 , 0.019427 , 0.015432  , 0.013598 , 0.010617],
[0.651358  , 0.116043 , 0.083666 , 0.064406 , 0.11115   , 0.089641 , 0.071479],
[5.415279  , 1.140077 , 0.789125 , 0.620157 , 1.123055  , 0.786196 , 0.613554],
[53.750999 , 10.94354 , 7.436622 , 5.652318 , 10.941552 , 7.389212 , 5.603844]]

parallel_units=[6,9,12,6,9,12]
parallel_units=np.array(parallel_units)

time_matrix=np.array(time)
print("Speed up")
print(tabulate.tabulate(time_matrix[:,0].reshape(-1,1)/time_matrix[:,1:],tablefmt="latex"))


print("Efficiency")
print(tabulate.tabulate(time_matrix[:,0].reshape(-1,1)/(parallel_units*time_matrix[:,1:]),tablefmt="latex"))
