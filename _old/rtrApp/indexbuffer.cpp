#include "indexbuffer.h"


IndexBuffer::IndexBuffer(QVector<IndexBuffer::T> data,
                         QOpenGLBuffer::UsagePattern usage)
    : buffer_(QOpenGLBuffer::IndexBuffer),
      num_elements_(data.size())

{
    // don't create anything if there is no data
    if(data.size() == 0)
        return;

    // create new vertex buffer
    if(!buffer_.create())
        qFatal("Unable to create index buffer");

    // set usage pattern and copy data into buffer
    buffer_.bind();
    buffer_.setUsagePattern(usage);
    buffer_.allocate(data.constData(), data.size() * sizeof(T));
}

IndexBuffer::IndexBuffer(const std::vector<IndexBuffer::T>& data,
            QOpenGLBuffer::UsagePattern usage)
    : buffer_(QOpenGLBuffer::IndexBuffer),
      num_elements_(data.size())

{
    // don't create anything if there is no data
    if(data.size() == 0)
        return;

    // create new vertex buffer
    if(!buffer_.create())
        qFatal("Unable to create vertex buffer");

    // set usage pattern and copy data into buffer
    buffer_.bind();
    buffer_.setUsagePattern(usage);
    buffer_.allocate(data.data(), data.size() * sizeof(T));
}

void
IndexBuffer::bind()
{
    if(!buffer_.bind())
        qFatal("could not bind VBO");
}

