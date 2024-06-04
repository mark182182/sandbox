import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"

import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
import tensorflow as tf


def main():
    dftrain = pd.read_csv(
        "https://storage.googleapis.com/tf-datasets/titanic/train.csv"
    )
    dfeval = pd.read_csv("https://storage.googleapis.com/tf-datasets/titanic/eval.csv")
    y_train = dftrain.pop(
        "survived"
    )  # we are dropping the survived column from dftrain (this is what we want to predict)
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
    # print()
    # print(feature_columns)
    # print()

    def make_input_fn(data_df, label_df, num_epochs=10, shuffle=True, batch_size=32):
        def input_function():  # this inner function will be returned
            ds = tf.data.Dataset.from_tensor_slices(
                (dict(data_df), label_df)
            )  # create tf.data.Dataset object with data and its laabel
            if shuffle:
                ds = ds.shuffle(1000)  # randomize the order of the data
            ds = ds.batch(batch_size).repeat(
                num_epochs
            )  # split dataset into batches of 32 and repeat process for number of epochs
            return ds  # return a batch of the dataset

        return input_function  # return a function object for use

    train_input_fn = make_input_fn(dftrain, y_train)
    eval_input_fn = make_input_fn(dfeval, y_eval, num_epochs=1, shuffle=False)

    linear_est = tf.estimator.LinearClassifier(feature_columns=feature_columns)
    
    linear_est.train(train_input_fn)
    result = linear_est.evaluate(eval_input_fn) # get model metrics/stats by testing on testing data
        
    print(flush=True)
    print(result)
    
    result = list(linear_est.predict(eval_input_fn)) # the result will be the list of all of our prediction
    
    # Check the survival of a person
    print(dfeval.loc[0])
    print(y_eval.loc[0]) # the actual value of the survival (0=died, 1=survived)
    print(result[0]["probabilities"][0]) # the chance of death
    print(result[0]["probabilities"][1]) # the chance of survival


if __name__ == "__main__":
    main()
