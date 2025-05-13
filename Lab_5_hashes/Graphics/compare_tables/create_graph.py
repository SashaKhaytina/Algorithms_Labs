import matplotlib.pyplot as plt

def get_tables(filename):
    x, y = [], []
    with open(filename, 'r') as file:
        for line in file:
            parts = line.strip().split()
            x.append(float(parts[0]))  # load factor
            y.append(float(parts[1]))  # time
    return x, y


load_factors, times = get_tables("load_factor_list.txt")
# load_factors, times = get_tables("load_factor_op_addr_line.txt")
# load_factors, times = get_tables("load_factor_op_addr_square.txt")


sorted_data = sorted(zip(load_factors, times), key=lambda pair: pair[0])
load_factors_sorted = [x[0] for x in sorted_data]
times_sorted = [x[1] for x in sorted_data]

plt.style.use('seaborn')
plt.figure(figsize=(10, 6))
plt.plot(load_factors_sorted, times_sorted, 'bo-', linewidth=2, markersize=8)

plt.xlabel('Load Factor', fontsize=12)
plt.ylabel('Time (ms)', fontsize=12)
plt.title('Зависимость time от load factor для метода цепочек', fontsize=15)
# plt.title('time(load factor) для открытой адресации (линейный метод)', fontsize=15)
# plt.title('time(load factor) для открытой адресации (квадратичный метод)', fontsize=15)


plt.grid(True, linestyle='--', alpha=0.6)
plt.xticks(fontsize=10)
plt.yticks(fontsize=10)

plt.tight_layout()
plt.savefig('load_factor_list_graph.png', dpi=300)
# plt.savefig('load_factor_op_addr_line_graph.png', dpi=300)
# plt.savefig('load_factor_op_addr_square_graph.png', dpi=300)



plt.show()