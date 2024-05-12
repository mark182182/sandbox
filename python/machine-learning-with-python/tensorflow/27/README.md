## Natural Language Processing With RNNs: Building the Model

### Notes:

- Building the model (see [main.py](main.py))

### Questions:

- Fill in the blanks below to complete the build_model function:

```python
def build_mode(vocab_size, embedding_dim, rnn_units, batch_size):
    model = tf.keras.Sequential([
        tf.keras.layers.Embedding(vocab_size,
                                  embedding_dim,
                                  batch_input_shape=[batch_size, None]),
        tf.keras.layers.__A__(rnn_units,
                              return_sequences=__B__,
                              recurrent_initializer='glorot_uniform),
        tf.keras.layers.Dense(__C__)
    ])
    __D__
```

A: LSTM B: True C: vocab_size D: return model
