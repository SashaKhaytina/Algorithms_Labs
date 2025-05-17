import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    arr_sizes = []
    times = []
    with open(filename, 'r') as file:
        for line in file:
            size, time = line.split()
            arr_sizes.append(int(size))
            times.append(float(time))
    return np.array(arr_sizes), np.array(times)


def graphic_settings(title, x_lable, y_lable):
    plt.title(title, fontsize=14, pad=20)
    plt.xlabel(x_lable, fontsize=12)
    plt.ylabel(y_lable, fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=12)

    plt.xlim(left=10000) # левый край по оx (size)- 100
    plt.yscale('log')  # Логарифмическая шкала
    plt.tight_layout()


def main():
    # sort1_sizes, sort1_times = read_data('quick_lomuto_sort.txt')
    sort2_sizes, sort2_times = read_data('quick_hoar_sort.txt')
    # sort3_sizes, sort3_times = read_data('selection_sort.txt')
    # sort4_sizes, sort4_times = read_data('shell_sort.txt')

    plt.figure(figsize=(15, 9))

    # plt.plot(sort1_sizes, sort1_times, 'b-o', label='quick_lomut_sort', linewidth=2, markersize=6)
    plt.plot(sort2_sizes, sort2_times, 'r-o', label='quick_hoar_sort', linewidth=2, markersize=6)
    # plt.plot(sort3_sizes, sort3_times, 'g-o', label='selection_sort', linewidth=2, markersize=6)
    # plt.plot(sort4_sizes, sort4_times, 'm-o', label='shell_sort', linewidth=2, markersize=6)

    graphic_settings('Сравнение времени работы квадратичных сортировок', 'Размер массива', 'Время выполнения (мс)')

    plt.savefig('quick_sorting_compa4567865456789rison.png', dpi=300)

if __name__ == "__main__":
    main()
