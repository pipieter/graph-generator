CC     := gcc
CFLAGS := -O3 -w -lm -Wall -Wextra -Wpedantic

OUT     := graph-generate
SOURCES := main.c graph500/generator/graph_generator.c graph500/generator/make_graph.c graph500/generator/splittable_mrg.c graph500/generator/utils.c

$(OUT): $(SOURCES)
	$(CC) $^ -o $@ $(CFLAGS)
