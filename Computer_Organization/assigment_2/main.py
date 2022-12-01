## IMPORTS 
import  subprocess # calls commands
import matplotlib.pyplot as plt # plotting - in use currently

# Compile programs and set up execute command
subprocess.run(['make'])

print('2D array access|not done|')
test_miss_command = ['./test_miss']
test_hit_command = ['./test_hit']

results_test_miss = {}
results_test_hit = {}

array_size_max = 3000
iter_step = 10
iterations = 20
for iteration in range(iterations):
    for number in range(0, array_size_max, iter_step):
        print(f'$DEBUG: it {iteration + 1}\ttotal_size: {number * 24}B') #debug
        
        test_miss_command.append(str(number))
        result = float(subprocess.run(test_miss_command, stdout=subprocess.PIPE).stdout.decode('utf-8'))
        if (number * 24) not in results_test_miss:
            results_test_miss[number * 24] = result
        else:
            results_test_miss[number * 24] += result
        test_miss_command.pop()

        test_hit_command.append(str(number))
        result = float(subprocess.run(test_hit_command, stdout=subprocess.PIPE).stdout.decode('utf-8'))
        if number * 24 not in results_test_hit:
            results_test_hit[number * 24] = result
        else:
            results_test_hit[number * 24] += result 
        test_hit_command.pop()

for key in results_test_miss: results_test_miss[key] /= iterations
for key in results_test_hit: results_test_hit[key] /= iterations

def plot_results(ylabel: str, xlabel: str, results_miss: dict, results_hit: dict, title: str, file_path: str):
    with plt.style.context('bmh'):    
        plt.ylabel(xlabel)
        plt.xlabel(ylabel)

        plt.plot(results_miss.keys(), sorted(results_miss.values()), label='test miss')
        plt.plot(results_hit.keys(), sorted(results_hit.values()), label='test hit')

        leg = plt.legend(loc='upper center')
        plt.title(title)
        plt.savefig(file_path, dpi=300)
        plt.clf()

print(results_test_hit) # debug
print(results_test_miss) # debug

print(f'Plotting\nARRAY SIZE: {array_size_max}, ITERATIONS: {iterations}, STEP: {iter_step} ')
