# makefile 		1.0		20101028
#
# @author klehmc
# @version 1.0
# @date 20101028
# @course cs3841-002
#
# Copyright 2010 klehmc
#
# This file was developed from several tutorials on the web by searching
# for "automated c compilation"
#
EXENAME = pong
# libraries
LDFLAGS = -lpthread -lncurses
#max debug info (g3), max warning (Wall), c99+os calls (gnu99)
CFLAGS = -g3 -Wall -std=gnu99 
CC = gcc

# Build a list of the object files to create, based on the .c we find
OBJS = $(patsubst %.c,%.o,$(wildcard *.c))

all: $(EXENAME)

$(EXENAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXENAME)

# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	@$(CC) -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

clean:
	rm -f $(EXENAME) *.o *.d
