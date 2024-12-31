#include <vulkan/vulkan.h>
#include <stdexcept>
#include <unordered_map>
// As defined in Vulkan 1.0 API:
// Provided by VK_VERSION_1_0
// typedef struct VkInstanceCreateInfo {
// VkStructureType             sType;
// const void*                 pNext;
// VkInstanceCreateFlags       flags;
// const VkApplicationInfo*    pApplicationInfo;
// uint32_t                    enabledLayerCount;
// const char* const*          ppEnabledLayerNames;
// uint32_t                    enabledExtensionCount;
// const char* const*          ppEnabledExtensionNames;
// } VkInstanceCreateInfo;

// Provided by VK_VERSION_1_0
// typedef struct VkApplicationInfo {
// VkStructureType    sType;
// const void*        pNext;
// const char*        pApplicationName;
// uint32_t           applicationVersion;
// const char*        pEngineName;
// uint32_t           engineVersion;
// uint32_t           apiVersion;
// } VkApplicationInfo;

// https://registry.khronos.org/vulkan/specs/latest/man/html/VkApplicationInfo.html
// https://registry.khronos.org/vulkan/specs/latest/man/html/VkApplicationInfo.html

void VulkanInstance() {
    // Create an instance data member
    VkInstance instance;
    // Information about our application is held inside VkApplicationInfo
    VkApplicationInfo appInfo{};
    // Inform that struct type is VK_STRUCTURE_TYPE_APPLICATION_INFO
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // No need to chain structures so no pNext
    // Ideally, use .pNext to point to another struct that provides more
    // Settings or operations
    // Set the Application Name
    appInfo.pApplicationName = "Pong";
    // Major, Minor, Patch Number
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0 , 0);
    // Set the game engine name
    appInfo.pEngineName= "High Performance Pong";
    // Set the Vulkan Engine version
    appInfo.engineVersion = VK_MAKE_VERSION(1, 2 ,0);
    // Set API Version
    appInfo.apiVersion = VK_API_VERSION_1_2;

    // MANDATORY STRUCT: Passes Global Extensions + Validation Layers for use
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    // Chain Struct. This passes appInfo information to the createInfo struct
    createInfo.pNext = &appInfo;
    // No need for Flags, TBD. Flags allow you to set bits for certain features
    // such as software portability. As defined Flags is a bitmask of VkInstanceCreateFlagBits
    createInfo.flags = 0; 
    // Provide information from AppInfo struct
    createInfo.pApplicationInfo = &appInfo;
    // Create the Vulkan Instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    // Check if the instance was created successfully   
    if (result != VK_SUCCESS) {
        static const std::unordered_map<VkResult, const char*> errorCodes = {
            {VK_ERROR_OUT_OF_HOST_MEMORY, "Host memory allocation failed due to insufficient resources."},
            {VK_ERROR_OUT_OF_DEVICE_MEMORY, "Device memory allocation failed due to insufficient resources."}   ,
            {VK_ERROR_INITIALIZATION_FAILED, "Vulkan initialization failed, possibly due to a system or driver issue."},
            {VK_ERROR_LAYER_NOT_PRESENT, "A requested layer is not available on the system."},
            {VK_ERROR_EXTENSION_NOT_PRESENT, "A requested extension is not available on the system."},
            {VK_ERROR_INCOMPATIBLE_DRIVER, "The installed driver is not compatible with the requested Vulkan features or version."},
        };
    auto it = errorCodes.find(result);
    if (it != errorCodes.end()) {
        throw std::runtime_error(it->second);
    } else {
        throw std::runtime_error("Failed to create Vulkan instance");
    }
    }
}