
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
import numpy as np

def rotation_matrix(axis, theta):
    axis = np.asarray(axis)
    axis = axis / np.sqrt(np.dot(axis, axis))
    a = np.cos(theta / 2.0)
    b, c, d = -axis * np.sin(theta / 2.0)
    return np.array([[a*a+b*b-c*c-d*d, 2*(b*c-a*d), 2*(b*d+a*c)],
                     [2*(b*c+a*d), a*a+c*c-b*b-d*d, 2*(c*d-a*b)],
                     [2*(b*d-a*c), 2*(c*d+a*b), a*a+d*d-b*b-c*c]])

v = np.array([[1, 1, -1], [1, -1, -1], [-1, -1, -1], [-1, 1, -1], [0, 0, 1]])

# Создаем два подграфика
fig, (ax1, ax2) = plt.subplots(1, 2, subplot_kw=dict(projection='3d'))

ax1.scatter(v[:, 0], v[:, 1], v[:, 2])

faces = [[v[j] for j in face] for face in [[0, 1, 4], [1, 2, 4], [2, 3, 4], [3, 0, 4]]]
ax1.add_collection3d(Poly3DCollection(faces, facecolors='cyan', linewidths=1, edgecolors='r'))

theta = np.radians(int(input("Введите угол: "))) 
select = int(input("Выберите один из следующих вариантов: 0 -- поворот вокруг оси х; 1 -- поворот вокруг оси у; 2 -- поворот вокруг оси z: "))

rot = rotation_matrix([select == i for i in range(3)], theta)
v_rot = np.dot(v, rot.T)

ax2.scatter(v_rot[:, 0], v_rot[:, 1], v_rot[:, 2])

faces_rot = [[v_rot[j] for j in face] for face in [[0, 1, 4], [1, 2, 4], [2, 3, 4], [3, 0, 4]]]
ax2.add_collection3d(Poly3DCollection(faces_rot, facecolors='cyan', linewidths=1, edgecolors='r', alpha=0.5))

ax1.auto_scale_xyz([-2, 2], [-2, 2], [-2, 2])
ax2.auto_scale_xyz([-2, 2], [-2, 2], [-2, 2])

plt.show()