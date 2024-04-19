
import matplotlib.pyplot as plt
import numpy as np
import time
#генерация отрезков 
np.random.seed(int(time.time()))
num_segments = 10
segments = np.random.rand (num_segments, 2, 2)
# Определение пространственных точек
select = int (input ("Выберите один из следующих вариантов: 1 -- ввести координаты окна в ручную;     2 -- оставить координаты окна по умолчанию: "))
if (select == 1):
 # Задаем прямоугольное окно
  x1 = float(input("Введите x-координату верхнего левого угла окна: "))
  y1 = float(input("Введите y-координату верхнего левого угла окна: "))
  x2 = float(input("Введите x-координату нижнего правого угла окна: "))
  y2 = float(input("Введите y-координату нижнего правого угла окна: "))
  window = np.array([[x1, y1], [x2, y2]])
else :
  window = np.array([[0.25, 0.25],[0.75, 0.75]])

#бинарный поиск 
intersections = []
for segment in segments:
    if ((segment[:, 0] >= window[0, 0]).any() and (segment[:, 0] <= window[1, 0]).any() and
        (segment[:, 1] >= window[0, 1]).any() and (segment[:, 1] <= window[1, 1]).any()):
      intersections.append(True)
    else:
      intersections.append(False)
        

#визулизация 
plt.figure()
plt.plot([window[0,0],window[1,0],window[1,0],window[0,0],window[0,0]], 
         [window[0,1],window[0,1],window[1,1],window[1,1],window[0,1]], 'r-')
for i, segment in enumerate (segments):
    if intersections[i]:
      plt.plot(segment[:,0], segment[:,1], 'g-')
    else :
      plt.plot(segment[:,0], segment[:,1], 'b-')
plt.show()