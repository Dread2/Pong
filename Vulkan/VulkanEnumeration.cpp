#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>
void VulkanEnumeration(VkInstance instance) {
    uint32_t systemDeviceCount = 0;
    VkPhysicalDevice mainGPU = VK_NULL_HANDLE;
     // Create a list because systems usually have Integrated Graphics + GPU, or multiple.
     // Enumerate the devices to find how many actually GPUs are on system. I only want to fill in the count. 
     // Then create a vector, resize it using above and then pass a pointer to the array because Vulkan API magic.
    vkEnumeratePhysicalDevices(instance, &systemDeviceCount, NULL);
    std::vector<VkPhysicalDevice> physicalDevices(systemDeviceCount);
    // You need to query, make the vector bigger and then get the actual
    vkEnumeratePhysicalDevices(instance, &systemDeviceCount, physicalDevices.data());
    // Select Main GPU
    VkPhysicalDevice selectedGPU = physicalDevices[0];
    // Query for the device properties, useful later
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(selectedGPU, &deviceProperties);
    // Print what GPU you selected;
    std::cout << "GPU Selected: " << deviceProperties.deviceName << "\n";
}