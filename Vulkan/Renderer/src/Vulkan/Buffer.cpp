#include "Buffer.h"
#include "GPU.h"

#include "CommandPool.h"

Buffer::Buffer(VkDeviceSize bufferSize, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryFlags) {}

/*
void Buffer::CopyBuffer(VkBuffer& from, VkBuffer& to, VkDeviceSize size, const CommandPool& commandPool, const DeviceContext& context) {

	VkCommandBufferAllocateInfo createInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
	createInfo.commandPool = commandPool.GetCommandPool();
	createInfo.commandBufferCount = 1;
	createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	VkCommandBuffer commandBuffer;
	VKCALL(vkAllocateCommandBuffers(context.Handle->Get(), &createInfo, &commandBuffer));

	VkCommandBufferBeginInfo recordInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
	recordInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &recordInfo);

	VkBufferCopy copyInfo{};
	copyInfo.size = size;

	vkCmdCopyBuffer(commandBuffer, from, to, 1, &copyInfo);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(context.GPU->GetTransferQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(context.GPU->GetTransferQueue());

	vkFreeCommandBuffers(context.Handle->Get(), commandPool.GetCommandPool(), 1, &commandBuffer);
}
_*/