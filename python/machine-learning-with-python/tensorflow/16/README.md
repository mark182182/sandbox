## Convolutional Neural Networks

### Notes:

- <b>Deep Computer Vision</b>: it is used for a lot of things, like image classification, object detection/recognition
  - The goal of our <em>convolutional neural networks</em> will be to classify and detect images or specific objects from within the image
- The following concepts as needed:
  - Image Data
  - Convolutional Layer
  - Pooling Layer
  - CNN Architectures
- <b>Image Data</b>: image data is usually made up of 3 dimensions: height, widght and color channels
- <b>Convolutional Neural Network</b>:
  - Each convnet is made up of one or many convolutional layers.
  - These layers are different than the dense layers we have seen previously. Their goal is to find patterns from within images that can be used to classify the image or parts of it. It's familiar to a densely connected NN.
  - The fundemental differente between dense and a convolutional layer is that dense detects patterns globally, while conv. layer detects patterns locally (part of the image)
  - Example: it learns how the cat ear looks like and can recognize it
- <b>Multiple Convolutional Layers</b>
- Output feature map needs to be created by filtering the image

### Questions:

Dense neural networks analyze input on a global scale and recognize patterns in specific areas. Convolutional neural networks...:

- scan through the entire input a little at a time and learn local patterns.
