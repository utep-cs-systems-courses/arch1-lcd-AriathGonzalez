# makfile configuration
COMMON_OBJECTS  = main.o 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: led.elf 

#additional rules for files
led.elf: ${COMMON_OBJECTS} main.o switches.o stateMachines.o buzzer.o led.o wdInterruptHandler.o p2_interrupt_handler.o dim_sequence_c.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

led2.elf: ${COMMON_OBJECTS} main.o switches.o stateMachines.o buzzer.o led.o wdInterruptHandler.o p2_interrupt_handler.o dim_sequence_s.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../lib/libTimer.a

load: led.elf
	msp430loader.sh led.elf

load2: led2.elf
	msp430loader.sh led2.elf

clean:
	rm -f *.o *.c~ *.h~ *~ *.c# *.elf

dim_sequence_c.o: led.h stateMachines.h

dim_sequence_s.o: led.h stateMachines.h

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h led.h switches.h buzzer.h

stateMachines.o: led.h stateMachines.h buzzer.h switches.h notes.h

buzzer.o: buzzer.h

p2_interrupt_handler.o: switches.h

switches.o: switches.h led.h

main.o: led.h switches.h led.h

