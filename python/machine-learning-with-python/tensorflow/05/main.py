import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
from six.moves import urllib
import tensorflow as tf


def main():
    dftrain = pd.read_csv(
        "https://storage.googleapis.com/tf-datasets/titanic/train.csv"
    )
    dfeval = pd.read_csv("https://storage.googleapis.com/tf-datasets/titanic/eval.csv")
    y_train = dftrain.pop(
        "survived"
    )  # we are dropping the survived column from dftrain
    y_eval = dfeval.pop("survived")

    print(dftrain["age"])  # show the values for the age column
    print(dftrain.loc[0])  # the row values for the first column
    print(
        dftrain.describe()
    )  # gives an overall information on the data (mean, std, min etc.)
    print(dftrain.shape)  # the shape of the tensor

    CATEGORICAL_COLUMNS = [
        "sex",
        "n_siblings_spouses",
        "parch",
        "class",
        "deck",
        "embark_town",
        "alone",
    ]

    NUMERIC_COLUMNS = ["age", "fare"]

    feature_columns = []
    for feature_name in CATEGORICAL_COLUMNS:
        vocabulary = dftrain[
            feature_name
        ].unique()  # gets a lsit of all unique values from given feature column
        feature_columns.append(
            tf.feature_column.categorical_column_with_vocabulary_list(
                feature_name, vocabulary
            )
        )

    for feature_name in NUMERIC_COLUMNS:
        feature_columns.append(
            tf.feature_column.numeric_column(feature_name, dtype=tf.float32)
        )

    print(dftrain["embark_town"].unique())
    print()
    print(feature_columns)


if __name__ == "__main__":
    main()
