BUILD_DIR := build

.PHONY: run clean

run: build
	./$(BUILD_DIR)/cppRef

build: always
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DCMAKE_BUILD_TYPE=Debug 2>/dev/null
	@cd $(BUILD_DIR) && make

always:

clean:
	rm -rf $(BUILD_DIR)
