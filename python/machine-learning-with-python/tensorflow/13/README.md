## Neural Networks: Activation Functions

### Notes:

- <b>Activation function</b>: as we can't garantee the output number to be 0 or 1 (can be 700 or anything different), so we have to take any number that we get and make it 0 or 1 with a function.
  - Types of activation functions:
    - Relu (Rectified Linear Unit)
    - Tanh (Hyperbolic Tangent)
    - Sigmoid (this can be used to have an output value of 0 or 1)
  - How we use it is: we take the weighted sum plus the bias (at the output layer), and then we apply an activation function to it <b>before</b> we send that value to the next neuron
  - We can use it on other layers as well, e.g. at the hidden layer
    - E.g.: we can move the points up or down in whatever direction in n dimensional space (2D->3D), so we can move it in directions we couldn't before
- <b>Loss function</b>: a method of evaluating how well the algorithm models the dataset.
  - A loss function measures the discrepancy between the predicted outputs and the actual target values in a neural network, guiding the training process by optimizing the model parameters.
  - If the predictions are totally off, the loss function will output a higher number. If they're pretty good, it'll output a lower number.
  - If it's high, we have to change the weights
  - Common loss/cost functions include:
    - Mean Squared Error (MSE): Measures the average of the squares of the errors—that is, the average squared difference between the estimated values and the actual value.
    - Mean Absolute Error (MAE): Measures the average magnitude of the errors in a set of predictions, without considering their direction.
    - Hinge Loss: Used primarily for binary classification tasks, it measures the error of predictions where the goal is to ensure that the correct class is not only predicted correctly, but also with a margin of confidence from the decision boundary.
- <b>Gradient descent</b>: it's an optimization algorithm used to minimize (low as possible) the loss function in neural networks by iteratively adjusting the model's parameters.
  - In this case, we are looking for a global minimum.
  - Gradient descent will tell us how to 
  get to this global minimum (where the loss function is low as possible)
- <b>Backpropagation</b>: a method used in neural networks to optimize the weights through <em>gradient descent</em> by calculating and propagating errors backward from the output to the input layer.



### Questions:

Which activation function squishes values between -1 and 1?

- Tanh (Hyperbolic Tangent)
