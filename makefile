CC = g++ #le compilateur
flags = -W -std=c++20 -lpthread

headers = Exception/exception.h Utils/utils.h Trading/trading.h Simulation/simulation.h

exceptionFile = Exception/exceptionAIO.cpp
exceptionIncludes = $(headers) Exception/exception.cpp
exceptionObj = exception.o

utilsFile = Utils/utilsAIO.cpp 
utilsIncludes = $(headers) Utils/utilsTemplatesException.hpp Utils/utilsException.hpp Utils/tabExt.hpp Utils/tabExt2.hpp Utils/table.cpp
utilsObj = utils.o

tradingFile = Trading/tradingAIO.cpp
tradingIncludes = $(headers) Trading/tradingException.hpp Trading/bougie.cpp Trading/timeFrame.cpp Trading/chart.cpp
tradingObj = trading.o

simulationFile = Simulation/simulationAIO.cpp
simulationIncludes = $(headers) Simulation/simulationException.hpp Simulation/random.cpp Simulation/brownian.cpp Simulation/heston.cpp Simulation/StocReturn.cpp
simulationObj = simulation.o

mainFile = work.cpp
objs = $(exceptionObj) $(utilsObj) $(tradingObj) $(simulationObj)
exe = test


all: $(exe) clean execution

$(exe):  $(objs) main.o
	@echo -n
	@echo edition des liens :
	@echo -n "\t"
	$(CC) -o $@ $(objs) main.o

$(simulationObj) : $(simulationFile)
	@echo -n
	@echo compilation de $(simulationFile):
	@echo -n "\t"
	$(CC) $(flags) -o $@ -c $(simulationFile)
$@ : $(simulationIncludes)

$(tradingObj) : $(tradingFile)
	@echo -n
	@echo compilation de $(tradingFile):
	@echo -n "\t"
	$(CC) $(flags) -o $@ -c $(tradingFile)
$@ : $(tradingIncludes)

$(utilsObj) : $(utilsFile)
	@echo -n
	@echo compilation de $(utilsFile):
	@echo -n "\t"
	$(CC) $(flags) -o $@ -c $(utilsFile)
$@ : $(utilsInclude)

$(exceptionObj) : $(excetionFile)
	@echo -n
	@echo compilation de $(exceptionFile):
	@echo -n "\t"
	$(CC) $(flags) -o $@ -c $(exceptionFile)
$@ : $(exception)

main.o : $(mainFile)
	@echo -n
	@echo compilation de $(mainFile):
	@echo -n "\t"
	$(CC) $(flags) -o $@ -c $(mainFile)

execution:
	@echo -n
	@echo execution :
	@echo -n "\t"
	./$(exe)

clean:
	@echo -n
	@echo supperession des intermédiaires:
	@echo -n "\t"
	rm -f $(objs) main.o

.PHONY: all execution clean
