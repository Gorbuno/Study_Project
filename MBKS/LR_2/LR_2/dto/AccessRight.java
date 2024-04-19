package dto;

import dto.MyObject;

import java.util.Objects;

public class AccessRight { // Класс для представления права доступа
    private Subject subject; // Субъект, которому предоставляется право
    private MyObject myObject; // Объект, к которому предоставляется право

    public AccessRight(Subject subject, MyObject myObject) { // Конструктор класса
        this.subject = subject; // Инициализация субъекта
        this.myObject = myObject; // Инициализация объекта
    }

    public Subject getSubject() { // Метод для получения субъекта
        return subject; // Возвращает субъект
    }

    public MyObject getObject() { // Метод для получения объекта
        return myObject; // Возвращает объект
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AccessRight that = (AccessRight) o;
        return subject.getName().equals(that.subject.getName())
                && myObject.getName().equals(that.myObject.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(subject.getName(), myObject.getName());
    }
}
