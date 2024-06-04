## Reinforcement Learning With Q-Learning: Part 2

### Notes:

- <b>Local maxima</b>: not able to move forward to other states and stucks in the local maxima (stays in the state), if it always only picks the highest reward
  - We have to implement the idea of picking a <b>random valid action</b>
- <b>Updating Q-Values</b>: `Q[state, action] = Q[state, action] + alpha * (reward + gamma *max(Q[newState,:]) - Q[state, action])`
  - alpha: learning rate
  - gamma: discount factor
  - <b>Learning rate</b>: how much change is permitted on each QTable update.
    - A high learning rate means that each update will introduce a large change to the current state-action value.
  - <b>Discount factor</b>: define a balance between a reward state and the future state
    - A high discount factor means that future rewards will be considered more heavily.
  - To perform updates on this table, we will let the agent explore the enviornment for a certain period of time and use each of its actions to make an update.
  - Slowly we should start to notice the agent learning and choosing better actions.

### Questions:

- What can happen if the agent does not have a good balance of taking random actions and using learned actions?

The agent will always try to maximize its reward for the current state/action, leading to local maxima.
