## Creating a Convolutional Neural Network

### Notes:

- Using the CIFAR dataset: 60.000 32x32 color images with 6000 images of each class
- Labels: Airplane, Automobile, Bird, Cat, etc.
- Creating the Convnet (see [main.py](main.py))
- Create the model

### Questions:

Fill in the blanks below to complete the architecture for a convolutional neural network:

```python
model = models.__A__()
model.add(layers.__B__(32, (3, 3), activation='relu', input_shape=(32, 32, 3)))
model.add(layers.__C__(2, 2))
model.add(layers.__B__(64, (3, 3), activation='relu'))
model.add(layers.__C__(2, 2))
model.add(layers.__B__(32, (3, 3), activation='relu'))
model.add(layers.__C__(2, 2))
```

- A: Sequential
  B: Conv2D
  C: MaxPooling2D
