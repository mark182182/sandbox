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
import gym
import time


def main():
    env = gym.make("FrozenLake-v1")  # we are going to use the FrozenLake enviornment
    print(env.observation_space.n)  # get number of states
    print(env.action_space.n)  # get number of actions
    env.reset()  # reset enviornment to default state
    action = env.action_space.sample()  # get a random action
    new_state, reward, done, info = env.step(
        action
    )  # take action, notice it returns information about the action

    # Building the Q-Table
    STATES = env.observation_space.n
    ACTIONS = env.action_space.n

    Q = np.zeros((STATES, ACTIONS))  # create a matrix with all 0 values
    print(Q)

    EPISODES = 1500  # how many times to run the enviornment from the beginning
    MAX_STEPS = 100  # max number of steps allowed for each run of enviornment

    LEARNING_RATE = 0.81  # learning rate
    GAMMA = 0.96
    RENDER = False  # render the GUI for the enviornment

    epsilon = 0.9  # start with a 90% chance of picking a random action

    rewards = []
    for episode in range(EPISODES):
        state = env.reset()
        for _ in range(MAX_STEPS):
            if RENDER:
                env.render()

            if np.random.uniform(0, 1) < epsilon:
                # we will check if a randomly selected value is less than epsilon.
                action = env.action_space.sample()  # take random action
            else:
                action = np.argmax(
                    Q[state, :]
                )  # use Q table to pick best action based on current values

            next_state, reward, done, _ = env.step(action)

            # updating the q values using the formula
            Q[state, action] = Q[state, action] + LEARNING_RATE * (
                reward + GAMMA * np.max(Q[next_state, :]) - Q[state, action]
            )

            state = next_state

            if done:
                rewards.append(reward)
                epsilon -= 0.001
                break  # reached goal

    print(Q)
    print(f"Average reward: {sum(rewards)/len(rewards)}:")
    # and now we can see our Q values!

    # we can plot the training progress and see how the agent improved
    import matplotlib.pyplot as plt

    def get_average(values):
        return sum(values)/len(values)

    avg_rewards = []
    for i in range(0, len(rewards), 100):
        avg_rewards.append(get_average(rewards[i:i+100])) 

    plt.plot(avg_rewards)
    plt.ylabel('average reward')
    plt.xlabel('episodes (100\'s)')
    plt.show()

if __name__ == "__main__":
    main()
