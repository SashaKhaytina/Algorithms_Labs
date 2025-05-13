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


files = ["hash_table_str_len.txt", "hash_table_str_sum.txt", "hash_table_str_polin.txt", "hash_table_str_crc32.txt"]
all_data_of_files = [get_tables(file) for file in files]

plt.style.use('seaborn')
plt.figure(figsize=(20, 10))

# Считаем дисперсию
y3 = all_data_of_files[2][1]  # Высоты графика 3
y4 = all_data_of_files[3][1]  # Высоты графика 4

dicp3 = np.var(y3)
dicp4 = np.var(y4)



titles = [
    "Длина строки (обрезан по x)",
    "Сумма букв",
    f"Полиномиальная (дисперсия - {dicp3:.2f})",
    f"CRC32 (дисперсия - {dicp4:.2f})"
]

widht_stolbs = [
    0.5,
    0.6,
    0.6,
    0.6
    ]

# Построение 3 гистограмм в одном ряду
for i, (x, y) in enumerate(all_data_of_files, 1):
    plt.subplot(2, 2, i)                                           # 2 строкb, 2 столбца, текущий график i
    if (i == 1):
        plt.xlim(right=100)
    plt.bar(x, y, width=widht_stolbs[i-1], color=plt.cm.tab10(i))  # Разные цвета для графиков
    plt.xlabel("Значение хеш-функции")
    plt.ylabel("Количество элементов")
    plt.title(titles[i-1])
    plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig("hash_functions_for_strings_comparison.png", dpi=300)
plt.show()