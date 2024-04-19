
import numpy as np
from scipy.interpolate import splprep, splev
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
k = int (input ("Введите угол: "))

# Определение пространственных точек
select = int (input ("Выберите один из следующих вариантов: 1 -- ввести координаты сплайна в ручную;     2 -- оставить координаты сплайна по умолчанию: "))
if (select == 1):
  user_input = input("Введите координаты 1 точки: ")
  numbers = [float(num) for num in user_input.split()]
  np_array_1 = np.array(numbers)
  user_input = input("Введите координаты 2 точки: ")
  numbers = [float(num) for num in user_input.split()]
  np_array_2 = np.array(numbers)
  user_input = input("Введите координаты 3 точки: ")
  numbers = [float(num) for num in user_input.split()]
  np_array_3 = np.array(numbers)
  user_input = input("Введите координаты 4 точки: ")
  numbers = [float(num) for num in user_input.split()]
  np_array_4 = np.array(numbers)
  user_input = input("Введите координаты 5 точки: ")
  numbers = [float(num) for num in user_input.split()]
  np_array_5 = np.array(numbers)
          
  points = np.array([np_array_1, np_array_2, np_array_3, np_array_4, np_array_5])    
else :
  points = np.array([[0, 0, 0], [1, 2, 3], [2, 3, 1], [3, 2, 2], [4, 1, 3]])


x_points = points[:,0]
y_points = points[:,1]
z_points = points[:,2]

# print (points)
# Создание кривой
tck, u = splprep(points.transpose(), u=None, s=0.0)
u_new = np.linspace(u.min(), u.max(), 1000)
x_new, y_new, z_new = splev(u_new, tck, der=0)

# Поворот вокруг оси X
theta = np.radians(k)
rx = np.array([[1, 0, 0], [0, np.cos(theta), -np.sin(theta)], [0, np.sin(theta), np.cos(theta)]])
rotated_points = np.dot(rx, points.transpose()).transpose()

# Поворот вокруг оси Y
theta = np.radians(k)
ry = np.array([[np.cos(theta), 0, np.sin(theta)], [0, 1, 0], [-np.sin(theta), 0, np.cos(theta)]])
rotated_points = np.dot(ry, rotated_points.transpose()).transpose()

# Построение кривых
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(points[:,0], points[:,1], points[:,2], 'bo-')
ax.plot(rotated_points[:,0], rotated_points[:,1], rotated_points[:,2], 'ro-')
plt.show()