import requests
import os
import torch
import torch.nn as nn
import time
import numpy as np
import inspect
import sys
import datetime
from datetime import datetime
import pytz
from torch.nn import functional as F

block_size = 8
batch_size = 4

max_iters = 1000
learning_rate = 3e-4
eval_iters = 250

def debug_info1():
    # Get the frame of the caller (one level up)
    caller_frame = inspect.currentframe().f_back

    # Get the function name of the caller
    function_name = inspect.getframeinfo(caller_frame).function

    # Get the line number of the caller
    line_number = inspect.getframeinfo(caller_frame).lineno

    current_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    print(f"{current_time} > Invoke:{function_name}():{line_number}")
    return function_name, line_number

def programming_training1():
    # %%time
    # %time
    # %timeit
    # %prun
    # Test env
    randint = torch.randint(-100, 100, (8,))
    print(randint)

    tensor = torch.tensor([[0.1, 1.2], [2.2, 3.1], [4.9, 5.2]], dtype=torch.float32)
    print(tensor)

    zeros = torch.zeros((2, 3))
    print(zeros)

    ones = torch.ones((2, 3))
    print(ones)

    input = torch.empty(2, 3)
    print(input)

    range = torch.arange(5)
    print(range)

    linspace = torch.linspace(3, 10, steps=5)
    print(linspace)

    logspace = torch.logspace(start=-10, end=10, steps=5)
    print(logspace)

    eye = torch.eye(5)
    print(eye)

    a = torch.empty((4, 5), dtype=torch.int64)
    print(a)
    empty_like = torch.empty_like(a)
    print(empty_like)

    start_time = time.time()
    zeros = torch.zeros(1, 1)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time} seconds")
    print(f"Elapsed time: {elapsed_time:.4f} seconds")
    # Test end

    print("Elapsed time test round 1")
    torch_rand1 = torch.rand(1000, 1000).to(device)
    torch_rand2 = torch.rand(1000, 1000).to(device)
    np_rand1 = torch.rand(1000, 1000)
    np_rand2 = torch.rand(1000, 1000)

    print(torch_rand1)
    print(torch_rand2)

    print(np_rand1)
    print(np_rand2)

    start_time = time.time()
    rand = (torch_rand1 @ torch_rand2) # multiply
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time} seconds")

    start_time = time.time()
    rand = np.multiply(np_rand1, np_rand2)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time} seconds")

    print("Elapsed time test round 2")
    torch_rand1 = torch.rand(100, 100, 100, 100).to(device)
    torch_rand2 = torch.rand(100, 100, 100, 100).to(device)
    np_rand1 = torch.rand(100, 100, 100, 100)
    np_rand2 = torch.rand(100, 100, 100, 100)

    start_time = time.time()
    rand = (torch_rand1 @ torch_rand2) # multiply
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time} seconds")

    start_time = time.time()
    rand = np.multiply(np_rand1, np_rand2)
    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time} seconds")

    # torch.stack, torch.mutinomial, torch.tril, torch.triu, input.T / input.transpose

    probabilities = torch.tensor([0.5, 0.4, 0.3, 0.2, 0.9, 0.65])
    samples = torch.multinomial(probabilities, num_samples=10, replacement=True)
    print(samples)

    tensor = torch.tensor([1, 2, 3, 4])
    output = torch.cat((tensor, torch.tensor([5])), dim=0)
    print(output)

    out = torch.tril(torch.ones(5, 5))
    print(out)
    out = torch.triu(torch.ones(5, 5))
    print(out)

    out = torch.zeros(5, 5).masked_fill(torch.tril(torch.ones(5, 5)) == 0, float('-inf'))
    print(out)

    out = torch.zeros(5, 5).masked_fill(torch.triu(torch.ones(5, 5)) == 0, float('-inf'))
    print(out)

    out = torch.exp(out)
    print(out)
    print(out.sum(1, keepdim=True))
    out = out / out.sum(1, keepdim=True)
    print(out)

    input = torch.randn(2, 3, 4)
    print(input)
    print(input.shape)
    print(input.T)
    print(input.T.shape)
    out = input.transpose(0,2)
    print(out.shape)
    print(out)
    out = input.transpose(0,1)
    print(out.shape)
    print(out)

    tensor1 = torch.tensor([1, 2, 3])
    tensor2 = torch.tensor([4, 5, 6])
    tensor3 = torch.tensor([7, 8, 9])

    stacked_tensor = torch.stack([tensor1, tensor2, tensor3])
    print(stacked_tensor)

def programming_training2():
    sample = torch.tensor([10., 10., 10.])

    print(f"sample={sample}")
    linear = nn.Linear(3, 3, bias=False)
    print(f"linear={linear}")

    for parm in linear.parameters():
        print(f"parm={parm}")

    print(f"linear(sample)={linear(sample)}")
    #print(debug_info1())

    import torch.nn.functional as F
    tensor1 = torch.tensor([1.0, 2.0, 3.0])
    softmax_output = F.softmax(tensor1, dim=0)
    print(f"softmax_output={softmax_output}")


# def test_fun1(func):
#     def wrapper(*args, **kwargs):
#         caller_frame = inspect.currentframe().f_back
#         function_name = inspect.getframeinfo(caller_frame).function
#         line_number = inspect.getframeinfo(caller_frame).lineno
#         print(f"Invoker: {function_name}, Line: {line_number}")
#         return func(*args, **kwargs)
#     return wrapper

# @test_fun1
# def test_fun2():
#     print("This is test_fun2.")

def env_check():
    device = 'CUDA' if torch.cuda.is_available() else 'CPU'

    # Get the current time in UTC
    utc_now = datetime.now(pytz.utc)

    # Convert to the user's local time zone, assuming a typical time zone (e.g., US/Eastern)
    # You can replace 'US/Eastern' with the appropriate time zone if known
    local_time = utc_now.astimezone(pytz.timezone('US/Eastern'))

    print(f"Python version: {sys.version}, Device type: {device}, {local_time}")

    return device

def loadfile():
    url = 'https://www.gutenberg.org/cache/epub/22566/pg22566.txt'
    filename = 'wizard_of_oz.txt'

    # with open('wizard_of_oz.txt', 'wb') as f:
    #     f.write(response.content)
    current_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(current_dir, filename)

    # if not os.path.isfile(file_path):
    if not os.path.exists(file_path):
        print("File is not exist and need to download from the internet.")
        response = requests.get(url)
        with open(filename, 'wb') as f:
            f.write(response.content)
        print("File downloaded.")
    else:
        print("File already exists.")

    return file_path

def get_batch(mode, train_data, val_data):
    data = train_data if mode == 'train' else val_data
    ix = torch.randint(len(data) - block_size, (batch_size, ))
    # print(f"ix:{ix}")
    x = torch.stack([data[i:i+block_size] for i in ix])
    y = torch.stack([data[i+1:i+block_size+1] for i in ix])
    return x, y

def get_random_chunk(split):
    filename = "openwebtext/train_split.txt" if split == 'train' else "openwebtext/val_split.txt"
    with open(filename, 'rb') as f:
        with mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) as mm:
            # Determine the file size and a random position to start reading
            file_size = len(mm)
            start_pos = random.randint(0, (file_size) - block_size*batch_size)

            # Seek to the random position and read the block of text
            mm.seek(start_pos)
            block = mm.read(block_size*batch_size-1)

            # Decode the block to a string, ignoring any invalid byte sequences
            decoded_block = block.decode('utf-8', errors='ignore').replace('\r', '')
            # Train and test splits
            data = torch.tensor(encode(decoded_block), dtype=torch.long)
    return data

def get_batch2(split):
    data = get_random_chunk(split)
    ix = torch.randint(len(data) - block_size, (batch_size,))
    # print(f"ix:{ix}")
    x = torch.stack([data[i:i+block_size] for i in ix])
    y = torch.stack([data[i+1:i+block_size+1] for i in ix])
    x, y = x.to(device), y.to(device)
    return x, y

def demo_test1():
    a = torch.rand(2, 3, 5)
    print(a)
    print(a.shape)
    x, y, z = a.shape
    a = a.view(z,y,x)
    print(a)
    print(a.shape)

class BigramLanguageModel(nn.Module):
    def __init__(self, vocab_size):
        super().__init__()
        self.token_embedding_table = nn.Embedding(vocab_size, vocab_size)

    def forward(self, index, targets=None):
        # logits = self.token_embedding_table(index)
        # B, T, C = logits.shape
        # logits = logits.view(B*T, C)
        # targets = targets.view(B*T)
        # loss = F.cross_entropy(logits, targets)
        logits = self.token_embedding_table(index)
        if targets is None:
            loss = None
        else:
            B, T, C = logits.shape
            logits = logits.view(B*T, C)
            targets = targets.view(B*T)
            loss = F.cross_entropy(logits, targets)

        return logits, loss

    def generate(self, index, max_new_tokens):
        for _ in range(max_new_tokens):
            logits, loss = self.forward(index)
            logits = logits[:, -1, :]
            probs = F.softmax(logits, dim=-1)
            index_next = torch.multinomial(probs, num_samples=1)
            index = torch.cat((index, index_next), dim=1)
        return index

@torch.no_grad()
def estimate_loss():
    out = {}
    model.eval()
    for split in ['train', 'val']:
        losses = torch.zeros(eval_iters)
        for k in range(eval_iters):
            X, Y =  get_batch(split)
            logits, loss = model(X, Y)
            losses[k] = loss.item()
        out[split] = losses.mean()
    model.train()
    return out

def fun_optimizer(model, data):
    optimizer = torch.optim.AdamW(model.parameters(), lr=learning_rate)

    n = int(0.8*len(data))
    train_data = data[:n]
    val_data = data[n:]

    for inter in range(max_iters):
        xb, yb = get_batch('train', train_data, val_data)

        logits, loss = model.forward(xb, yb)
        optimizer.zero_grad(set_to_none=True)
        loss.backward()
        optimizer.step()
        # print(f">>>{inter}:{loss.item()}")
    print(f">>>{loss.item()}")

def main_test(file_path, device):
    with open(file_path, 'r', encoding='utf-8') as f:
        text = f.read()
    print(f">>>text({len(text)}):{text[:128]}")
    chars = sorted(list(set(text)))
    vocab_size = len(chars)
    print(f">>>chars({vocab_size}):{chars}")

    string_to_int = {ch:i for i,ch in enumerate(chars)}
    int_to_string = {i:ch for i,ch in enumerate(chars)}
    print(f"Str2Int:{string_to_int}")
    print(f"Int2Str:{int_to_string}")

    encode = lambda s: [string_to_int[c] for c in s]
    decode = lambda l: ''.join([int_to_string[i] for i in l])

    test_string = "X:Hello world!"
    print(f"Encode:{encode(test_string)}")
    print(f"Decode:{decode(encode(test_string))}")

    data = torch.tensor(encode(text), dtype=torch.long)
    print(f"Data({len(data)}:{data.shape}:{data.dtype}):{data[:200]}")

    n = int(0.8*len(data))
    train_data = data[:n]
    val_data = data[n:]

    print(f"TrainDLen:{len(train_data)} ValidateDLen:{len(val_data)}")
    print(f"block_size = {block_size}")

    x, y = get_batch('train', train_data, val_data)
    if not device == 'CPU':
        x, y = x.to(device), y.to(device)
    print(f"Input:{x}")
    print(f"Targets:{y}")

    #////

    x = train_data[:block_size]
    y = train_data[1:block_size+1]

    for t in range(block_size):
        context = x[:t+1]
        target = y[t]
        print(f"when input is {context} the target: {target}")

    model = BigramLanguageModel(vocab_size)
    if not device == 'CPU':
        m = model.to(device)
        context = torch.zeros((1,1), dtype=torch.long, device=device)
    else:
        m = model
        context = torch.zeros((1,1), dtype=torch.long)

    generate_chars = decode(m.generate(context, max_new_tokens=500)[0].tolist())
    print(f">>>R1:{generate_chars}")
    # return m, data

    fun_optimizer(m, data)

    generate_chars = decode(m.generate(context, max_new_tokens=500)[0].tolist())
    print(f">>>R2:{generate_chars}")

if __name__ == '__main__':
    device = env_check()
    #programming_training1() # Torch fundamental
    #programming_training2() # NN fundamental
    main_test(loadfile(), device)

    #demo_test1()
    print("Done")

# The end of this file
