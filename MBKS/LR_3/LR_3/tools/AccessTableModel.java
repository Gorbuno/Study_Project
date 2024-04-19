package tools;

import dto.AccessRight;
import dto.MyObject;
import dto.Subject;

import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class AccessTableModel extends AbstractTableModel {
    private List<Subject> subjects;
    private List<MyObject> myObjects;
    private Set<AccessRight> accessRights;

    public AccessTableModel() {
        this.subjects = new ArrayList<>();
        this.myObjects = new ArrayList<>();
        this.accessRights = new HashSet<>();
    }

    public int addSubject(Subject subject) {
        if (subject.getName().length() > 1){
            JOptionPane.showMessageDialog(null,
                    "Subject "+subject.getName()+" name is long.", "Error", JOptionPane.ERROR_MESSAGE);
            return 1;
        }else{
        subjects.add(subject);
        return 0;}
    }
    public int addObject(MyObject myObject) {
        if (myObject.getName().length() > 1){
            JOptionPane.showMessageDialog(null,
                    "Object "+myObject.getName()+" name is long.", "Error", JOptionPane.ERROR_MESSAGE);
            return 1;
        }else{
        myObjects.add(myObject);
        return 0;}
    }
    public void grantAccessRight(Subject subject, MyObject myObject) {
        AccessRight accessRight = new AccessRight(subject, myObject);
        accessRights.add(accessRight);
    }
    public void removeSubject(String name) {
        subjects.removeIf(subject -> subject.getName().equals(name));
    }
    public void removeObject(String name) {
        myObjects.removeIf(myObject -> myObject.getName().equals(name));
    }
    public void removeAccessRight(String subjectName, String objectName) {
        accessRights.removeIf(accessRight ->
                accessRight.getSubject().getName().equals(subjectName) &&
                        accessRight.getObject().getName().equals(objectName)
        );
    }
    public MyObject[] getAllObjects() {
        return myObjects.toArray(new MyObject[0]);
    }
    @Override
    public int getRowCount() {
        return subjects.size();
    }
    @Override
    public int getColumnCount() {
        return myObjects.size() + 1;
    }
    @Override
    public String getColumnName(int column) {
        if (column == 0) {
            return "Subject";
        }
        return myObjects.get(column - 1).getName();
    }
    @Override
    public String getValueAt(int rowIndex, int columnIndex) {
        if (columnIndex == 0) {
            return subjects.get(rowIndex).getName();
        }
        String subjectName = subjects.get(rowIndex).getName();
        String objectName = myObjects.get(columnIndex - 1).getName();
        return findAccessRight(subjectName, objectName);
    }
    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return false;
    }
    @Override
    public void setValueAt(Object aValue, int rowIndex, int columnIndex) {}
    public List<Subject> getSubjects() {return subjects;}
    public List<MyObject> getObjects() {return myObjects; }
    public Set<AccessRight> getAccessRights() {return accessRights;}
    public String findAccessRight(String subjectName, String objectName) {
        for (AccessRight accessRight : accessRights) {
            if (accessRight.getSubject().getName().equals(subjectName) &&
                    accessRight.getObject().getName().equals(objectName)) { return "Доступен"; }
        }
        return "0";
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
    public boolean subjectExists(String name) {
        for (Subject subject : subjects) {
            if (subject.getName().equals(name)) { return true; }
        }
        return false;
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
            } else { System.out.println("A subject with the new name already exists."); }
        } else { System.out.println("Subject not found."); }
    }
    public void renameObject(String oldName, String newName) {
        MyObject objectToRename = findObjectByName(oldName);
        if (objectToRename != null) {
            if (!objectExists(newName)) {
                objectToRename.setName(newName);
                updateObjectReferences(oldName, newName);
            } else { System.out.println("An object with the new name already exists."); }
        } else { System.out.println("Object not found."); }
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
