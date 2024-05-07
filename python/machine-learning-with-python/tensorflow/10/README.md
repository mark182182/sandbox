## Core Learning Algorithms: Hidden Markov Models

### Notes:

- <b>Hidden Markov Models</b>: it works with probabilities to predict future events or states. These states are "hidden", as we never actually access or look at these states while we interact with the model.
  - At each state we have an observation
  - Definition: http://jedlik.phy.bme.hu/~gerjanos/HMM/node4.html
  - Example: create a hidden markov model that can predict the weather
  - Reference: https://www.tensorflow.org/probability/api_docs/python/tfp/distributions/HiddenMarkovModel
  - <b>States</b>: in each hidden markov model, we have a finite set of states, these can be like "warm" and "cold" or "high" and "low". These states are hidden, as we do not directly observe them.
  - <b>Observations</b>: Each state has a particular outcome or observation with it based on a probability distribution. An example of this is the following: <u>On a hot day Tim has an 80% chance of being happy and a 20% change of being sad.</u>
  - <b>Transitions</b>: Each state will have a probability defining the likelyhood of transitioning to a different state. An example is the following: <u>a cold day has a 30% chance of being followed by a hot day and a 70% chance of being followed by another cold day.</u>
  - To create a hidden markov model, we need states, obersvation and transition distribution

### Questions:

What makes a Hidden Markov model different than linear regression or classification?

- It uses probability distributions to predict future events or states.
