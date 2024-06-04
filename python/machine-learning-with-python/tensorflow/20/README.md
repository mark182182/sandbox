## Convolutional Neural Networks: Picking a Pretrained Model

### Notes:

- Using MobileNet V2 (by Google), which was trained on 1.4 million images and has 1000 different classes
- We want to use this model as its convolutional base, so we <b>don't</b> want to load the <em>top (classification) layer</em>
- <b>Freezing</b> the base: refers to <b>disabling</b> the training property of a layer
  - It simple means we won't make any changes to the weights of any layers that are frozen during training
  - This is importart, as we don't want to change the convolutional base that already has learned weights
- Adding our classifier: using a global average pooling layer that will average the entier 5x5 area of each 2D feature map and return to us a single 1280 element vector per filter.
- Adding the prediction layer
- Combining the layers together

### Questions:

Fill in the blanks below to use Google's pre-trained MobileNet V2 model as a base for a convolutional neural network:

```python
base_model = tf.__A__.applications.__B__(input_shape=(160, 160, 3),
                                               include_top=__C__,
                                               weights='imagenet'
                                               )

```

- A: keras B: MobileNetV2 C: False
