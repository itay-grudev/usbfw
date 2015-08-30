# Copyright (C) 2015 Itay Grudev <itay@grudev.com>
#
# This file is part of the USB Firewall.
# USB Firewall is free software:  you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3 as published
# by the Free Software Foundation.
#
# USB  Firewall  is distributed in the hope  that it will be  useful,  but
# WITHOUT ANY WARRANTY;  without even implied warranty of  MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# version 3 for more details.
#
# You should have received a copy of the  GNU General Public License along
# with the software. If not, see <http://www.gnu.org/licenses/>.

EXECNAME = usbfw
BINDIR   = bin/
OBJDIR   = $(BINDIR)obj/

# List the source input directories
SRCDIRS = .

# The source file types (headers excluded).
# .c indicates C source files, and others C++ ones.
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp

SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
OBJECTS = $(addprefix $(OBJDIR), $(SOURCES:.cpp=.o))

# Compiler command
CC = g++

# Initial flags (are added to the compile command first)
# You might need CCFLAGS -I /usr/local/include/
CCFLAGS = -Wall -pedantic -std=c++11
LDFLAGS =

EXECUTABLE = $(BINDIR)$(EXECNAME)

# Check for debug or not
ifeq ($(BUILD),debug)
	CCFLAGS += -g
else
	CCFLAGS += -O2
endif

# Check if we need to make a seperate bin folder
ifneq ($(BINDIR), )
	BINDIRCOMMAND = mkdir -p $(BINDIR)
else
	BINDIRCOMMAND =
endif

# Check if we need to make a seperate obj folder and its subfolder structure
ifneq ($(OBJDIR), )
	OBJDIRCOMMAND = mkdir -p $(OBJDIR)
	OBJDIRCOMMAND += $(foreach d,$(SRCDIRS), $(OBJDIR)$(d))
else
	OBJDIRCOMMAND =
endif

# Building recipies
all: $(SOURCES) $(EXECUTABLE)

run:
	$(EXECUTABLE)

$(EXECUTABLE): bindir objdir $(OBJECTS)
	$(CC) $(CCFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

bindir:
	$(BINDIRCOMMAND)

objdir:
	$(OBJDIRCOMMAND)

$(OBJECTS) : $(OBJDIR)%.o : $(SRCDIR)%.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) -c -o $@ $<

# Cleaning recipies
clean: clean-bin clean-obj

clean-bin:
	rm -rf $(BINDIR)

clean-obj:
	rm -rf $(OBJDIR)

.PHONY: all run clean clean-bin clean-obj bindir objdir
