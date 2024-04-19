package dto;

public class Subject { // Класс для представления субъекта
    private String name; // Имя субъекта

    public Subject(String name) { // Конструктор класса
        this.name = name; // Инициализация имени субъекта
    }

    public String getName() { // Метод для получения имени субъекта
        return name; // Возвращает имя субъекта
    }
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {return name;}

}
