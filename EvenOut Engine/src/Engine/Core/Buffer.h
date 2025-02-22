 #pragma once

#include "Engine/LogSystem/Log.h"

namespace Engine
{
	enum class ShaderDataType
	{
		None = 0, Vec, Vec2, Vec3 , Vec4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
		case ShaderDataType::Vec:		return 4;
		case ShaderDataType::Vec2:		return 4 * 2;
		case ShaderDataType::Vec3:		return 4 * 3;
		case ShaderDataType::Vec4:		return 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		}

		LOG_CORE("Unknown ShaderDataType!", LOG_ERROR);
		 
		return 0;
	}
	
	struct BufferElement 
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetElementCount() const
		{
			switch (Type) 
			{
			case ShaderDataType::Vec:	return 1;
			case ShaderDataType::Vec2:  return 2;
			case ShaderDataType::Vec3:  return 3;
			case ShaderDataType::Vec4:  return 4;
			case ShaderDataType::Int:	return 1;
			case ShaderDataType::Int2:	return 2;
			case ShaderDataType::Int3:	return 3;
			case ShaderDataType::Int4:	return 4;
			case ShaderDataType::Bool:	return 1;

			}
		}
	};

	class BufferLayout 
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) 
		:m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }


		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride() 
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;

	};

	class VertexBuffer
	{
		public:
			virtual ~VertexBuffer() {}

			virtual void Bind() const  = 0;
			virtual void Unbind() const = 0;

			virtual const BufferLayout& GetLayout() const = 0;
			virtual void SetLayout(const BufferLayout & layout) = 0;

			virtual void SetData(const void* data, uint32_t size) = 0;

			static std::shared_ptr<VertexBuffer> Create(float* vertices, uint32_t size);
			static std::shared_ptr<VertexBuffer> Create(uint32_t size);
	};

	class IndexBuffer
	{
		public:
			virtual ~IndexBuffer() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			virtual uint32_t GetCount() const = 0;

			static std::shared_ptr<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}

