StoreCalculator.out : main.o reading_file_cmds.o date_analizing.o shophandling.o cityhandling.o provhandling.o openinitdir.o
	g++ main.o reading_file_cmds.o date_analizing.o shophandling.o cityhandling.o provhandling.o openinitdir.o -o StoreCalculator.out

main.o: main.cpp reading_file_cmds.h openinitdir.h 
	g++ -c main.cpp -o main.o

reading_file_cmds.o: reading_file_cmds.cpp reading_file_cmds.h
	g++ -c reading_file_cmds.cpp -o reading_file_cmds.o

date_analizing.o: date_analizing.cpp date_analizing.h
	g++ -c date_analizing.cpp -o date_analizing.o

shophandling.o: shophandling.cpp shophandling.h date_analizing.h
	g++ -c shophandling.cpp -o shophandling.o

cityhandling.o: cityhandling.cpp cityhandling.h shophandling.h reading_file_cmds.h
	g++ -c cityhandling.cpp -o cityhandling.o

provhandling.o: provhandling.cpp provhandling.h cityhandling.h reading_file_cmds.h
	g++ -c provhandling.cpp -o provhandling.o

openinitdir.o: openinitdir.cpp openinitdir.h cityhandling.h reading_file_cmds.h provhandling.h
	g++ -c openinitdir.cpp -o openinitdir.o

.PHONY:clean
clean:
	rm *.o
	rm StoreCalculator.out
