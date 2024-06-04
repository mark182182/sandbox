import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"

import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
import tensorflow as tf
import keras


def main():
    # MNIST Fashion Dataset willbe used
    fashion_mnist = keras.datasets.fashion_mnist

    (train_images, train_labels), (test_images, test_labels) = (
        fashion_mnist.load_data()
    )  # split into testing and training

    print(train_images.shape)  # 60.000 images that are made up of 28x28 pixels

    print(
        train_images[0, 23, 23]
    )  # look at one pixel (values between 0-255, so these are grayscale images)

    print(train_labels[:10])  # first 10 training labels

    class_names = [
        "T-shirt/top",
        "Trouser",
        "Pullover",
        "Dress",
        "Coat",
        "Sandal",
        "Shirt",
        "Sneaker",
        "Bag",
        "Ankle boot",
    ]

    plt.figure()  # look at some images
    plt.imshow(train_images[1])
    plt.colorbar()
    plt.grid(False)
    plt.show() # show the image instead of saving
    # plt.savefig("image.png")

    # preprocessing the data, which means prior transformations to our data before feeding it the model
    train_images = train_images = 255.0
    
    # we need to preprocess the test images in the same way as well
    test_images = test_images = 255.0

if __name__ == "__main__":
    main()
