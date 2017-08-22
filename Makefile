CC     = gcc
CFLAGS = -O2 -Wall
INCDIR = -I/usr/X11R6/include/X11 -I/usr/X11R6/include
DESTDIR= /usr/X11R6
LIBDIR = -L/usr/X11R6/lib

# for Linux
LIBS   = -lXpm -lX11 -lXext

# for Solaris
#LIBS   = -lXpm  -lX11 -lXext -lsocket -lnsl

OBJS   = wmep8.o xutils.o

.c.o:
	$(CC) $(CFLAGS) -D$(shell echo `uname -s`) -c $< -o $*.o $(INCDIR)

all:    wmep8.o wmep8

wmep8.o: wmep8-master.xpm wmep8-numbers.xpm wmep8-master-mask.xbm
wmep8:	$(OBJS)
	$(CC) $(COPTS) $(SYSTEM) -o wmep8 $^ $(INCDIR) $(LIBDIR) $(LIBS)

clean:
	for i in $(OBJS) ; do \
                rm -f $$i; \
        done
	rm -f wmep8

install::	wmep8
	install -c -s -m 0755 wmep8 $(DESTDIR)/bin
