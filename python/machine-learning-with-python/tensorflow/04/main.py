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

    plt.figure()  # Create a new figure
    dftrain.age.hist(bins=20)  # Plot the histogram
    plt.savefig("age_histogram.png")  # Save the figure to a PNG file

    plt.figure()
    dftrain.sex.value_counts().plot(kind="barh")
    plt.savefig("sex_distribution.png")

    plt.figure()
    dftrain["class"].value_counts().plot(kind="barh")
    plt.savefig("class_distribution.png")

    # Create a diagram on the survival ratio based on the given sex
    plt.figure()  # Create a new figure
    pd.concat([dftrain, y_train], axis=1).groupby("sex").survived.mean().plot(
        kind="barh"
    ).set_xlabel("% survive")
    plt.savefig("survival_ratio_by_sex.png")


if __name__ == "__main__":
    main()
