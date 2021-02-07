#pragma once

#include <GL/glew.h>
#include <UB/Debug.hpp>

namespace UB
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		void debugPrint() const;

		inline unsigned int getCount() const { return m_count; };

	private:
		unsigned int m_id;
		unsigned int m_count;
	};
}