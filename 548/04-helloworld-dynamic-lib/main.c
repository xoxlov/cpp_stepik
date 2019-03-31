#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

void (*hello_message)(const char *);

bool init_library() {
	void *hdl = dlopen("./libHello.so", RTLD_LAZY);
	if (NULL == hdl)
		return false;
	hello_message = (void (*)(const char*))dlsym(hdl, "hello_message");
	if (NULL == hello_message)
       		return false;	
	return true;
}

int main()
{
	if (init_library())
		hello_message("Vasya");
	else
		printf("Library was not loaded\n");
	return 0;
}

/* Комменты:
 *
 * По фэншую бы еще dlclose(hdl); сделать перед выходом, но hdl мы теряем внутри init_library(),
 * т.е.  hdl автоматически закрывается при выходе из области видимости. При завершении процесса, в котором был вызов
 * dlopen() ,какой-то системный процесс сам уменьшит на единицу счётчик ссылок для структуры, связанной с открытой
 * ﻿библиотекой. Стандарт ﻿POSIX не требует вызова ﻿dlclose() "to ever unload a library from address space﻿". И вызов
 * dlclose() не ﻿обязывает систему немедленно ﻿освободить структуру, связанную с библиотекой.
 *
 * // Альтернативный вариант, чтобы вызвать функцию
 * typedef void (*hello_msg)(const char *);
 *
 * union {
 *     hello_msg f;
 *     void *p;
 * } fu;
 * fu.p = dlsym(libh, "hello_msg");
 * fu.f("test");
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */