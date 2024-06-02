import pandas as pd
import matplotlib.pyplot as plt

def read_computation_times(file_path):
    data = {}
    
    with open(file_path, 'r') as file:
        for line in file:
            name, values = line.split(':')
            name = name.strip().replace(' multiplication', '').replace(' ', '_')
            values = [float(x) for x in values.split()]
            data[name] = values
    
    return data

# Path to the txt file
file_path = 'Computation_times.txt'

# Read the data
data = read_computation_times(file_path)

# Convert to DataFrame
df = pd.DataFrame(data)

# Plotting
plt.figure(figsize=(12, 8))

# Defining colors for each algorithm
colors = {
    "Naive": "orange",
    "DFT": "green",
    "Karatsuba": "red",
    "Recursive_FFT": "magenta",
    "Iterative_FFT": "blue"
}

# Draw
for column in df.columns[1:]:
    plt.plot(df["n_size"], df[column], marker='o', label=column.replace('_', ' '), color=colors[column])

plt.xlabel("n size")
plt.ylabel("Time in seconds")
plt.title("Polynomial Multiplication Algorithms Performance")
plt.legend()
plt.grid(True, which="both", ls="--")

plt.show()
