package dto;
import java.util.Objects;

public class AccessRight {
    private Subject subject;
    private MyObject myObject;

    public AccessRight(Subject subject, MyObject myObject) {
        this.subject = subject;
        this.myObject = myObject;
    }

    public Subject getSubject() {
        return subject;
    }

    public MyObject getObject() {
        return myObject;
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
