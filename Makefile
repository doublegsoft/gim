# Copyright (C) 2016-2022 Davidson Francis <davidsondfgl@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>

CC       ?= gcc
AR        = ar
SRC       = $(CURDIR)/src
CFLAGS   +=  -Wall -Wextra -O2
CFLAGS   +=  -std=c99 -pedantic
ARFLAGS   =  cru

EXE				=	gim
SRC				=	$(CURDIR)/src
OBJ 			= $(CURDIR)/build/make/obj

.PHONY: gim

# General objects
base64.o:
	$(CC) $(CFLAGS) -c $(SRC)/base64.c -o $(OBJ)/base64.o

sha1.o:
	$(CC) $(CFLAGS) -c $(SRC)/sha1.c -o $(OBJ)/sha1.o

utf8.o:
	$(CC) $(CFLAGS) -c $(SRC)/utf8.c -o $(OBJ)/utf8.o

handshake.o:
	$(CC) $(CFLAGS) -c $(SRC)/handshake.c -o $(OBJ)/handshake.o

ws.o:
	$(CC) $(CFLAGS) -c $(SRC)/ws.c -o $(OBJ)/ws.o

ini.o:
	$(CC) $(CFLAGS) -c $(SRC)/ini.c -o $(OBJ)/ini.o

sqlite3.o:
	$(CC) $(CFLAGS) -c $(SRC)/sqlite3.c -o $(OBJ)/sqlite3.o

gfc_string.o:
	$(CC) $(CFLAGS) -c $(SRC)/gfc_string.c -o $(OBJ)/gfc_string.o

gim-model.o:
	$(CC) $(CFLAGS) -c $(SRC)/gim-model.c -o $(OBJ)/gim-model.o

jim: base64.o sha1.o utf8.o handshake.o ws.o ini.o sqlite3.o gim-model.o
	$(CC) $(SRC)/jim.c -o $(OBJ)/../$(EXE) \
	$(OBJ)/*.o


# Clean
clean:
	@rm -f $(OBJ)/*.o
