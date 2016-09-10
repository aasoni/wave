CC     = g++
CFLAGS = -I./ -Isrc -std=c++0x
SDIR   = src
SRCS   = $(wildcard $(SDIR)/*.cpp)
OBJS   = $(subst .cpp,.o,$(SRCS))

all: wave_simulate.tsk

wave_simulate.tsk: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SDIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean cleanest

clean:
	rm -f $(SDIR)/*.o

cleanest: clean
	rm -f wave_simulate.tsk
