import random
import string
import os

file_size = int(os.environ.get('FILE_SIZE', 0))
file_name = f"file_{file_size}.txt"

def generate_random_string(length):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for _ in range(length))

with open(os.path.join('/output/', file_name), "w") as f:
    for _ in range(file_size):  
        f.write(generate_random_string(1000) + "\n")
