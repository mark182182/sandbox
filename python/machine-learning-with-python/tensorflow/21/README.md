## Natural Language Processing With RNNs

### Notes:

- <b>Natural Language Processing</b> (NLP):
  - A disciple in computing that deals with the <em>communication</em> between natural (human) languages and computer languages. A common example of NLP is something like spellcheck or autocomplete. NLP is a field that focuses on how computers can understand and/or process natural/human languages
  - In our example, we will write a play
- <b>Recurrent Neural Networks</b> (RNN):
  - Most capable of processing sequential data such as text or characters called a recurrent neural network (they are fairly complex)
  - What can a RNN typically do?
    - Sentiment analysis
    - Character generator
- <b>Sequence Data</b>:
  - Unlike images, sequence data such as long chains of text, weather patterns, videos and really anything where the notion of a <em>step or time is relevant</em> needs to be processed and handled in a special way.
  - Why is test data a sequence: textual data contains many words that follow a <em>very specific and meaningful order</em>, we need to be able to <em>keep track of</em> each word and <em>when</em> it occurs in the data.
  - Simply encoding an entire paragraph of text into one data point wouldn't give us a very meaningful picture of data and would be very difficult to do anything with.
  - We process <em>one word at a time</em>, and we keep track of where each of these words appear and use that information to try to understand the meaning of pieces of text.
- <b>Encoding Text</b>

### Questions:

Natural Language Processing is a branch of artificial intelligence that...:

- deals with how computers understand and process natural/human languages.
