import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"
os.environ["KMP_DUPLICATE_LIB_OK"] = "True"

import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
import tensorflow as tf
import keras
from keras import datasets, layers, models
from numpy import asarray
from keras.preprocessing.image import ImageDataGenerator
import tensorflow_datasets as tfds


def main():

    # load and split
    (train_images, train_labels), (test_images, test_labels) = (
        datasets.cifar10.load_data()
    )

    # normalize pixel values to be between 0 and 1
    train_images, test_images = train_images / 255.0, test_images / 255.0

    class_names = [
        "airplane",
        "automobile",
        "bird",
        "cat",
        "deer",
        "dog",
        "frog",
        "horse",
        "ship",
        "truck",
    ]

    IMG_INDEX = 1
    plt.imshow(train_images[IMG_INDEX], cmap=plt.cm.binary)
    plt.xlabel(class_names[train_labels[IMG_INDEX][0]])
    # plt.show()

    # CNN architecture
    model = models.Sequential()
    # 32 filters of size 3x3 over our input data
    model.add(layers.Conv2D(32, (3, 3), activation="relu", input_shape=(32, 32, 3)))
    # Max pooling operation using 2x2 samples and a stride of 2
    model.add(layers.MaxPooling2D((2, 2)))
    model.add(layers.Conv2D(64, (3, 3), activation="relu"))
    model.add(layers.MaxPooling2D((2, 2)))
    model.add(layers.Conv2D(64, (3, 3), activation="relu"))

    model.summary()
    # This completes the convolutional base

    # Adding Dense Layers, as we need the previously extracted features and add a way to classify them.
    model.add(layers.Flatten())
    model.add(layers.Dense(64, activation="relu"))
    model.add(layers.Dense(10))

    # The shape of our data is changed, we can see that the flatten layer changes the shape of our data, so that we can feed it to the 64 node dense layer, followed by the final output layer of 10 neurons (one for each class).
    model.summary()

    # Compile to model and use the recommended hyper parameters from TensorFlow
    model.compile(
        optimizer="adam",
        loss=keras.losses.SparseCategoricalCrossentropy(from_logits=True),
        metrics=["accuracy"],
    )

    history = model.fit(
        train_images,
        train_labels,
        epochs=1,
        validation_data=(test_images, test_labels),
    )

    test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=2)
    print(test_acc)

    # created a data generator object that transforms images
    datagen = ImageDataGenerator(
        rotation_range=40,
        width_shift_range=0.2,
        height_shift_range=0.2,
        shear_range=0.2,
        zoom_range=0.2,
        horizontal_flip=True,
        fill_mode="nearest",
    )

    # pick an image to transfor
    test_img = train_images[20]
    img = asarray(test_img)  # convert image to numpy arry
    img = img.reshape((1,) + img.shape)  # reshape image

    # The dataset has been updated and we have to use the new URL, but we can't specify that as an argument in the tfds.load function
    setattr(
        tfds.image_classification.cats_vs_dogs,
        "_URL",
        "https://download.microsoft.com/download/3/E/1/3E1C3F21-ECDB-4869-8368-6DEBA77B919F/kagglecatsanddogs_5340.zip",
    )

    # split the data manually into 80% training, 10% testing, 10% validation
    (raw_train, raw_validation, raw_test), metadata = tfds.load(
        "cats_vs_dogs",
        split=["train[:80%]", "train[80%:90%]", "train[90%:]"],
        with_info=True,
        as_supervised=True,
    )

    IMG_SIZE = 160  # All images will be resized to 160x160

    def format_example(image, label):
        """
        returns an image that is reshaped to IMG_SIZE
        """
        image = tf.cast(image, tf.float32)
        # 127.5 is half of 255, that's why we are using this value
        image = (image / 127.5) - 1
        image = tf.image.resize(image, (IMG_SIZE, IMG_SIZE))
        return image, label

    IMG_SHAPE = (IMG_SIZE, IMG_SIZE, 3)
    # create the base model from the pre-trained model MobileNet V2
    base_model = keras.applications.MobileNetV2(
        input_shape=IMG_SHAPE,
        # as we training the dataset for only cats and dogs, we don't need the 1000+ other classes
        include_top=False,
        weights="imagenet",
    )

    base_model.summary()
    # At this point, this base_model will output a shape (32,5,5,1280) tensor that is a feature extraction of our original (1,160,160,3) image.
    # This 32 means that we have 32 layers of different filters/features.

    # Adding our classifier
    global_average_layer = keras.layers.GlobalAveragePooling2D()

    # Add the prediction layer that will be a single dense neuron. We can do this, because we only have two classes to predict for.

    prediction_layer = keras.layers.Dense(1)

    # Combine the layers together in a model

    model = keras.Sequential([base_model, global_average_layer, prediction_layer])

    model.summary()

    # Training the model using a very small learning rate, to ensure that the model does not have any major changes

    base_learning_rate = 0.0001
    model.compile(
        optimizer=keras.optimizers.RMSprop(learning_rate=base_learning_rate),
        loss=keras.losses.BinaryCrossentropy(from_logits=True),
        metrics=["accuracy"],
    )

    # We can evaluate the model to see how it does before training it on our new images
    initial_epochs = 3
    validation_steps = 20

    # loss0, accurac0 = model.evaluate(validation_batches, steps = validation_steps)

    # Train it on our images
    history = model.fit(
        train_batches, epochs=initial_epochs, validation_data=validation_batches
    )

    acc = history.history["accuracy"]
    print(acc)

    # Saving the model
    model.save("dogs_vs_cats.h5")
    new_model = keras.models.load_model("dogs_vs_cats.h5")  # h5 is a keras type


if __name__ == "__main__":
    main()
