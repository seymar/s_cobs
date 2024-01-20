OUT = test_cobs.out
.NOTPARALLEL:
all: createdirs build
createdirs:; @mkdir -p build
build: $(OUT)
$(OUT): %.out: %; @mv $< $@
clean:; rm -f $(OUT)
run: r
r: all; @./$(OUT) 

# $(OUT): ../cobs.c

