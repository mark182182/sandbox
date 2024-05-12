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
from keras.datasets import imdb
from keras.preprocessing import sequence


def main():

    VOCAB_SIZE = 88584

    MAXLEN = 250
    BATCH_SIZE = 64

    (train_data, train_labels), (test_data, test_labels) = imdb.load_data(
        num_words=VOCAB_SIZE
    )

    # one review
    print(train_data[1])

    # preprocessing the data (review > 250 trim the extra words, if < 250 add 0's to make it equal to 250)
    train_data = tf.keras.utils.pad_sequences(train_data, MAXLEN)
    test_data = tf.keras.utils.pad_sequences(test_data, MAXLEN)

    # Creating the model
    model = tf.keras.Sequential(
        [
            tf.keras.layers.Embedding(VOCAB_SIZE, 32),
            tf.keras.layers.LSTM(32),
            tf.keras.layers.Dense(1, activation="sigmoid"),
        ]
    )

    model.summary()

    # Training the model
    model.compile(loss="binary_crossentropy", optimizer="rmsprop", metrics=["acc"])

    history = model.fit(train_data, train_labels, epochs=1, validation_split=0.2)

    results = model.evaluate(test_data, test_labels)
    print(results)
    
if __name__ == "__main__":
    main()
