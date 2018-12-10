# @author Matthias P. Nowak
# @copyright LGPL 3.0 https://opensource.org/licenses/lgpl-3.0.html
#


# ******************************************
# ***** general definitions for C++ code *****
# ******************************************
SRCS=$(wildcard *.cc)
OBJS=$(SRCS:.cc=.o)

##### the target program #####
TARGET=clean-disk

all: $(TARGET)

##################################################
##### precompiled headers section - C++ case #####
##################################################
CXXFLAGS+=-H -g
HDRS=$(wildcard *.h)
GCHS=$(HDRS:.h=.h.gch)
%.h.gch: %.h
	$(CXX) $(CXXFLAGS) -o $@ $^
$(OBJS): $(GCHS)

#############################
##### rules for target ######
#############################
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)


##### general rules #####

clean:
	rm -f *.o $(TARGET) *.gch

git:
	git add *.cc *.h makefile
	git commit -a

.PHONY: clean test all git

