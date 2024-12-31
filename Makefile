# Pong Target
Pong:
	g++ -std=c++17 ./Vulkan/*.h ./Vulkan/*.cpp main.cpp -lvulkan -o Pong
# Clean
clean:
	@rm Pong