DEST     = 	$(HOME)/LIB

LIBRAN   = 	libran.a

INCLUDES = 	

CFLAGS   = 	$(INCLUDES)

HEADERS  =	libran.h

SRCS     =	ranexp.c \
		rangauss.c \
		ranset.c \
		random.c \
		randival.c \
		rndnmbr.c \
		init.c
 
OBJS     =	ranexp.o \
		rangauss.o \
		ranset.o \
		random.o \
		randival.o \
		rndnmbr.o \
		init.o

$(LIBRAN):	$(OBJS)
		ar rv $(LIBRAN) $(OBJS)
		ranlib $(LIBRAN)

depend:		$(SRCS)
		makedepend $(INCLUDES) $(SRCS)

install:	$(LIBRAN)
		cp $(LIBRAN) $(DEST)/$(LIBRAN)
		cp libran.h $(HOME)/INCLUDE/libran.h
clean::
		/bin/rm $(OBJS) $(LIBRAN)

# DO NOT DELETE THIS LINE -- make depend depends on it.
