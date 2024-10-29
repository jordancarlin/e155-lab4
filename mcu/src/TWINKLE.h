// Pitch in Hz, duration in ms

#ifndef TWINKLE
#define TWINKLE

#define A3 220
#define A3s 233.1
#define B3 246.9
#define C4 261.6
#define C4s 277.2
#define D4 293.7
#define D4s 311.1
#define E4 329.6
#define F4 349.2
#define F4s 370.0
#define G4 392.0
#define G4s 415.3
#define A4 440
#define A4s 466.2
#define B4 493.9
#define C5 523.3
#define C5s 554.4
#define D5 587.3
#define D5s 622.2
#define E5 659.2
#define F5 698.4
#define F5s 740.9
#define G5 784.0
#define G5s 830.6
#define A5 880

#define half 500
#define quarter 250

const int twinkle[][2] = {
{C4,	quarter},
{C4,	quarter},
{G4,	quarter},
{G4,	quarter},
{A4,	quarter},
{A4,	quarter},
{G4,	half},
{F4,	quarter},
{F4,	quarter},
{E4,	quarter},
{E4,	quarter},
{D4,	quarter},
{D4,	quarter},
{C4,	half},
{G4,	quarter},
{G4,	quarter},
{F4,	quarter},
{F4,	quarter},
{E4,	quarter},
{E4,	quarter},
{D4,	half},
{G4,	quarter},
{G4,	quarter},
{F4,	quarter},
{F4,	quarter},
{E4,	quarter},
{E4,	quarter},
{D4,	half},
{C4,	quarter},
{C4,	quarter},
{G4,	quarter},
{G4,	quarter},
{A4,	quarter},
{A4,	quarter},
{G4,	half},
{F4,	quarter},
{F4,	quarter},
{E4,	quarter},
{E4,	quarter},
{D4,	quarter},
{D4,	quarter},
{C4,	half},
{  0,	0}};

#endif
