#include <UB/Graphics/VertexArray.hpp>

UB::VertexArray::VertexArray() : m_id(0)
{
	GLCall(glCreateVertexArrays(1, &m_id));
}

UB::VertexArray::VertexArray(const VertexArray& va2) : m_id(0)
{
	m_id = va2.m_id;
}

UB::VertexArray::~VertexArray()
{
	//GLCall(glDeleteVertexArrays(1, &m_id));
}

void UB::VertexArray::addBuffer(const UB::VertexBuffer& vb, const UB::VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void UB::VertexArray::bind() const
{
	//std::cout << "[INFO] Index" << m_id << std::endl;
	GLCall(glBindVertexArray(m_id));
}

void UB::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
