#include "ring_buffer.h"
#define capacity (8)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full=0;
uint16_t lap_counter_head=0;
uint16_t counter_size_head=0;


uint8_t ring_buffer_size(void)
{
	uint8_t size = 0;
	if (head_ptr > tail_ptr) {
		size = head_ptr - tail_ptr;
	}
    if(head_ptr==tail_ptr){ // Si llega al final de la memoria

		size=lap_counter_head*capacity+counter_size_head;
	}

    return size;


}

uint8_t ring_buffer_is_empty(void){ //esta funcion retorna 1 si esta vacio y 0 si No esta vacio

	if(head_ptr== tail_ptr && is_full==0){
		return 1; //esta vacio
	}else{
		return 0;// No esta vacio
	}


}



uint8_t ring_buffer_is_full(void){ //esta funcion retorna 1 si esta vacio y 0 si No esta vacio

	if( is_full!=0){
		return 1; //esta lleno
	}else{
		return 0;// No esta lleno
	}


}

void ring_buffer_reset(void){


	if(is_full!=0){
		for(uint8_t i=0;i<capacity;i++){
			  ring_buffer[tail_ptr+i]= '\0';
		}
	}else if(is_full==0){
		for(uint8_t i=0;i<=head_ptr - tail_ptr;i++){
			  ring_buffer[tail_ptr+i]= '\0';
		}

	}
	//reseta las banderas y contadores
    head_ptr = 0;
    tail_ptr = 0;
    is_full = 0;
    lap_counter_head = 0;  // Si estás utilizando un contador de vueltas
    counter_size_head = 0;
}

void ring_buffer_write (uint8_t data){

ring_buffer[head_ptr]= data;
head_ptr = head_ptr + 1 ;

        if(head_ptr>= capacity){ // Si llega al final de la memoria
			head_ptr = 0;
			lap_counter_head=2; // hace el conteo de la primer vuelta

		}
		if(is_full != 0){ // Si se pierden los datos
			tail_ptr =tail_ptr +1;
		}
		if(tail_ptr >= capacity){ // Si la cola llega al final de la memoria
			tail_ptr=0;
		}
		if(head_ptr == tail_ptr){ // Si la cabeza alcanza la cola
			is_full=1;
			counter_size_head++;// cuenta las posiciones que se corrio la cabeza despues de la primer vuelta.

        }
 }

uint8_t ring_buffer_read(uint8_t *byte)
{

	  if ((is_full!=0)||(head_ptr != tail_ptr)){
		  *byte = ring_buffer[tail_ptr];
		  tail_ptr = tail_ptr +1;
		  if(tail_ptr >= capacity){
			  tail_ptr =0;
		  }
	      is_full =0;



	  return 1;
   }
   return 0;
}
