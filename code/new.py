import networkx as nx
from networkx import algorithms
import numpy as np
import random
from networkx.algorithms import components
from networkx.algorithms.components import  strongly_connected_components
from networkx.algorithms.components import *

n = 200
q = 0.5
#tf = open("Output.txt", "w")
a = np.identity(n)
for x in range(0, n):
	for y in range(0,n):
		random.seed()
		if x==y :
			a[x][y]=0
			#tf.write("0")
		elif random.randrange(1,1000000)/1000000 < q :
			a[x][y]=-1
			#tf.write(" ")
			#tf.write("-1")
		else :
			a[x][y]=1
			#tf.write("1")


G=nx.from_numpy_matrix(a)
H=G.to_directed()
S=strongly_connected_components(H)
L=list(nx.dfs_postorder_nodes(H))
sg=list(S)

