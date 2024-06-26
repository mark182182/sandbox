import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"
os.environ["KMP_DUPLICATE_LIB_OK"] = "True"

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

    # plt.figure()  # look at some images
    # plt.imshow(train_images[1])
    # plt.colorbar()
    # plt.grid(False)
    # plt.show() # show the image instead of saving
    # plt.savefig("image.png")

    # preprocessing the data, which means prior transformations to our data before feeding it the model
    train_images = train_images / 255.0

    # we need to preprocess the test images in the same way as well
    test_images = test_images / 255.0

    # Sequential is the most basic form, where information is passed from one side to the other
    model = keras.Sequential(
        [
            # Flatten takes the 28x28 pixels and makes them into 784 pixels
            keras.layers.Flatten(input_shape=(28, 28)),  # input layer (1)
            # Dense means all neurons are connected from the previous
            keras.layers.Dense(128, activation="relu"),  # hidden layer (2)
            # Output layer has 10 output layer (because we have 10 class_names)
            # softmax will take care of probability distribution (making the output between 0 and 1)
            keras.layers.Dense(10, activation="softmax"),  # output layer (3)
        ]
    )

    model.compile(
        # adam will take care of gradient descent
        optimizer="adam",
        loss="sparse_categorical_crossentropy",
        metrics=["accuracy"],
    )

    # check epochs 1 or 8 or 10
    model.fit(train_images, train_labels, epochs=1)

    test_loss, test_acc = model.evaluate(test_images, test_labels, verbose=1)
    print('Test accuracy:', test_acc)
    
    script_directory = os.path.dirname(os.path.abspath(__file__))
    
    # The example image (CC0 rights) contains inverted colors, as the images that were used to trian model contains black backgrounds 
    imgToPredict=load_image_into_numpy_array(f"{script_directory}/shirt28x28.png")
    # Shape should be (28,28) as we have 28x28 size and no color channels
    print(imgToPredict.shape)
    
    print(imgToPredict)
    # We have to flatten our image to fit the model
    flattenedImgToPredict = imgToPredict.reshape(-1, 28, 28)
    print(flattenedImgToPredict)
    
    # We need values between 0 and 1
    transformedImgToPredict=flattenedImgToPredict / 255.0
    predictions = model.predict(transformedImgToPredict)
    # The probability distribution of the output layer of the first image
    print(predictions[0])
    
    # check the class for the prediction, it should be a shirt
    print("Prediction: " + class_names[np.argmax(predictions[0])])
    plt.figure()
    plt.imshow(imgToPredict)
    plt.colorbar()
    plt.grid(False)
    plt.show()
    
def load_image_into_numpy_array(imgPath: str):
    import PIL
    from PIL import Image, ImageOps
    from numpy import asarray
    print('Pillow Version:', PIL.__version__)
    
    # This loads our (28,28,4) image, 28x28 size and 4 color channels
    image = Image.open(imgPath)
    # summarize some details about the image
    # print(image.format)
    # print(image.size)
    # print(image.mode)
    
    # We need a grayscale image, because our model was trained on them, and our example has 4 color channels
    image = ImageOps.grayscale(image)
    return asarray(image)

if __name__ == "__main__":
    main()
