import os

os.environ["TF_USE_LEGACY_KERAS"] = "1"

import numpy as np  # very optimized way to handle arrays
import pandas as pd  # data analytics tool (storing, loading, visualizing data, stc.)

import matplotlib.pyplot as plt
import tensorflow as tf
import keras
import tensorflow_probability as tfp


def main():
    tfd = tfp.distributions
    initial_distribution = tfd.Categorical(probs=[0.8, 0.2])  # Refer to step 2
    transition_distribution = tfd.Categorical(
        probs=[[0.7, 0.3], [0.2, 0.8]]
    )  # Refer to step 3 and 4
    observation_distribution = tfd.Normal(
        loc=[0.0, 15.0], scale=[5.0, 10.0]
    )  # Refer to step 5

    # the loc argument represents the mean and the scale is the standard deviation

    model = tfd.HiddenMarkovModel(
        initial_distribution=initial_distribution,
        transition_distribution=transition_distribution,
        observation_distribution=observation_distribution,
        num_steps=7,
    )

    mean = model.mean()
    print(mean)
    
    # we need to evaluate part of the graph from within a session to see the value of this tensor
    with tf.compat.v1.Session() as sess:
        print(mean.numpy())


if __name__ == "__main__":
    main()
