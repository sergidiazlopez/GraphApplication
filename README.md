# Traveling Salesman Problem

![[sshot-009.png]]

## Problem Description

Imagine you need to deliver mail to various points on a campus, and your goal is to find the shortest route that visits all these points and returns to the starting point. This problem is known as the Traveling Salesman Problem (TSP).

### Modeling the Network of Paths

We can model the network of paths as an undirected weighted graph where:

- Each node represents a location on the campus that can receive mail (or an intersection of paths).
- Each edge has a weight representing the Euclidean distance between the two connected locations.

The objective is to visit a subset of nodes in a way that minimizes the total route length.

## Formal Model of the Traveling Salesman Problem

The formal model of the Traveling Salesman Problem consists of:

- A list of vertices representing the mail delivery points.
- The starting point as the first vertex.
- The destination point as the last vertex.
- The solution route corresponds to the list of vertices in the order they are visited. It includes all vertices of the graph, even if they are not part of the route.

## Project Objective

The main objective of this project is to apply various algorithmic techniques to solve the Traveling Salesman Problem and analyze and compare the results obtained.

## Application

The project involves using basic C++ programming skills, including:

- Control structures and exceptions.
- Working with structs, classes, and templates (template creation is not required).
- Functions and methods.
- Compilation with Visual Studio 2019.

## Algorithms

- **Dijkstra**
- **TSP Greedy** 
- **TSP Backtracking Pure** 
- **TSP Backtracking Greedy** 
- **TSP Branch and Bound** (not included)
- **TSP Probabilistic**
