all : solver

CCC = g++
CCFLAGS = -O3 
LIBS= -lm
TARGETDIR=.
CPPFLAGS += \
         -I. \
		 -std=c++11

OBJS2 = \
	    $(TARGETDIR)/removals.o \
        $(TARGETDIR)/repairs.o \
	    $(TARGETDIR)/main.o \
        $(TARGETDIR)/vrp.o \
        $(TARGETDIR)/cvrp.o \
        $(TARGETDIR)/vehicle.o \
        $(TARGETDIR)/solution.o \
        $(TARGETDIR)/params.o \
        $(TARGETDIR)/alns.o \

$(TARGETDIR)/solver: $(OBJS2)
	$(CCC)  $(CCFLAGS) -o $(TARGETDIR)/solver $(OBJS2)

$(TARGETDIR)/params.o: Params.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Params.cpp -o $(TARGETDIR)/params.o

$(TARGETDIR)/removals.o: removals.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c removals.cpp -o $(TARGETDIR)/removals.o

$(TARGETDIR)/repairs.o: repairs.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c repairs.cpp -o $(TARGETDIR)/repairs.o

$(TARGETDIR)/vrp.o: vrp.hpp vrp.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c vrp.cpp -o $(TARGETDIR)/vrp.o

$(TARGETDIR)/cvrp.o: cvrp.hpp cvrp.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c cvrp.cpp -o $(TARGETDIR)/cvrp.o

$(TARGETDIR)/vehicle.o: vehicle.hpp vehicle.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c vehicle.cpp -o $(TARGETDIR)/vehicle.o

$(TARGETDIR)/solution.o: solution.hpp solution.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c solution.cpp -o $(TARGETDIR)/solution.o

$(TARGETDIR)/alns.o: alns.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c alns.cpp -o $(TARGETDIR)/alns.o

$(TARGETDIR)/main.o: main.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c main.cpp -o $(TARGETDIR)/main.o

clean:
	 $(RM) \
     $(TARGETDIR)/*.o