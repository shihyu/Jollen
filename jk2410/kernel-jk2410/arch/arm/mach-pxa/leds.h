/*
 * include/asm-arm/arch-pxa/leds.h
 *
 * Copyright (c) 2001 Jeff Sutherland, Accelent Systems Inc.
 *
 * blinky lights for various PXA-based systems:
 *
 */

extern void lubbock_leds_event(led_event_t evt);
extern void idp_leds_event(led_event_t evt);
extern void pxa_cerf_leds_event(led_event_t evt);
