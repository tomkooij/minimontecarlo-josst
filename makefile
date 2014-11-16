#
# Makefile tested on Cygwin-x64 (Windows 7 laptop) 
#    and RedHat Linux 2.6 (tevere.nikef.nl)
#

# CFLAGS =	-g -I. -I/home/josst/SOURCES/LIBRAN/
#CFLAGS =	-g -I. -I/localstore/hermes/josst/LIBRAN
CFLAGS = -g -I.
LFLAGS = 	-g

SRCS =		main.c \
		compelec.c \
		compscat.c \
		next_interaction.c\
		new_event.c \
		pe.c \
		process_electron.c \
		process_photon.c

OBJS =		$(SRCS:.c=.o)

# LIBS =		/home/josst/SOURCES/LIBRAN/libran.a
LIBS =		LIBRAN/libran.a

PROGRAM =	a.out

$(PROGRAM):	$(OBJS)
		cc $(LFLAGS) $(OBJS) $(LIBS) -o $@ -lm

depend:		$(SRCS)
		makedepend $(CFLAGS) $(SRCS)

clean:
		/bin/rm $(OBJS)
# DO NOT DELETE
