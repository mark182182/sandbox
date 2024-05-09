## Neural Networks: Creating a Model

### Notes:

- Getting the data into the right places is hard, creating the model is generally easy, once we have the data figured it out
- <b>Hyperparameters tuning</b>: is a process of changing the values and looking how models perform with different parameters
- We want to make sure to generalize the model as much as possible to be accurate on new data
- If you have more epochs, it can lead to overfitting the data, because it will see the same data so many times, that is worse for predicting new data
  - In this case, lowering the number of epochs can help
- Create the model (see [main.py](main.py))

### Questions:

Fill in the blanks below to build a sequential model of dense layers:

```python
model = __A__.__B__([
    __A__.layers.Flatten(input_shape=(28, 28)),
    __A__.layers.__C__(128, activation='relu'),
    __A__.layers.__C__(10, activation='softmax')
])
```

- A: keras
  B: Sequential
  C: Dense
