LIB=./lib
INCLUDE=./include
SRC=./src
OBJ=./obj
UTIL=util

CC=gcc

FLAGS=  -O3 -Wall


INCFLAGS = -I$(INCLUDE) -I$(INCLUDE)/$(UTIL)

all: libOPF opf_split opf_accuracy opf_train opf_classify opf_learn opf_distance opf_info opf_fold opf_merge opf_cluster statistics txt2opf opf2txt opf_check opf_normalize opfknn_train opfknn_classify Myopfknn_train Myopfknn_classify

libOPF: libOPF-build
	echo "libOPF.a built..."

libOPF-build: \
util \
$(OBJ)/OPF.o \

	ar csr $(LIB)/libOPF.a \
$(OBJ)/common.o \
$(OBJ)/set.o \
$(OBJ)/gqueue.o \
$(OBJ)/realheap.o \
$(OBJ)/sgctree.o \
$(OBJ)/subgraph.o \
$(OBJ)/OPF.o \

$(OBJ)/OPF.o: $(SRC)/OPF.c
	$(CC) $(FLAGS) -c $(SRC)/OPF.c $(INCFLAGS) \
	-o $(OBJ)/OPF.o

opf_split: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_split.c  -L./lib -o bin/opf_split -lOPF -lm

opf_accuracy: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_accuracy.c  -L./lib -o bin/opf_accuracy -lOPF -lm

opf_train: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_train.c  -L./lib -o bin/opf_train -lOPF -lm

opf_classify: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_classify.c  -L./lib -o bin/opf_classify -lOPF -lm

opf_learn: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_learn.c  -L./lib -o bin/opf_learn -lOPF -lm

opf_distance: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_distance.c  -L./lib -o bin/opf_distance -lOPF -lm

opf_info: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_info.c  -L./lib -o bin/opf_info -lOPF -lm

opf_fold: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_fold.c  -L./lib -o bin/opf_fold -lOPF -lm

opf_merge: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_merge.c  -L./lib -o bin/opf_merge -lOPF -lm

opf_cluster: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_cluster.c  -L./lib -o bin/opf_cluster -lOPF -lm
	
statistics:
	$(CC) $(FLAGS) tools/src/statistics.c  -o tools/statistics -lm

txt2opf: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) tools/src/txt2opf.c  -L./lib -o tools/txt2opf -lOPF -lm

opf_check: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) tools/src/opf_check.c  -L./lib -o tools/opf_check -lOPF -lm

opf2txt: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) tools/src/opf2txt.c  -L./lib -o tools/opf2txt -lOPF -lm

opf_normalize: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opf_normalize.c  -L./lib -o bin/opf_normalize -lOPF -lm
	
opfknn_train: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opfknn_train.c  -L./lib -o bin/opfknn_train -lOPF -lm

opfknn_classify: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/opfknn_classify.c  -L./lib -o bin/opfknn_classify -lOPF -lm

Myopfknn_train: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/Myopfknn_train.c  -L./lib -o bin/Myopfknn_train -lOPF -lm

Myopfknn_classify: libOPF
	$(CC) $(FLAGS) $(INCFLAGS) src/Myopfknn_classify.c  -L./lib -o bin/Myopfknn_classify -lOPF -lm

util: $(SRC)/$(UTIL)/common.c $(SRC)/$(UTIL)/set.c $(SRC)/$(UTIL)/gqueue.c $(SRC)/$(UTIL)/realheap.c $(SRC)/$(UTIL)/sgctree.c $(SRC)/$(UTIL)/subgraph.c
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/common.c -o $(OBJ)/common.o
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/set.c -o $(OBJ)/set.o
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/gqueue.c -o $(OBJ)/gqueue.o
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/realheap.c -o $(OBJ)/realheap.o
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/sgctree.c -o $(OBJ)/sgctree.o
	$(CC) $(FLAGS) $(INCFLAGS) -c $(SRC)/$(UTIL)/subgraph.c -o $(OBJ)/subgraph.o


## Compiling LibOPF with LibIFT

opf-ift: libOPF-ift

libOPF-ift: libOPF-ift-build
	echo "libOPF.a built with IFT..."

libOPF-ift-build: \
OPF-ift.o \

	ar csr $(LIB)/libOPF.a \
$(OBJ)/OPF.o \

OPF-ift.o: $(SRC)/OPF.c
	$(CC) $(FLAGS) -c $(SRC)/OPF.c -I$(INCLUDE) -I$(IFT_DIR)/include \
	-o $(OBJ)/OPF.o

## Cleaning-up

clean:
	rm -f $(LIB)/lib*.a; rm -f $(OBJ)/*.o bin/* tools/opf_check tools/statistics tools/txt2opf tools/opf2txt tools/opf_check

clean_results:
	rm -f *.out *.opf *.acc *.time *.opf training.dat evaluating.dat testing.dat

clean_results_in_examples:
	rm -f examples/*.out examples/*.opf examples/*.acc examples/*.time examples/*.opf examples/training.dat examples/evaluating.dat examples/testing.dat


