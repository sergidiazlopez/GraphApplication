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
directory = os.listdir(f"{current_dir}\\GraphsAnalysis\\arestes\\")

args = [f"{current_dir}\\GraphApplicationProf.exe", "Authors", "probabilistic", "Grafo", "Visitas", "TRK_Save_Dir"]
#args = [f"{current_dir}\\x64\\Release\\GraphApplication.exe", "Authors", "probabilistic", "Grafo", "Visitas", "TRK_Save_Dir"]

algorithms = [
    #"greedy",
    ##"backtracking",
    #"backtrackinggreedy",
    #"branchandbound1",
    #"branchandbound2",
    #"branchandbound3",
    "probabilistic"
]

# Graph file name, n. vertex, n. edges, n. visits
graphs_2 = [
    ["Graf10_20_3",10,20,3],
    ["graf20_100_4",20,100,4],
    ["graf30_300_8",30,300,8],
    ["Graf50_200_6",50,200,6],
    ["Graf100_200_17",100,200,17]

]

graphs = [
    [500, 100, 4],
    [500, 300, 4],
    [500, 500, 4],
    [500, 700, 4],
    [500, 1000, 4],
    [500, 3000, 4],
    [500, 5000, 4],
    [500, 7000, 4],
    [500, 10000, 4],
]

for algo in algorithms:
    args[2] = algo  # Define arguments for algorithm

    data_X = []
    data_Y = []
    for g in graphs:
        # Define arguments for graph file
        args[3] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\arestes\\{'graph_' + str(g[0]) + '_' + str(g[1]) + '_' + str(g[2]) + '.GR'}")
        args[4] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\arestes\\{'graph_' + str(g[0]) + '_' + str(g[1]) + '_' + str(g[2]) + '.VIS'}")
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
        data_X.append(g[1])
        data_Y.append(numpy.array(results).mean())
    print(data_Y)
    plt.plot(data_X, data_Y, label=algo)
plt.legend()
plt.xlabel("n.Arestes")
plt.ylabel("Temps d'execució")
plt.savefig("arestes.png")