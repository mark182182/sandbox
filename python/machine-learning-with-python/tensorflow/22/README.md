## Natural Language Processing With RNNs: Part 2

### Notes:

- History of NLP's:
  1. <b>Bag of words</b>:
     - The bag-of-words model represents text by counting word occurrences, disregarding word order, and focusing on word presence within a document
     - It is a simple and efficient way to represent text, but it lacks the ability to capture semantic relationships between words.
  2. <b>Word embeddings</b>:
     - Word embeddings are dense vector representations of words capturing semantic relationships, enhancing text analysis compared to sparse one-hot encodings
     - They are learned from large corpora of text data and can capture complex relationships between words.
  3. <b>RNN based models</b>:
     - (RNN) models process sequential data by retaining memory of past inputs, enabling learning from sequences
     - They are well-suited for tasks involving sequential data, such as language modeling and machine translation.
  4. <b>LSTM based models</b>:
     - Long Short-Term Memory (LSTM) models, a type of RNN, retain long-term dependencies, making them effective for learning sequences
     - LSTMs have specialized cells that can selectively remember and forget information, allowing them to capture long-range dependencies in data.
  5. <b>Bi-directional LSTM</b>:
     - Bi-directional LSTMs process sequences in both forward and backward directions, capturing context from past and future inputs
     - This allows them to consider the entire sequence when making predictions, which can be beneficial for tasks such as sequence labeling and machine translation.
  6. <b>Attention based</b>:
     - Attention mechanisms allow models to focus on specific parts of input sequences, enhancing performance in tasks requiring selective processing
     - They enable models to dynamically allocate attention to different parts of the input, which can be particularly useful for tasks such as machine translation and text summarization.
  7. <b>Transformers</b>:
     - Transformers use self-attention mechanisms to weigh word importance in a sequence, excelling in tasks with long-range dependencies and parallel processing
     - They are based on the concept of attention and can capture long-range dependencies without the need for recurrent or convolutional layers.
     - Transformers have achieved state-of-the-art results in various natural language processing tasks and have become widely used in the field.

### Questions:

Word embeddings are...:

- a vectorized representation of words in a given document that places words with similar meanings near each other.
