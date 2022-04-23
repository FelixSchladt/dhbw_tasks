main:
	gcc -o main main.c

test:
	gcc -o test file_generator.c test_ticket.c

run-test:
	rm -f tmp/*
	gcc -o test file_generator.c test_ticket.c
	./test -p tmp

run:
	gcc -o main main.c
	./main
