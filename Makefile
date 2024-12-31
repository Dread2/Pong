# Pong Target
Pong:
	g++ -I ./Vulkan -o Pong Vulkan/Vulkan*.cpp main.cpp -lvulkan -o Pong
# PHONY
.PHONY: clean
# Clean
clean:
	@rm Pong