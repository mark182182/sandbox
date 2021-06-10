### Notes on the language specification and other stuff

Dangling pointers:

- Cause: pointing to a memory location which has been deleted/freed
- Solution: Initialize pointer to NULL

Vertex input:

- Floating point coordinate data in 3D space. Can be absolute or normalized values (from -1.0 to 1.0).

VBO (vertex buffer object):

- Used to load the verticies into the GPU memory

VAO (vertex array object):

- Used store vertex attribute calls and bind VBOs

EAO (element buffer object):

- Used to specify what verticies should be drawn

Graphics pipeline:

- Vertex data -> vertex shader -> shape assembly -> geometry shader -> rasterization -> fragment shader -> testing and blending, final color

Vertex shader:

- Used to specify how the coordinates are connected together to form a shape

Fragment shader:

- Used to specify how the different shapes are colored. Blends colors, produces the final color of the pixel.
