all: st_pipeline

queue.o: queue.c queue.h
	gcc -c queue.c -o queue.o -Wall -Wextra -pthread

active_object.o: active_object.c active_object.h
	gcc -c active_object.c -o active_object.o -Wall -Wextra -pthread

st_pipeline.o: st_pipeline.c
	gcc -c st_pipeline.c -o st_pipeline.o -Wall -Wextra -pthread

st_pipeline: st_pipeline.o queue.o active_object.o
	gcc st_pipeline.o queue.o active_object.o -o st_pipeline -Wall -Wextra -pthread -lm

clean:
	rm -f *.o st_pipeline