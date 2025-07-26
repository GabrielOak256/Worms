# Makefile for PDCurses for X11

SHELL		= /bin/bash
THIS		= Makefile



PDCURSES_SRCDIR	= ..

osdir		= .
srcdir		= $(PDCURSES_SRCDIR)/pdcurses
demodir		= $(PDCURSES_SRCDIR)/demos

prefix		= /usr/local
exec_prefix	= ${prefix}
libdir		= ${exec_prefix}/lib
bindir		= ${exec_prefix}/bin
includedir	= ${prefix}/include

PDCURSES_CONFIG_H	=$(osdir)/config.h
PDCURSES_CURSES_H	=$(PDCURSES_SRCDIR)/curses.h
PDCURSES_CURSPRIV_H	=$(PDCURSES_SRCDIR)/curspriv.h
PDCURSES_HEADERS	=$(PDCURSES_CONFIG_H) $(PDCURSES_CURSES_H) \
$(PDCURSES_CURSPRIV_H)
PDCURSES_X11_H		=$(osdir)/pdcx11.h

SHLPRE		= lib
SHLPST		= .so
LD_RXLIB1	= ld -G
LD_RXLIB2	=   -L/usr/lib/x86_64-linux-gnu -lXaw -lXmu -lXt -lX11 -lXpm -lSM -lICE -lXext    -lc

CFLAGS		= -I/usr/x86_64-w64-mingw32/include -O

CPPFLAGS	= -DHAVE_CONFIG_H -DXCURSES  -I$(PDCURSES_SRCDIR)

BUILD		= x86_64-w64-mingw32-gcc -c $(CFLAGS) $(CPPFLAGS) -I/usr/include/X11 -I/usr/include
DYN_BUILD	=  $(BUILD) -fPIC -DDYNAMIC -o $@

LINK		= x86_64-w64-mingw32-gcc
LDFLAGS		= $(LIBCURSES) -L/usr/x86_64-w64-mingw32/lib    -L/usr/lib/x86_64-linux-gnu -lXaw -lXmu -lXt -lX11 -lXpm -lSM -lICE -lXext   

INSTALL		= $(osdir)/install-sh
RANLIB		= x86_64-w64-mingw32-ranlib

LIBCURSES	= libXCurses.a

LIB_DEPS        = -L$(PDCURSES_SRCDIR)/x11 -lXCurses

PDCLIBS		= $(LIBCURSES) 

DEMOS		= firework ozdemo ptest rain testcurs tuidemo worm xmas
DEMOOBJS	= firework.o ozdemo.o ptest.o rain.o testcurs.o tui.o \
tuidemo.o worm.o xmas.o

SHLFILE		= XCurses

all:	$(PDCLIBS)

install:
	$(INSTALL) -d -m 755 $(DESTDIR)$(libdir)
	$(INSTALL) -d -m 755 $(DESTDIR)$(bindir)
	$(INSTALL) -d -m 755 $(DESTDIR)$(includedir)
	$(INSTALL) -d -m 755 $(DESTDIR)$(includedir)/xcurses
	$(INSTALL) -c -m 644 $(PDCURSES_CURSES_H) \
		$(DESTDIR)$(includedir)/xcurses/curses.h
	$(INSTALL) -c -m 644 $(PDCURSES_SRCDIR)/panel.h \
		$(DESTDIR)$(includedir)/xcurses/panel.h
	$(INSTALL) -c -m 644 $(osdir)/libXCurses.a $(DESTDIR)$(libdir)/libXCurses.a
	-$(RANLIB) $(DESTDIR)$(libdir)/libXCurses.a
	-$(INSTALL) -c -m 755 $(osdir)/$(SHLPRE)$(SHLFILE)$(SHLPST) \
		$(DESTDIR)$(libdir)/$(SHLPRE)$(SHLFILE)$(SHLPST)
	$(INSTALL) -c -m 755 $(osdir)/xcurses-config $(DESTDIR)$(bindir)/xcurses-config

clean:
	-rm -rf *.o *.sho trace $(PDCLIBS) $(DEMOS) config.log \
		config.cache config.status

demos:	$(DEMOS)

distclean: clean
	-rm -f Makefile config.h xcurses-config

mostlyclean: clean

realclean: distclean

LIBOBJS = addch.o addchstr.o addstr.o attr.o beep.o bkgd.o border.o \
clear.o color.o delch.o deleteln.o getch.o getstr.o getyx.o \
inch.o inchstr.o initscr.o inopts.o insch.o insstr.o instr.o kernel.o \
keyname.o mouse.o move.o outopts.o overlay.o pad.o panel.o printw.o \
refresh.o scanw.o scr_dump.o scroll.o slk.o termattr.o \
touch.o util.o window.o debug.o

PDCOBJS = pdcclip.o pdcdisp.o pdcgetsc.o pdckbd.o pdcscrn.o pdcsetsc.o \
pdcutil.o sb.o scrlbox.o

LIBSHOBJS = $(LIBOBJS:.o=.sho)
PDCSHOBJS = $(PDCOBJS:.o=.sho)

SHOFILES = $(LIBSHOBJS) $(PDCSHOBJS)

$(LIBCURSES) : $(LIBOBJS) $(PDCOBJS)
	ar rv $@ $?
	-$(RANLIB) $@

$(SHLPRE)$(SHLFILE)$(SHLPST) : $(SHOFILES)
	$(LD_RXLIB1) -o $@ $(SHOFILES) $(LD_RXLIB2)

$(LIBOBJS) $(PDCOBJS) $(SHOFILES) : $(PDCURSES_HEADERS)
$(PDCOBJS) $(PDCSHOBJS) : $(PDCURSES_X11_H)
$(DEMOOBJS) : $(PDCURSES_CURSES_H)
$(DEMOS) : $(LIBCURSES)

addch.o: $(srcdir)/addch.c
	$(BUILD) $(srcdir)/addch.c

addchstr.o: $(srcdir)/addchstr.c
	$(BUILD) $(srcdir)/addchstr.c

addstr.o: $(srcdir)/addstr.c
	$(BUILD) $(srcdir)/addstr.c

attr.o: $(srcdir)/attr.c
	$(BUILD) $(srcdir)/attr.c

beep.o: $(srcdir)/beep.c
	$(BUILD) $(srcdir)/beep.c

bkgd.o: $(srcdir)/bkgd.c
	$(BUILD) $(srcdir)/bkgd.c

border.o: $(srcdir)/border.c
	$(BUILD) $(srcdir)/border.c

clear.o: $(srcdir)/clear.c
	$(BUILD) $(srcdir)/clear.c

color.o: $(srcdir)/color.c
	$(BUILD) $(srcdir)/color.c

delch.o: $(srcdir)/delch.c
	$(BUILD) $(srcdir)/delch.c

deleteln.o: $(srcdir)/deleteln.c
	$(BUILD) $(srcdir)/deleteln.c

getch.o: $(srcdir)/getch.c
	$(BUILD) $(srcdir)/getch.c

getstr.o: $(srcdir)/getstr.c
	$(BUILD) $(srcdir)/getstr.c

getyx.o: $(srcdir)/getyx.c
	$(BUILD) $(srcdir)/getyx.c

inch.o: $(srcdir)/inch.c
	$(BUILD) $(srcdir)/inch.c

inchstr.o: $(srcdir)/inchstr.c
	$(BUILD) $(srcdir)/inchstr.c

initscr.o: $(srcdir)/initscr.c
	$(BUILD) $(srcdir)/initscr.c

inopts.o: $(srcdir)/inopts.c
	$(BUILD) $(srcdir)/inopts.c

insch.o: $(srcdir)/insch.c
	$(BUILD) $(srcdir)/insch.c

insstr.o: $(srcdir)/insstr.c
	$(BUILD) $(srcdir)/insstr.c

instr.o: $(srcdir)/instr.c
	$(BUILD) $(srcdir)/instr.c

kernel.o: $(srcdir)/kernel.c
	$(BUILD) $(srcdir)/kernel.c

keyname.o: $(srcdir)/keyname.c
	$(BUILD) $(srcdir)/keyname.c

mouse.o: $(srcdir)/mouse.c
	$(BUILD) $(srcdir)/mouse.c

move.o: $(srcdir)/move.c
	$(BUILD) $(srcdir)/move.c

outopts.o: $(srcdir)/outopts.c
	$(BUILD) $(srcdir)/outopts.c

overlay.o: $(srcdir)/overlay.c
	$(BUILD) $(srcdir)/overlay.c

pad.o: $(srcdir)/pad.c
	$(BUILD) $(srcdir)/pad.c

panel.o: $(srcdir)/panel.c $(PDCURSES_SRCDIR)/panel.h
	$(BUILD) $(srcdir)/panel.c

printw.o: $(srcdir)/printw.c
	$(BUILD) $(srcdir)/printw.c

refresh.o: $(srcdir)/refresh.c
	$(BUILD) $(srcdir)/refresh.c

scanw.o: $(srcdir)/scanw.c
	$(BUILD) $(srcdir)/scanw.c

scr_dump.o: $(srcdir)/scr_dump.c
	$(BUILD) $(srcdir)/scr_dump.c

scroll.o: $(srcdir)/scroll.c
	$(BUILD) $(srcdir)/scroll.c

slk.o: $(srcdir)/slk.c
	$(BUILD) $(srcdir)/slk.c

termattr.o: $(srcdir)/termattr.c
	$(BUILD) $(srcdir)/termattr.c

touch.o: $(srcdir)/touch.c
	$(BUILD) $(srcdir)/touch.c

util.o: $(srcdir)/util.c
	$(BUILD) $(srcdir)/util.c

window.o: $(srcdir)/window.c
	$(BUILD) $(srcdir)/window.c

debug.o: $(srcdir)/debug.c
	$(BUILD) $(srcdir)/debug.c

pdcclip.o: $(osdir)/pdcclip.c
	$(BUILD) $(osdir)/pdcclip.c

pdcdisp.o: $(osdir)/pdcdisp.c
	$(BUILD) $(osdir)/pdcdisp.c

pdcgetsc.o: $(osdir)/pdcgetsc.c
	$(BUILD) $(osdir)/pdcgetsc.c

pdckbd.o: $(osdir)/pdckbd.c
	$(BUILD) $(osdir)/pdckbd.c

pdcscrn.o: $(osdir)/pdcscrn.c
	$(BUILD) $(osdir)/pdcscrn.c

pdcsetsc.o: $(osdir)/pdcsetsc.c
	$(BUILD) $(osdir)/pdcsetsc.c

pdcutil.o: $(osdir)/pdcutil.c
	$(BUILD) $(osdir)/pdcutil.c

scrlbox.o: $(osdir)/scrlbox.c
	$(BUILD) $(osdir)/scrlbox.c

sb.o: $(osdir)/sb.c
	$(BUILD) $(osdir)/sb.c

addch.sho: $(srcdir)/addch.c
	$(DYN_BUILD) $(srcdir)/addch.c
	

addchstr.sho: $(srcdir)/addchstr.c
	$(DYN_BUILD) $(srcdir)/addchstr.c
	

addstr.sho: $(srcdir)/addstr.c
	$(DYN_BUILD) $(srcdir)/addstr.c
	

attr.sho: $(srcdir)/attr.c
	$(DYN_BUILD) $(srcdir)/attr.c
	

beep.sho: $(srcdir)/beep.c
	$(DYN_BUILD) $(srcdir)/beep.c
	

bkgd.sho: $(srcdir)/bkgd.c
	$(DYN_BUILD) $(srcdir)/bkgd.c
	

border.sho: $(srcdir)/border.c
	$(DYN_BUILD) $(srcdir)/border.c
	

clear.sho: $(srcdir)/clear.c
	$(DYN_BUILD) $(srcdir)/clear.c
	

color.sho: $(srcdir)/color.c
	$(DYN_BUILD) $(srcdir)/color.c
	

delch.sho: $(srcdir)/delch.c
	$(DYN_BUILD) $(srcdir)/delch.c
	

deleteln.sho: $(srcdir)/deleteln.c
	$(DYN_BUILD) $(srcdir)/deleteln.c
	

getch.sho: $(srcdir)/getch.c
	$(DYN_BUILD) $(srcdir)/getch.c
	

getstr.sho: $(srcdir)/getstr.c
	$(DYN_BUILD) $(srcdir)/getstr.c
	

getyx.sho: $(srcdir)/getyx.c
	$(DYN_BUILD) $(srcdir)/getyx.c
	

inch.sho: $(srcdir)/inch.c
	$(DYN_BUILD) $(srcdir)/inch.c
	

inchstr.sho: $(srcdir)/inchstr.c
	$(DYN_BUILD) $(srcdir)/inchstr.c
	

initscr.sho: $(srcdir)/initscr.c
	$(DYN_BUILD) $(srcdir)/initscr.c
	

inopts.sho: $(srcdir)/inopts.c
	$(DYN_BUILD) $(srcdir)/inopts.c
	

insch.sho: $(srcdir)/insch.c
	$(DYN_BUILD) $(srcdir)/insch.c
	

insstr.sho: $(srcdir)/insstr.c
	$(DYN_BUILD) $(srcdir)/insstr.c
	

instr.sho: $(srcdir)/instr.c
	$(DYN_BUILD) $(srcdir)/instr.c
	

kernel.sho: $(srcdir)/kernel.c
	$(DYN_BUILD) $(srcdir)/kernel.c
	

keyname.sho: $(srcdir)/keyname.c
	$(DYN_BUILD) $(srcdir)/keyname.c
	

mouse.sho: $(srcdir)/mouse.c
	$(DYN_BUILD) $(srcdir)/mouse.c
	

move.sho: $(srcdir)/move.c
	$(DYN_BUILD) $(srcdir)/move.c
	

outopts.sho: $(srcdir)/outopts.c
	$(DYN_BUILD) $(srcdir)/outopts.c
	

overlay.sho: $(srcdir)/overlay.c
	$(DYN_BUILD) $(srcdir)/overlay.c
	

pad.sho: $(srcdir)/pad.c
	$(DYN_BUILD) $(srcdir)/pad.c
	

panel.sho: $(srcdir)/panel.c $(PDCURSES_SRCDIR)/panel.h
	$(DYN_BUILD) $(srcdir)/panel.c
	

printw.sho: $(srcdir)/printw.c
	$(DYN_BUILD) $(srcdir)/printw.c
	

refresh.sho: $(srcdir)/refresh.c
	$(DYN_BUILD) $(srcdir)/refresh.c
	

scanw.sho: $(srcdir)/scanw.c
	$(DYN_BUILD) $(srcdir)/scanw.c
	

scr_dump.sho: $(srcdir)/scr_dump.c
	$(DYN_BUILD) $(srcdir)/scr_dump.c
	

scroll.sho: $(srcdir)/scroll.c
	$(DYN_BUILD) $(srcdir)/scroll.c
	

slk.sho: $(srcdir)/slk.c
	$(DYN_BUILD) $(srcdir)/slk.c
	

termattr.sho: $(srcdir)/termattr.c
	$(DYN_BUILD) $(srcdir)/termattr.c
	

touch.sho: $(srcdir)/touch.c
	$(DYN_BUILD) $(srcdir)/touch.c
	

util.sho: $(srcdir)/util.c
	$(DYN_BUILD) $(srcdir)/util.c
	

window.sho: $(srcdir)/window.c
	$(DYN_BUILD) $(srcdir)/window.c
	

debug.sho: $(srcdir)/debug.c
	$(DYN_BUILD) $(srcdir)/debug.c
	

pdcclip.sho: $(osdir)/pdcclip.c
	$(DYN_BUILD) $(osdir)/pdcclip.c
	

pdcdisp.sho: $(osdir)/pdcdisp.c
	$(DYN_BUILD) $(osdir)/pdcdisp.c
	

pdcgetsc.sho: $(osdir)/pdcgetsc.c
	$(DYN_BUILD) $(osdir)/pdcgetsc.c
	

pdckbd.sho: $(osdir)/pdckbd.c
	$(DYN_BUILD) $(osdir)/pdckbd.c
	

pdcscrn.sho: $(osdir)/pdcscrn.c
	$(DYN_BUILD) $(osdir)/pdcscrn.c
	

pdcsetsc.sho: $(osdir)/pdcsetsc.c
	$(DYN_BUILD) $(osdir)/pdcsetsc.c
	

pdcutil.sho: $(osdir)/pdcutil.c
	$(DYN_BUILD) $(osdir)/pdcutil.c
	

scrlbox.sho: $(osdir)/scrlbox.c
	$(DYN_BUILD) $(osdir)/scrlbox.c
	

sb.sho: $(osdir)/sb.c
	$(DYN_BUILD) $(osdir)/sb.c
	

firework: firework.o
	$(LINK) firework.o -o $@ $(LDFLAGS)

ozdemo: ozdemo.o
	$(LINK) ozdemo.o -o $@ $(LDFLAGS)

ptest: ptest.o
	$(LINK) ptest.o -o $@ $(LDFLAGS)

rain: rain.o
	$(LINK) rain.o -o $@ $(LDFLAGS)

testcurs: testcurs.o
	$(LINK) testcurs.o -o $@ $(LDFLAGS)

tuidemo: tuidemo.o tui.o
	$(LINK) tui.o tuidemo.o -o $@ $(LDFLAGS)

worm: worm.o
	$(LINK) worm.o -o $@ $(LDFLAGS)

xmas: xmas.o
	$(LINK) xmas.o -o $@ $(LDFLAGS)

firework.o: $(demodir)/firework.c
	$(BUILD) $(demodir)/firework.c

ozdemo.o: $(demodir)/ozdemo.c
	$(BUILD) $(demodir)/ozdemo.c

ptest.o: $(demodir)/ptest.c $(PDCURSES_SRCDIR)/panel.h
	$(BUILD) $(demodir)/ptest.c

rain.o: $(demodir)/rain.c
	$(BUILD) $(demodir)/rain.c

testcurs.o: $(demodir)/testcurs.c
	$(BUILD) $(demodir)/testcurs.c

tui.o: $(demodir)/tui.c $(demodir)/tui.h
	$(BUILD) $(demodir)/tui.c

tuidemo.o: $(demodir)/tuidemo.c
	$(BUILD) $(demodir)/tuidemo.c

worm.o: $(demodir)/worm.c
	$(BUILD) $(demodir)/worm.c

xmas.o: $(demodir)/xmas.c
	$(BUILD) $(demodir)/xmas.c

# This section provides for compiling and linking the
# ncurses test programs.

ncurses_testdir	= $(HOME)/ncurses-6.4/test

NCURSES_TESTS	= bs gdc hanoi knight tclock lrtest ncurses

ncurses_tests: $(NCURSES_TESTS)

ncurses_clean:
	-rm -f *.o trace $(NCURSES_TESTS)

NCFLAGS		= -I$(demodir) -I$(ncurses_testdir)

bs: bs.o $(LIBCURSES)
	$(LINK) bs.o -o $@ $(LDFLAGS)

gdc: gdc.o $(LIBCURSES)
	$(LINK) gdc.o -o $@ $(LDFLAGS)

hanoi: hanoi.o $(LIBCURSES)
	$(LINK) hanoi.o -o $@ $(LDFLAGS) -lm

knight: knight.o $(LIBCURSES)
	$(LINK) knight.o -o $@ $(LDFLAGS)

tclock: tclock.o $(LIBCURSES)
	$(LINK) tclock.o -o $@ $(LDFLAGS) -lm

lrtest: lrtest.o $(LIBCURSES)
	$(LINK) lrtest.o -o $@ $(LDFLAGS)

ncurses: ncurses.o $(LIBCURSES)
	$(LINK) ncurses.o -o $@ $(LDFLAGS)

bs.o: $(ncurses_testdir)/bs.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/bs.c

gdc.o: $(ncurses_testdir)/gdc.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/gdc.c

hanoi.o: $(ncurses_testdir)/hanoi.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/hanoi.c

knight.o: $(ncurses_testdir)/knight.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/knight.c

tclock.o: $(ncurses_testdir)/tclock.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/tclock.c

lrtest.o: $(ncurses_testdir)/lrtest.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/lrtest.c

ncurses.o: $(ncurses_testdir)/ncurses.c $(PDCURSES_CURSES_H)
	$(BUILD) $(NCFLAGS) $(ncurses_testdir)/ncurses.c
