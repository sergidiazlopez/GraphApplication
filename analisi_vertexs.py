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
directory = os.listdir(f"{current_dir}\\GraphsAnalysis\\vertexs\\")

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

graphs = [
    [10, 20, 4],
    [20, 20, 4],
    [30, 20, 4],
    [40, 20, 4],
    [50, 20, 4],
    [100, 20, 4],
    [200, 20, 4],
    [300, 20, 4],
    [400, 20, 4],
    [500, 20, 4],
    [1000, 20, 4],
    [2000, 20, 4],
    [3000, 20, 4],
    [4000, 20, 4],
    [5000, 20, 4],
    [6000, 20, 4],
    [7000, 20, 4],
    [8000, 20, 4],
    [9000, 20, 4],
    [10000, 20, 4],
]

for algo in algorithms:
    args[2] = algo  # Define arguments for algorithm

    data_X = []
    data_Y = []
    for g in graphs:
        # Define arguments for graph file
        args[3] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\vertexs\\{'graph_' + str(g[0]) + '_' + str(g[1]) + '_' + str(g[2]) + '.GR'}")
        args[4] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\vertexs\\{'graph_' + str(g[0]) + '_' + str(g[1]) + '_' + str(g[2]) + '.VIS'}")
        args[5] = re.sub("\\\\", "/", f"{current_dir}\\LOGS\\{'graph_' + str(g[0]) + '_' + str(g[1]) + '_' + str(g[2]) + '.TRK'}")

        print("Ejecutando tu GraphApplication...")
        print("Algorithm:", algo)
        print("Graph:", g)

        # Execute GraphApplication 10 times
        results = []
        for e in range(0,10):
            subprocess.run(args, cwd=re.sub("\\\\", "/", current_dir))

            # Read execution time
            with open(re.sub("\\\\", "/", f"{current_dir}/Authors"), "r") as f:
                t = float(f.readlines()[-2][:-2].split()[-1])
            results.append(t)


        # Vertex graphic
        data_X.append(g[0])
        mean = numpy.array(results).mean()
        data_Y.append(mean)
        print(mean)
    print(data_Y)
    plt.plot(data_X, data_Y, label=algo)
plt.legend()
#plt.title("Vertex")
plt.xlabel("n.Vertexs")
plt.ylabel("Temps d'execució")
plt.savefig("vertex.png")