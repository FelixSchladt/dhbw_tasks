#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum morse { DOT, LINE };

struct node {
	uint8_t data;
    char charakter;
	struct node* dot;
	struct node* line;
};

struct node* newNode(int data, char character)
{
	struct node* node = (struct node*)malloc(sizeof(struct node));

	node->data = data;
	node->dot = NULL;
	node->line = NULL;
	return (node);
}

char find_char(struct node Node, uint8_t * symbol) {
   printf("int sym: %d\n");
   puts(NULL);
}

char * get_string_from_morse(struct node Node, char * morse) {
   find_char() 
}

int main()
{
	struct node* root = newNode(NULL, NULL);

	root->dot = newNode(DOT, 'E');
	root->line = newNode(LINE, 'T');


	root->dot->dot = newNode(DOT, 'I');
	root->dot->line = newNode(LINE, 'A');

    root->line->dot = newNode(DOT, 'N');
    root->line->line = newNode(LINE, 'M');


	root->dot->dot->dot = newNode(DOT, 'S');
	root->dot->dot->line = newNode(LINE, 'U');

	root->dot->line->dot = newNode(DOT, 'R');
	root->dot->line->line = newNode(LINE, 'W');

	root->line->dot->dot = newNode(DOT, 'D');
	root->line->dot->line = newNode(LINE, 'K');

	root->line->line->dot = newNode(DOT, 'G');
	root->line->line->line = newNode(LINE, 'O');


    root->dot->dot->dot->dot = newNode(DOT, 'H');
    root->dot->dot->dot->line = newNode(LINE, 'V');

	root->dot->dot->line->dot = newNode(DOT, 'F');
	root->dot->dot->line->line = newNode(LINE, NULL); //Ü

	root->dot->line->dot->dot = newNode(DOT, 'L');
	root->dot->line->dot->line = newNode(LINE, NULL); //Ä

	root->dot->line->line->dot = newNode(DOT, 'P');
	root->dot->line->line->line = newNode(LINE, 'J');

	root->line->dot->dot->dot = newNode(DOT, 'B');
	root->line->dot->dot->line = newNode(LINE, 'X');

	root->line->dot->line->dot = newNode(DOT, 'C');
	root->line->dot->line->line = newNode(LINE, 'Y');

	root->line->line->dot->dot = newNode(DOT, 'Z');
	root->line->line->dot->line = newNode(LINE, 'Q');

	root->line->line->line->dot = newNode(DOT, NULL);
	root->line->line->line->line = newNode(LINE, NULL); //CH


    root->dot->dot->dot->dot->dot = newNode(DOT, '5');
    root->dot->dot->dot->dot->line = newNode(LINE, '4');

    //root->dot->dot->dot->line->dot = newNode(DOT, 'V');
    root->dot->dot->dot->line->line = newNode(LINE, '3');

	//root->dot->dot->line->dot->dot = newNode(LINE, 'F');
	//root->dot->dot->line->dot->line = newNode(LINE, 'F');

	//root->dot->dot->line->line->dot = newNode(LINE, NULL); //Ü
	root->dot->dot->line->line->line = newNode(LINE, '2');

	//root->dot->line->dot->dot->dot = newNode(DOT, 'L');
	//root->dot->line->dot->dot->line = newNode(DOT, 'L');

	//root->dot->line->dot->line->dot = newNode(DOT, NULL); 
	//root->dot->line->dot->line->line = newNode(DOT, NULL);

	//root->dot->line->line->dot->dot = newNode(LINE, 'P');
	//root->dot->line->line->dot->line = newNode(LINE, 'P');

	//root->dot->line->line->line->dot = newNode(LINE, 'J');
	root->dot->line->line->line->line = newNode(LINE, '1');

	root->line->dot->dot->dot->dot = newNode(DOT, '6');
	//root->line->dot->dot->dot->line = newNode(DOT, 'B');

	//root->line->dot->dot->line->dot = newNode(DOT, 'X');
	//root->line->dot->dot->line->line = newNode(DOT, 'X');

	//root->line->dot->line->dot->dot = newNode(LINE, 'C');
	//root->line->dot->line->dot->line = newNode(LINE, 'C');

	//root->line->dot->line->line->dot = newNode(LINE, 'Y');
	//root->line->dot->line->line->line = newNode(LINE, 'Y');

	root->line->line->dot->dot->dot = newNode(DOT, '7');
	//root->line->line->dot->dot->line = newNode(DOT, 'Z');

	//root->line->line->dot->line->dot = newNode(DOT, 'Q');
	//root->line->line->dot->line->line = newNode(DOT, 'Q');

	root->line->line->line->dot->dot = newNode(DOT, '8');
	//root->line->line->line->dot->line = newNode(LINE, NULL);

	root->line->line->line->line->dot = newNode(DOT, '9');
	root->line->line->line->line->line = newNode(LINE, '0'); 


	return 0;
}

