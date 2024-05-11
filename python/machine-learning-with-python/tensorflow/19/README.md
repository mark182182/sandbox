## Convolutional Neural Networks: Evaluating the Model

### Notes:

- Evaluating the Convnet (see [main.py](main.py))
- Working with small datasets
- <b>Data augmentation</b>: to avoid overfitting the data and create a <em>larger</em> dataset from a <em>smaller</em> one, by performing random transformations (compression, rotation, streches, color changes) on our images, so our model can generalize better
  - Esentially we are creating many images one image from one image to extract the features better
- Convolutional NNs are good for creating models for small datasets with data augmentation
- What if we still don't have enough images?
  - We can use only a <em>part of</em> a <b>pretrained model</b> (1.8 million images in our case) as a base of the model and <b>fine tune</b> the last few layers of our network, so it works better

### Questions:

What is <b>not</b> a good way to increase the accuracy of a convolutional neural network?

- Using your test data to retrain the model.
