#pragma once

#include <GL/glew.h>
#include <UB/Debug.hpp>
#include <UB/Graphics/VertexBuffer.hpp>
#include <UB/Graphics/VertexBufferLayout.hpp>

namespace UB
{
	class VertexArray
	{
	public:
		VertexArray();
		VertexArray(const VertexArray&);
		~VertexArray();

		void addBuffer(const UB::VertexBuffer& vb, const UB::VertexBufferLayout& layout);

		void bind() const;
		void unbind() const;

	private:
		unsigned int m_id;
	};
}