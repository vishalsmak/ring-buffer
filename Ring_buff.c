
#include "Can_RB.h"


void initRingBuffer (ringbuffer_t *ring, volatile CAN_MSG_T *buffer, uint16_t size)
{
	ring->buffer = buffer;
	ring->size = size;
	ring->head = 0;
	ring->tail = 0;
}

void initCan_Ringbuffer(void)
{
	rx_frame_Buff =  (CAN_MSG_T*) malloc (MAX_STRUCTS * sizeof(CAN_MSG_T));
	initRingBuffer(&rxRing,rx_frame_Buff,MAX_STRUCTS);
}

bool addToRingBuffer (ringbuffer_t *ring, const CAN_MSG_T *msg)
{
    uint16_t nextEntry;

    nextEntry = (ring->head + 1) % ring->size;

    /* check if the ring buffer is full */
    if (nextEntry == ring->tail)  return false ;

    /* add the element to the ring */
    memcpy ((void *)&ring->buffer[ring->head], (void *)msg, sizeof (CAN_MSG_T));

    /* bump the head to point to the next free entry */
    ring->head = nextEntry;

    return (true);
}

bool removeFromRingBuffer (ringbuffer_t *ring, CAN_MSG_T *msg)
{

    /* check if the ring buffer has data available */
    if (isRingBufferEmpty (ring) == true)  return false ;

    /* copy the message */
    memcpy ((void *)msg, (void *)&ring->buffer[ring->tail], sizeof (CAN_MSG_T));

    /* bump the tail pointer */
    ring->tail = (ring->tail + 1) % ring->size;

    return (true);
}

/*
 * \brief Count the number of entries in the specified ring buffer.
 *
 * \param ring - ring buffer to use.
 *
 * \retval a count of the number of elements in the ring buffer.
 *
 */

uint16_t ringBufferCount (ringbuffer_t *ring)
{
    if (ring->tail == ring->head)  return 0 ;
    if (ring->tail  < ring->head)  return ring->head - ring->tail ;
	else                         return ring->size - ring->tail + ring->head ;
}


void add_CAN_frames(CAN_MSG_T *tempFrame)
{
	addToRingBuffer(&rxRing, tempFrame);
}

bool get_Can_rx_buff(CAN_MSG_T *msg)
{
	uint32_t result;

	result = removeFromRingBuffer(&rxRing,msg) ? 1 : 0;

	return result;
}

uint16_t get_Can_RB_count(void)
{
	return ringBufferCount(&rxRing);
}
