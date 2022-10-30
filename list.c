/* Melody Trinh 
 * COEN 12
 * Term project 
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <stdbool.h>
# include "list.h"


struct list{
	int count; 
	struct node *head; 
	struct node *tail; 
}; 

typedef struct node{
	
	void **data; 
	int first;
	int last;   
	struct node *next; 
	struct node *prev; 
} NODE; 

//Creates a list 
//O(1)
LIST *createList(void)
{
	LIST *lp= malloc(sizeof(LIST)); 
	assert (lp != NULL); 
	lp -> count= 0; 
	lp -> head = NULL; 
	lp -> tail = NULL; 
	return lp; 
}

//GOes through each node and array and frees each index
//O(n)
void destroyList(LIST *lp)
{
	assert (lp != NULL); 
	NODE *pDel, *pNext; 
	pDel = lp -> head; 

	while(pDel != NULL)
	{
		pNext = pDel; 
		pDel = pDel -> next; 
		int i; 
		for( i= 0; i< 20; i++)
		{
			free(pNext -> data[i]); 
		}
		free(pNext); 
	}


	free(lp); 
}

//Returns how many elements are in the list
//O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL); 
	return (lp -> count); 
}

//Adds item as the first item of the list at the start of the array
//O(1)
void addFirst(LIST *lp, void *item) 
{


	assert(lp!=NULL);
  	NODE* temp = lp->head;
  	if (temp == NULL || (20 + lp->head->last - lp->head->first + 1)%20 == 0)
  	{
    		temp = malloc(sizeof(NODE));
    		assert(temp!=NULL);

    		temp->data = malloc(sizeof(void*) * 20);
		int i; 
		for(i = 0; i< 20; i++)
		{
			temp -> data[i]= NULL; 
		}
    		temp->first = -1;
    		temp->last = -1;
    		if(lp->head!=NULL)
    		{
      			temp->next = lp->head;
      			lp-> head -> prev = temp;
    		}
     		temp->prev = NULL; 
      		lp->head = temp;
      		if(lp->tail == NULL)
      		{
        		lp->tail = temp;
      		}
  	}		
    
	if (temp -> first== -1 && temp -> last == -1)
  	{
    		temp -> first = 0;
    		temp -> last = 0;
  	}
    
  	else if (temp->first == 0)
  	{
    		temp->first = 19;
  	}
    
  	else
  	{
    		temp->first = temp->first-1;
  	}
    
  	temp->data[temp->first] = item;
  	lp->count++;

}

//Adds item to end of list at the end of the array 
//O(1)
void addLast(LIST *lp, void *item)
{	assert(lp!=NULL);
  	NODE* temp = lp->tail;
  	if (temp == NULL || (20 + lp->tail->last - lp->tail->first + 1)%20 == 0)
  	{
    		temp = malloc(sizeof(NODE));
    		assert(temp !=NULL);

    		temp->data = malloc(sizeof(void*) * 20);
		int i;
                for(i = 0; i< 20; i++)
                {
                        temp -> data[i]= NULL;
                }
      		temp->first = -1;
      		temp->last = -1;
      		if(lp->tail!=NULL)
      		{
        		temp->prev = lp->tail;
       			lp-> tail -> next = temp;
      		}
     		temp->next = NULL;
      		lp-> tail = temp;
      		if(lp->head == NULL)
      		{
        		lp->head = temp;
      		}
   
  	}

  	if (temp->first == -1 && temp->last == -1)
  	{
    		temp -> first = 0;
    		temp -> last = 0;
  	}
    
  	else if (temp->last == 19)
  	{
    		temp -> last = 0;
  	}
  
  	else
  	{
    		temp->last = temp->last+1;
  	}    
    
	temp->data[temp->last] = item;
  	lp->count++;
 
}

//Removes first element of the list at the start of array 
//O(1)
void *removeFirst(LIST *lp)
{

	assert(lp!=NULL && lp->count != 0);
  	NODE* temp = lp->head;
  	if (lp->head->first == -1)
  	{
    		lp->head = temp->next;
    		free(temp);
    		temp = lp->head;
    		temp->prev = NULL;
  	}
  
  	void* x = temp->data[temp->first];
  	temp->data[temp->first] = NULL;
  	 
  	if (temp->first == temp->last && temp->first != -1)
  	{
    		temp->first = -1;
    		temp->last = -1;
  	}
  
  	else if(temp -> first == 19)
	{
  		temp->first= 0;
	}

  	else
  	{
    		temp->first= temp->first+ 1;
  	}
  
  	lp->count--;
  	return x;
}

//Removes last item in the list at the end of the array 
//O(1)
void *removeLast(LIST *lp)
{
	
	assert(lp!=NULL && lp->count != 0);
  	NODE* temp = lp->tail;
  	if (lp->tail->last == -1)
  	{
    		lp->tail = temp->prev;
    		free(temp);
    		temp = lp->tail;
    		temp->next = NULL;
  	}

  	void* last = temp->data[temp->last];
  	temp->data[temp->last] = NULL;

  	if (temp->last == temp->first)
  	{
    	temp->last = -1;
    	temp->first = -1;
  	}
    
  	else if (temp->last == 0)
  	{
    		temp -> last = 19;
  	}
  
  	else
  	{
    		temp -> last = temp -> last - 1;
  	}
  
  	lp->count--;
  	return last;
}

//Returns a specific item given the index
//O(n)
void *getItem(LIST *lp, int index)
{
	assert(index < lp->count && lp != NULL);
  	NODE* temp = lp->head;
 	int x = (20 + lp->head->last - lp->head->first + 1)%20;
	void * item;
	while (index > x)
	{
		index = index - x;
                while(index >= 20)
                {
                        index = index -20;
                        temp = temp->next;
                }
                item= temp -> data[(temp -> first + index) % 20];
                return item;
	} 
      		item= temp -> data[(temp-> first + index) %20]; 
		return item;
  
}

//Sets index in list as item 
//O(n)
void setItem(LIST *lp, int index, void *item)
{
	assert(index < lp->count && lp != NULL);
        NODE* temp = lp->head;
        int x = (20 + lp->head->last - lp->head->first + 1)%20;
        while (index > x)
        {
                index = index - x;
                while(index >= 20)
                {
                        index = index -20;
                        temp = temp->next;
                }
                temp -> data[(temp -> first + index) % 20]= item; 
        }
               
                temp -> data[(temp -> first + index) % 20]= item;
}


