## Natural Language Processing With RNNs: Sentiment Analysis


### Notes:

- <b>Sentiment Analysis</b>: indentifying and categorizing opinions expressed in a piece of text, especially in order to determine whether the writer's attitude towards a particular topic, product, etc. is positive, negative, or neutral
- IMDB movie review dataset (25.000 reviews)

### Questions:

- Fill in the blanks below to create the model for the RNN:
```python
model = __A__.keras.Sequential([
    __A__.keras.layers.__B__(88584, 32),
    __A__.keras.layers.__C__(32),
    __A__.keras.layers.Dense(1, activation='sigmoid')
])
```

A: tf B: Embedding C: LSTM