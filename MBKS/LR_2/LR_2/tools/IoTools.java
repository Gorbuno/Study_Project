package tools;

import dto.AccessRight;
import dto.MyObject;
import dto.Subject;

import javax.swing.*;
import java.io.*; // Импорт классов для работы с вводом-выводом
import java.util.ArrayList;
import java.util.List;

public class IoTools { // Класс для системы контроля доступа

    private IoTools() {
    }
    public static void saveAccessMatrixToFile(AccessTableModel tableModel, String fileName) { // Метод для сохранения матрицы доступа в файл
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) { // Создание объекта BufferedWriter
            // Получаем список всех субъектов
            List<Subject> subjects = tableModel.getSubjects();
            // Получаем список всех объектов
            List<MyObject> myObjects = tableModel.getObjects();

            // Проходим по каждому субъекту
            for (Subject subject : subjects) {
                // Создаем список для хранения объектов, к которым у субъекта есть доступ
                List<String> accessibleObjects = new ArrayList<>();

                // Проходим по каждому объекту
                for (MyObject myObject : myObjects) {
                    // Проверяем, имеет ли субъект доступ к объекту
                    String accessRight = tableModel.findAccessRight(subject.getName(), myObject.getName());
                    // Если доступ есть, добавляем имя объекта в список
                    if (!"0".equals(accessRight)) {
                        accessibleObjects.add(myObject.getName());
                    } else {
                        // Если доступа нет, добавляем имя объекта в список с особым обозначением
                        accessibleObjects.add(myObject.getName() + "(нет доступа)");
                    }
                }

                // Объединяем имена объектов в одну строку, разделяя их символом "-"
                String objectsAccess = String.join("-", accessibleObjects);

                // Записываем в файл строку вида "столбец1: столбец2 - столбец3 - ..."
                writer.write(subject.getName() + ": " + objectsAccess + "\n");
            }

            JOptionPane.showMessageDialog(null,
                    "Matrix is save in " + fileName); // Отображение сообщения успешной записи

        } catch (IOException e) { // Обработка исключений
            e.printStackTrace(); // Вывод информации об исключении
        }
    }

    /**
     * почему мы не добавляем в список субъект из файла и объект?
     **/
    public static void loadAccessMatrixFromFile(AccessTableModel tableModel, String fileName) { // Метод для загрузки матрицы доступа из файла
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) { // Создание объекта BufferedReader
            String line; // Переменная для хранения строки
            while ((line = reader.readLine()) != null) { // Чтение строк из файла
                String[] parts = line.split(":"); // Разделение строки на объекты и субъект
                if (parts.length == 2) { // Проверка количества частей
                    String subjectName = parts[0]; // Имя субъекта
                    String[] objects = parts[1].split("-"); // Разделение строки на объекты

                    // Поиск субъекта и объекта по именам
                    Subject subject = tableModel.findSubjectByName(subjectName);

                    // Если субъект не найден, создаем его и добавляем в список
                    if (subject == null) {
                        subject = new Subject(subjectName);
                        tableModel.getSubjects().add(subject);
                    }

                    for (var obj : objects) {
                        // Удаляем пометку "(нет доступа)" из имени объекта, если она есть
                        String objectName = obj.replace("(нет доступа)", "").trim();
                        MyObject myObject = tableModel.findObjectByName(objectName);
                        if (myObject == null) {
                            myObject = new MyObject(objectName);
                            tableModel.getObjects().add(myObject);
                        }
                        // Добавляем право доступа только если объект не имеет пометки "(нет доступа)"
                        if (!obj.contains("(нет доступа)")) {
                            tableModel.grantAccessRight(subject, myObject);
                        }
                    }
                }
            }
        } catch (IOException e) { // Обработка исключений
            e.printStackTrace(); // Вывод информации об исключении
        }
    }
}

