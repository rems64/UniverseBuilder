#pragma once

#include <GL/glew.h>
#include <UB/Debug.hpp>

namespace UB
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(const void*, unsigned int);
		~VertexBuffer();

		void setBuffer(const void*, unsigned int);

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_id;
	};
}