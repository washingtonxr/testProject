from tokenizers import CharBPETokenizer

# Initialize a tokenizer
vocab = "./path/to/vocab.json"
merges = "./path/to/merges.txt"
tokenizer = CharBPETokenizer(vocab, merges)

# And then encode:
encoded = tokenizer.encode("I can feel the magic, can you?")
print(encoded.ids)
print(encoded.tokens)
