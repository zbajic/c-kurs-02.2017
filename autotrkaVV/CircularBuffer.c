#include "Common.h"

void Init(buffer_struct* buf) {
	buf->rear = buf->front = buf->buffer;
}

int isFull(buffer_struct* buf)
{
	if (buf->front == (buf->rear+1)) return 1;
	if ((buf->rear == &(buf->buffer[BUFFER_SIZE-1])) && (buf->front == &(buf->buffer[0]))) return 1;
	return 0;
}


int isEmpty(buffer_struct* buf)
{
	if (buf->front == buf->rear) return 1;
	return 0;
}

int put(buffer_struct* buf, buffer_type x)
{
	if (isFull(buf)) return 0;
	*(buf->rear) = x;
	buf->rear++;
	if (buf->rear == &(buf->buffer[BUFFER_SIZE])) buf->rear = &(buf->buffer[0]);
	return 1;
}

void dump(buffer_struct* buf)
{
	int i;
	if (isEmpty(buf)) return;
	buffer_type* current;
	current = (buf->front);
	do
	{
		printf ("Datum trke: %s\n",current->datum);
		current++;
		if (current == &(buf->buffer[BUFFER_SIZE])) current = &(buf->buffer[0]);
	}
	while (!(current == (buf->rear)));
}
