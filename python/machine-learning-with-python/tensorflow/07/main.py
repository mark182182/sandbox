import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"

import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
import tensorflow as tf
import keras


def main():
    # Reference: https://www.tensorflow.org/tutorials/estimator/premade
    CSV_COLUMN_NAMES = [
        "SepalLength",
        "SepalWidth",
        "PetalLength",
        "PetalWidth",
        "Species",
    ]
    SPECIES = ["Setosa", "Versicolor", "Virginica"]

    train_path = tf.keras.utils.get_file(
        "iris_training.csv",
        "https://storage.googleapis.com/download.tensorflow.org/data/iris_training.csv",
    )
    test_path = tf.keras.utils.get_file(
        "iris_test.csv",
        "https://storage.googleapis.com/download.tensorflow.org/data/iris_test.csv",
    )

    train = pd.read_csv(train_path, names=CSV_COLUMN_NAMES, header=0)
    test = pd.read_csv(test_path, names=CSV_COLUMN_NAMES, header=0)

    print(train.head())  # look at the data

    train_y = train.pop("Species")
    test_y = test.pop("Species")
    train.head()  # the species column is gone

    print(train.shape)
    print(train_y.head())

    def input_fn(features, labels, training=True, batch_size=256):
        # Convert the inputs to a Dtaset
        dataset = tf.data.Dataset.from_tensor_slices((dict(features), labels))

        # Shuffle and repeat, if you are in training mode
        if training:
            dataset = dataset.shuffle(1000).repeat()

        return dataset.batch(batch_size)

    feature_columns = []
    for key in train.keys():
        feature_columns.append(tf.feature_column.numeric_column(key=key))


if __name__ == "__main__":
    main()
