## Introduction to TensorFlow
### Notes:
- Tensor:
  - <b>Definition</b>: It is a generalization of <em>vectors</em> and <em>matrices</em> to potentially higher dimensions.
  - It is kind of a datapoint
  - A vector can have any <b>number of dimentions</b> in it (like in 2 dimensions it can have x and y, etc.)
  - Tensors are the main object in TensorFlow and it is the main object that is passed around in our program
  - Each tensor represents a partialy defined computation that will eventually produce a value
- TensorFlow:
  - TensorFlow represents tensors as <b>n dimentional arrays</b>
  - TensorFlow programs work by building a <em>graph</em> of Tensor objects that details how tensors are related.
  - Running different parts of our graph allow results to be generated
  - Each tensor has a <em>data type</em> and a <em>shape</em>
  - Data Types include: float32, int32, string and others
  Shape: represents the dimensions of data
  - Creating Tensors (see [main.py](main.py))
  - Rank/Degree of Tensors:
    - Rank means degree, it simply means the <b>number of dimensions involved</b> in the tensor
    - Rank 0 means it's a scalar value
    - You can determine the number of rank by looking at the deepest nested list (call tf.rank)
  - Shape:
    - It means <em>how many items</em> we have in each <em>dimension</em>
    - Call tensor.shape to check its shape
  - Changing shape:
    - We will do this a lot of times (see [main.py](main.py))
  - Types of Tensors:
    - The most commonly used types are:
      - Variable
      - Constant
      - Placeholder
      - SparseTensor
    - With the exception of <em>Variable</em> all these types are immutable
  - Evaluating Tensors:
    - We need to create a session to evaluate a Tensor (see [main.py](main.py))



### Questions:
Which of the following is <b>not</b> a type of tensor?
- Flowing