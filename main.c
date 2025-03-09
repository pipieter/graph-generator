#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph500/generator/graph_generator.h"
#include "graph500/generator/make_graph.h"

int main(int argc, const char **argv) {
  float density;
  const uint64_t seed1 = 0x1234;
  const uint64_t seed2 = 0x5678;

  const char *path;
  int64_t nvertices;
  int64_t log2_nvertices;
  int64_t desired_nedges;
  int64_t nedges;
  packed_edge *edge_list;
  FILE *file;

  int64_t v0, v1;

  if (argc < 3) {
    printf("Usage: generator [path] [nvertices] (density)\n");
    printf("  - path:        The name of the output file.\n");
    printf("  - nvertices:   The amount of vertices in the graph. Must be a power of two (will be rounded down to the nearest lower power of two).\n");
    printf("  - density:     (optional) The density of the graph, a value between 0 and 1. The default value is 0.25\n");
    return 0;
  }

  if (argc >= 4) {
    density = atof(argv[3]);
  } else {
    density = 0.25f;
  }
  density = density < 0.0 ? 0.01 : density;
  density = density > 1.0 ? 1.0  : density;

  nvertices = atoi(argv[2]);
  log2_nvertices = (int)floor(log2(nvertices));
  nvertices = pow(2, log2_nvertices);
  desired_nedges = (int64_t)(density * nvertices * (nvertices - 1) / 2);

  make_graph(log2_nvertices, desired_nedges, seed1, seed2, &nedges, &edge_list);

  path = argv[1];
  file = fopen(path, "w");
  if (!file) {
    fprintf(stderr, "Could not create or write to %s\n", path);
    return 1;
  }

  fprintf(file, "p GENERATED %ld %ld\n", nvertices, nedges);

  for (int i = 0; i < nedges; i++) {
    v0 = get_v0_from_edge(&edge_list[i]);
    v1 = get_v1_from_edge(&edge_list[i]);
    fprintf(file, "e %ld %ld\n", v0, v1);
  }

  fclose(file);

  free(edge_list);

  return 0;
}