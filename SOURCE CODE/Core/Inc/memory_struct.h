#ifndef __MEMORY_STRUCT_H__
#define __MEMORY_STRUCT_H__

#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


struct node{
    uint8_t ID[5];
    uint8_t used_mem;
};
//uncomment this section for debugging

uint8_t equalZero(uint8_t* CardID1);

////////////////////////////////////////////////////////////
 void duplicateID(uint8_t* CardID1, uint8_t* CardID2);
                                                    
 uint8_t equalID(uint8_t* CardID1, uint8_t* CardID2);
                                                
 uint8_t largerID(uint8_t* CardID1, uint8_t* CardID2);

 struct node* newNode(uint8_t *ID);

 void inorder();
/////////////////////////////////////////////////////////////

uint8_t search(uint8_t* key);

uint8_t add_new_card(uint8_t* key);

uint8_t delete_card();

uint8_t set_admin(uint8_t *ID);

uint8_t check_admin(uint8_t *ID);


  

#endif //__MEMORY_STRUCT_H__
