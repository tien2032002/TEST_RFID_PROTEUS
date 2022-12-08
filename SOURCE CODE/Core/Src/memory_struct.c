#include "memory_struct.h"
#include "global.h"
#include "fsm.h"
#include <stdlib.h>


struct node admin;
struct node array[100];
int counter=0;


uint8_t equalZero(uint8_t* CardID1) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID1[i] != 0) return 0;
	}
	return 1;
}

uint8_t largerID(uint8_t* CardID1, uint8_t* CardID2) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID1[i] > CardID2[i]) return 1;
	}
	return 0;
}

uint8_t equalID(uint8_t* CardID1, uint8_t* CardID2) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID1[i] != CardID2[i]) return 0;
	}
	return 1;
}

void duplicateID(uint8_t* CardID1, uint8_t* CardID2){
    	uint8_t i;
	for (i = 0; i < 5; i++) {
		CardID1[i] = CardID2[i];
	}
}


void insert(uint8_t* key){
    if(counter>=100) return;
    counter++;
    for(int i=0;i<100;i++){
        if(array[i].used_mem==0){
            array[i].used_mem=1;
            for(uint8_t j=0;j<5;j++) array[i].ID[j] = key[j];
            return;
        }
    }

}


void delete_all(){
    counter=0;
    for(int i=0;i<100;i++)
        array[i].used_mem=0;
}

uint8_t search(uint8_t* key){
    if(equalID(admin.ID,key)) return 1;//admin card
    for(int i=0;i<100;i++){
        if((equalID(array[i].ID,key)) &&
          (array[i].used_mem==1)) return 1; //registered card
    }
    return 0; //not found card
}

uint8_t add_new_card(uint8_t* key)
{
       insert(key);
       return 1;
}



uint8_t delete_card(){
        delete_all();
        return 1;
}


uint8_t set_admin(uint8_t *ID){
        duplicateID(admin.ID, ID);
        return 1;
}

uint8_t check_admin(uint8_t *ID){
	return equalID(ID, admin.ID);
}
