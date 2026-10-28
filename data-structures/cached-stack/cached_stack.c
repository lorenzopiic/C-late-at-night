/* Implemenation of a generic "cached" stack data structure. 
*  For fun and for stydying the "tagged union" technique.
*  Copyright (C) Lorenzo Tomasello 2026                      */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<limits.h>
#include<float.h>
#include<errno.h>
#include"cached_stack.h"

//#define DEBUG
int
main(void)
{
    Stack* STACK = malloc(sizeof *STACK);
    if(STACK == NULL){
        perror("Allocation Error\n");
        return EXIT_FAILURE;
	}
        Cache* CACHE = malloc(sizeof *CACHE);
    if(CACHE == NULL){
        perror("Allocation Error\n");
        return EXIT_FAILURE;
    }

/*

   "instructions_choice" is used for them main menu management to handle the first step of the program

   "push_options_choice" is used to manage the choice of data type to push

   "advanced_settings_choice" is used to select which particular action to perform, given the provided set 
*/
        int instructions_choice;
        int push_options_choice;
		int advanced_settings_choice; 

        main_loop_instructions(); /* Dipslays the general menu of the progam */
        printf(">>> ");

 /* main LOOP */
while(1){
      /* See check_input */
	if(!check_input(&instructions_choice)){
	   	fprintf(stderr,"\nPlease, enter a number >>> ");
        continue;
	}
	if(instructions_choice == 5 ) { break; }
	
	switch (instructions_choice) {
		case 1:
{
             print_divider();
             push_options(); /* Displays the data types supported by the data structure */
             printf(">>> ");

            while (1) {
                if (!check_input(&push_options_choice)) {
                    fprintf(stderr, "\nError! You entered characters instead of a number!\n");
                } else if (!check_push_options_choice(&push_options_choice)) {
                    // not betweeen 1-5 //
					fprintf(stderr, "\nError! You entered an invalid choice!\n");
                } else {
                    break;
                }
                print_divider();
                push_options();
                fprintf(stdout,"\nEnter a valid choice now >>> ");
            }
                        // Ok, now we are sure that the choice of what to push is a number between 1-5 //
            type_t* data = manage_push_options_choice(&push_options_choice);

/* DESCRIPTION:

   "type_t"

   type_t: This struct represents the data type abstraction that we want to push into the data structure;
   essentially inside it there is:

    - a "union" containing the data types that I have prepared for the program and then,
    - an "enum" that reports the tags of the various types

   so that we can make the wrappers that actually allocate the data in the heap work

*/
      if (!push(STACK, data)){
        fprintf(stderr,"Error! Something went wrong...\n");
    }
           break;
} // END case 1 //
        case 2:
{
        if(pop(STACK,CACHE) == true){
            fprintf(stdout,"\nAn element was successully popped from the stack!\n");
                        //fprintf(stdout,"Number of stack's elements:%ld\n",STACK->nodes_counter);
                        print_divider();
                } else {
                        // STACK is empty //
                        goto NEWCHOICE;
                }
            break;
} //END case 2 //
        case 3:
{
                        display_status(STACK, CACHE);
                        print_divider();
                        break;
} // END case 3 //
		case 4:
{	
		advanced_settings(); 
		print_divider();
	   	fprintf(stdout,">>> "); 	
        while (1) {
			if (!check_input(&advanced_settings_choice)) {
				fprintf(stderr, "\nError! You entered characters instead of a number!\n");
                	} else if (!check_advanced_settings_choice(&advanced_settings_choice)){
                    // not betweeen 1-10//
                      fprintf(stderr, "\nError! You entered an invalid choice!\n");
                } else {

                    break;
				}
                print_divider();
                advanced_settings(); 
                fprintf(stdout,"\nEnter a valid choice now >>> "); 
		}
		if(manage_advanced_settings_choice(STACK,CACHE,&advanced_settings_choice)){
			break;
	} else { // MANAGE THIS SITUATION
		fprintf(stderr,"\nSome error occurred using advanced settings...\n"); 
		goto NEWCHOICE;
   			}

} // END case 4 //        
	default:
            printf("\nError! Invalid choice...\n\n");
            main_loop_instructions();
            break;
        }
NEWCHOICE:
            fprintf(stdout,"\nInsert new choice >>> ");
            fflush(stdout);
    } // end while loop() //
    puts("Program ended!");

        return 0;
} // END MAIN //

void main_loop_instructions(void) {
    printf("\nEnter your choice:\n");
    printf("1 to push an element into the stack\n");
    printf("2 to pop an element from the stack\n");
    printf("3 to display the number of elements of the data structures\n");
    printf("4 to see advanced settings menu\n");
    printf("5 to end the program\n");
}


void push_options(void){
	printf("What kind of data do you want to push?\n\n");
	printf("1 >>> char\n2 >>> short\n3 >>> int\n4 >>> double\n5 >>> string\n");
}
void print_divider(void){ fprintf(stdout,"\n\n/* ===================================================================== */\n\n"); }
void advanced_settings(void){
    printf("\nEnter your choice:\n");
    printf("1 to see the element on top of the  stack\n");
    printf("2 to see the element at the bottom of the stack\n");
    printf("3 to see the element on top of the  cache\n");
    printf("4 to see the element at the bottom of the cache\n");
    printf("5 to print n element of the stack\n");
    printf("6 to print n element of the cache\n");
    printf("7 to delete n element from the stack\n");
    printf("8 to delete n element from the cache\n");
    printf("9 to clear all the stack\n");
    printf("10 to clear all the the cache\n");
}

void clean_buffer(void){
        int c;
        while((c = getchar())!= '\n' && c != EOF);
}

void display_status(Stack* stackPtr,Cache* cachePtr){
	
	if(stackPtr->nodes_counter == 0){
		fprintf(stdout,"\nStack is empty...\n"); 
	} else {
		fprintf(stdout,"\nStack's elements >>> %ld\n", stackPtr->nodes_counter);
	 }
	if(cachePtr->nodes_counter == 0){
		fprintf(stdout,"\nCache is empty...\n");
	} else {
		fprintf(stdout,"Cache's elements >>> %ld\n", cachePtr->nodes_counter);
	}	
}

/* DESCRIPTION:
  
  "check_input()" 
 
  This function performs an initial check on the input provided by the user when selecting the operation
  for the program to execute. If the user enters "characters" or "floating-point numbers", the function 
  returns an error, and the loop prompts the user to enter a valid choice again.
 
 */
bool check_input(int* target) {
  
  	char buffer[3000];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) { return false; }

    char* endptr;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0') || errno == ERANGE) {
	  	return false; 
    }

    if (val < INT_MIN || val > INT_MAX) { return false; }
    *target = (int)val;
    return true;
}

/*  DESCRIPTION: 
   
    "check_push_options_choice()"
   
    This function checks whether the integer entered by the user is between 1 and 5; if this check fails, the foo
    returns an error and this time the loop prompts you to enter a valid option until the latter is provided.
*/ 
bool check_push_options_choice(int* choice){
	switch(*choice){
		case 1:
		case 2:
		case 3: 
		case 4: 
		case 5:
			return true; 
		default:
			return false; 
	}
}

/*  DESCRIPTION: 
   
    "check_advanced_settings_choice()"
   
    This function checks whether the integer entered by the user is between 1 and 10; if this check fails, the foo
    returns an error and this time the loop prompts you to enter a valid option until the latter is provided.


*/
bool check_advanced_settings_choice(int* choice) {
	switch(*choice){
		case 1:	case 2: case 3:	case 4:	case 5: 
		case 6: case 7: case 8: case 9: case 10: return true;
   		default: return false;
	}
}

/* DESCRIPTION:
  
  "manage_push_options_choice()"
    
  This function serves as a "type dispatcher". It determines the user-selected data type at runtime
  and delegates memory allocation to the corresponding type-specific function.

*/

bool manage_advanced_settings_choice(Stack* stackPtr, Cache* cachePtr,int*option){

    switch(*option){
    case 1:
{
		if(show_stack_top(stackPtr)){
			break;  
		
		} else { return false;  
	}
}
    case 2:
    {
		show_stack_bottom(stackPtr);
        break;
    }
    case 3:
    {
		show_cache_top(cachePtr);
        break;    
    }
    case 4:
    {
		show_cache_bottom(cachePtr);
        break;
    }
    case 5:
    {
        break;
    }
    case 6:
    {
        break;
    }
    case 7:
    {
        break;
    } 
    case 8: 
    {
        break;
    }
    case 9: 
    {
        break;
    }  
  case 10: 
    {
        break;
    }
 } // END SWITCH //
}

type_t* manage_push_options_choice(int* option){
		type_t* ret = NULL; 
		switch(*option){
			case TYPE_CHAR: {
				printf("\n");
    		  	char ch;
    		  	char buffer[128];
    			
				while (1) {
        			fprintf(stdout, "Enter the char >>> ");
        			if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            		continue;
        		}
				/* fgets stores the \n, this means that a single valid char produces
				  a sequence like "a\n\0" (length 2)  */
					if (strlen(buffer) == 2 && buffer[0] != '\n') {
            
           		    if (isdigit((unsigned char)buffer[0])) {
                		fprintf(stderr, "\nError >>> Enter just a char, no digits...\n");
                		continue;
            		}	
            	ch = buffer[0];
           		 break; // clean input // 
            
        			} else {
            	fprintf(stderr, "\nError >>> Enter just one char at a time...\n");
        		}
    		}
    
   			ret = allocate_char(&ch);
    		break;
			}
			case TYPE_SHORT: {
        		printf("\n");    
				short sh;	
				while(1){
					fprintf(stdout,"Enter the short >>> ");
					if(check_input_short(&sh)){  break; }
					
					fprintf(stderr,"\nError >>> Invalid short format");
					fprintf(stderr,"(no chars, decimals or overflow)\n\n"); 
				}
				ret = allocate_short(&sh);
			   	break;
			}
			case TYPE_INT: {
        		printf("\n");    
			   	int integer;
				while(1){
					fprintf(stdout,"Enter the int >>> ");
					if(check_input_int(&integer)) { break; }				
				
					fprintf(stderr,"\nError >>> invalid int format "); 
					fprintf(stderr,"(no chars, decimals or overflow)\n\n");
				}
			   	ret = allocate_int(&integer);
				break;
			}
			case TYPE_DOUBLE:
        		printf("\n");    
				double doub; 
				while(1){
					fprintf(stdout,"Enter the double >>> ");
					if(check_input_double(&doub)) { break; }
					
					fprintf(stderr,"\nError >>> invalid double format "); 
					fprintf(stderr,"(no chars or overflow)\n\n");

				}
				ret = allocate_double(&doub); 	
				break;
			case TYPE_STRING:
        		printf("\n");   
			    char* string = NULL; 
				while(1){
					fprintf(stdout,"Enter the string >>> ");
				    if(check_input_string(&string)) { break; }	
					
					fprintf(stderr,"\nError >>> invalid string format ");
					fprintf(stdout,"(only characters are allowed)\n\n"); 
				   		
				}	
				ret = allocate_string(string);
				break; 				
		    default:
                return NULL; //invalid TYPE returns an error	
        } // end switch //
		
	print_divider(); 	
	return ret;
}

bool check_input_short(short* target){

	char buffer[1200];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) { return false; }
    char* endptr;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);

    if (  endptr == buffer || 
	   (  *endptr != '\n'  &&
		  *endptr != '\0') || 
		  errno == ERANGE) { return false; }

    if ( val < SHRT_MIN || 
		 val > SHRT_MAX)   { return false; }

     *target = (short)val;
    
	 return true; // safe input //
}

bool check_input_int(int* target){
	
	char buffer[1200];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) { return false; }
    char* endptr;
    errno = 0;
    long val = strtol(buffer, &endptr, 10);

	if ( endptr  == buffer || 
	   ( *endptr != '\n'   &&
	  	 *endptr != '\0')  ||
	   	 errno == ERANGE)  { return false; }
    
	if ( val < INT_MIN || 
		 val > INT_MAX)   { return false; }
	
	*target = (int)val; 
	return true; // safe //
}

bool check_input_double(double* target){
	
	char buffer[1200];
	if(fgets(buffer, sizeof(buffer), stdin) == NULL ) { return false; }
	char* endptr; 
	errno = 0; 
	long val = strtol(buffer, &endptr, 10);

	if ( endptr  == buffer || 
	   ( *endptr != '\n'   &&
	  	 *endptr != '\0')  ||
	   	 errno == ERANGE)  { return false; }
    
	if ( val < DBL_MIN || 
		 val > DBL_MAX)   { return false; }
	
	*target = (double)val; 
	return true; // safe // 
}

bool check_input_string(char** target){
	char buffer[4000];
	if(fgets(buffer, sizeof(buffer), stdin) == NULL) { return false; }
	size_t buffer_len = strlen(buffer);	
    
/*  if just a newline was typed we return an error */
    if(buffer_len == 0) { return false; }   

	#ifdef DEBUG
        printf("\nDEBUG inside check_input_string()\n>>> buffer read form stdin: %s\n",buffer); 
        printf("\nDEBUG inside check_input_string()\n>>> buffer_len %ld\n",buffer_len);
    #endif

/*
  fgets() DESCRIPTION
 
  fgets() reads in at most one less than size characters from stream and stores them into the buffer
  pointed  to  by  s. 
  Reading  stops after an EOF or a newline.
  If a newline is read it is stored into the buffer.
  A terminating null byte ('\0') is stored after the last character in the buffer.
*/
 
/* 
 So we have to fix the problem that fgets() stores the newline onto the buffer
    
     0 1 2 3 4  5  6
    |h|e|l|l|o|\n|\0|    
     
    so the len of the string should be 6, and we have to replace the nullbyte at stringlen-1; 
*/
    if(buffer_len > 0 && buffer[buffer_len-1] == '\n'){
       buffer[buffer_len-1] = '\0';

}
	for(size_t i = 0; buffer[i] != '\0'; i++){
		if(isdigit(buffer[i])){ 
			return false; 
		}
	}
    *target = malloc(sizeof(char) * buffer_len);
    if(*target == NULL){
        perror("Allocation error...\n");
        *target = NULL;  
       return false;
}
    strncpy(*target,buffer,buffer_len);
	return true; // safe //			
}

type_t* allocate_short(short* sh) {
	type_t* ret = malloc(sizeof(*ret));
	if(ret != NULL){
		ret->type.short_num = *sh; 
		ret->tag = TYPE_SHORT; 
	} else {
		perror("Allocation Error");
		return NULL; 
	}	
	return ret;  
}

type_t* allocate_char(char* ch) {
	type_t* ret = malloc(sizeof(*ret));
	if(ret != NULL){
		ret->type.char_num = *ch;
		ret->tag = TYPE_CHAR;
	} else {
		perror("Allocation Error");
		return NULL; 
	}
	 return ret; 
}

type_t* allocate_int(int* integer){
	type_t * ret = malloc(sizeof(*ret));
	if(ret != NULL){
		ret->type.int_num = *integer;
		ret->tag = TYPE_INT;
	} else{
		perror("Allocation error");
		return NULL; 
	}
	return ret; 
}

type_t * allocate_double(double* doub){
	type_t * ret = malloc(sizeof(*ret));
	if(ret != NULL){
		ret->type.double_num = *doub;
		ret->tag = TYPE_DOUBLE;
	} else {
		perror("Allocation error...");
		return NULL;
	}
	return ret; 
}

type_t* allocate_string(char* src_string){
	size_t len_counter=0; 
/* 
 ok, we recive a pointer to a line organizied like this:

  0 1 2 3 4  5 
 |h|e|l|l|o|\0|

 so the for loop below will count the exact length of the line.

 We need to increase the counter another time to reserve space for the '\0'

*/	
    for(size_t i = 0;src_string[i] != '\0'; i++ && len_counter++){ ; }
    
    len_counter++; // IMPORTANT // 

	type_t* ret = malloc(sizeof(*ret));
	if(ret != NULL){
		char* dest_string = malloc(len_counter);
	   	if(dest_string != NULL){
			strncpy(dest_string,src_string,len_counter);
			ret->tag = TYPE_STRING;
			ret->type.string = dest_string;
			} else {
				perror("Allocation error...");
				free(ret);
                ret = NULL; // Always be safe //
                return NULL; 
			}	
		}	
	return ret; 
}

bool push(Stack* stackPtr, type_t* item){
	stacknode* newNode = malloc(sizeof(*newNode));
	if(newNode != NULL){
		switch(item->tag){
			case TYPE_CHAR: 
			case TYPE_SHORT: 
			case TYPE_INT: 
			case TYPE_DOUBLE:
			   newNode->value.type = item->type;
               newNode->value.tag = item->tag;	
			   break;
			case TYPE_STRING: 
			   #ifdef DEBUG
                printf("\nDEBUG case TYPE_STRING inside push()\n"
                ">>> strlen(item->type.string) : %ld\n" ,strlen(item->type.string)); 
                #endif
                 char* temp = malloc(strlen(item->type.string));
			   if(temp != NULL) {
			   	strncpy(temp, item->type.string, strlen(item->type.string));
			   	newNode->value.tag = item->tag;
			  	newNode->value.type.string = temp;
                #ifdef DEBUG
                printf("\nDEBUG case TYPE_STRING's newNode allocation inside push()\n"
                       ">>> printing newNode->value.type.string : %s\n",
                        newNode->value.type.string); 
                #endif
			} else {
				perror("Allocation Error...");
				temp = NULL;
			   	free(newNode);
				return false;  	
			}
		   	break; 	   
		} // end Switch // 
		if(stackPtr->head == NULL){
			stackPtr->head = newNode; 
		   	stackPtr->head->nextNode = NULL; 
			stackPtr->nodes_counter++; 			
		} else {
		newNode->nextNode = stackPtr->head;
	   	stackPtr->head = newNode; 		
		stackPtr->nodes_counter++; 
	} 
        } else {
		perror("Allocation Error...");
		newNode = NULL; 
		return false; 
	}
    return true; 
}

bool pop(Stack* stackPtr, Cache* cachePtr){
	if(stackPtr->head == NULL){
	  	fprintf(stderr,"Stack is empty...\n"); 
		return false;
	}	
    
    // We save a reference of the current head of the stack // 
    stacknode* temp = stackPtr->head;
	
    if(cachePtr->nodes_counter < CACHESIZE){
		push_back(cachePtr, stackPtr->head->value);
	}else{
		manage_cache_fullness(cachePtr,stackPtr->head->value); 
	}
	switch(stackPtr->head->value.tag){
		case TYPE_CHAR: 
		case TYPE_SHORT: 
		case TYPE_INT: 
		case TYPE_DOUBLE:
			stackPtr->head = stackPtr->head->nextNode;
			free(temp);
			temp = NULL;	
			break;
		case TYPE_STRING:
			stackPtr->head = stackPtr->head->nextNode;
			free(temp->value.type.string);
			temp->value.type.string = NULL;
			free(temp);
			temp = NULL; 
			break;		
	}
	stackPtr->nodes_counter--;
	return true; 
}

void push_back(Cache* cachePtr,type_t item){
	stacknode* newNode = malloc(sizeof(*newNode));
	if(newNode != NULL){
		newNode->nextNode = NULL; 
		switch(item.tag) {
			case TYPE_CHAR: 
			case TYPE_SHORT: 
			case TYPE_INT: 
			case TYPE_DOUBLE:
			   newNode->value.tag = item.tag;
               newNode->value.type = item.type; 
			   break;
			case TYPE_STRING: 
               char* temp = malloc(strlen(item.type.string));
			   if(temp != NULL) {
			   	strncpy(temp, item.type.string, strlen(item.type.string));
			   	newNode->value.tag = item.tag;
			  	newNode->value.type.string = temp;
            } else {
				perror("Allocation Error...");
			   	free(newNode);
                newNode = NULL; 
				return; 	
			}
		   	break; 	   
		} // end Switch // 
		if(cachePtr == NULL){
			cachePtr->top = newNode;
			cachePtr->bottom = newNode; 
			cachePtr->top->nextNode = NULL; 
			cachePtr->bottom->nextNode = NULL; 
			cachePtr->nodes_counter++;	
			return;
		}
		newNode->nextNode = cachePtr->top;
	   	cachePtr->top = newNode; 		
		cachePtr->nodes_counter++;
	} else {
		perror("Allocation Error...");
		return;
	}
}

void manage_cache_fullness(Cache* cachePtr,type_t item){
		printf("Warning! The cache memory is full!\n"
				"Using it will override the last pushed information\n"
				"Do you want to use it anyway?\n"
				"1 to push\n2 to avoid\nEnter your choice >>> ");
		unsigned short choice = 0; 
		scanf("%hu", &choice);
		if(choice != 1 && choice != 2){
		while(choice != 1 && choice != 2){
			fprintf(stderr,"Invalid choice!");
		   	fprintf(stdout,"Enter a valid choice >>> "); 	
			scanf("%hu", &choice);
		 }
		} else { // temporary way to validate a choice //
		if(choice == 1){
		   stacknode* del = cachePtr->bottom;
		   switch(del->value.tag){
			   case TYPE_CHAR: 
			   case TYPE_SHORT:
			   case TYPE_INT: 
			   case TYPE_DOUBLE:
			       break;
			   case TYPE_STRING:
				   free(del->value.type.string);
			       del->value.type.string = NULL; 
			       break;		
			}
		    free(del);
		    del = NULL;
		    cachePtr->nodes_counter--;
		    set_cache_bottom(cachePtr); 	
	} else {
		fprintf(stdout,"Ok the cache will remain the same...\n");
		}
	}
}


bool show_stack_top(Stack* stackPtr){

	if(stackPtr->head == NULL){
		fprintf(stderr,"Error trying to inspect the top of the Stack >>> Stack is empty...\n");
		return false; 
	}
type_t* top = &(stackPtr->head->value);

switch(stackPtr->head->value.tag){
	case TYPE_CHAR:
		fprintf(stdout,"\nElemnt on top of the stack is >>> %c\n", 
			top->type.char_num);
		top = NULL; 
		return true; 
	
	case TYPE_SHORT:
		fprintf(stdout,"\nElemnt on top of the stack is >>> %d\n",
			   top->type.short_num);
		top = NULL; 
		return true; 
	
	case TYPE_INT:
		fprintf(stdout,"\nElemnt on top of the stack is >>> %d\n",
				top->type.int_num);
		top = NULL; 
		return true; 
	
	case TYPE_DOUBLE:
		fprintf(stdout,"\nElemnt on top of the stack is >>> %lf\n",
				top->type.double_num);
		top = NULL; 
		return true; 		
	
		
	case TYPE_STRING:
		fprintf(stdout,"\nElement on top of the stack is >>> %s\n",
				top->type.string); 
		top = NULL; 
		return true;		
	
	} // END SWITCH // 
	top = NULL; 
	return false;  // If here something went wrong // 
}

bool show_stack_bottom(Stack* stackPtr){}
bool show_cache_top(Cache* cachePtr){}
bool show_cache_bottom(Cache* cachePtr){}



void set_cache_bottom(Cache* cachePtr){
	stacknode* current = cachePtr->top;
	stacknode* previous = NULL; 
	
	while(current != NULL){
		previous = current; 
		current = current->nextNode; 
	}
	if(previous != NULL){
	cachePtr->bottom = previous; 
	cachePtr->bottom->nextNode = NULL; 
	}
	previous = NULL; 
	current  = NULL;
}


/*======================= TO DO ===========================
 *
 *	Fix the check_input_char function, it is different from
 *  the other foos that I wrote for the same task
 *
 *  Need to fix bugs in string handling, and in double number checking 
 *  I think to have fixed many of the bugs in string management, but need to check that
 *  many other times to be completely sure 
 *
 * FIX inside manage_cache_fullness():
 * -Need to protect in a decent way the input handling in this foo
 * */


