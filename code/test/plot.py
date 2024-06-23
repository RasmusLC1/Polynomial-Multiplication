import matplotlib.pyplot as plt
import sys

def plot_data(data, output_file='output.png'):
    print("Received data:", data)  # Debug: Print the received data
    try:
        y = [abs(complex(d.strip())) for d in data.split(",") if d.strip()]  # Parse complex numbers
        x = range(len(y))

        plt.figure()
        plt.stem(x, y)
        plt.title("Magnitude of DFT Results")
        plt.xlabel("Index")
        plt.ylabel("Magnitude")
        plt.savefig(output_file)
        print(f"Plot saved as {output_file}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    plot_data(sys.argv[1], 'output.png')
