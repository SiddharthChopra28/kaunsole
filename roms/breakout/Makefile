ASSET_SRC := $(shell find assets -type f)
ASSET_OBJ := $(ASSET_SRC:assets/%=build/assets/%.o)
SRCS := main.c
BUILDDIR := .

$(BUILDDIR)/breakout: $(SRCS) $(ASSETS)
	$(CC) -fPIC -shared $^ -o $@

build/assets/%.o: assets/%
	mkdir -p $(dir $@)

clean:
	rm game *.o
