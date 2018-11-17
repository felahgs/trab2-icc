       PROG   = cgSolver
    MODULOS   = utils \
                geraMat \
                validateEntry \
                gradients

           CC = gcc -std=c11 -g
         OBJS = $(addsuffix .o,$(MODULOS))

         LIKWID = /home/soft/likwid
        # LIKWID = /usr/local
 LIKWID_FLAGS = -I$(LIKWID)/include
  LIKWID_LIBS = -L$(LIKWID)/lib

   AVX_FLAGS = -march=native -mavx -O3 -falign-functions=32 -falign-loops=32 -fstrict-aliasing
   AVX_LOG_FLAGS = -fopt-info-vec -fopt-info-vec-missed 

       CFLAGS = $(LIKWID_FLAGS) 
       LFLAGS = $(LIKWID_LIBS) -lm

.PHONY: all clean limpa purge faxina distclean debug avx likwid

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

all: $(PROG)

doc: Doxyfile
	doxygen $<

debug:         CFLAGS += -DDEBUG

avx:           CFLAGS += $(AVX_FLAGS) $(AVX_LOG_FLAGS)
avx likwid:    CFLAGS += -DLIKWID_PERFMON
avx likwid:    LFLAGS += -llikwid

Doxyfile:
	doxygen -g
	sed -e "s;OPTIMIZE_OUTPUT_FOR_C *= *.*;OPTIMIZE_OUTPUT_FOR_C = YES;g" $@ >$@.new
	sed -e "s;EXTRACT_ALL *= *.*;EXTRACT_ALL = YES;g" $@.new >$@
	sed -e "s;EXTRACT_PRIVATE *= *.*;EXTRACT_PRIVATE = YES;g" $@ >$@.new
	sed -e "s;EXTRACT_STATIC *= *.*;EXTRACT_STATIC = YES;g" $@.new >$@
	sed -e "s;EXTRACT_LOCAL_METHODS *= *.*;EXTRACT_LOCAL_METHODS = YES;g" $@ >$@.new
	sed -e "s;GENERATE_LATEX *= *.*;GENERATE_LATEX = NO;g" $@.new >$@
	sed -e "s;SOURCE_BROWSE *= *.*;SOURCE_BROWSE = YES;g" $@ >$@.new
	sed -e "s;VERBATIM_HEADER *= *.*;VERBATIM_HEADER = YES;g" $@.new >$@
	rm -f $@.new

likwid avx debug: $(PROG)

$(PROG):  $(PROG).o

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp

purge distclean:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) *.o core a.out
	@rm -f *.png marker.out *.log
