## Reinforcement Learning With Q-Learning: Example

### Notes:

- Q-Learning example (see [main.py](main.py))
- <b>Epsilon</b>: start at 90% change of picking random values instead of from the QTable
  - Reduce the epsilon value as we train the model, so it will pick values from the QTable

### Questions:

- Fill in the blanks to complete the following Q-Learning equation:

```python
Q[__A__, __B__] = Q[__A__, __B__] + LEARNING_RATE * (reward + GAMMA * np.max(Q[__C__, :]) - Q[__A__, __B__])
```

A: state B: action C: next_state
