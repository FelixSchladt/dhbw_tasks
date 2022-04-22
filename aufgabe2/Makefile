main:
	rm ./main
	gcc -o main main.c
test:
	gcc -o test file_generator.c test_ticket.c
run-test:
	rm -f tmp/*
	./test -p tmp
run:
	rm ./main
	gcc -o main main.c
	./main
