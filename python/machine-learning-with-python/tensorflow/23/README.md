## Natural Language Processing With RNNs: Recurring Neural Networks

### Notes:

- The fundemental difference between a dense NN (which uses feed forward) and a convolutional NN is that a convolutional NN contains an <b>inner loop</b>
  - The inner loop processes our data at different time steps, and maintains an internal memory and an internal state, so when it look at new input, it will remember what it seen previously
- LSTM (Long Short-Term Memory):
  - Long term memory data structure storing all of the previously seen inputs as well when we saw them.
  - This allows for us to access any previous value we want at any point in time
  - Example: "Hi I am Tim" is processed one word at a time and at time0 we have "Hi" and at time1 we have "Hi I"
  - It allows up to track and access any state at any point in time
### Questions:

- What is true about Recurrent Neural Networks?

4: Both 2 and 3.
