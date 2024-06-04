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
        # Ensure features and labels are of type float32
        features = {key: tf.cast(value, tf.float32) for key, value in features.items()}
        labels = tf.cast(labels, tf.int32)  # Assuming labels are to be integers

        # Convert the inputs to a Dtaset
        dataset = tf.data.Dataset.from_tensor_slices((dict(features), labels))

        # Shuffle and repeat, if you are in training mode
        if training:
            dataset = dataset.shuffle(1000).repeat()

        return dataset.batch(batch_size)

    feature_columns = []
    for key in train.keys():
        feature_columns.append(tf.feature_column.numeric_column(key=key))

    # Build a DNN with 2 hidden layers with 30 and 10 hidden nodes each.
    classifier = tf.estimator.DNNClassifier(
        feature_columns=feature_columns,
        # Two hidden layers of 30 and 10 nodes respectively (arbitrary decided).
        hidden_units=[30, 10],
        # The model must choose between 3 classes
        n_classes=3,
    )

    classifier.train(
        input_fn=lambda: input_fn(train, train_y),
        steps=5000,
    )

    eval_result = classifier.evaluate(
        input_fn=lambda: input_fn(test, test_y, training=False)
    )

    print(eval_result)

    # These should be the expected results
    expected = ["Setosa", "Versicolor", "Virginica"]
    
    # We are predicting the species based on these values
    predict_x = {
        "SepalLength": [5.1, 5.9, 6.9],
        "SepalWidth": [3.3, 3.0, 3.1],
        "PetalLength": [1.7, 4.2, 5.4],
        "PetalWidth": [0.5, 1.5, 2.1],
    }

    def input_fn(features, batch_size=256):
        # Converts the inputs to a Dataset without labels
        return tf.data.Dataset.from_tensor_slices(dict(features)).batch(batch_size)

    predictions = classifier.predict(input_fn=lambda: input_fn(predict_x))
    for pred_dict in predictions:
        print(pred_dict)
        class_id = pred_dict["class_ids"][0]
        probability = pred_dict["probabilities"][class_id]

        print(
            'Prediction is "{}" ({:.1f}%)'.format(SPECIES[class_id], 100 * probability)
        )


if __name__ == "__main__":
    main()
