import random
import numpy as np
import heapq
import matplotlib.pyplot as plt

# Константы
PROCESSING_TIME = 0.136  # Время обработки одной заявки (сек)
LAMBDA_1 = 10          # Параметр гиперэкспоненциального распределения
LAMBDA_2 = 50
P_LAMBDA = [0.5, 0.5]   # Вероятности выбора распределения
QUEUE_SIZE = 8          # Максимальный размер очереди
MAX_PROCESSES = 6       # Количество одновременно работающих процессов
PRIORITY_LEVELS = 6     # Уровни приоритетов

# Генерация времени через гиперэкспоненциальное распределение
def generate_hyperexponential():
    selected_lambda = np.random.choice([LAMBDA_1, LAMBDA_2], p=P_LAMBDA)
    return np.random.exponential(1 / selected_lambda)

# Генерация случайного приоритета
def generate_priority():
    return random.randint(1, PRIORITY_LEVELS)

# Класс заявки
class Request:
    def __init__(self, arrival_time, priority):
        self.arrival_time = arrival_time
        self.priority = priority
        self.start_time = None
        self.finish_time = None

    def __lt__(self, other):
        return self.priority > other.priority  # Высший приоритет ближе к началу очереди

# Класс системы
class System:
    def __init__(self):
        self.current_time = 0
        self.processor = []  # Занятые процессы
        self.queue = []      # Очередь заявок
        self.total_requests = 0
        self.processed_requests = 0
        self.dropped_requests = 0
        self.total_wait_time = 0
        self.busy_time = 0
        self.buffer_usage = []
        self.process_usage = []

    def process_request(self, request):
        """Начало обработки заявки"""
        request.start_time = self.current_time
        request.finish_time = self.current_time + PROCESSING_TIME
        heapq.heappush(self.processor, request)

    def step(self, new_request=None):
        """Шаг моделирования"""
        # Завершаем обработку заявок
        while self.processor and self.processor[0].finish_time <= self.current_time:
            finished_request = heapq.heappop(self.processor)
            self.processed_requests += 1
            self.total_wait_time += finished_request.start_time - finished_request.arrival_time

        # Добавляем новую заявку
        if new_request:
            if len(self.processor) < MAX_PROCESSES:
                self.process_request(new_request)
            elif len(self.queue) < QUEUE_SIZE:
                heapq.heappush(self.queue, new_request)
            else:
                # Если очередь заполнена, проверяем приоритет
                lowest_priority_request = self.queue[-1]
                if new_request.priority > lowest_priority_request.priority:
                    heapq.heappop(self.queue)
                    heapq.heappush(self.queue, new_request)
                else:
                    self.dropped_requests += 1

        # Перемещаем заявки из очереди в процессор
        while len(self.processor) < MAX_PROCESSES and self.queue:
            next_request = heapq.heappop(self.queue)
            self.process_request(next_request)

        # Сохраняем данные о занятости ресурсов
        self.buffer_usage.append(len(self.queue))
        self.process_usage.append(len(self.processor))

        # Учитываем занятость процессора
        if self.processor:
            self.busy_time += PROCESSING_TIME

    def run(self, max_time=10, max_requests=100000000):
        """Запуск моделирования"""
        while self.current_time < max_time and self.total_requests < max_requests:
            # Генерация новой заявки
            interarrival_time = generate_hyperexponential()
            self.current_time += interarrival_time
            new_request = Request(self.current_time, generate_priority())
            self.total_requests += 1
            self.step(new_request)

        # Расчёт метрик
        efficiency = self.processed_requests / self.total_requests if self.total_requests > 0 else 0
        avg_wait_time = self.total_wait_time / self.processed_requests if self.processed_requests > 0 else 0

        return {
            "total_requests": self.total_requests,
            "processed_requests": self.processed_requests,"dropped_requests": self.dropped_requests,
            "total_wait_time": self.total_wait_time,
            "avg_wait_time": avg_wait_time,
            "busy_time": self.busy_time,
            "efficiency": efficiency,
            "buffer_usage": self.buffer_usage,
            "process_usage": self.process_usage,
        }

# Основной код
if __name__ == "__main__":
    system = System()
    stats = system.run(max_time=10, max_requests=100)

    # Вывод статистики
    print("СТАТИСТИКА:")
    print(f"Общее число заявок: {stats['total_requests']}")
    print(f"Обработано заявок: {stats['processed_requests']}")
    print(f"Отброшено заявок: {stats['dropped_requests']}")
    print(f"Общее время ожидания: {stats['total_wait_time']:.3f} сек")
    print(f"Среднее время ожидания: {stats['avg_wait_time']:.3f} сек")
    print(f"Суммарное время занятости процессора: {stats['busy_time']:.3f} сек")
    print(f"Эффективность системы: {stats['efficiency']:.2%}")

    # График занятости
    time_points = range(len(stats['buffer_usage']))
    plt.figure(figsize=(12, 6))
    plt.bar(time_points, stats['buffer_usage'], width=0.4, label="Занятость очереди")
    plt.bar(time_points, stats['process_usage'], width=0.4, label="Занятость процессов", alpha=0.7)
    plt.title("Занятость очереди")
    plt.xlabel("Шаги времени")
    plt.ylabel("Количество заявок")
    plt.legend()
    plt.grid()
    plt.show()
