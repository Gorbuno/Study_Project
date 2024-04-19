import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

# Функция для генерации многоугольников
def generate_polygons(n, min_vertices=3, max_vertices=10):
    polygons = []
    for _ in range(n):
        num_vertices = np.random.randint(min_vertices, max_vertices+1)
        vertices = np.random.rand(num_vertices, 3)
        polygons.append(vertices)
    return polygons

# Функция для определения пересечения между многоугольником и сканирующей строкой
def find_intersections(polygon, y):
    intersections = []
    for i in range(len(polygon)):
        p1 = polygon[i]
        p2 = polygon[(i+1) % len(polygon)]
        if min(p1[1], p2[1]) <= y <= max(p1[1], p2[1]):
            x = p1[0] + (p2[0] - p1[0]) * (y - p1[1]) / (p2[1] - p1[1])
            intersections.append(x)
    intersections.sort()
    return intersections

# Функция для вычисления глубину (z-координату) пикселя
def compute_z(polygon, x, y):
    return polygon[0][2]

# Функция для визуализации многоугольников с использованием z-буфера
def visualize_polygons(polygons, screen_width, screen_height):
    # Инициализация z-буфера и буфера кадра
    z_buffer = np.full((screen_width, screen_height), np.inf)
    frame_buffer = np.zeros((screen_width, screen_height, 3))
    
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    
    for polygon in polygons:
        for y in range(screen_height):
            intersections = find_intersections(polygon, y)
            if intersections:
                for x in range(int(intersections[0]), int(intersections[1])):
                    z = compute_z(polygon, x, y)
                    if z < z_buffer[x, y]:
                        z_buffer[x, y] = z
                        frame_buffer[x, y] = [1, 1, 1] # Предполагаем, что цвет многоугольника белый
    
    # Визуализация многоугольника
    for polygon in polygons:
        poly3d = [polygon.tolist()]
        ax.add_collection3d(Poly3DCollection(poly3d, facecolors='white', linewidths=1, edgecolors='r', alpha=.25))
    
    plt.show()

# Генерация 5 многоугольников
polygons = generate_polygons(5)

# Визуализация многоугольников
visualize_polygons(polygons, 800, 600)
