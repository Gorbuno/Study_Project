package tools;

import dto.AccessRight;
import dto.MyObject;
import dto.Subject;

import javax.swing.table.AbstractTableModel; // Импорт класса AbstractTableModel для создания модели таблицы
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List; // Импорт интерфейса List для работы со списками
import java.util.Set;

public class AccessTableModel extends AbstractTableModel { // Определение класса AccessMatrixTableModel, расширяющего AbstractTableModel
    private List<Subject> subjects; // Список субъектов
    private List<MyObject> myObjects; // Список объектов
    private Set<AccessRight> accessRights; // Список прав доступа

    public AccessTableModel() { // Конструктор класса
        this.subjects = new ArrayList<Subject>(); // Инициализация списка субъектов
        this.myObjects = new ArrayList<>(); // Инициализация списка объектов
        this.accessRights = new HashSet<>(); // Инициализация списка прав доступа
    }

    public void addSubject(Subject subject) { // Метод для добавления субъекта
        subjects.add(subject); // Добавляет субъект в список
    }

    public void addObject(MyObject myObject) { // Метод для добавления объекта
        myObjects.add(myObject); // Добавляет объект в список
    }

    public void grantAccessRight(Subject subject, MyObject myObject) { // Метод для предоставления права доступа
        AccessRight accessRight = new AccessRight(subject, myObject); // Создание нового права доступа
        accessRights.add(accessRight); // Добавление права доступа в список
    }


    public void removeSubject(String name) { // Метод для удаления субъекта
        subjects.removeIf(subject -> subject.getName().equals(name)); // Удаление субъекта по имени
    }

    public void removeObject(String name) { // Метод для удаления объекта
        myObjects.removeIf(myObject -> myObject.getName().equals(name)); // Удаление объекта по имени
    }

    public void removeAccessRight(String subjectName, String objectName) { // Метод для удаления права доступа
        accessRights.removeIf(accessRight -> // Удаление права доступа по имени субъекта и объекта
                accessRight.getSubject().getName().equals(subjectName) &&
                        accessRight.getObject().getName().equals(objectName)
        );
    }

    @Override
    public int getRowCount() { // Метод для получения количества строк в таблице
        return subjects.size(); // Возвращает количество субъектов
    }

    @Override
    public int getColumnCount() { // Метод для получения количества столбцов в таблице
        return myObjects.size() + 1; // Возвращает количество объектов плюс один столбец для имен субъектов
    }

    @Override
    public String getColumnName(int column) { // Метод для получения имени столбца
        if (column == 0) { // Если столбец - первый
            return "Subject"; // Возвращает "Subject"
        }
        return myObjects.get(column - 1).getName(); // Возвращает имя объекта
    }

    @Override
    public String getValueAt(int rowIndex, int columnIndex) { // Метод для получения значения ячейки
        if (columnIndex == 0) { // Если столбец - первый
            return subjects.get(rowIndex).getName(); // Возвращает имя субъекта
        }
        // Используем метод findAccessRight для получения права доступа
        String subjectName = subjects.get(rowIndex).getName(); // Получаем имя субъекта
        String objectName = myObjects.get(columnIndex - 1).getName(); // Получаем имя объекта
        return findAccessRight(subjectName, objectName); // Возвращает найденное право доступа
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) { // Метод для определения, является ли ячейка редактируемой
        // Все ячейки нередактируемы
        return false;
    }

    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) { // Метод для установки значения ячейки
    }

    public List<Subject> getSubjects() { // Метод для получения списка субъектов
        return subjects; // Возвращает список субъектов
    }

    public List<MyObject> getObjects() { // Метод для получения списка объектов
        return myObjects; // Возвращает список объектов
    }

    public Set<AccessRight> getAccessRights() { // Метод для получения списка прав доступа
        return accessRights; // Возвращает список рав доступа
    }

    public String findAccessRight(String subjectName, String objectName) { // Метод для поиска права доступа
        for (AccessRight accessRight : accessRights) { // Проход по всем правам доступа
            if (accessRight.getSubject().getName().equals(subjectName) && // Сравнение имени субъекта
                    accessRight.getObject().getName().equals(objectName)) { // Сравнение имени объекта
                return "Доступен"; // Возвращает найденное право доступа
            }
        }
        return "0"; // Возвращает "0", если права доступа не найдены
    }


    public Subject findSubjectByName(String name) {
        for (Subject subject : subjects) {
            if (subject.getName().equals(name)) {
                return subject;
            }
        }
        return null;
    }

    public MyObject findObjectByName(String name) {
        for (MyObject myObject : myObjects) {
            if (myObject.getName().equals(name)) {
                return myObject;
            }
        }
        return null;
    }

    public boolean subjectExists(String name) { // Метод для проверки существования субъекта
        for (Subject subject : subjects) { // Проход по всем субъектам
            if (subject.getName().equals(name)) { // Сравнение имен
                return true; // Субъект найден
            }
        }
        return false; // Субъект не найден
    }

    public boolean objectExists(String name) {
        for (MyObject myObject : myObjects) {
            if (myObject.getName().equals(name)) {
                return true;
            }
        }
        return false;
    }

    public void renameSubject(String oldName, String newName) {
        Subject subjectToRename = findSubjectByName(oldName);
        if (subjectToRename != null) {
            if (!subjectExists(newName)) {
                subjectToRename.setName(newName);
                updateSubjectReferences(oldName, newName);
            } else {
                System.out.println("A subject with the new name already exists.");
            }
        } else {
            System.out.println("Subject not found.");
        }
    }

    public void renameObject(String oldName, String newName) {
        MyObject objectToRename = findObjectByName(oldName);
        if (objectToRename != null) {
            if (!objectExists(newName)) {
                objectToRename.setName(newName);
                updateObjectReferences(oldName, newName);
            } else {
                System.out.println("An object with the new name already exists.");
            }
        } else {
            System.out.println("Object not found.");
        }
    }

    private void updateSubjectReferences(String oldName, String newName) {
        for (AccessRight accessRight : accessRights) {
            if (accessRight.getSubject().getName().equals(oldName)) {
                accessRight.getSubject().setName(newName);
            }
        }
    }

    private void updateObjectReferences(String oldName, String newName) {
        for (AccessRight accessRight : accessRights) {
            if (accessRight.getObject().getName().equals(oldName)) {
                accessRight.getObject().setName(newName);
            }
        }
    }
}
