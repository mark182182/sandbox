## Core Learning Algorithms: Using Probabilities to make Predictions

### Notes:
- Modeling a simle weather system and trying to predict the temperature on each day given the following information:
1. Cold days are encoded by a 0 and hot days are encoded by a 1.
2. The first day in our sequence has an 80% chance of being cold.
3. A cold day has a 30% chance of being followed by a hot day.
4. A hot day has a 20% chance of being followed by a cold day.
5. On each day the temperature is normally distributed with mean and standard deviation 0 and 5 on a cold day and mean and standard deviation 15 and 10 on a hot day.
- Build the model (see [main.py](main.py))

### Questions:

What TensorFlow module should you import to implement `.HiddenMarkovModel()`?

- tensorflow_probability
