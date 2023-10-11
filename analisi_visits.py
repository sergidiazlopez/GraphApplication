# Ejecutar el programa

import filecmp
import subprocess
import os
import re
import time
import matplotlib.pyplot as plt
import numpy
import numpy as np
import pandas

current_dir = os.path.dirname(os.path.realpath(__file__))
directory = os.listdir(f"{current_dir}\\GraphsAnalysis\\visits\\")

args = [f"{current_dir}\\GraphApplicationProf.exe", "Authors", "probabilistic", "Grafo", "Visitas", "TRK_Save_Dir"]
#args = [f"{current_dir}\\x64\\Release\\GraphApplication.exe", "Authors", "probabilistic", "Grafo", "Visitas", "TRK_Save_Dir"]

algorithms = [
    "greedy",
    #"backtracking",
    "backtrackinggreedy",
    "branchandbound1",
    "branchandbound2",
    "branchandbound3",
    #"probabilistic"
]

# Graph file name, n. vertex, n. edges, n. visits
graph = 'graph_30_100'
visits = [3,5,6,7,8,9,10]

for algo in algorithms:
    args[2] = algo  # Define arguments for algorithm

    data_X = []
    data_Y = []
    for v in visits:
        # Define arguments for graph file
        args[3] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\visits\\{graph + '.GR'}")
        args[4] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\visits\\{str(v) + '.VIS'}")
        args[5] = re.sub("\\\\", "/", f"{current_dir}\\LOGS\\{graph + '.TRK'}")

        print("Ejecutando tu GraphApplication...")
        print("Algorithm:", algo)
        print("Graph:", graph)
        print("Visits:", v)

        # Execute GraphApplication 10 times
        results = []
        for e in range(0,10):
            subprocess.run(args, cwd=re.sub("\\\\", "/", current_dir))

            # Read execution time
            with open(re.sub("\\\\", "/", f"{current_dir}/Authors"), "r") as f:
                t = float(f.readlines()[-2][:-2].split()[-1])
            results.append(t)

        # Vertex graphic
        data_X.append(v)
        mean = numpy.array(results).mean()
        print(mean)
        data_Y.append(mean)
    print(data_Y)
    plt.plot(data_X, data_Y, label=algo)
plt.legend()
#plt.title("Visits")
plt.xlabel("n.Visits")
plt.ylabel("Temps d'execució")
plt.savefig("visits.png")