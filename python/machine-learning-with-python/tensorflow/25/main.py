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

    # Making predictions

    word_index = imdb.get_word_index()

    def encode_text(text):
        tokens = keras.preprocessing.text.text_to_word_sequence(text)
        tokens = [word_index[word] if word in word_index else 0 for word in tokens]
        return tf.keras.utils.pad_sequences([tokens], MAXLEN)[0]

    text = "that movie was just amazing, so amazing"
    encoded = encode_text(text)
    print(encoded)

    # while were at it lets make a decode function

    reverse_word_index = {value: key for (key, value) in word_index.items()}

    def decode_integers(integers):
        PAD = 0
        text = ""
        for num in integers:
            if num != PAD:
                text += reverse_word_index[num] + " "

        return text[:-1]

    print(decode_integers(encoded))

    # now time to make a prediction
    def predict(text):
        encoded_text = encode_text(text)
        pred = np.zeros((1, 250))
        pred[0] = encoded_text
        result = model.predict(pred)
        print(result[0])

    positive_review = "That movie was! really loved it and would great watch it again because it was amazingly great"
    predict(positive_review)

    negative_review = "that movie really sucked. I hated it and wouldn't watch it again. Was one of the worst things I've ever watched"
    predict(negative_review)


if __name__ == "__main__":
    main()
