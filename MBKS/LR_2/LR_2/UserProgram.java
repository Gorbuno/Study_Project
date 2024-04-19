// пользовательская прога

// Импорт необходимых библиотек для работы с графическим интерфейсом, обработки событий и чтения файлов
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

// Объявление класса UserProgram, который будет использоваться для фильтрации текста по правам доступа пользователя
public class UserProgram {
    // Объявление переменных для хранения элементов графического интерфейса
    private JFrame frame;
    private JTextField userNameField;
    private JTextField inputTextField;
    private JTextArea filteredTextArea;
    private JButton submitButton;

    // Точка входа в программу
    public static void main(String[] args) {
        // Инициализация графического интерфейса в отдельном потоке
        EventQueue.invokeLater(() -> {
            try {
                UserProgram window = new UserProgram();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    // Конструктор класса UserProgram, который вызывает метод инициализации
    public UserProgram() {
        initialize();
    }

    // Метод инициализации, который создает и настраивает графический интерфейс
    private void initialize() {
        // Создание и настройка окна
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        // Создание и настройка метки для имени пользователя
        JLabel lblUserName = new JLabel("User Name:");
        lblUserName.setBounds(10, 10, 80, 25);
        frame.getContentPane().add(lblUserName);

        // Создание и настройка текстового поля для ввода имени пользователя
        userNameField = new JTextField();
        userNameField.setBounds(100, 10, 150, 25);
        frame.getContentPane().add(userNameField);
        userNameField.setColumns(10);

        // Создание и настройка метки для ввода текста
        JLabel lblInputText = new JLabel("Input Text:");
        lblInputText.setBounds(10, 40, 80, 25);
        frame.getContentPane().add(lblInputText);

        // Создание и настройка текстового поля для ввода текста
        inputTextField = new JTextField();
        inputTextField.setBounds(100, 40, 150, 25);
        frame.getContentPane().add(inputTextField);
        inputTextField.setColumns(10);

        // Создание и настройка кнопки для отправки текста
        submitButton = new JButton("Submit");
        submitButton.setBounds(10, 70, 80, 25);
        frame.getContentPane().add(submitButton);

        // Создание и настройка области для отображения отфильтрованного текста
        filteredTextArea = new JTextArea();
        filteredTextArea.setBounds(10, 100, 414, 150);
        frame.getContentPane().add(filteredTextArea);

        // Добавление слушателя событий для кнопки отправки текста
        submitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Получение имени пользователя и введенного текста
                String userName = userNameField.getText();
                String inputText = inputTextField.getText();
                // Фильтрация текста по правам доступа пользователя
                Set<String> filteredText = filterText(userName, inputText);
                // Отображение отфильтрованного текста
                filteredTextArea.setText(filteredText.stream().collect(Collectors.joining("-")));
            }
        });
    }

    // Метод для фильтрации текста по правам доступа пользователя
    private Set<String> filterText(String userName, String inputText) {
        // Путь к файлу с правами доступа
        String accessRightsFilePath = "access_rights.txt";
        Set<String> filteredText = new HashSet<>();
        try {
            // Чтение всех строк из файла с правами доступа
            List<String> lines = Files.readAllLines(Paths.get(accessRightsFilePath));
            // Проход по каждой строке файла
            for (String line : lines) {
                // Разделение строки на части по символу ":"
                String[] parts = line.split(":");
                // Проверка, что строка содержит имя пользователя и права доступа
                if (parts.length == 2 && parts[0].equals(userName)) {
                    // Получение прав доступа пользователя
                    var objects = List.of(parts[1].split("-"));
                    // Фильтрация введенного текста по правам доступа
                    for (char c : inputText.toCharArray()) {
                        String charStr = String.valueOf(c);
                        if (objects.contains(charStr)) {
                            filteredText.add(charStr);
                        }
                    }
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            // Обработка ошибки чтения файла
            filteredText = Set.of("Error reading access rights file.");
        }
        return filteredText;
    }
}

