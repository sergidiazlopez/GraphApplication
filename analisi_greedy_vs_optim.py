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
args_MOD = [f"{current_dir}\\GraphApplicationMOD.exe", "Authors", "Grafo", "Track", "TRK_Dist_Save_Dir"]
algorithms = [
    "greedy",
    #"backtracking",
    #"backtrackinggreedy",
    #"branchandbound1",
    #"branchandbound2",
    "branchandbound3",
    #"probabilistic"
]

# Graph file name, n. vertex, n. edges, n. visits

graphs = [
    [100, 500, 4],
    [200, 500, 4],
    [300, 500, 4],
    [400, 500, 4],
    [500, 500, 4],

]
graphs = [
    [400, 1000, 4],
    [400, 2000, 4],
    [400, 3000, 4],
    [400, 4000, 4],
    [400, 5000, 4],

]

graphs = [
    [400, 500, 5],
    [400, 500, 6],
    [400, 500, 7],
    [400, 500, 8],
    [400, 500, 9],

]

for g in graphs:
    results = []
    print("Graph:", g)
    for algo in algorithms:
        args[2] = algo  # Define arguments for algorithm
        # Define arguments for graph file
        args[3] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\vertexs\\{str(g[0]) + '_' + str(g[1]) + '.GR'}")
        #args[4] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\vertexs\\{str(g[0]) + '_' + str(g[1]) + '.VIS'}")
        args[4] = re.sub("\\\\", "/", f"{current_dir}\\GraphsAnalysis\\vertexs\\{str(g[2]) + '.VIS'}")
        args[5] = re.sub("\\\\", "/", f"{current_dir}\\LOGS\\{str(g[0]) + '_' + str(g[1]) + '.TRK'}")

        args_MOD[2] = args[3]
        args_MOD[3] = args[5]
        args_MOD[4] = args[5] + 'LEN'

        save_file_alumno = args[5]


        # Execute GraphApplication 10 times

        subprocess.run(args, cwd=re.sub("\\\\", "/", current_dir))

        # Read execution time
        with open(re.sub("\\\\", "/", f"{current_dir}/Authors"), "r") as f:
            #t = float(f.readlines()[-2][:-2].split()[-1])
            t = (f.readlines()[-1][:-1])

        #print("Guardando Track Lenght con GraphAppMOD...")

        subprocess.run(args_MOD, cwd=re.sub("\\\\", "/", current_dir))

        with open(f"{save_file_alumno}", "r") as f:
            lines_alumno = f.readlines()

        with open(f"{save_file_alumno + 'LEN'}", "r") as f:
            alumno_dist = float(f.readlines()[0])

        #print(alumno_dist)

        results.append(alumno_dist)

    print(results)
    print("diferencia:", results[0] - results[1])