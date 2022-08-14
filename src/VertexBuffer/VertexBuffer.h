//
// Created by Erhan Kurnaz on 30/05/2022.
//
#pragma once

class VertexBuffer {
private:
    unsigned int m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetSubData(const void* data, unsigned int size, unsigned int offset);
};
