all: libLcd.a lcddemo.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

libLcd.a: font-11x16.o font-5x7.o font-8x12.o lcdutils.o lcddraw.o buzzer.o led.o switches.o stateMachines.o p2_interrupt_handler.o wdt_handler.o
	$(AR) crs $@ $^

buzzer.o: buzzer.c buzzer.h
lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h
led.o: led.c led.h switches.h
p2_interrupt_handler.o: switches.h
switches.o: switches.c switches.h led.h
stateMachines.o: stateMachines.c stateMachines.h led.h buzzer.h switches.h notes.h

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f libLcd.a *.o *.c~ *.h~ *~ *.c# *.elf

lcddemo.elf: lcddemo.o libLcd.a 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer 

load: lcddemo.elf
	msp430loader.sh $^
