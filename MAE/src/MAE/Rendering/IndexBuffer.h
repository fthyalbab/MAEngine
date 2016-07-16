#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Types.h>

class IndexBuffer: public Releasable {
public:
	enum {
		MapWrite = 0x01,
		MapRead  = 0x02
	};

	virtual void release() = 0;

	template<typename T> T* map(uint offset, uint size, uint flags) {
		return (T*) map(offset, size, flags);
	}

	virtual void* map(uint offset, uint size, uint flags) = 0;
	virtual void unmap() = 0;
	virtual void upload(const void* data, uint offset, uint size) = 0;
};
