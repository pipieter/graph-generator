# Graph Generator

Generates directed graph files using on Graph500's Kronecker graph generator implementation. Graphs are saved as DIMACS graph file format.

## Building

The binary can be built using `make`.

## Usage

```bash
./graph-generator [path] [edges] (density) 
```

The amount of edges needs to be a power of two. If it is not, it will be lowered to the previous power of two. Density expects a number between 0.0001 and 1.0, otherwise it will be clipped between those two values. Density has a default value of 0.25.

Example:

```bash
./graph-generator 1024.graph 1024 0.25
```

Note that the amount of edges will approximate the density, and is not guaranteed to equal it. The edges in the resulting DIMACS file are not sorted, and duplicate edges can occur.