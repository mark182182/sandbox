## Neural Networks with TensorFlow

### Notes:

- The point of a neural network is to provide classification or predictions for us
- Input layer of the NN:
  - Example: (simple) for an image, we need all the pixels, so for a 28x28 image we need all pixels
- Hidden layers of the NN:
  - Every single layer is connected to another layer via <b>weights</b>
  - Every single connected layer is connected to every single node (dense layer)
  - The trainable parameters are the connections (where the connections have weights like the edges of graphs in a weighted graph)
- <b>Bias</b>: there is only one bias and a bias exists in the previous layer to the layer that it effects (e.g. one to the hidden layer or one to the output layer)
- Output layer of the NN:
  - Examples:
    - (simple) we have one output neuron that can be 0 or 1 (if it's 0 => red, if it's 1 => blue)
    - Have as many neurons as classes that we're looking for. We can calculate the probability distribution for the classes
  - We take the weighted sum of the weights plus the weight, so we can see the output of the NN

### Questions:

A densely connected neural network is one in which...:

- all the neurons in the current layer are connected to every neuron in the previous layer.
