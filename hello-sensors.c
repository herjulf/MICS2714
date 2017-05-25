/*
 * Copyright (c) 2015, Copyright Robert Olsson / Radio Sensors AB  
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 *
 * Author  : Robert Olsson robert@radio-sensors.com
 * Created : 2015-11-22
 */

/**
 * \file
 *         A simple application showing NOX reading on RSS2 mote
 */

#include "contiki.h"
#include "sys/etimer.h"
#include <stdio.h>
#include <math.h>
#include "adc.h"
#include "dev/leds.h"

PROCESS(hello_sensors_process, "Hello sensor process");
AUTOSTART_PROCESSES(&hello_sensors_process);

static struct etimer et;

#define MIC2714_M  0.9986
#define MIC2714_A  0.163
double m = MIC2714_M;
double a = MIC2714_A;

/* Converts to NO2 ppm according to MIC2714 NO2 curve 
   We assume pure NO2 */

double mics2714(double vcc, double v0, double corr)
{
  double no2, rsr0;
  /* Voltage divider */
  rsr0 = (vcc - v0)/v0;
  /* Transfer function */
  no2 = a * pow(rsr0, m);
  return no2 + corr;
}

void
show()
{
  double v0, no2, vcc = 5;

  for(v0 = 0.1; v0 <= 4.6; v0 += 0.5)  { 
    no2 = mics2714(vcc, v0, 0);
    printf(" v0=%4.2f NO2=%4.2f ppm\n", v0, no2);
  }
}

PROCESS_THREAD(hello_sensors_process, ev, data)
{
  PROCESS_BEGIN();

  leds_init(); 
  show();

  etimer_set(&et, CLOCK_SECOND * 5);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    etimer_reset(&et);
  }
  PROCESS_END();
}
