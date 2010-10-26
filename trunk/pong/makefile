EXENAME = pong
LDFLAGS = -lpthread -lncurses

CC = gcc
CFLAGS = -g3 -Wall -std=gnu99 #max debug info, max warning, c99+os calls

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
