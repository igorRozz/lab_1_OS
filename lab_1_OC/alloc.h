#pragma once
class alloc
{
public:
	alloc(size_t memorySize);
	~alloc();
	void mem_dump();
	void* mem_alloc(size_t size);
	void mem_free(void* ptr);
	void* mem_realloc(void* ptr, size_t size);
private:
	size_t memorySize;
	void* memory;
};