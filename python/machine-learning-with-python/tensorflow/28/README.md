## Natural Language Processing With RNNs: Training the Model

### Notes:

- Training the model (see [main.py](main.py))

### Questions:

- Fill in the blanks below to save your model's checkpoints in the ./checkpoints directory and call the latest checkpoint for training:

```python
checkpoint_dir = __A__
checkpoint_prefix = os.path.join(checkpoint_dir, 'ckpt_{epoch}')

checkpoint_callback = tf.keras.callbacks.__B__(
    filepath=checkpoint_prefix,
    save_weights_only=True
)

history = model.fit(data, epochs=2, callbacks=[__C__])
```

A: './checkpoints' B: ModelCheckpoint C: checkpoint_callback
