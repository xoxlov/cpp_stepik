// Разделяемые библиотеки (shared libraries) (lib share gcc ldd elf)
// http://www.opennet.ru/base/dev/shared_lib_intro.txt.html

#include "hello.h"

int main()
{
	hello_message("Vasya");
	return 0;
}
