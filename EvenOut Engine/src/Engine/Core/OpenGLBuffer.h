#pragma once

#include "Buffer.h"

namespace Engine 
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
		public:
			OpenGLVertexBuffer(float* vertices, uint32_t size);
			OpenGLVertexBuffer(uint32_t size);

			virtual ~OpenGLVertexBuffer();

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual const BufferLayout& GetLayout() const override { return m_Layout; }
			virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

			virtual void SetData(const void* data, uint32_t size) override;
		private:
			uint32_t m_RendererID;
			BufferLayout m_Layout;

	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const { return m_Count; }

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};
}

