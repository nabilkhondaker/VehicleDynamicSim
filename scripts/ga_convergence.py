import matplotlib.pyplot as plt
import numpy as np

# Mocking GA convergence plotting
def plot_convergence():
    generations = np.arange(0, 50)
    fitness = 10.0 * np.exp(-0.1 * generations) + 0.5 + np.random.normal(0, 0.2, 50)
    
    plt.figure(figsize=(8, 5))
    plt.plot(generations, fitness, 'o-', color='purple')
    plt.title('Genetic Algorithm Convergence: Understeer Minimization')
    plt.xlabel('Generation')
    plt.ylabel('Best Fitness (Lower is Better)')
    plt.grid(True)
    plt.savefig('ga_convergence.png')

if __name__ == "__main__":
    plot_convergence()
