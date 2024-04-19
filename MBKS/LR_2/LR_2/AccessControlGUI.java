import dto.MyObject;
import dto.Subject;
import tools.AccessTableModel;
import tools.IoTools;

import javax.swing.*; // Импорт классов Swing для создания графического интерфейса
import javax.swing.table.TableColumn;
import java.awt.*; // Импорт классов AWT для работы с графическими компонентами

public class AccessControlGUI extends JFrame { // Определение класса AccessControlGUI, расширяющего JFrame
    private JTextField subjectNameField; // Текстовое поле для ввода имени субъекта
    private JTextField objectNameField; // Текстовое поле для ввода имени объекта
    private JButton addSubjectButton; // Кнопка для добавления субъекта
    private JButton addObjectButton; // Кнопка для добавления объекта
    private JButton grantAccessRightButton; // Кнопка для предоставления права доступа
    private JButton saveAccessMatrixButton; // Кнопка для сохранения матрицы доступа
    private JButton loadAccessMatrixButton; // Кнопка для загрузки матрицы доступа
    private JButton removeSubjectButton; // Кнопка для удаления субъекта
    private JButton removeObjectButton; // Кнопка для удаления объекта
    private JButton removeAccessRightButton; // Кнопка для удаления права доступа
    private JButton renameSubjectButton; // Кнопка для удаления субъекта
    private JButton renameObjectButton; // Кнопка для удаления объекта

    private JTable accessTable; // Таблица для отображения матрицы доступа
    private AccessTableModel tableModel; // Модель данных для таблицы матрицы доступа

    public AccessControlGUI() { // Конструктор класса AccessControlGUI
        setLayout(new GridLayout(1, 2));// Установка компоновщика
        setSize(800, 300);// Установка размера окна
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Установка действия при закрытии окна
        setTitle("Admin Programm"); // Установка заголовка окна

        subjectNameField = new JTextField(); // Создание текстового поля для ввода имени субъекта
        objectNameField = new JTextField(); // Создание текстового поля для ввода имени объекта
        addSubjectButton = new JButton("Add Subject"); // Создание кнопки для добавления субъекта
        addObjectButton = new JButton("Add Object"); // Создание кнопки для добавления объекта
        grantAccessRightButton = new JButton("Grant Access Right"); // Создание кнопки для предоставления права доступа
        saveAccessMatrixButton = new JButton("Save Access Matrix"); // Создание кнопки для сохранения матрицы доступа
        loadAccessMatrixButton = new JButton("Load Access Matrix"); // Создание кнопки для загрузки матрицы доступа
        removeSubjectButton = new JButton("Remove Subject"); // Создание кнопки для удаления субъекта
        removeObjectButton = new JButton("Remove Object"); // Создание кнопки для удаления объекта
        removeAccessRightButton = new JButton("Remove Access Right"); // Создание кнопки для удаления права доступа
        renameSubjectButton = new JButton("Rename Subject"); // Создание кнопки для удаления права доступа
        renameObjectButton = new JButton("Rename Object"); // Создание кнопки для удаления права доступа

        // Создание модели данных для JTable
        tableModel = new AccessTableModel();
        accessTable = new JTable(tableModel);
        setTableBounds();

        tableModel.addTableModelListener(e -> {
            refreshTable();
        });


        JPanel PanelInputSubject = new JPanel();
        PanelInputSubject.setLayout(new BoxLayout(PanelInputSubject, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelInputSubject.add(new JLabel("Subject Name:"));
        PanelInputSubject.add(subjectNameField);

        JPanel PanelSubject = new JPanel();
        PanelSubject.setLayout(new BoxLayout(PanelSubject, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelSubject.add(addSubjectButton);
        PanelSubject.add(removeSubjectButton);
        PanelSubject.add(renameSubjectButton);

        JPanel PanelInputObject = new JPanel();
        PanelInputObject.setLayout(new BoxLayout(PanelInputObject, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelInputObject.add(new JLabel("Object Name:"));
        PanelInputObject.add(objectNameField);

        JPanel PanelObject = new JPanel();
        PanelObject.setLayout(new BoxLayout(PanelObject, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelObject.add(addObjectButton);
        PanelObject.add(removeObjectButton);
        PanelObject.add(renameObjectButton);

        JPanel PanelAccessRightLabel = new JPanel();
        PanelAccessRightLabel.setLayout(new BoxLayout(PanelAccessRightLabel, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelAccessRightLabel.add(new JLabel("Action to Access Right :"));

        JPanel PanelAccessRight = new JPanel();
        PanelAccessRight.setLayout(new BoxLayout(PanelAccessRight, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelAccessRight.add(grantAccessRightButton);
        PanelAccessRight.add(removeAccessRightButton);

        JPanel PanelMatrixLabel = new JPanel();
        PanelMatrixLabel.setLayout(new BoxLayout(PanelMatrixLabel, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelMatrixLabel.add(new JLabel("Action to Access matrix :"));

        JPanel PanelMatrix = new JPanel();
        PanelMatrix.setLayout(new BoxLayout(PanelMatrix, BoxLayout.X_AXIS)); // Установка горизонтального BoxLayout
        PanelMatrix.add(saveAccessMatrixButton);
        PanelMatrix.add(loadAccessMatrixButton);



        // Создание вертикального компоновщика для кнопок todo
        Box buttonBox = Box.createVerticalBox();
        buttonBox.add(PanelInputSubject); // Добавление метки для текстового поля имени субъекта
        buttonBox.add(PanelSubject); // Добавление текстового поля для ввода имени субъекта
        buttonBox.add(PanelInputObject); // Добавление метки для текстового поля имени объекта
        buttonBox.add(PanelObject); // Добавление текстового поля для ввода имени объекта
        buttonBox.add(PanelAccessRightLabel); // Добавление кнопки для добавления субъекта
        buttonBox.add(PanelAccessRight); // Добавление кнопки для добавления субъекта
        buttonBox.add(PanelMatrixLabel); // Добавление кнопки для добавления субъекта
        buttonBox.add(PanelMatrix); // Добавление кнопки для добавления объекта

        // Добавление вертикального компоновщика с кнопками в GUI
        add(buttonBox, BorderLayout.WEST);
        // Добавление JTable в GUI
        add(new JScrollPane(accessTable), BorderLayout.EAST);


        addSubjectButton.addActionListener(e -> // Добавление слушателя событий к кнопке добавления субъекта
        {
            String subjectName = subjectNameField.getText(); // Получение имени субъекта из текстового поля
            if (subjectName.length() == 1){
            if (subjectName.isEmpty()) { // Проверка, не пустое ли имя субъекта
                JOptionPane.showMessageDialog(null,
                        "Subject name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            if (tableModel.subjectExists(subjectName)) { // Проверка, существует ли уже субъект с таким именем
                JOptionPane.showMessageDialog(null,
                        "Subject name already exists.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            tableModel.addSubject(new Subject(subjectName)); // Добавление нового субъекта в систему контроля доступа
            subjectNameField.setText(""); // Очистка текстового поля имени субъекта
            refreshTable();}
            else {
                JOptionPane.showMessageDialog(null,
                        "Subject name is long.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
            }
        });

        addObjectButton.addActionListener(e -> // Добавление слушателя событий к кнопке добавления объекта
        {
            String objectName = objectNameField.getText(); // Получение имени объекта из текстового поля
            if (objectName.length() == 1){
            if (objectName.isEmpty()) { // Проверка, не пустое ли имя объекта
                JOptionPane.showMessageDialog(null,
                        "Object name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            if (tableModel.objectExists(objectName)) { // Проверка, существует ли уже объект с таким именем
                JOptionPane.showMessageDialog(null,
                        "Object name already exists.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            tableModel.addObject(new MyObject(objectName)); // Добавление нового объекта в систему контроля доступа
            objectNameField.setText(""); // Очистка текстового поля имени объекта
            refreshTable();}
            else {
                JOptionPane.showMessageDialog(null,
                        "Object name is long.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
            }
        });

        grantAccessRightButton.addActionListener(e -> { // Добавление слушателя событий к кнопке предоставления права доступа
            String subjectName = subjectNameField.getText(); // Получение имени субъекта из текстового поля
            String objectName = objectNameField.getText(); // Получение имени объекта из текстового поля
            // Проверка, не пусты ли имена субъекта и объекта
            if (subjectName.isEmpty() || objectName.isEmpty()) {
                JOptionPane.showMessageDialog(null,
                        "Subject or object or right names cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }

            // Поиск субъекта и объекта по их именам
            Subject subject = tableModel.findSubjectByName(subjectName);
            MyObject myObject = tableModel.findObjectByName(objectName);

            // Проверка, найдены ли субъект и объект
            if (subject == null) {
                JOptionPane.showMessageDialog(null,
                        "Subject not found.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            if (myObject == null) {
                JOptionPane.showMessageDialog(null,
                        "Object not found.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }

            // Предоставление права доступа
            tableModel.grantAccessRight(subject, myObject);

            // Очистка текстовых полей после успешной операции
            subjectNameField.setText("");
            objectNameField.setText("");
            refreshTable();
        });

        saveAccessMatrixButton.addActionListener(e -> { // Добавление слушателя событий к кнопке сохранения матрицы доступа
            IoTools.saveAccessMatrixToFile(tableModel, "access_rights.txt"); // Сохранение матрицы доступа в файл
        });

        // Добавление слушателя событий к кнопке загрузки матрицы доступа
        loadAccessMatrixButton.addActionListener(e -> {// Загрузка матрицы доступа из файла
            IoTools.loadAccessMatrixFromFile(tableModel, "access_rights.txt");
            refreshTable();
        });

        removeSubjectButton.addActionListener(e -> { // Добавление слушателя событий к кнопке удаления субъекта
            String subjectName = subjectNameField.getText(); // Получение имени субъекта из текстового поля
            if (subjectName.isEmpty()) { // Проверка, не пустое ли имя субъекта
                JOptionPane.showMessageDialog(null, "Subject name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            tableModel.removeSubject(subjectName); // Удаление субъекта из системы контроля доступа
            subjectNameField.setText(""); // Очистка текстового поля имени субъекта
            refreshTable();
        });

        removeObjectButton.addActionListener(e -> {  // Добавление слушателя событий к кнопке удаления объекта
            String objectName = objectNameField.getText(); // Получение имени объекта из текстового поля
            if (objectName.isEmpty()) { // Проверка, не пустое ли имя объекта
                JOptionPane.showMessageDialog(null,
                        "Object name cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            tableModel.removeObject(objectName); // Удаление объекта из системы контроля доступа
            objectNameField.setText(""); // Очистка текстового поля имени объекта
            refreshTable();
        });

        removeAccessRightButton.addActionListener(e -> { // Добавление слушателя событий к кнопке удаления права доступа
            String subjectName = subjectNameField.getText(); // Получение имени субъекта из текстового поля
            String objectName = objectNameField.getText(); // Получение имени объекта из текстового поля
            if (subjectName.isEmpty() || objectName.isEmpty()) { // Проверка, не пусты ли имена субъекта и объекта
                JOptionPane.showMessageDialog(null,
                        "Subject and object names cannot be empty.", "Error", JOptionPane.ERROR_MESSAGE); // Отображение сообщения об ошибке
                return;
            }
            tableModel.removeAccessRight(subjectName, objectName); // Удаление права доступа из системы контроля доступа
            subjectNameField.setText(""); // Очистка текстового поля имени субъекта
            objectNameField.setText(""); // Очистка текстового поля имени объекта
            refreshTable();
        });

        renameSubjectButton.addActionListener(e -> renameSubject());
        renameObjectButton.addActionListener(e -> renameObject());

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
        accessTable.setRowHeight(25); // Высота строки в пикселях

        // Настройка ширины столбцов
        for (int i = 0; i < accessTable.getColumnCount(); i++) {
            accessTable.getColumnModel().getColumn(i).setPreferredWidth(100); // Ширина столбца в пикселях
        }
    }

    private void renameSubject() {
        // Создание окна для ввода старого и нового названий субъекта
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

    private void renameObject() {
        // Создание окна для ввода старого и нового названий объекта
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

    public static void main(String[] args) { // Главный метод программы
        AccessControlGUI gui = new AccessControlGUI();// Создание графического интерфейса с передачей системы контроля доступа
        gui.setVisible(true); // Отображение графического интерфейса
    }
}
