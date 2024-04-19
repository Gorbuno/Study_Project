import dto.MyObject;
import dto.Subject;
import tools.AccessTableModel;
import tools.IoTools;

import javax.swing.*;
import javax.swing.table.TableColumn;
import java.awt.*;
public class AccessControlGUI extends JFrame {
    private JTextArea subjectNameField, objectNameField;
    private JButton addSubjectButton, addObjectButton;
    private JButton grantAccessRightButton, removeAccessRightButton, createSubjectWithAccessButton;
    private JButton grantAllAccessButton, removeAllAccessButton;
    private JButton saveAccessMatrixButton, loadAccessMatrixButton;
    private JButton removeSubjectButton, removeObjectButton;
    private JButton renameSubjectButton, renameObjectButton;
    private JTable accessTable;
    private AccessTableModel tableModel;

    public AccessControlGUI() {
        setLayout(new GridLayout(1, 2));
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Admin Programm");

        subjectNameField = new JTextArea();
        objectNameField = new JTextArea();

        addSubjectButton = new JButton("Add");
        removeSubjectButton = new JButton("Remove");
        renameSubjectButton = new JButton("Rename");

        addObjectButton = new JButton("Add");
        removeObjectButton = new JButton("Remove");
        renameObjectButton = new JButton("Rename");

        createSubjectWithAccessButton = new JButton("Create");
        grantAccessRightButton = new JButton("Grant");
        grantAllAccessButton = new JButton("Grant All");
        removeAccessRightButton = new JButton("Remove");
        removeAllAccessButton = new JButton("Remove All");
        saveAccessMatrixButton = new JButton("Save");
        loadAccessMatrixButton = new JButton("Load");

        tableModel = new AccessTableModel();
        accessTable = new JTable(tableModel);
        setTableBounds();

        tableModel.addTableModelListener(e -> refreshTable());

        JPanel panelInput = new JPanel();
        panelInput.setLayout(new BoxLayout(panelInput, BoxLayout.X_AXIS));
        panelInput.add(new JLabel("Subject Name:"));
        panelInput.add(subjectNameField);
        panelInput.add(new JLabel("Object Name:"));
        panelInput.add(objectNameField);

        JPanel PanelSubject = new JPanel();
        PanelSubject.setLayout(new BoxLayout(PanelSubject, BoxLayout.X_AXIS));
        PanelSubject.add(new JLabel("Action to Subject:"));
        PanelSubject.add(addSubjectButton);
        PanelSubject.add(removeSubjectButton);
        PanelSubject.add(renameSubjectButton);

        JPanel panelObject = new JPanel();
        panelObject.setLayout(new BoxLayout(panelObject, BoxLayout.X_AXIS));
        panelObject.add(new JLabel("Action to Object:"));
        panelObject.add(addObjectButton);
        panelObject.add(removeObjectButton);
        panelObject.add(renameObjectButton);

        JPanel panelAccessRight = new JPanel();
        panelAccessRight.setLayout(new BoxLayout(panelAccessRight, BoxLayout.X_AXIS));
        panelAccessRight.add(new JLabel("Action to Access Right:"));
        panelAccessRight.add(createSubjectWithAccessButton);
        panelAccessRight.add(grantAccessRightButton);
        panelAccessRight.add(removeAccessRightButton);

        JPanel panelAccessRight2 = new JPanel();
        panelAccessRight2.setLayout(new BoxLayout(panelAccessRight2, BoxLayout.X_AXIS));
        panelAccessRight2.add(new JLabel("Action to Access Right to all object:"));
        panelAccessRight2.add(grantAllAccessButton);
        panelAccessRight2.add(removeAllAccessButton);

        JPanel panelMatrix = new JPanel();
        panelMatrix.setLayout(new BoxLayout(panelMatrix, BoxLayout.X_AXIS));
        panelMatrix.add(new JLabel("Action to Access matrix:"));
        panelMatrix.add(saveAccessMatrixButton);
        panelMatrix.add(loadAccessMatrixButton);

        Box buttonBox = Box.createVerticalBox();
        buttonBox.add(panelInput);
        buttonBox.add(PanelSubject);
        buttonBox.add(panelObject);
        buttonBox.add(panelAccessRight);
        buttonBox.add(panelAccessRight2);
        buttonBox.add(panelMatrix);

        add(buttonBox, BorderLayout.WEST);
        add(new JScrollPane(accessTable), BorderLayout.EAST);

        addSubjectButton.addActionListener(e -> addSubject());
        removeSubjectButton.addActionListener(e -> removeSubject());
        renameSubjectButton.addActionListener(e -> renameSubject());

        addObjectButton.addActionListener(e ->addObject());
        removeObjectButton.addActionListener(e -> removeObject());
        renameObjectButton.addActionListener(e -> renameObject());

        createSubjectWithAccessButton.addActionListener(e -> {
            String[] subjectNames = subjectNameField.getText().split("\n");
            String[] objectNames = objectNameField.getText().split("\n");
            createSubjectWithAccess( subjectNames, objectNames);
            subjectNameField.setText("");
            objectNameField.setText("");
            refreshTable();
        });
        grantAccessRightButton.addActionListener(e -> {
            String[] subjectNames = subjectNameField.getText().split("\n");
            String[] objectNames = objectNameField.getText().split("\n");
            grantAccessRight(subjectNames, objectNames);
            subjectNameField.setText("");
            objectNameField.setText("");
            refreshTable();
        });
        grantAllAccessButton.addActionListener(e -> grantAllAccess());
        removeAccessRightButton.addActionListener(e -> {
            String[] subjectNames = subjectNameField.getText().split("\n");
            String[] objectNames = objectNameField.getText().split("\n");
            removeAccessRight(subjectNames, objectNames);
            subjectNameField.setText("");
            objectNameField.setText("");
            refreshTable();
        });
        removeAllAccessButton.addActionListener(e -> removeAllAccess());

        saveAccessMatrixButton.addActionListener(e -> {
            IoTools.saveAccessMatrixToFile(tableModel, "access_rights.txt");
        });
        loadAccessMatrixButton.addActionListener(e -> {
            IoTools.loadAccessMatrixFromFile(tableModel, "access_rights.txt");
            refreshTable();
        });
    }

    public Subject createSubject(String subjectName) {
        Subject newSubject = new Subject(subjectName);

       if ( tableModel.addSubject(newSubject) == 0){
        return newSubject;}
       else return null;
    }
    public MyObject createObject(String objectName) {
        MyObject newObject = new MyObject(objectName);

        if (tableModel.addObject(newObject) == 0){
        return newObject;}
        else {return null;}
    }
    private void syncColumnModel() {
        var columnModel = accessTable.getColumnModel();
        var model = accessTable.getModel();
        while (columnModel.getColumnCount() > 0) {
            columnModel.removeColumn(columnModel.getColumn(0));
        }
        for (int i = 0; i < model.getColumnCount(); i++) {
            var col = new TableColumn(i);
            col.setHeaderValue(model.getColumnName(i));
            columnModel.addColumn(col);
        }
    }
    private void refreshTable(){
        syncColumnModel();
        accessTable.revalidate();
        accessTable.repaint();
    }
    private void setTableBounds() {
        accessTable.setRowHeight(25);
        for (int i = 0; i < accessTable.getColumnCount(); i++) {
            accessTable.getColumnModel().getColumn(i).setPreferredWidth(100);
        }
    }

    /**Action to Subject*/
    private void addSubject() {
        String subjectName = subjectNameField.getText();
        if (subjectName.length() == 1){
            if (subjectName.isEmpty()) {
                JOptionPane.showMessageDialog(null,
                        "Subject name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            if (tableModel.subjectExists(subjectName)) {
                JOptionPane.showMessageDialog(null,
                        "Subject name already exists.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            tableModel.addSubject(new Subject(subjectName));
            subjectNameField.setText("");
            refreshTable();}
    }
    private void removeSubject() {
        String subjectName = subjectNameField.getText();
        if (subjectName.isEmpty()) {
            JOptionPane.showMessageDialog(null, "Subject name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        tableModel.removeSubject(subjectName);
        subjectNameField.setText("");
        refreshTable();
    }
    private void renameSubject() {
        JFrame renameSubjectFrame = new JFrame("Rename Subject");
        renameSubjectFrame.setSize(300, 150);
        renameSubjectFrame.setLayout(new GridLayout(3, 2));
        renameSubjectFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JLabel oldNameLabel = new JLabel("Old Name:");
        JTextField oldNameField = new JTextField();
        JLabel newNameLabel = new JLabel("New Name:");
        JTextField newNameField = new JTextField();
        JButton renameButton = new JButton("Rename");

        renameButton.addActionListener(e -> {
            String oldName = oldNameField.getText();
            String newName = newNameField.getText();
            if (!oldName.isEmpty() && !newName.isEmpty() && newName.length() <= 1) {
                tableModel.renameSubject(oldName, newName);
                renameSubjectFrame.dispose();
            } else {
                JOptionPane.showMessageDialog(null, "Both fields must be filled.", "Error", JOptionPane.ERROR_MESSAGE);
            }

            refreshTable();
        });

        renameSubjectFrame.add(oldNameLabel);
        renameSubjectFrame.add(oldNameField);
        renameSubjectFrame.add(newNameLabel);
        renameSubjectFrame.add(newNameField);
        renameSubjectFrame.add(renameButton);
        renameSubjectFrame.setVisible(true);
    }

    /**Action to Object*/
    private void addObject() {
        String objectName = objectNameField.getText();
        if (objectName.length() == 1){
            if (objectName.isEmpty()) {
                JOptionPane.showMessageDialog(null,
                        "Object name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            if (tableModel.objectExists(objectName)) {
                JOptionPane.showMessageDialog(null,
                        "Object name already exists.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }
            tableModel.addObject(new MyObject(objectName));
            objectNameField.setText("");
            refreshTable();}
    }
    private void removeObject() {
        String objectName = objectNameField.getText();
        if (objectName.isEmpty()) {
            JOptionPane.showMessageDialog(null,
                    "Object name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        tableModel.removeObject(objectName);
        objectNameField.setText("");
        refreshTable();
    }
    private void renameObject() {
        JFrame renameObjectFrame = new JFrame("Rename Object");
        renameObjectFrame.setSize(300, 150);
        renameObjectFrame.setLayout(new GridLayout(3, 2));
        renameObjectFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JLabel oldNameLabel = new JLabel("Old Name:");
        JTextField oldNameField = new JTextField();
        JLabel newNameLabel = new JLabel("New Name:");
        JTextField newNameField = new JTextField();
        JButton renameButton = new JButton("Rename");

        renameButton.addActionListener(e -> {
            String oldName = oldNameField.getText();
            String newName = newNameField.getText();
            if (!oldName.isEmpty() && !newName.isEmpty()&& newName.length() <= 1) {
                tableModel.renameObject(oldName, newName);
                renameObjectFrame.dispose();
            } else {
                JOptionPane.showMessageDialog(null, "Both fields must be filled.", "Error", JOptionPane.ERROR_MESSAGE);
            }

            refreshTable();
        });

        renameObjectFrame.add(oldNameLabel);
        renameObjectFrame.add(oldNameField);
        renameObjectFrame.add(newNameLabel);
        renameObjectFrame.add(newNameField);
        renameObjectFrame.add(renameButton);
        renameObjectFrame.setVisible(true);

    }

    /**Action to Access Right*/
    public void createSubjectWithAccess(String[] subjectNames, String[] objectNames) {
        if (subjectNames.length == 0 || objectNames.length == 0) {
            JOptionPane.showMessageDialog(null,
                    "Subject or object names cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        for (String subjectName: subjectNames){
            Subject subject = tableModel.findSubjectByName(subjectName);
            if (subject == null) {
                subject = createSubject(subjectName);
                if (subject == null) continue;
            }

            for (String objectName : objectNames) {
                MyObject myObject = tableModel.findObjectByName(objectName);
                if (myObject == null) {
                    myObject = createObject(objectName);
                    if (myObject == null) continue;
                }
                tableModel.grantAccessRight(subject, myObject);
            }
        }
    }
    private void grantAccessRight(String[] subjectNames, String[] objectNames){
            if (subjectNames.length == 0 || objectNames.length == 0) {
                JOptionPane.showMessageDialog(null,
                        "Subject or object names cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
                return;
            }

            for (String subjectName : subjectNames) {
                Subject subject = tableModel.findSubjectByName(subjectName.trim());
                if (subject == null) {
                    JOptionPane.showMessageDialog(null,
                            "Subject not found: " + subjectName, "Error", JOptionPane.ERROR_MESSAGE);
                    continue;
                }

                for (String objectName : objectNames) {
                    MyObject myObject = tableModel.findObjectByName(objectName.trim());
                    if (myObject == null) {
                        JOptionPane.showMessageDialog(null,
                                "Object not found: " + objectName, "Error", JOptionPane.ERROR_MESSAGE);
                        continue;
                    }
                    tableModel.grantAccessRight(subject, myObject);
                }
            }
        }
    private void removeAccessRight(String[] subjectNames, String[] objectNames){
        if (subjectNames.length == 0 || objectNames.length == 0) {
            JOptionPane.showMessageDialog(null,
                    "Subject or object names cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        for (String subjectName : subjectNames) {
            Subject subject = tableModel.findSubjectByName(subjectName.trim());
            if (subject == null) {
                JOptionPane.showMessageDialog(null,
                        "Subject not found: " + subjectName, "Error", JOptionPane.ERROR_MESSAGE);
                continue;
            }

            for (String objectName : objectNames) {
                MyObject myObject = tableModel.findObjectByName(objectName.trim());
                if (myObject == null) {
                    JOptionPane.showMessageDialog(null,
                            "Object not found: " + objectName, "Error", JOptionPane.ERROR_MESSAGE);
                    continue;
                }

                tableModel.removeAccessRight(subjectName, objectName);
            }
        }
    }

    public void grantAllAccess() {
        String[] subjectNames = subjectNameField.getText().split("\n");
        MyObject[] allObjects = tableModel.getAllObjects();

        for (String subjectName : subjectNames) {
            Subject subject = tableModel.findSubjectByName(subjectName);
            if (subject == null) {
                Subject newSubject = new Subject(subjectName);
                tableModel.addSubject(newSubject);
                subject = newSubject;
            }

            for (MyObject object : allObjects) {
                tableModel.grantAccessRight(subject, object);
            }
        }
        subjectNameField.setText("");
        objectNameField.setText("");
        refreshTable();
    }
    public void removeAllAccess() {
        String[] subjectNames = subjectNameField.getText().split("\n");
        MyObject[] allObjects = tableModel.getAllObjects();

        for (String subjectName : subjectNames) {
            Subject subject = tableModel.findSubjectByName(subjectName);
            if (subject != null) {
                for (MyObject object : allObjects) {
                    tableModel.removeAccessRight(subject.getName(), object.getName());
                }
            }
        }
        subjectNameField.setText("");
        objectNameField.setText("");
        refreshTable();
    }

    public static void main(String[] args) {
        AccessControlGUI gui = new AccessControlGUI();
        gui.setVisible(true);
    }
}
