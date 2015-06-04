/* Protocol 2 (stop-and-wait) also provides for a one-directional flow of
 * data from sender to receiver. The communication channel is once again
 * assumed to be error free, as in protocol 1. However, this time, the
 * receiver has only a finite buffer capacity and a finite procesing speed,
 * so the protocol must explicitly prevent the sender from flooding the
 * receiver with data faster than it can be handled.
 *
 * To compile: cc -o protocol2 p2.c simulator.o
 * To run: protocol2 events timeout  pct_loss  pct_cksum  debug_flags
 *
 * Note that any value greater than zero for pct_loss or pct_cksum may
 * result in a deadlock, since this protocol assumes a reliable channel.
 *
 * Written by Andrew S. Tanenbaum
 * Revised by Shivakant Mishra
 * Revised, 2010, by Stephen W. Turner
 */

typedef enum {frame_arrival} event_type;
#include <stdio.h>
#include <stdlib.h>
#include "protocol.h"

void sender2(void)
{
  frame s;	/* buffer for an outbound frame */
  packet buffer;	/* buffer for an outbound packet */
  event_type event;	/* frame_arrival is the only possibility */
  int count;

  while (true) {
	count++;
        from_network_layer(&buffer);	/* go get something to send */
        init_frame(&s,count);
        s.info = buffer;	/* copy it into s for transmission */
        to_physical_layer(&s);	/* bye bye little frame */
        wait_for_event(&event);	/* do not proceed until given the go ahead */
  }
}

void receiver2(void)
{
  frame r, s;	/* buffers for frames */
  event_type event;	/* frame_arrival is the only possibility */
  int nt;	/* new tick - copy of current time */

  init_frame(&s,0);
  while (true) {
        wait_for_event(&event);	/* only possibility is frame_arrival */
        nt = from_physical_layer(&r);	/* go get the inbound frame */
        to_network_layer(&r.info);	/* pass the data to the network layer */
        to_physical_layer(&s);	/* send a dummy frame to awaken sender */
  }
}

int main(int argc, char *argv[])
{
  int timeout_interval, pkt_loss, garbled, debug_flags;
  long event;
  int multiples;

  if (!parse_first_six_parameters(argc, argv, &event, &timeout_interval,
                                   &pkt_loss, &garbled, &debug_flags,&multiples))  {
    printf ("Usage: p2 events timeout loss cksum debug datafile-flag\n");
    exit(1);
  }

  printf("\n\n Simulating Protocol 2\n");
  start_simulator(sender2, receiver2, event, timeout_interval, pkt_loss, garbled, debug_flags, multiples);
}

