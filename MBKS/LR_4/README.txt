Задача: разработать программу, управляющую уровнями секретности папок в файловой системе и контролирующую информационные потоки между ними.

Основные функции программы делятся на две части — работа с уровнями секретности и копирование файлов.

Работа с уровнями секретности:
1. Создание (с заданным именем), изменение (имя и секретность) и удаление уровней секретности. Все изменения в уровнях секретности внутри программы должны влиять на папки, которым этим уровни назначены.
2. Могут существовать уровни секретности, которые не установлены ни для одной папки.
3. Создание (с заданным именем), переименование и удаление папок и подпапок внутри заданной корневой папки.
4. Новые папки должны создаваться с минимальным доступным уровнем секретности.
5. Как следствие, в списке всегда должен быть хотя бы один уровень секретности, который считается минимальным.
6. Выбор уровня секретности для папок и подпапок из нескольких заданных в программе вариантов.

Копирование файлов:
1. Копирование файлов между папками согласно модели Белла — Лападулы. При этом копируются все файлы, лежащие внутри папки.
2. Выбор папок для копирования происходит в интерфейсе программы. При этом должны отображаться только папки, подходящие под выбранный уровень секретности.
3. Предусмотрите работу со вложенностью папок — папки разных уровней секретности могут быть вложенными друг в друга, копирование должно учитывать эту ситуацию.

Корнем файловой системы в этой работе считается заранее выбранная папка на ваше усмотрение — например, "C:\\LAB4".

---------------------------------------------------------
Обратите внимание: в этой работе вы имеете дело с настоящими папками и файлами в файловой системе, но уровнями секретности и копированием управляет ваша программа. Не нужно придумывать, как реализовать «настоящие» уровни секретности для папок внутри ОС, достаточно хранить и обрабатывать список уровней секретности в привязке к папкам где-то в системе.
---------------------------------------------------------

Требования к программе: приложение с пользовательским интерфейсом, язык программирования любой, все поля подписаны, предусмотрена обработка ошибок. Программа должна быть скомпилирована в ехе-файл, иметь иконку и открываться отдельно от среды разработки