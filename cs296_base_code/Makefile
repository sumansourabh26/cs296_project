.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################


# Project Name (generate executable with this name)
TARGET = cs296_18_exe
SHARED_LIB = true

TARGET_USING_LIB = cs296_18_exelib
STATIC_LIB = libCS296test.a 
DYNAMIC_LIB = libCS296test.so


# Project Paths
PROJECT_ROOT :=$(CURDIR)
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
DOCDIR = $(PROJECT_ROOT)/doc
SRCDIR = $(PROJECT_ROOT)/src
MYOBJDIR = $(PROJECT_ROOT)/myobjs
MYBINDIR = $(PROJECT_ROOT)/mybins
MYLIBDIR = $(PROJECT_ROOT)/mylibs
DATADIR = $(PROJECT_ROOT)/data
SCRIPTDIR = $(PROJECT_ROOT)/scripts

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"

########################################################################################

BOXSRC = $(BOX2D_ROOT)/src


SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
MYOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(MYOBJDIR)/%.o)
WITHOUT_MAIN := $(filter-out $(MYOBJDIR)/main.o ,$(MYOBJS))

LATEXFILE = cs296_report_18

########################################################################################

.PHONY: all setup exe exelib clean distclean doc report data

all: setup

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p myobjs
	@mkdir -p mybins
	@mkdir -p mylibs
	@if test -e $(BOX2D_ROOT)/include/Box2D && test -e $(BOX2D_ROOT)/lib/Box2D; \
	then $(ECHO) "Already Installed Box2D"; \
	else tar -xvzf $(BOXSRC)/Box2D.tgz -C $(BOXSRC) && cd $(BOXSRC)/Box2D && mkdir build296 \
	&& cd build296 && cmake ../ && make && make install && cd $(PROJECT_ROOT); \
	fi;

exe: setup $(MYBINDIR)/$(TARGET)
	@$(ECHO) "[Executable generated using object files! ]"
	
exelib: setup $(MYBINDIR)/$(TARGET_USING_LIB)
	@$(ECHO) "[Executable generated using library! ]"

######################################################################################

$(MYBINDIR)/$(TARGET_USING_LIB): $(MYOBJDIR)/main.o createLIB 
	@$(PRINTF) "$(MESG_COLOR)Building executable using library:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@if ($(SHARED_LIB)); \
	then $(CC) -o $@ $< $(MYLIBDIR)/$(DYNAMIC_LIB) $(LDFLAGS) $(LIBS) 2> temp.log || touch temp.err; \
	else $(CC) -o $@ $(LDFLAGS) $< $(MYLIBDIR)/$(STATIC_LIB) $(LIBS) 2> temp.log || touch temp.err; \
	fi;
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

createLIB: $(WITHOUT_MAIN)
	@if ($(SHARED_LIB)); \
	then rm -f $(MYLIBDIR)/$(DYNAMIC_LIB) && gcc -shared -o $(MYLIBDIR)/$(DYNAMIC_LIB) $(WITHOUT_MAIN) 2> temp.log || touch temp.err;\
	else rm -f $(MYLIBDIR)/$(STATIC_LIB) && ar -cvq $(MYLIBDIR)/$(STATIC_LIB) $(WITHOUT_MAIN) 2> temp.log || touch temp.err;\
	fi;
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err


#######################################################################################
$(MYBINDIR)/$(TARGET): $(MYOBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(MYOBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include $(MYOBJS:.o=.d)
$(MYOBJS): $(MYOBJDIR)/%.o:$(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -fPIC -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err	

#######################################################################################

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

report:
	cd $(DOCDIR); \
	latex $(LATEXFILE); \
	bibtex $(LATEXFILE); \
	latex $(LATEXFILE); \
	latex $(LATEXFILE); \
	pdflatex $(LATEXFILE); \
	$(RM) -f cs296_report_18.dvi cs296_report_18.aux cs296_report_18.bbl cs296_report_18.log cs296_report_18.blg

########################################################################################

data: exe
	@$(PRINTF) "Generating CSV data files: "
	@cd $(SCRIPTDIR); \
	./g18_gen_data.sh; \
	./g18_gen_csv.sh; \
	./g18_gen_data_csv.sh; \
	./g18_gen_data_random.sh
	@$(ECHO) "Done"

########################################################################################

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(MYOBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(MYBINDIR) $(MYLIBDIR) $(DOCDIR)/cs296_report_18.pdf \
	$(DATADIR)/*txt $(DATADIR)/*.csv
	@$(ECHO) "Done"

distclean: clean
	@$(RM) -rf $(MYOBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(MYBINDIR) $(MYLIBDIR) $(DOCDIR)/html \
	$(EXTERNAL_ROOT)/include/* $(EXTERNAL_ROOT)/lib/* $(EXTERNAL_ROOT)/src/Box2D

