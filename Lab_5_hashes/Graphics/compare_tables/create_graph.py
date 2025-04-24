# import matplotlib.pyplot as plt

# def get_tables(filename):
#     x, y = [], []
#     with open(filename, 'r') as file:
#         for line in file:
#             parts = line.strip().split()
#             x.append(float(parts[0]))  # load factor обычно float
#             y.append(float(parts[1]))  # время тоже может быть float
#     return x, y

# # Получаем данные из файла
# load_factors, times = get_tables("load_factor_list.txt")

# # Создаем график
# plt.style.use('seaborn')
# plt.figure(figsize=(10, 6))  # Размер графика
# plt.plot(load_factors, times, 'bo-', linewidth=2, markersize=8)  # Синие точки с линиями

# # Настройка осей и заголовка
# plt.xlabel('Load Factor', fontsize=12)
# plt.ylabel('Time (ms)', fontsize=12)
# plt.title('Зависимость time от load_factors', fontsize=14)

# # Сетка и дополнительные настройки
# plt.grid(True, linestyle='--', alpha=0.6)
# plt.xticks(fontsize=10)
# plt.yticks(fontsize=10)

# # Выводим график
# plt.tight_layout()
# plt.savefig('load_factor_list_graph.png', dpi=300)
# plt.show()


import matplotlib.pyplot as plt

def get_tables(filename):
    x, y = [], []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            x.append(float(parts[0]))  # load factor
            y.append(float(parts[1]))  # time
    return x, y

# Получаем и сортируем данные
# load_factors, times = get_tables("load_factor_list.txt")
# load_factors, times = get_tables("load_factor_op_addr_line.txt")
load_factors, times = get_tables("load_factor_op_addr_square.txt")


# Сортируем данные по возрастанию load factor
sorted_data = sorted(zip(load_factors, times), key=lambda pair: pair[0])
load_factors_sorted = [x[0] for x in sorted_data]
times_sorted = [x[1] for x in sorted_data]

# Создаем график
plt.style.use('seaborn')
plt.figure(figsize=(10, 6))
plt.plot(load_factors_sorted, times_sorted, 'bo-', linewidth=2, markersize=8)

# Настройка осей
plt.xlabel('Load Factor', fontsize=12)
plt.ylabel('Time (ms)', fontsize=12)
plt.title('Зависимость time от load factor', fontsize=14)

# Дополнительные настройки
plt.grid(True, linestyle='--', alpha=0.6)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

# Сохраняем и показываем график
plt.tight_layout()
# plt.savefig('load_factor_list_graph.png', dpi=300)
# plt.savefig('load_factor_op_addr_line_graph.png', dpi=300)
plt.savefig('load_factor_op_addr_square_graph.png', dpi=300)



plt.show()