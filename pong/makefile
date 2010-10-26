SHELL = /bin/sh
SRCDIR = .
CC = gcc
YACC = bison -y
CDEBUG = -g
COMPLIANCE_FLAGS =
CFLAGS = $(COMPLIANCE_FLAGS) $(CDEBUG) -I. -I$(SRCDIR)
LDFLAGS = -g -lpthread -lncurses
# List your sources and objects here.
SOURCES =
OBJS = pong.o opponent.o ballctrl.o paddlectrl.o
# list the name of your output program here.
EXECUTABLE = pong

$(EXECUTABLE) : $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXECUTABLE)  $(OBJS)

include $(OBJS:.o=.d)

all : $(OBJS) $(EXECUTABLE)

	
%.o : %.c #Defines how to translate a single c file into an object file.
	echo compiling $<
	echo $(CC) $(CFLAGS) -c $<
	$(CC) $(CFLAGS) -E $< > $<.preout
	$(CC) $(CFLAGS) -S $<
	$(CC) $(CFLAGS) -c $<
	echo done compiling $<


%.d : %.c #Defines how to generate the dependencies for the given files.  -M gcc option generates dependencies.
	@set -e; rm -f $@; \
	$(CC) $(COMPLIANCE_FLAGS ) -M $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

clean :   # Clean build in which everything is created from scratch.
	rm -f *.o
	rm -f *d
	rm -f *bb
	rm -f *bbg
	rm -f *gcov
	rm -f *da
	rm -f *preout
	rm -f *.s
	rm -f $(EXECUTABLE)
