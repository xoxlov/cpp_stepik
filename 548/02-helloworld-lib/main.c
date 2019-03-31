// Разделяемые библиотеки (shared libraries) (lib share gcc ldd elf)
// http://www.opennet.ru/base/dev/shared_lib_intro.txt.html

#include "hello.h"

int main()
{
	hello_message("Vasya");
	return 0;
}

/*
 * Для вывода символических имен объектного(бинарного) файла используется nm
 * Для сборки динамической библиотеки gcc требуется указать опцию --shared
 * с++filt используется для восстановления исходного имени функций (Demangle) на языках на C++ и Java
 * В основе работы make лежит информация о зависимостях частей проекта
 *
 */