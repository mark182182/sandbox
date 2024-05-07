## Core Learning Algorithms: The Training Process

### Notes:

- Previously, we have broken down what categorical and numerical columns represent
- The training process:
  - Fairly simple for a linear model, as we only need to feed information to it (only 627 rows)
  - What if we are training a large machine learning model (like 27 TB)? We have to load it in batches.
  - We can load it in a small batch size of 32 (just a specific set of elements)
  - <b>Epochs</b>: <em>how many times</em> the model is going to see the data
    - As we do this multiple times, it will see the pick up on patterns
    - <b>Overfitting</b>: We can pass too much data to the process, and it will be bad at classifying new data
    - Because of overfitting, we are going to do this in <b>increments</b> starting from lower to higher to see how the training process will work with the data
  - <b>Input function</b>: The way that we define how our data is going to be broken up into epochs and into baches
    - This usually doesn't have to be coded by ourselves (see the examples on the TensorFlow website and in [main.py](main.py))
    - Example: It takes our pandas dataframe and will encode our data into a `tf.data.Dataset` object
- Creating the model:
  - <b>Estimator</b>: a basic algorihm implementation in TensorFlow
- <b>Loss function</b>: a method of evaluating how well the algorithm models the dataset.
  - If the predictions are totally off, the loss function will output a higher number. If they're pretty good, it'll output a lower number.

### Questions:

What are epochs?

- The number of times the model will see the same data.
