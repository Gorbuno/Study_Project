package tools;

import dto.MyObject;
import dto.Subject;

import javax.swing.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class IoTools {
    private IoTools() {}
    public static void saveAccessMatrixToFile(AccessTableModel tableModel, String fileName) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            List<Subject> subjects = tableModel.getSubjects();
            List<MyObject> myObjects = tableModel.getObjects();
            for (Subject subject : subjects) {
                List<String> accessibleObjects = new ArrayList<>();
                for (MyObject myObject : myObjects) {
                    String accessRight = tableModel.findAccessRight(subject.getName(), myObject.getName());
                    if (!"0".equals(accessRight)) {
                        accessibleObjects.add(myObject.getName());
                    } else {
                        accessibleObjects.add(myObject.getName() + "(нет доступа)");
                    }
                }
                String objectsAccess = String.join("-", accessibleObjects);
                writer.write(subject.getName() + ": " + objectsAccess + "\n");
            }

            JOptionPane.showMessageDialog(null,
                    "Matrix is save in " + fileName);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void loadAccessMatrixFromFile(AccessTableModel tableModel, String fileName) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(":");
                if (parts.length == 2) {
                    String subjectName = parts[0];
                    String[] objects = parts[1].split("-");
                    Subject subject = tableModel.findSubjectByName(subjectName);
                    if (subject == null) {
                        subject = new Subject(subjectName);
                        tableModel.getSubjects().add(subject);
                    }

                    for (var obj : objects) {
                        String objectName = obj.replace("(нет доступа)", "").trim();
                        MyObject myObject = tableModel.findObjectByName(objectName);
                        if (myObject == null) {
                            myObject = new MyObject(objectName);
                            tableModel.getObjects().add(myObject);
                        }
                        if (!obj.contains("(нет доступа)")) {
                            tableModel.grantAccessRight(subject, myObject);
                        }
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

