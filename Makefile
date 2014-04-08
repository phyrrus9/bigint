BINDIR = bin
OBJS = $(BINDIR)/bigint.o $(BINDIR)/miscoperations.o $(BINDIR)/arithmatichelpers.o $(BINDIR)/arithmaticops.o $(BINDIR)/comparisonops.o $(BINDIR)/unaryops.o $(BINDIR)/bitwiseops.o $(BINDIR)/unarybitwiseops.o
SRCS = bigint.cpp miscoperations.cpp arithmatichelpers.cpp arithmaticops.cpp comparisonops.cpp unaryops.cpp bitwiseops.cpp unarybitwiseops.cpp
INCL = bigint.h arithmatichelpers.h
FLAGS =
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
OUT = $(BINDIR)/libbig.so
endif
ifeq ($(UNAME), Darwin)
OUT = $(BINDIR)/libbig.dylib
endif

all: $(OUT) $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/libbig.so: $(OBJS) $(BINDIR)
	g++ -shared $(OBJS) -o libbig.so

$(BINDIR)/libbig.dylib: $(OBJS) $(BINDIR)
	libtool -dynamic -flat_namespace -install_name /usr/lib/libbig.dylib  -lSystem -compatibility_version 1.0 -current_version 1.0.0  -undefined suppress $(OBJS) -o $(BINDIR)/libbig.dylib -macosx_version_min 10.6

$(BINDIR)/bigint.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/bigint.o -c bigint.cpp $(FLAGS)
	
$(BINDIR)/miscoperations.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/miscoperations.o -c miscoperations.cpp $(FLAGS)

$(BINDIR)/arithmatichelpers.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/arithmatichelpers.o -c arithmatichelpers.cpp $(FLAGS)

$(BINDIR)/arithmaticops.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/arithmaticops.o -c arithmaticops.cpp $(FLAGS)

$(BINDIR)/comparisonops.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/comparisonops.o -c comparisonops.cpp $(FLAGS)

$(BINDIR)/unaryops.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/unaryops.o -c unaryops.cpp $(FLAGS)

$(BINDIR)/bitwiseops.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/bitwiseops.o -c bitwiseops.cpp $(FLAGS)

$(BINDIR)/unarybitwiseops.o: $(SRCS) $(BINDIR)
	g++ -o $(BINDIR)/unarybitwiseops.o -c unarybitwiseops.cpp $(FLAGS)

install: $(OUT) $(INCL)
	cp $(OUT) /usr/lib/
	cp bigint.h /usr/include/

clean:
	rm -rf $(BINDIR)
