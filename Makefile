# Makefile
# Artur Miguel Dias, 2012
#
# LAP - Projeto 3


##############################################################################
# Base configuration
##############################################################################

APP = Snake
VERSION = 0.00.1
CC = gcc
CPP = g++
CFLAGS = -Wall -W -O1
DEFINES =
LIBS= # -lm
OBJ_DIR = obj
DEBUG =
NAMES = wxTiny Snake
OS = $(shell uname | cut -c 1-7)
EXTRA = -m64

##############################################################################
# Computed configuration
##############################################################################

define OBJS
    $(addprefix $(OBJ_DIR)/,                                            \
        $(addsuffix .o, $(foreach file, $(NAMES), $(file)))             \
    )
endef

ZFLAGS = $(DEBUG)
ZDEFINES = $(EXTRA) -DOS=$(OS) $(DEFINES)
ZLIBS = $(EXTRA) $(LIBS)
ZPRE =

ifeq ($(OS),MINGW32)
ZDEFINES += -DUSE_WXWIDGETS                                             \
            -mthreads -pipe -fmessage-length=0                          \
            -DHAVE_W32API_H -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE    \
            -IC:/SourceCode/Libraries/wxWidgets2.8/lib/gcc_dll/mswu     \
            -IC:/SourceCode/Libraries/wxWidgets2.8/include
ZLIBS += -enable-auto-import -export-all-symbols -mthreads              \
            -LC:/SourceCode/Libraries/wxWidgets2.8/lib/gcc_dll -lwxmsw28u

else # Assume Unix/MacOS
ZDEFINES += -DUSE_WXWIDGETS $(shell wx-config --unicode --cxxflags)
ZLIBS += $(shell wx-config --unicode --libs)
ZPRE +=                                                                 \
 if ! type wx-config >/dev/null 2>&1; then                              \
  echo "\n";                                                            \
  echo "*************************************************************"; \
  echo "Missing WXWIDGETS dependency:";                                 \
  echo "  The developement library \"libwxgtk2.8-dev\" is missing!!!";  \
  echo "  For WXWIDGETS support, you need to install it yourself.";     \
  echo "  In Debian-based systems it is enough to issue the command:";  \
  echo "        sudo apt-get install libwxgtk2.8-dev";                  \
  echo "*************************************************************"; \
  echo "\n";                                                            \
  exit 1;                                                               \
 fi;
endif


##############################################################################
# Build Snake as an application
##############################################################################

$(APP): $(OBJ_DIR) $(OBJS)
	$(CPP) $(CFLAGS) -o $(APP) $(OBJS) $(ZLIBS)
	@$(ZPOST)
	@$(CPP) --version

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(ZFLAGS) $(ZDEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CPP) $(ZFLAGS) $(ZDEFINES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


##############################################################################
# Utilities
##############################################################################

.PHONY : todos
todos:
	todos *.c *.cpp *.h

.PHONY : fromdos
fromdos:
	fromdos *.c *.cpp *.h

.PHONY : file
file:
	file *.c *.cpp *.h

.PHONY : install
install: clean
	todos G*.c G*.h G*.cpp
	cp G*.c G*.h G*.cpp Makefile
	fromdos G*.c G*.h G*.cpp

.PHONY : vi
vi:
	vi *.cpp *.h

.PHONY : clean
clean:
	rm -rf $(APP) $(OBJ_DIR)

run: $(APP)
	./$(APP)

all: $(APP)


##############################################################################
# THE END
##############################################################################
