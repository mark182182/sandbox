## Reinforcement Learning With Q-Learning

### Notes:

- <b>Reinforcement learning</b>: different than the other machine learning techniques earlier, and has many applications in training <em>agents</em> (an AI) to interact with environments, like games.
  - Rather than feeding our maching model millions of examples, we let our model come up with it's own examples by <em>exploring an <b>environment</b></em>
- Terminology:
  - <b>Environment</b>: this is what our agent will explore (example: a level in a game)
  - <b>Agent</b>: an entity that is exploring the environment, take different actions within the environment (example: our character)
  - <b>State</b>: at all times our agent will be in a state, which simply tells us about the status of the target (example: the location of the agent within the environment, and moving locations would change the agent's state)
  - <b>Action</b>: any iteraction between the agent and the environment (example: moving to the left or jumping).
    - An action <em>may or may not</em> change the current state of the agent, as nothing is an action as well! (example: pressing a key)
  - <b>Reward</b>: every action that our agent takes will result in a reward of some magnitude (positive or negative).
    - The goal of our agent will be to maximize it's reward in an environment.
    - Sometimes the reward will be clear, example increasing the score.
    - If an agent were to perform an action, which results in them losing score, or possible dying in the environment, then they would receive a negative reward.
    - The most important part of reinforcement learning is determing how to <b>reward the agent</b>.
- <b>Q-Learning</b>: simple, yet powerful technique that involves learning a <em>matrix of action-reward values</em>
  - The matrix is a shape (number of possible states, number of possible actions), where each value at matrix[n, m] represents the agents expected reward given they are in a state n and take action m.
  - The Q-learning algorithm defines the way we update the values in the matrix and decide what actions to take at each state.
  - The idea is that after a successful training/learning of this Q-Table/matrix, we can determine the action an agent should take in any state by looking at the states row in the matrix and taking the maximum value column as the action.
### Questions:

- The key components of reinforcement learning are...

environment, agent, state, action, and reward.
