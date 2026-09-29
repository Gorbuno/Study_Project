# Импорт необходимых модулей
import sys
import json
import os
import shutil
import re

# импорт компонентов для графического интерфейса
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QLabel, \
    QLineEdit, QPushButton, QHBoxLayout, QMessageBox, \
    QTableWidget, QTableWidgetItem, QAbstractItemView, QListWidget, QListWidgetItem, QFrame

# Путь к файлу JSON
access_levels_json_path = ".\\accessLevelsData.json"
folders_json_path = ".\\foldersData.json"

main_directory = 'C:\\MBKSLAB4'

access_levels = {"public": "0"} # Уровни секретности
folders = {} # Папки

# Проверка корректности имени папки
def is_valid_folder_name(name):
    if re.search(r'[.<>:"/|?*]', name) is not None:  # Проверка на наличие недопустимых символов
        return False
    if name.startswith(' ') or name.endswith(' '):          # Проверка на наличие пробелов в начале или конце имени
        return False
    if not name.strip():                                    # Проверка на то, что имя папки не пустое и не состоит только из пробелов
        return False
    return True                                             # Все проверки прошли успешно


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    # Описание интерфейса
    def init_ui(self):
        # Устанавливаем размеры окна
        self.setMinimumWidth(1600)
        self.setMinimumHeight(700)
        # Горизонтальный макет для всего окна
        main_layout = QHBoxLayout()

        # Левая часть: блок управления
        left_layout = QVBoxLayout()

        # Рамка для создания уровня секретности
        create_level_frame = QFrame()
        create_level_frame.setFrameShape(QFrame.StyledPanel)
        create_level_frame.setFrameShadow(QFrame.Raised)
        create_level_frame_layout = QVBoxLayout()
        create_level_frame_layout.addWidget(QLabel("Создание нового уровня конфиденциальности"))  # Подпись
        self.access_level_name = QLineEdit('Name')
        self.access_level_name.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_num = QLineEdit('Level')
        self.access_level_num.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_create_btn = QPushButton('Create level')
        self.access_level_create_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.access_level_create_btn.clicked.connect(self.create_access_level)
        create_level_frame_layout.addWidget(self.access_level_name)
        create_level_frame_layout.addWidget(self.access_level_num)
        create_level_frame_layout.addWidget(self.access_level_create_btn)
        create_level_frame.setLayout(create_level_frame_layout)
        left_layout.addWidget(create_level_frame)

        # Рамка для удаления уровня секретности
        delete_level_frame = QFrame()
        delete_level_frame.setFrameShape(QFrame.StyledPanel)
        delete_level_frame.setFrameShadow(QFrame.Raised)
        delete_level_frame_layout = QVBoxLayout()
        delete_level_frame_layout.addWidget(QLabel("Удаление уровня конфиденциальности"))  # Подпись
        self.access_level_delete_name = QLineEdit('Level')
        self.access_level_delete_name.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_delete_btn = QPushButton('Delete level')
        self.access_level_delete_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.access_level_delete_btn.clicked.connect(self.delete_access_level)
        delete_level_frame_layout.addWidget(self.access_level_delete_name)
        delete_level_frame_layout.addWidget(self.access_level_delete_btn)
        delete_level_frame.setLayout(delete_level_frame_layout)
        left_layout.addWidget(delete_level_frame)

        # Рамка для изменения уровня секретности
        edit_level_frame = QFrame()
        edit_level_frame.setFrameShape(QFrame.StyledPanel)
        edit_level_frame.setFrameShadow(QFrame.Raised)
        edit_level_frame_layout = QVBoxLayout()
        edit_level_frame_layout.addWidget(QLabel("Изменение уровня конфиденциальности"))  # Подпись
        self.access_level_edit_name_old = QLineEdit('Name')
        self.access_level_edit_name_old.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_edit_name_new = QLineEdit('New name')
        self.access_level_edit_name_new.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_edit_num_new = QLineEdit('New level')
        self.access_level_edit_num_new.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.access_level_edit_btn = QPushButton('Remane level')
        self.access_level_edit_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.access_level_edit_btn.clicked.connect(self.edit_access_level)
        edit_level_frame_layout.addWidget(self.access_level_edit_name_old)
        edit_level_frame_layout.addWidget(self.access_level_edit_name_new)
        edit_level_frame_layout.addWidget(self.access_level_edit_num_new)
        edit_level_frame_layout.addWidget(self.access_level_edit_btn)
        edit_level_frame.setLayout(edit_level_frame_layout)
        left_layout.addWidget(edit_level_frame)

        # Рамка для создания папки
        create_folder_frame = QFrame()
        create_folder_frame.setFrameShape(QFrame.StyledPanel)
        create_folder_frame.setFrameShadow(QFrame.Raised)
        create_folder_frame_layout = QVBoxLayout()
        create_folder_frame_layout.addWidget(QLabel("Создание папки"))  # Подпись
        self.folder_name = QLineEdit('Folder name')
        self.folder_name.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_create_btn = QPushButton('Create folder')
        self.folder_create_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.folder_create_btn.clicked.connect(self.create_folder)
        create_folder_frame_layout.addWidget(self.folder_name)
        create_folder_frame_layout.addWidget(self.folder_create_btn)
        create_folder_frame.setLayout(create_folder_frame_layout)
        left_layout.addWidget(create_folder_frame)

        # Рамка для удаления папки
        delete_folder_frame = QFrame()
        delete_folder_frame.setFrameShape(QFrame.StyledPanel)
        delete_folder_frame.setFrameShadow(QFrame.Raised)
        delete_folder_frame_layout = QVBoxLayout()
        delete_folder_frame_layout.addWidget(QLabel("Удаление папки"))  # Подпись
        self.folder_delete_name = QLineEdit('Folder')
        self.folder_delete_name.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_delete_btn = QPushButton('Delete folder')
        self.folder_delete_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.folder_delete_btn.clicked.connect(self.delete_folder)
        delete_folder_frame_layout.addWidget(self.folder_delete_name)
        delete_folder_frame_layout.addWidget(self.folder_delete_btn)
        delete_folder_frame.setLayout(delete_folder_frame_layout)
        left_layout.addWidget(delete_folder_frame)

        # Рамка для переименования папки
        edit_folder_frame = QFrame()
        edit_folder_frame.setFrameShape(QFrame.StyledPanel)
        edit_folder_frame.setFrameShadow(QFrame.Raised)
        edit_folder_frame_layout = QVBoxLayout()
        edit_folder_frame_layout.addWidget(QLabel("Переименование папки и/или изменить уровень конфиденциальности"))  # Подпись
        self.folder_edit_name_old = QLineEdit('Name')
        self.folder_edit_name_old.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_edit_name_new = QLineEdit('New name')
        self.folder_edit_name_new.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_edit_access_level_new = QLineEdit('New level')
        self.folder_edit_access_level_new.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_edit_btn = QPushButton('Rename folder/change access rights')
        self.folder_edit_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.folder_edit_btn.clicked.connect(self.edit_folder)
        edit_folder_frame_layout.addWidget(self.folder_edit_name_old)
        edit_folder_frame_layout.addWidget(self.folder_edit_name_new)
        edit_folder_frame_layout.addWidget(self.folder_edit_access_level_new)
        edit_folder_frame_layout.addWidget(self.folder_edit_btn)
        edit_folder_frame.setLayout(edit_folder_frame_layout)
        left_layout.addWidget(edit_folder_frame)

        # Рамка для копирования папки
        copy_folder_frame = QFrame()
        copy_folder_frame.setFrameShape(QFrame.StyledPanel)
        copy_folder_frame.setFrameShadow(QFrame.Raised)
        copy_folder_frame_layout = QVBoxLayout()
        copy_folder_frame_layout.addWidget(QLabel("Копирование папки"))  # Подпись
        self.folder_to_copy = QLineEdit('From')
        self.folder_to_copy.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_destination = QLineEdit('To')
        self.folder_destination.setStyleSheet("background-color: white; border: 1px solid gray;")
        self.folder_copy_btn = QPushButton('Copy')
        self.folder_copy_btn.setStyleSheet("background-color: white; border: 1px solid blue;")
        self.folder_copy_btn.clicked.connect(self.copy_folder)
        copy_folder_frame_layout.addWidget(self.folder_to_copy)
        copy_folder_frame_layout.addWidget(self.folder_destination)
        copy_folder_frame_layout.addWidget(self.folder_copy_btn)
        copy_folder_frame.setLayout(copy_folder_frame_layout)
        left_layout.addWidget(copy_folder_frame)

        main_layout.addLayout(left_layout)

        # Правая часть: блок с папками и уровнями
        right_layout = QVBoxLayout()

        # Поле с уровнями
        self.access_levels_list_name = QLabel('Уровни конфиденциальности')
        self.access_levels_list_name.setStyleSheet("background-color: white;")  # Добавляем стиль к QLabel
        self.access_levels_list = QTableWidget()
        self.access_levels_list.setMinimumSize(750, 300)
        self.access_levels_list.horizontalHeader().hide()
        self.access_levels_list.verticalHeader().hide()
        self.access_levels_list.setEditTriggers(QAbstractItemView.NoEditTriggers)
        right_layout.addWidget(self.access_levels_list_name)
        right_layout.addWidget(self.access_levels_list)

        # Поле с папками
        self.folders_list_name = QLabel('Папки')
        self.folders_list_name.setStyleSheet("background-color: white;")  # Добавляем стиль к QLabel
        self.folders_list = QTableWidget()
        self.folders_list.setMinimumSize(750, 300)
        self.folders_list.horizontalHeader().hide()
        self.folders_list.verticalHeader().hide()
        self.folders_list.setEditTriggers(QAbstractItemView.NoEditTriggers)
        right_layout.addWidget(self.folders_list_name)
        right_layout.addWidget(self.folders_list)

        main_layout.addLayout(right_layout)

        # Установка стилей
        self.setStyleSheet("""
            background-color: #ADD8E6;
            QLineEdit {
                background-color: white;
                border: 1px solid gray;
            }
            QPushButton {
                background-color: white;
                border: 1px solid blue;
            }
            QTableWidget {
                background-color: white;
            }
        """)
        self.update()

        # Устанавливаем ширину таблиц, чтобы они занимали все пространство
        self.access_levels_list.setFixedWidth(743)
        self.folders_list.setFixedWidth(743)

        self.setLayout(main_layout)

    # Отображение ошибок
    def show_error(self, msg_text):
        print(msg_text)
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Warning)
        msg.setWindowTitle("Error")
        msg.setText(msg_text)
        msg.setStandardButtons(QMessageBox.Ok)
        msg.exec_()

    # Работа со словарем
    def is_in_dict(self, item, dict):
        existing_flag = False
        if len(dict) > 0:
            if item in dict:
                existing_flag = True
        return existing_flag

    def process_changes(self, old_str, new_str):
        # Разбиваем строку old_str на части по символу обратного слэша \\
        old_parts = old_str.split('\\')
        # Аналогично разбиваем строку new_str на части
        new_parts = new_str.split('\\')

        # Определяем индекс последнего вхождения символа обратного слэша в old_str
        last_index = old_str.count('\\')

        # Проходим по меньшему количеству частей между old_parts и new_parts
        for i in range(min(len(old_parts), len(new_parts))):
            # Если текущий индекс больше или равен индексу последнего вхождения обратного слэша,
            # заменим соответствующую часть old_parts на часть из new_parts
            if i >= last_index:
                old_parts[i] = new_parts[i]

        # Соединяем обработанные части обратным слэшем в одну строку
        processed_str = '\\'.join(old_parts)
        # Возвращаем итоговую строку
        return processed_str

    def can_edit_folder_access_level(self, folder_name, level):
        flag = True
        if folder_name.count('\\') > 0:
            folder_name_parts = folder_name.split('\\')
            folder_name_parts.pop(len(folder_name_parts) - 1)
            parent_folder_name = '\\'.join(folder_name_parts)
            if int(access_levels[folders[parent_folder_name]]) >= int(level):
                for f in folders:
                    a = folder_name.count('\\')
                    b = f.count('\\')
                    if (folder_name in f) and ((b - a) == 1):
                        if int(level) < int(access_levels[folders[f]]):
                            flag = False
                            break
            else:
                flag = False
        else:
            for f in folders:
                a = folder_name.count('\\')
                b = f.count('\\')
                if (folder_name in f) and ((b - a) == 1):
                    if int(level) < int(access_levels[folders[f]]):
                        flag = False
                        break

        return flag

    def can_create_folder(self, folder_name):
        flag = False
        if folder_name.count('\\') > 0:
            for folder in folders:
                if folder in folder_name:
                    folder_name_parts = folder_name.split('\\')
                    folder_name_parts.pop(len(folder_name_parts) - 1)
                    parent_folder_name = '\\'.join(folder_name_parts)
                    if folder == parent_folder_name:
                        flag = True
        else:
            flag = True
        return flag

    def can_edit_access_level(self, level_name, level):
        folders_to_check = []
        for folder in folders:
            if folders[folder] == level_name:
                folders_to_check.append(folder)

        can_edit = True

        for folder in folders_to_check:
            if folder.count('\\') == 0:
                for f in folders:
                    a = folder.count('\\')
                    b = f.count('\\')
                    if (folder in f) and ((b - a) == 1):
                        if int(level) < int(access_levels[folders[f]]):
                            can_edit = False
            else:
                folder_name_parts = folder.split('\\')
                folder_name_parts.pop(len(folder_name_parts) - 1)
                parent_folder_name = '\\'.join(folder_name_parts)
                if int(access_levels[folders[parent_folder_name]]) >= int(level):
                    for f in folders:
                        a = folder.count('\\')
                        b = f.count('\\')
                        if (folder in f) and ((b - a) == 1):
                            if int(level) < int(access_levels[folders[f]]):
                                can_edit = False
                else:
                    can_edit = False

        return can_edit

    def ui_reset(self):
        self.access_level_edit_name_new.setText(' новое имя уровня секретности')
        self.access_level_edit_num_new.setText(' новая секретность')
        self.folder_edit_name_new.setText(' новое имя папки')
        self.folder_edit_access_level_new.setText(' новый уровень секретности')

    # основные функции
    def create_access_level(self):
        name = self.access_level_name.text()
        num = self.access_level_num.text()
        if name.isalnum() and (len(name) > 0):
            if not (self.is_in_dict(name, access_levels)):
                if num.isdigit() and (len(num) > 0) and (int(num) <= 10 and int(num) >= 0):
                    access_levels[name] = num
                    # обновление ui
                else:
                    self.show_error("Неккоректное значение секретности")
            else:
                self.show_error("Уровень секретности уже существует")
        else:
            self.show_error("Неккоректное имя уровня секретности")
        print(access_levels)
        json_update()
        self.access_levels_table_update()
        self.folders_table_update()
        self.ui_reset()

    def create_folder(self):
        name = self.folder_name.text()
        name_parts = name.split('\\')

        if len(name_parts) > 1:
            parent_folder = '\\'.join(name_parts[:-1])  # Имя родительской папки

            if self.is_in_dict(parent_folder, folders):
                # Проверка уровня секретности
                if int(access_levels[folders[parent_folder]]) >= int(access_levels["public"]):
                    # Проверка корректности имени папки
                    if is_valid_folder_name(name_parts[-1]) and (len(name_parts[-1]) > 0):
                        # Проверка, существует ли папка
                        if not (self.is_in_dict(name, folders)):
                            # Создание папки
                            script_dir = main_directory
                            new_folder_path = os.path.join(script_dir, name)
                            os.makedirs(new_folder_path)

                            # Добавление папки в словарь
                            folders[name] = "public"  # Задаем уровень секретности по умолчанию

                            # Обновление UI
                            self.folders_table_update()

                        else:
                            self.show_error("Папка уже существует")
                    else:
                        self.show_error("Неккоректное имя папки")
                else:
                    self.show_error("Нельзя создать подпапку с уровнем секретности выше, чем у родительской")
            else:
                self.show_error("Родительская папка не существует")
        else:
            if self.is_in_dict(name, folders):
                self.show_error("Папка уже существует")
                return
            if is_valid_folder_name(name) and (len(name) > 0):
                if self.can_create_folder(name):
                    folders[name] = 'public'
                    script_dir = main_directory
                    new_folder_path = os.path.join(script_dir, name)
                    if not (os.path.exists(new_folder_path) and os.path.isdir(new_folder_path)):
                        os.makedirs(new_folder_path)
                else:
                    self.show_error("Вы не можете создать сразу несколько папок")
            else:
                self.show_error("Неккоректное имя папки")
            print(folders)
            json_update()
            self.access_levels_table_update()
            self.folders_table_update()
            self.ui_reset()

    def delete_access_level(self):
        name = self.access_level_delete_name.text()
        if name == 'public':
            self.show_error("Нельзя удалить уровень секретности public")
            return
        for folder in folders:
            if name in folder and folders[folder] != 'public' and folder != name:
                self.show_error("Нельзя удалить секретность")
                return
        parent_folders = []
        if name.isalnum() and (len(name) > 0):
            if self.is_in_dict(name, access_levels):
                for folder in folders:
                    if folders[folder] == name:
                        folders[folder] = 'public'
                        parent_folders.append(folder)
                del access_levels[name]

                for folder in folders:
                    for parent_folder in parent_folders:
                        if parent_folder in folder:
                            folders[folder] = 'public'

            else:
                self.show_error("Нет уровня секретности с таким именем")
        else:
            self.show_error("Неккоректное название уровня секретноcти")
        json_update()
        self.access_levels_table_update()
        self.folders_table_update()
        self.ui_reset()

    def delete_folder(self):
        name = self.folder_delete_name.text()
        name_parts = name.split('\\')

        if len(name_parts) > 1:
            parent_folder = '\\'.join(name_parts[:-1])  # Имя родительской папки

            if self.is_in_dict(parent_folder, folders):
                # Проверка уровня секретности
                if int(access_levels[folders[parent_folder]]) >= int(access_levels["public"]):
                    # Проверка корректности имени папки
                    if is_valid_folder_name(name_parts[-1]) and (len(name_parts[-1]) > 0):
                        # Проверка, существует ли папка
                        if not (self.is_in_dict(name, folders)):
                            # Создание папки
                            script_dir = main_directory
                            new_folder_path = os.path.join(script_dir, name)
                            os.makedirs(new_folder_path)

                            # Добавление папки в словарь
                            folders[name] = "public"  # Задаем уровень секретности по умолчанию

                            # Обновление UI
                            self.folders_table_update()

                        else:
                            self.show_error("Папка уже существует")
                    else:
                        self.show_error("Неккоректное имя папки")
                else:
                    self.show_error("Нельзя создать подпапку с уровнем секретности выше, чем у родительской")
            else:
                self.show_error("Родительская папка не существует")
        else:
            if is_valid_folder_name(name) and (len(name) > 0):
                if self.is_in_dict(name, folders):
                    script_dir = main_directory
                    folder_path = os.path.join(script_dir, name)
                    shutil.rmtree(folder_path)

                    update_dict = folders.copy()

                    for folder in folders:
                        if name in folder:
                            del update_dict[folder]

                    folders.clear()
                    folders.update(update_dict)

                else:
                    self.show_error("Нет папки с таким именем")
            else:
                self.show_error("Неккоректное имя папки")
            print(folders)
            json_update()
            self.access_levels_table_update()
            self.folders_table_update()
            self.ui_reset()

    def edit_access_level(self):
        name_old = self.access_level_edit_name_old.text()
        name_new = self.access_level_edit_name_new.text()
        num = self.access_level_edit_num_new.text()
        if name_old.isalnum() and (len(name_old) > 0):
            if self.is_in_dict(name_old, access_levels):
                if (name_new == ' новое имя уровня секретности') or (name_new == ''):
                    if (num == ' новую секретность') or (num == ''):
                        old_num = access_levels[name_old]
                        access_levels[name_old] = old_num
                    else:
                        if num.isdigit() and (len(num) > 0) and (int(num) <= 10 and int(num) >= 0):
                            if self.can_edit_access_level(name_old, num):
                                access_levels[name_old] = num
                            else:
                                self.show_error(
                                    "Нельзя задать уровень секретности больше, чем у родительской папки/меньше, чем у дочерней")
                        else:
                            self.show_error("Неккоректное значение секретности")
                else:
                    if name_new.isalnum() and (len(name_new) > 0):
                        if not (self.is_in_dict(name_new, access_levels)):
                            if (num == ' новый уровень секретности') or (num == ''):
                                old_num = access_levels[name_old]
                                del access_levels[name_old]
                                access_levels[name_new] = old_num
                                if len(folders) > 0:
                                    for folder in folders:
                                        if folders[folder] == name_old:
                                            folders[folder] = name_new
                            else:
                                if num.isdigit() and (len(num) > 0) and (int(num) <= 10 and int(num) >= 0):
                                    if self.can_edit_access_level(name_old, num):
                                        del access_levels[name_old]
                                        access_levels[name_new] = num
                                        if len(folders) > 0:
                                            for folder in folders:
                                                if folders[folder] == name_old:
                                                    folders[folder] = name_new
                                    else:
                                        self.show_error(
                                            "Нельзя задать уровень секретности больше, чем у родительской папки/меньше, чем у дочерней")
                                else:
                                    self.show_error("Неккоректное значение секретности")
                        else:
                            self.show_error("Уровень секретности уже существует")
                    else:
                        self.show_error("Неккоректное имя уровня секретности")
            else:
                self.show_error("Нет уровня секретности с таким именем")
        else:
            self.show_error("Неккоректное имя уровня секретности")
        print(access_levels)
        json_update()
        self.access_levels_table_update()
        self.folders_table_update()
        self.ui_reset()

    def edit_folder(self):
        name_old = self.folder_edit_name_old.text()
        name_new = self.folder_edit_name_new.text()
        level = self.folder_edit_access_level_new.text()
        if is_valid_folder_name(name_old) and (len(name_old) > 0):
            if self.is_in_dict(name_old, folders):
                if (name_new == ' новое имя папки') or (name_new == ''):
                    if (level == ' новый уровень секретности') or (level == ''):
                        old_level = folders[name_old]
                        folders[name_old] = old_level
                    else:
                        if level.isalnum() and (len(level) > 0):
                            if self.is_in_dict(level, access_levels):
                                # Получаем имя родительской папки
                                folder_name_parts = name_old.split('\\')
                                folder_name_parts.pop(len(folder_name_parts) - 1)
                                parent_folder_name = '\\'.join(folder_name_parts)

                                # Проверяем уровень секретности родительской папки
                                if int(access_levels[folders[parent_folder_name]]) >= int(access_levels[level]):
                                    folders[name_old] = level  # Изменяем уровень секретности
                                    self.folders_table_update()  # Обновляем таблицу с папками
                                else:
                                    self.show_error(
                                        "Нельзя задать уровень секретности больше, чем у родительской папки")
                                    return
                            else:
                                self.show_error("Нет уровня секретности с таким именем")
                        else:
                            self.show_error("Неккоректное имя уровня секретности")
                else:
                    if is_valid_folder_name(name_new) and (len(name_new) > 0):
                        if not (self.is_in_dict(name_new, folders)):
                            if (level == ' новый уровень секретности') or (level == ''):
                                processed_str = self.process_changes(name_old, name_new)
                                if name_old != processed_str:
                                    old_level = folders[name_old]
                                    del folders[name_old]
                                    folders[name_new] = old_level
                                else:
                                    self.show_error("Вы можете изменять только крайние папки в пути!")
                                    return

                                updated_dict = {}
                                for key, value in folders.items():
                                    if name_old in key:
                                        if name_new == key:
                                            updated_dict[key] = value
                                        else:
                                            new_key = key
                                            new_key = new_key.replace(name_old, name_new)
                                            updated_dict[new_key] = value
                                    else:
                                        updated_dict[key] = value
                                folders.clear()
                                folders.update(updated_dict)

                                script_dir = main_directory
                                old_folder_path = os.path.join(script_dir, name_old)
                                new_folder_path = os.path.join(script_dir, name_new)
                                os.rename(old_folder_path, new_folder_path)
                            else:
                                if level.isalnum() and (len(level) > 0):
                                    if self.is_in_dict(level, access_levels):
                                        processed_str = self.process_changes(name_old, name_new)
                                        if name_old != processed_str:
                                            if self.can_edit_folder_access_level(name_old, access_levels[level]):
                                                del folders[name_old]
                                                folders[name_new] = level

                                                updated_dict = {}
                                                for key, value in folders.items():
                                                    if name_old in key:
                                                        new_key = key.replace(name_old, name_new)
                                                        updated_dict[new_key] = value
                                                    else:
                                                        updated_dict[key] = value
                                                folders.clear()
                                                folders.update(updated_dict)
                                            else:
                                                self.show_error(
                                                    "Нельзя дать уровень секретности с значением больше, чем у родительской папки")
                                        else:
                                            self.show_error("Вы можете изменять только крайние папки в пути!")
                                            return

                                        script_dir = main_directory
                                        old_folder_path = os.path.join(script_dir, name_old)
                                        new_folder_path = os.path.join(script_dir, name_new)
                                        os.rename(old_folder_path, new_folder_path)
                                    else:
                                        self.show_error("Нет уровня секретности с таким именем")
                                else:
                                    self.show_error("Неккоректное имя уровня секретности")
                        else:
                            self.show_error("Папка уже существует")
                    else:
                        self.show_error("Неккоректное имя папки")
            else:
                self.show_error("Нет папки с таким именем")
        else:
            self.show_error("Неккоректное имя папки")
        print(folders)
        json_update()
        self.access_levels_table_update()
        self.folders_table_update()
        self.ui_reset()

    def access_levels_table_update(self):
        self.access_levels_list.clear()
        for j in range(0, self.access_levels_list.rowCount()):
            self.access_levels_list.removeRow(j - 1)
        for k in range(0, self.access_levels_list.columnCount()):
            self.access_levels_list.removeColumn(k - 1)
        self.access_levels_list.setColumnCount(2)
        self.access_levels_list.setColumnWidth(0, 370)
        self.access_levels_list.setColumnWidth(1, 370)
        self.access_levels_list.setRowCount(1)

        self.access_levels_list.setItem(0, 0, QTableWidgetItem("Level Name"))
        self.access_levels_list.setItem(0, 1, QTableWidgetItem("Level"))

        i = 1
        for access_level in access_levels:
            self.access_levels_list.insertRow(self.access_levels_list.rowCount())
            self.access_levels_list.setItem(i, 0, QTableWidgetItem(access_level))
            self.access_levels_list.setItem(i, 1, QTableWidgetItem(access_levels[access_level]))
            i += 1

    def folders_table_update(self):
        self.folders_list.clear()
        for j in range(0, self.folders_list.rowCount()):
            self.folders_list.removeRow(j - 1)
        for k in range(0, self.folders_list.columnCount()):
            self.folders_list.removeColumn(k - 1)
        self.folders_list.setColumnCount(2)
        self.folders_list.setColumnWidth(0, 370)
        self.folders_list.setColumnWidth(1, 370)
        self.folders_list.setRowCount(1)

        self.folders_list.setItem(0, 0, QTableWidgetItem("Folder name"))
        self.folders_list.setItem(0, 1, QTableWidgetItem("Level"))

        i = 1
        for folder in folders:
            self.folders_list.insertRow(self.folders_list.rowCount())
            self.folders_list.setItem(i, 0, QTableWidgetItem(folder))
            self.folders_list.setItem(i, 1, QTableWidgetItem(folders[folder]))
            i += 1

    def copy_folder(self):
        source = self.folder_to_copy.text()
        destination = self.folder_destination.text()
        fileToCopy = source.split('\\')[-1]
        if fileToCopy in destination:
            return
        main_patch = ''
        folders_to_copy = []

        if source.count('\\') > 0:
            patch_from_splitted = source.split('\\')
            patch_from_splitted.pop(len(patch_from_splitted) - 1)
            patch_from = '\\'.join(patch_from_splitted)
            main_patch = patch_from + '\\'

        if is_valid_folder_name(source):
            if self.is_in_dict(source, folders):
                print('source')
                print(source)
            else:
                self.show_error("Такой папки не существует")
                return
        else:
            self.show_error("Неккоректное название папки для копирования")
            return

        if is_valid_folder_name(destination):
            if self.is_in_dict(destination, folders):
                print('destination')
                print(destination)
            else:
                self.show_error("Такой папки не существует")
                return
        else:
            self.show_error("Неккоректное название папки назначения")
            return

        if source.count('\\') == 0:
            if int(access_levels[folders[source]]) <= int(access_levels[folders[destination]]):

                print('Copy')
                new_folders = []

                for folder in folders:
                    if folder.startswith(source):
                        folders_to_copy.append(folder)

                for f_t_c in folders_to_copy:
                    new_folders.append(destination + '\\' + f_t_c.replace(main_patch, ''))
                    folders[destination + '\\' + f_t_c.replace(main_patch, '')] = folders[f_t_c]

                print('new_folders')
                print(new_folders)

                for folder in new_folders:
                    script_dir = main_directory
                    new_folder_path = os.path.join(script_dir, folder)
                    if not (os.path.exists(new_folder_path) and os.path.isdir(new_folder_path)):
                        os.makedirs(new_folder_path)

                for folder in new_folders:
                    script_dir = main_directory
                    folder_path = os.path.join(script_dir, folder)
                    if self.is_in_dict(destination + '\\' + folder.replace(main_patch, ''), folders):
                        new_folder_path = os.path.join(script_dir,
                                                       destination + '\\' + folder.replace(main_patch, ''))
                    else:
                        new_folder_path = os.path.join(script_dir, destination)
                    print(folder_path)
                    print(new_folder_path)
                    list = os.listdir(folder_path)
                    print(list)
                    if len(list) > 0:
                        for item in list:
                            if '.' in item:
                                print(item)
                                shutil.copy(folder_path + '\\' + item, new_folder_path + '\\' + item)

            else:
                self.show_error('Нельзя скопировать из папки с уровнем секретности выше чем у папки назначения')
        else:
            parent_folders = []
            folder_name_parts = source.split('\\')
            while (len(folder_name_parts) > 1):
                folder_name_parts.pop(len(folder_name_parts) - 1)
                parent_folder_name = '\\'.join(folder_name_parts)
                parent_folders.append(parent_folder_name)

            can_copy = True
            for parent in parent_folders:
                if int(access_levels[folders[parent]]) > int(access_levels[folders[destination]]):
                    can_copy = False
            if can_copy:
                if int(access_levels[folders[source]]) <= int(access_levels[folders[destination]]):
                    print('Copy')
                    new_folders = []

                    for folder in folders:
                        if folder.startswith(source):
                            folders_to_copy.append(folder)

                    for f_t_c in folders_to_copy:
                        new_folders.append(destination + '\\' + f_t_c.replace(main_patch, ''))
                        folders[destination + '\\' + f_t_c.replace(main_patch, '')] = folders[f_t_c]

                    print('new_folders')
                    print(new_folders)

                    for folder in new_folders:
                        script_dir = main_directory
                        new_folder_path = os.path.join(script_dir, folder)
                        if not (os.path.exists(new_folder_path) and os.path.isdir(new_folder_path)):
                            os.makedirs(new_folder_path)

                    for folder in new_folders:
                        script_dir = main_directory
                        folder_path = os.path.join(script_dir, folder)
                        if self.is_in_dict(destination + '\\' + folder.replace(main_patch, ''), folders):
                            new_folder_path = os.path.join(script_dir,
                                                           destination + '\\' + folder.replace(main_patch, ''))
                        else:
                            new_folder_path = os.path.join(script_dir, destination)
                        print(folder_path)
                        print(new_folder_path)
                        list = os.listdir(folder_path)
                        print(list)
                        if len(list) > 0:
                            for item in list:
                                if '.' in item:
                                    print(item)
                                    shutil.copy(folder_path + '\\' + item, new_folder_path + '\\' + item)

                else:
                    self.show_error('Нельзя скопировать из папки с уровнем секретности выше чем у папки назначения')
            else:
                self.show_error('Нельзя скопировать из папки с уровнем секретности выше чем у папки назначения')

        json_update()
        self.access_levels_table_update()
        self.folders_table_update()
        self.ui_reset()

    def copy_folder_ex(self):
        source = self.folder_to_copy.text()
        destination = self.folder_destination.text()

        if is_valid_folder_name(source):
            if self.is_in_dict(source, folders):
                print(source)
            else:
                self.show_error("Такой папки не существует")
                return
        else:
            self.show_error("Неккоректное имя папки для копирования")
            return

        if is_valid_folder_name(destination):
            if self.is_in_dict(destination, folders):
                print(destination)
            else:
                self.show_error("Такой папки не существует")
                return
        else:
            self.show_error("Неккоректное имя папки назначения")
            return

        for_folders = []
        not_for_files = []
        for_files = []

        main_patch = ''

        if source.count('\\') > 0:
            patch_from_splitted = source.split('\\')
            patch_from_splitted.pop(len(patch_from_splitted) - 1)
            patch_from = '\\'.join(patch_from_splitted)
            print(patch_from)
            main_patch = patch_from + '\\'
            if not (int(access_levels[folders[patch_from]]) <= int(access_levels[folders[destination]])):
                self.show_error("Нельзя копировать в папку с меньшим уровнем секретности")
                return

        print('*копирование*')
        for folder in folders:
            if folder.startswith(source):
                if int(access_levels[folders[folder]]) <= int(access_levels[folders[destination]]):
                    for_files.append(folder)
                else:
                    not_for_files.append(folder)

        for folder in folders:
            for from_for_files in for_files:
                if (from_for_files != folder) and folder.startswith(from_for_files):
                    patch_from_splitted = folder.split('\\')
                    patch_from_splitted.pop(len(patch_from_splitted) - 1)
                    patch_from = '\\'.join(patch_from_splitted)
                    for_folders.append(patch_from)
                    break

        extra_for_files = []
        for f in for_files:
            for n_f in not_for_files:
                if f.startswith(n_f) and (n_f != f):
                    extra_for_files.append(f.replace(n_f + '\\', ''))
                else:
                    extra_for_files.append(f)

        print('for_files')
        print(for_files)
        print('not_for_files')
        print(not_for_files)
        print('for_folders')
        print(for_folders)

        new_folders = []
        for f_fol in for_folders:
            new_folders.append(destination + '\\' + f_fol.replace(main_patch, ''))
            folders[destination + '\\' + f_fol.replace(main_patch, '')] = folders[f_fol]

        print('new_folders')
        print(new_folders)

        for folder in new_folders:
            script_dir = main_directory
            new_folder_path = os.path.join(script_dir, folder)
            if not (os.path.exists(new_folder_path) and os.path.isdir(new_folder_path)):
                os.makedirs(new_folder_path)

        for folder in for_files:
            script_dir = main_directory
            folder_path = os.path.join(script_dir, folder)
            if self.is_in_dict(destination + '\\' + folder.replace(main_patch, ''), folders):
                new_folder_path = os.path.join(script_dir, destination + '\\' + folder.replace(main_patch, ''))
            else:
                new_folder_path = new_folder_path = os.path.join(script_dir, destination)
            print(folder_path)
            print(new_folder_path)
            list = os.listdir(folder_path)
            print(list)
            if len(list) > 0:
                for item in list:
                    if '.' in item:
                        print(item)
                        shutil.copy(folder_path + '\\' + item, new_folder_path + '\\' + item)

        json_update()
        self.access_levels_table_update()
        self.folders_table_update()


def json_update():
    # Создание данных для записи в JSON файл
    data = {"access_levels": access_levels}

    # Запись данных в JSON файл
    with open(access_levels_json_path, "w") as json_file:
        json.dump(data, json_file)
        json_file.close()
    print(f"Данные записаны в JSON файл: {access_levels_json_path}")

    # Создание данных для записи в JSON файл
    data = {"folders": folders}

    # Запись данных в JSON файл
    with open(folders_json_path, "w") as json_file:
        json.dump(data, json_file)
        json_file.close()
    print(f"Данные записаны в JSON файл: {folders_json_path}")


def get_data_from_json():
    # Чтение данных из JSON файла при старте программы
    data_from_json = {}
    try:
        with open(access_levels_json_path, "r") as json_data:
            print(json_data)
            data_from_json = json.load(json_data)
            print(data_from_json)
            json_data.close()
    except FileNotFoundError:
        print("Файл не найден.")
        return

    for access_level in data_from_json["access_levels"]:
        access_levels[access_level] = data_from_json["access_levels"][access_level]
    print("Данные взяты из JSON")
    print(access_levels)

    # Чтение данных из JSON файла при старте программы
    data_from_json = {}
    try:
        with open(folders_json_path, "r") as json_data:
            print(json_data)
            data_from_json = json.load(json_data)
            print(data_from_json)
            json_data.close()
    except FileNotFoundError:
        print("Файл не найден.")
        return

    for folder in data_from_json["folders"]:
        folders[folder] = data_from_json["folders"][folder]
    print("Данные взяты из JSON")
    print(folders)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    #app.setStyle('Windows')

    window = MainWindow()
    window.setWindowTitle("Folder Management")  # Изменяем заголовок окна
    window.show()
    get_data_from_json()
    window.access_levels_table_update()
    window.folders_table_update()
    sys.exit(app.exec_())

