import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import make_interp_spline, BSpline

# Функции для создания различных линий
def line(x, y):
    return x + y

def parabola(x, y):
    return x**2 + y**2

def cubic_spline(x, y):
    x = np.array(x)
    y = np.array(y)
    spline = make_interp_spline(x, y, k=3)
    return spline(x)

def bezier_spline(x, y):
    x = np.array(x)
    y = np.array(y)
    spline = make_interp_spline(x, y, k=3)
    return spline(x)

# Функция для билинейного преобразования
def bilinear_interpolation(a, b, pts):
    i = sorted(pts)
    (a1, b1, x11), (_a1, b2, x12), (a2, _b1, x21), (_a2, _b2, x22) = i
    if a1 != _a1 or a2 != _a2 or b1 != _b1 or b2 != _b2:
        print("The given points do not form a rectangle")
    if not a1 <= a <= a2 or not b1 <= b <= b2:
        print("The (a, b) coordinates are not within the rectangle")
    Y = (
        x11 * (a2 - a) * (b2 - b)
        + x21 * (a - a1) * (b2 - b)
        + x12 * (a2 - a) * (b - b1)
        + x22 * (a - a1) * (b - b1)
    ) / ((a2 - a1) * (b2 - b1) + 0.0)
    return Y

# Запрашиваем выбор первой линии
line1_type = int(input("Выберите тип первой линии (1 - отрезок, 2 - парабола, 3 - кубический сплайн, 4 - сплайн Безье): "))
if line1_type == 3 or line1_type == 4:
    x1_values = input("Введите значения x для построения первой линии, разделенные пробелом. Значения x должны быть строго возрастающими: ")
    y1_values = input("Введите значения y для построения первой линии, соответствующие введенным значениям x, разделенные пробелом: ")
    line1_x = list(map(float, x1_values.split()))
    line1_y = list(map(float, y1_values.split()))
    if line1_type == 3:
        Z1 = cubic_spline(line1_x, line1_y)
    elif line1_type == 4:
        Z1 = bezier_spline(line1_x, line1_y)
else:
    line1_values = list(map(float, input("Введите значения для построения первой линии: ").split()))
    Z1 = line1_values

# Запрашиваем выбор второй линии
line2_type = int(input("Выберите тип второй линии (1 - отрезок, 2 - парабола, 3 - кубический сплайн, 4 - сплайн Безье): "))
if line2_type == 3 or line2_type == 4:
    x2_values = input("Введите значения x для построения второй линии, разделенные пробелом. Значения x должны быть строго возрастающими: ")
    y2_values = input("Введите значения y для построения второй линии, соответствующие введенным значениям x, разделенные пробелом: ")
    line2_x = list(map(float, x2_values.split()))
    line2_y = list(map(float, y2_values.split()))
    if line2_type == 3:
        Z2 = cubic_spline(line2_x, line2_y)
    elif line2_type == 4:
        Z2 = bezier_spline(line2_x, line2_y)
else:
    line2_values = list(map(float, input("Введите значения для построения второй линии: ").split()))
    Z2 = line2_values

# Создание массивов x и y
x = np.linspace(-2, 2, 400)
y = np.linspace(-2, 2, 400)

# Создание билинейной поверхности
X, Y = np.meshgrid(x, y)
if line1_type == 1:
    Z1 = line(X, Y)
elif line1_type == 2:
    Z1 = parabola(X, Y)
elif line1_type == 3 or line1_type == 4:
    Z1 = cubic_spline(x, y)
if line2_type == 1:
    Z2 = line(X, Y)
elif line2_type == 2:
    Z2 = parabola(X, Y)
elif line2_type == 3 or line2_type == 4:
    Z2 = cubic_spline(x, y)

if (((line1_type == 1) or (line1_type == 2)) and ((line2_type == 1) or (line2_type == 2))):
    Z = Z1 + Z2
else:
    Z = Z1 + np.reshape(Z2, (400, 1))

# Визуализация поверхности
fig = plt.figure()
ax = plt.axes(projection='3d')
ax.plot_surface(X, Y, Z, linewidth=0, antialiased=False)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()

# Запрос выбора поверхности
surface_axis = int(input("Выберите ось поверхности (1 - x, 2 - y): "))

# Запрос угла поворота
angle = float(input("Введите угол поворота: "))

# Поворот поверхности
if surface_axis == 1:
    Z_rotated = Z * np.cos(angle) + Y * np.sin(angle)
elif surface_axis == 2:
    Z_rotated = Z * np.cos(angle) + X * np.sin(angle)

# Визуализация поверхности
fig = plt.figure()
ax = plt.axes(projection='3d')
surface = ax.plot_surface(X, Y, Z_rotated, linewidth=0, antialiased=False)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()
