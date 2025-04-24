import matplotlib.pyplot as plt
import numpy as np

def get_tables(filename):
    x, y = [], []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            x.append(int(parts[0]))
            y.append(int(parts[1]))
    return x, y

files = ["hash_table_num_mod.txt", "hash_table_num_bit.txt", "hash_table_num_knyt.txt"]
all_data_of_files = [get_tables(file) for file in files]

plt.style.use('seaborn')
plt.figure(figsize=(18, 7)) 

# Считаем дисперсию
y2 = all_data_of_files[1][1]  # Высоты графика 2
y3 = all_data_of_files[2][1]  # Высоты графика 3

var2 = np.var(y2)
var3 = np.var(y3)



titles = [
    "Взятие по модулю",
    f"Битовые операции (дисперсия - {var2:.2f})",
    f"Метод, предложенный Кнутом (дисперсия - {var3:.2f})"
]

# Построение 3 гистограмм в одном ряду
for i, (x, y) in enumerate(all_data_of_files, 1):
    plt.subplot(1, 3, i)                  # 1 строка, 3 столбца, текущий график i
    plt.bar(x, y, color=plt.cm.tab10(i))  # Разные цвета для каждого графика
    plt.xlabel("Значение хеш-функции")
    plt.ylabel("Количество элементов")
    plt.title(titles[i-1])
    plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()  
plt.savefig("hash_functions_for_numbers_comparison.png", dpi=300)
plt.show()