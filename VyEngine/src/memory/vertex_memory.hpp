#pragma once

#include <glad/glad.h>
#include <map>
#include <iostream>

/*
    Buffer Objects (VBO's, EBO's, etc...)
*/

class BufferObject
{
    public:

    // Buffer ID
    GLuint bID;

    // Type of buffer (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, etc...)
    GLenum type;

    // Constructor
    BufferObject(GLenum bufferType = GL_ARRAY_BUFFER) :
        type(bufferType), bID(0) {}
    
	/// <summary>
	/// Generate a Buffer Object and assign it to the ID.
	/// </summary>
	void generate()
	{
		glGenBuffers(1, &bID);
	}

	/// <summary>
	/// Bind the Buffer Object.
	/// </summary>
	void bind()
	{
		glBindBuffer(type, bID);
	}

	/// <summary>
	/// Unbind the Buffer Object.
	/// </summary>
	void clear()
	{
		glBindBuffer(type, 0);
	}

	/// <summary>
	/// Delete the Buffer Object.
	/// </summary>
	void cleanup()
	{
		glDeleteBuffers(1, &bID);
	}

	/// <summary>
	/// Create and initialize a Buffer Object's data store. (glBufferData)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="numElements: ">The number of elements that will determine the buffer's size
	/// by multiplying it by sizeof(T).</param>
	/// <param name="data: ">The pointer to data that will be copied into the data store for initialization, 
	/// or NULL if no data is to be copied.</param>
	/// <param name="usage: ">Specifies the expected usage pattern of the data store. 
	/// The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, 
	/// GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.</param>
	template<typename T>
	void setData(GLuint numElements, T* data, GLenum usage)
	{
		glBufferData(type, numElements * sizeof(T), data, usage);
	}


	/// <summary>
	/// Update a subset of the Buffer Object's data store. (glBufferSubData)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="offset: ">The offset into the buffer object's data store where data replacement will begin, 
	/// measured in bytes.</param>
	/// <param name="numElements: ">The number of elements that will determine the size of the data store being replaced 
	/// by multiplying it by sizeof(T).</param>
	/// <param name="data: ">The pointer to the new data that will be copied into the data store.</param>
	template<typename T>
	void updateData(GLintptr offset, GLuint numElements, T* data)
	{
		glBufferSubData(type, offset, numElements * sizeof(T), data);
	}


	/// <summary>
	/// Define an array of generic vertex attribute data. (glVertexAttribPointer)
	/// Enable the vertex attribute array at 'index.' (glEnableVertexAttribArray)
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index: ">The index of the generic vertex attribute to be modified.</param>
	/// <param name="size: ">The number of components per generic vertex attribute. Must be 1, 2, 3, 4.</param>
	/// <param name="type: ">The data type of each component in the array.</param>
	/// <param name="stride: ">The byte offset between consecutive generic vertex attributes.</param>
	/// <param name="offset: ">The offset of the first component of the first generic vertex attribute in the array 
	/// in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target.</param>
	/// <param name="divisor: "></param>
	template<typename T>
	void setAttPointer(GLuint index, GLint size, GLenum type, GLuint stride, GLuint offset, GLuint divisor = 0)
	{
		glVertexAttribPointer(index, size, type, GL_FALSE, stride * sizeof(T), (void*)(offset * sizeof(T)));
		glEnableVertexAttribArray(index);

		if (divisor > 0)
		{
			// Reset '_idx_' attribute every '_divisor_' iteration (Instancing)
			glVertexAttribDivisor(index, divisor);
		}
	}
};



/*
	Array Objects (VAO)
*/

class ArrayObject
{
public:

    // Array ID
	GLuint aID;

	// Map of names to buffers.
	std::map<const char*, BufferObject> buffers;


	// Get buffer (override [])
	BufferObject& operator[](const char* key) 
	{
		return buffers[key];
	}

	/// <summary>
	/// Generate a Vertex Array Object and assign it to the ID.
	/// </summary>
	void generate()
	{
		glGenVertexArrays(1, &aID);
	}

	/// <summary>
	/// Bind the Vertex Array Object.
	/// </summary>
	void bind()
	{
		glBindVertexArray(aID);
	}

	/// <summary>
	/// Unbind the Vertex Array Object.
	/// </summary>
	static void clear() 
	{
		glBindVertexArray(0);
	}

	/// <summary>
	/// Delete the vertex array and it's connected buffer objects.
	/// </summary>
	void cleanup()
	{
		glDeleteVertexArrays(1, &aID);

		for (auto& pair : buffers)
		{
			pair.second.cleanup();
		}
	}

	/// <summary>
	/// Render primitives from array data with glDrawArrays.
	/// </summary>
	/// <param name="mode: ">What kind of primitives to render.</param>
	/// <param name="first: ">The starting index in the enabled arrays.</param>
	/// <param name="count: ">The number of indices to be rendered.</param>
	void draw(GLenum mode, GLuint first, GLuint count)
	{
		glDrawArrays(mode, first, count);
	}

	/// <summary>
	/// Render primitives from array data with glDrawElements.
	/// </summary>
	/// <param name="mode: ">What kind of primitives to render.</param>
	/// <param name="count: ">The number of elements to be rendered.</param>
	/// <param name="type: ">The type of the values in indices. 
	/// Must be GL_UNSIGNED_BYTE or GL_UNSIGNED_SHORT.</param>
	/// <param name="indices: ">The pointer to the location where the indices are stored.</param>
	void drawElements(GLenum mode, GLuint count, GLenum type, GLint indices)
	{
		glDrawElements(mode, count, type, (void*)indices);
		std::cout << glGetError() << std::endl;
	}


	/// <summary>
	/// Draw multiple instances of a set of elements with glDrawElementsInstanced.
	/// </summary>
	/// <param name="mode: ">What kind of primitives to render.</param>
	/// <param name="count: ">The number of elements to be rendered.</param>
	/// <param name="type: ">The type of the values in indices. 
	/// Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.</param>
	/// <param name="indices: ">The pointer to the location where the indices are stored.</param>
	/// <param name="numInstances: ">The number of instances of the specified range of indices to be rendered.</param>
	void drawElementsInst(GLenum mode, GLuint count, GLenum type, GLint indices, GLuint numInstances = 1)
	{
		glDrawElementsInstanced(mode, count, type, (void*)indices, numInstances);
	}
};



/*
	Byte Size: 4
	Offset(- - ): 3, 6 * Byte Size (4) = 12, 24
	Stride(----): Size of Vertex in bytes (num of elements (8) * byte size (4) = 32)
 
	    | Vertex 1              | Vertex 2              | Vertex 3              |
	    |X |Y |Z |R |B |G |S |T |X |Y |Z |R |B |G |S |T |X |Y |Z |R |B |G |S |T |
	BYT 0 04 08 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76 80 84 88 92 96
	    |        |        |     |        |        |     |        |        |     |
	    |        |        |     |        |        |     |        |        |     |
	POS |-----------------------|-----------------------|-----------------------|
	    |        |              |              |        |        |        |
	CLR |-  -  - |-----------------------|-----------------------|-------------->
	    |        |                       |                       |
	UVS |- - - - - - - - -|-----------------------|-----------------------|----->


    glBufferData

    Buffer Binding Target 			Purpose
    GL_ARRAY_BUFFER 				Vertex attributes
    GL_ATOMIC_COUNTER_BUFFER 		Atomic counter storage
    GL_COPY_READ_BUFFER 			Buffer copy source
    GL_COPY_WRITE_BUFFER 			Buffer copy destination
    GL_DISPATCH_INDIRECT_BUFFER		Indirect compute dispatch commands
    GL_DRAW_INDIRECT_BUFFER 		Indirect command arguments
    GL_ELEMENT_ARRAY_BUFFER 		Vertex array indices
    GL_PIXEL_PACK_BUFFER 			Pixel read target
    GL_PIXEL_UNPACK_BUFFER 			Texture data source
    GL_QUERY_BUFFER 				Query result buffer
    GL_SHADER_STORAGE_BUFFER 		Read-write storage for shaders
    GL_TEXTURE_BUFFER 				Texture data buffer
    GL_TRANSFORM_FEEDBACK_BUFFER 	Transform feedback buffer
    GL_UNIFORM_BUFFER 				Uniform block storage
*/