import tensorflow as tf

# creating Tensors (with rank 0, as these are scalar values)
string = tf.Variable("this is a string", tf.string)
number = tf.Variable(324, tf.int16)
floating = tf.Variable(3.567, tf.float64)

# creating rank 1 Tensors (1 dimension)
rank1_tensor = tf.Variable(["Test", "Ok"], tf.string)

# creating rank 2 Tensors (2 dimension)
rank2_tensor = tf.Variable([["Test", "Ok"], ["test", "yes"]], tf.string)

# determine the rank of a tensor (see numpy for the rank)
tf.rank(rank2_tensor) # <tf.Tensor: shape=(), dtype=int32, numpy=2>

# check the tensor's shape
rank2_tensor.shape #TensorShape([2, 2])

# change the shape of a tensor
tensor0 = tf.zeros([5,5,5,5]) # creates a shape [5,5,5,5] tensor full of zeros
tensor1 = tf.ones([1,2,3]) # tf.ones() creates a shape [1,2,3] tensor full of ones
tensor2 = tf.reshape() # reshape existing data to shape [2,3,1]
tensor3 = tf.reshape(tensor2, [3, -1]) # -1 tells the tensor to calculate the shape of the dimension in that place, this will reshape the tensor to [3,2]

# The number of elements in the reshaped tensor MUST match the number in the original

# Evaluating a Tensor
with tf.Session() as sess: # creates as session using the default graph
  tensor2.eval()