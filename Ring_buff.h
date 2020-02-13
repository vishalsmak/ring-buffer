

#ifndef CAN_RB_H_
#define CAN_RB_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "board.h"

#define MAX_STRUCTS 				128


typedef struct
{
    volatile uint16_t head;
    volatile uint16_t tail;
    uint16_t size;
    volatile CAN_MSG_T *buffer;
}ringbuffer_t;


volatile CAN_MSG_T *rx_frame_Buff; //[SIZE_RX_BUFFER];
ringbuffer_t rxRing;

void initCan_Ringbuffer(void);
void initRingBuffer (ringbuffer_t *ring, volatile CAN_MSG_T *buffer, uint16_t size);
bool addToRingBuffer (ringbuffer_t *ring, const CAN_MSG_T *msg);
bool removeFromRingBuffer (ringbuffer_t *ring, CAN_MSG_T *msg);
static inline bool isRingBufferEmpty (ringbuffer_t *ring)
 {
 	return (ring->head == ring->tail);
 }
 uint16_t ringBufferCount (ringbuffer_t *ring);

 void add_CAN_frames(CAN_MSG_T *tempFrame);

 uint16_t get_Can_RB_count(void);

 bool get_Can_rx_buff(CAN_MSG_T *msg);

#endif /* CAN_RB_H_ */
