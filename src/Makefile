# Copyright {C} 2007 Gabriel Falcão <gabriel@guake-terminal.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or {at your option} any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License along with this program; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#mkdir -p ${HOME}/bin/ ${HOME}/lib/ && 

INSTALL=/usr/bin/install -c 
INSTALL_DATA=${INSTALL} -m 644 
INSTALL_PROGRAM=${INSTALL}
CREATE_DIR=/bin/mkdir -p
UNINSTALL=rm -rf

LIBPATH=lib/
LIBSOURCE=${LIBPATH}libpep8.c
LIBNAME=${LIBPATH}libpep8.so
EXECNAME=pep8check
EXECSOURCE = pep8check.c

all:
	make libs
	gcc -Wall -Wextra -Werror `pkg-config --libs --cflags glib-2.0` -Llib -lpep8 ${EXECSOURCE} -o pep8check

dist: clean
	tar cjvf ../`head -1 README | cut -d" " -f1`.tar.bz2 ../`pwd | sed 's/.*[/]\(.*\)/\1/'`

install: all
	@test '${USER}' = 'root' && \
		${INSTALL_PROGRAM} ${LIBNAME} /usr/${LIBNAME} && \
		${INSTALL_PROGRAM} ${EXECNAME} /usr/bin/${EXECNAME} || \
		${CREATE_DIR} ${HOME}/bin ${HOME}/lib && \
		${INSTALL_PROGRAM} ${LIBNAME} ${HOME}/${LIBNAME} && \
		${INSTALL_PROGRAM} ${EXECNAME} ${HOME}/bin/${EXECNAME} 
	make clean

uninstall: 
	@test '${USER}' = 'root' && \
		${UNINSTALL} /usr/${LIBNAME} && \
		${UNINSTALL} /usr/bin/${EXECNAME} || \
		${UNINSTALL} ${HOME}/${LIBNAME} && \
		${UNINSTALL} ${HOME}/bin/${EXECNAME} 

libs:
	gcc -fPIC -DPIC -soname -shared -Wall -Wextra -Werror `pkg-config --libs --cflags glib-2.0` ${LIBSOURCE} -o ${LIBNAME}

clean:
	rm -f ${EXECNAME}
	rm -f ${LIBNAME}
	rm -f *.bz2
