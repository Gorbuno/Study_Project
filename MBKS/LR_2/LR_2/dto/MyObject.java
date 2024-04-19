package dto;

public class MyObject { // Класс для представления объекта
    private String name; // Имя объекта

    public MyObject(String name) { // Конструктор класса
        this.name = name; // Инициализация имени объекта
    }

    public String getName() { // Метод для получения имени объекта
        return name; // Возвращает имя объекта
    }

    public void setName(String name) {
        this.name = name;
    }
    @Override
    public String toString() {return name;}
}
