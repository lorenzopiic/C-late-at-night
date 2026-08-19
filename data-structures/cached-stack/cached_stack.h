#define CACHESIZE 100
#include <stdlib.h>
#include<stdbool.h>
typedef enum types_tag {
	TYPE_CHAR   = 1,
	TYPE_SHORT  = 2,
	TYPE_INT    = 3,
	TYPE_DOUBLE = 4,
	TYPE_STRING = 5
} tags_t;

typedef union {
	char char_num;
	short short_num;
	int int_num; 
	double double_num; 	
	char* string;
}types;

typedef struct tagged_type {
	types type; 
	tags_t tag;
}type_t;

typedef struct stacknode {
  	type_t value; 
	struct stacknode* nextNode; 
}stacknode;

typedef struct Stack {
	stacknode* head;
	size_t nodes_counter;
}Stack;

typedef struct Cache {
	stacknode* top;
   	stacknode* bottom; 	
	size_t nodes_counter;
}Cache;

//======================================//
void main_loop_instructions(void);
void push_options(void); 
void clean_buffer(void);
bool check_input(int* target);
void print_divider(void);

bool check_push_options_choice(int* choice); 
type_t* manage_push_options_choice(int* option);

bool  check_input_short(short* target);
bool  check_input_int(int* target);
char* check_input_short(size_t* len);

/*============== Dynamic Allocation ================ */ 
type_t* allocate_short(short* sh);
type_t* allocate_char(char* ch);
type_t* allocate_int(int* integer);
type_t* allocate_double(double* doub);
type_t* allocate_string(char* src_string,size_t len);

/*=============== Stack ================ */

void push(Stack* stackPtr, type_t value);
void pop(Stack* stackPtr, Cache* cachePtr);

/*=============== Cache ================ */

void push_back(Cache* cachePtr,type_t item);
void manage_cache_fullness(Cache* cachePtr,type_t item); 
void set_cache_bottom(Cache* cachePtr);


//======================================//

