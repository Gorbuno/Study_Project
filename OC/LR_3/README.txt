Написать программу 1, которая при запуске принимает аргументы командной строки,
а затем в цикле выводит каждый аргумент на экран с задержкой в одну секунду.

Программа 1 должна выводить на экран свой идентификатор и идентификатор процесса-родителя.

Программа 1 должна формировать код завершения.

Программа 1 будет исполнять роль дочернего процесса.

Написать программу 2, которая запускает программу 1 в качестве дочернего процесса
с помощью вызовов fork() и exec().

Программа 2 должна вывести на экран идентификатор процесса-родителя, 
свой идентификатор и идентификатор дочернего процесса.

Программа 2 должна сформировать набор параметров для передачи в 
дочерний процесс аргументов командной строки.

Программа 2 должна ожидать завершения дочернего процесса, проверяя событие завершения
каждую половину секунды, а по завершению дочернего процесса вывести на экран код завершения.

Программа 2 будет исполнять роль родительского процесса.