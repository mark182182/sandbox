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
    # tf.keras.utils.pad_sequences
    path_to_file = tf.keras.utils.get_file(
        "shakespeare.txt",
        "https://storage.googleapis.com/download.tensorflow.org/data/shakespeare.txt",
    )

    # Read, then decode for py2 compat.
    text = open(path_to_file, "rb").read().decode(encoding="utf-8")
    # length of text is the number of characters in it
    print("Length of text: {} characters".format(len(text)))

    # Take a look at the first 250 characters in text
    print(text[:250])

    # encoding
    vocab = sorted(set(text))
    # Creating a mapping from unique characters to indices
    char2idx = {u: i for i, u in enumerate(vocab)}
    idx2char = np.array(vocab)

    def text_to_int(text):
        return np.array([char2idx[c] for c in text])

    text_as_int = text_to_int(text)

    # lets look at how part of our text is encoded
    print("Text:", text[:13])
    print("Encoded:", text_to_int(text[:13]))

    def int_to_text(ints):
        try:
            ints = ints.numpy()
        except:
            pass
        return "".join(idx2char[ints])

    print(int_to_text(text_as_int[:13]))

    # creating training examples
    seq_length = 100  # length of sequence for a training example
    examples_per_epoch = len(text) // (seq_length + 1)

    # Create training examples / targets
    char_dataset = tf.data.Dataset.from_tensor_slices(text_as_int)

    sequences = char_dataset.batch(seq_length + 1, drop_remainder=True)

    def split_input_target(chunk):  # for the example: hello
        input_text = chunk[:-1]  # hell
        target_text = chunk[1:]  # ello
        return input_text, target_text  # hell, ello

    dataset = sequences.map(
        split_input_target
    )  # we use map to apply the above function to every entry

    for x, y in dataset.take(2):
        print("\n\nEXAMPLE\n")
        print("INPUT")
        print(int_to_text(x))
        print("\nOUTPUT")
        print(int_to_text(y))

    # create the training batches
    BATCH_SIZE = 64
    VOCAB_SIZE = len(vocab)  # vocab is number of unique characters
    EMBEDDING_DIM = 256
    RNN_UNITS = 1024

    # Buffer size to shuffle the dataset
    # (TF data is designed to work with possibly infinite sequences,
    # so it doesn't attempt to shuffle the entire sequence in memory. Instead,
    # it maintains a buffer in which it shuffles elements).
    BUFFER_SIZE = 10000

    data = dataset.shuffle(BUFFER_SIZE).batch(BATCH_SIZE, drop_remainder=True)

    # building the model
    def build_model(vocab_size, embedding_dim, rnn_units, batch_size):
        model = tf.keras.Sequential(
            [
                tf.keras.layers.Embedding(
                    vocab_size, embedding_dim, batch_input_shape=[batch_size, None]
                ),
                tf.keras.layers.LSTM(
                    rnn_units,
                    return_sequences=True,
                    stateful=True,
                    recurrent_initializer="glorot_uniform",
                ),
                tf.keras.layers.Dense(vocab_size),
            ]
        )
        return model

    model = build_model(VOCAB_SIZE, EMBEDDING_DIM, RNN_UNITS, BATCH_SIZE)
    model.summary()

    # creating the loss function
    for input_example_batch, target_example_batch in data.take(1):
        example_batch_predictions = model(
            input_example_batch
        )  # ask our model for a prediction on our first batch of training data (64 entries)
        print(
            example_batch_predictions.shape,
            "# (batch_size, sequence_length, vocab_size)",
        )  # print out the output shape

    # we can see that the predicition is an array of 64 arrays, one for each entry in the batch
    print(len(example_batch_predictions))
    print(example_batch_predictions)

    # lets examine one prediction
    pred = example_batch_predictions[0]
    print(len(pred))
    print(pred)
    # notice this is a 2d array of length 100, where each interior array is the prediction for the next character at each time step

    # and finally well look at a prediction at the first timestep
    time_pred = pred[0]
    print(len(time_pred))
    print(time_pred)
    # and of course its 65 values representing the probabillity of each character occuring next

    # If we want to determine the predicted character we need to sample the output distribution (pick a value based on probabillity)
    sampled_indices = tf.random.categorical(pred, num_samples=1)

    # now we can reshape that array and convert all the integers to numbers to see the actual characters
    sampled_indices = np.reshape(sampled_indices, (1, -1))[0]
    predicted_chars = int_to_text(sampled_indices)

    predicted_chars  # and this is what the model predicted for training sequence 1

    def loss(labels, logits):
        return tf.keras.losses.sparse_categorical_crossentropy(
            labels, logits, from_logits=True
        )

    # compiling the model
    model.compile(optimizer="adam", loss=loss)


if __name__ == "__main__":
    main()
