
#include <stdarg.h>
#include <syscalls.h>
#include <libc.h>

static void* mallocBuffer = (void*)0x600000;

static void* lastMalloc;

void* malloc(int len) {

	lastMalloc = mallocBuffer;

	mallocBuffer += len * sizeof(void*);

	return lastMalloc;

}

void* calloc(int len) {
	char* space = (char*)malloc(len);

	for (int i = 0; i < len; i++) {
		space[i] = (char)0;
	}

	return (void*)space;
}

void free(void* m) {

	if (m = lastMalloc) {
		mallocBuffer = m;
	}

}

int strpos(char* s, char n) {

	for (int pos = 0; s[pos] != 0; pos++) {
		if (s[pos] == n) {
			return pos;
		}
	}

	return -1;


}

static void vfprintf(FD fd, char* fmt, va_list ap) {

	char* str = calloc(MAX_PRINTF_LEN);
	//char* pos;
	int i = 0;
	int j = 0;
	//int fmtlen = strlen(fmt);

	//va_start(ap, fmt);


	// i: posicion en el fmt
	// j: posicion en el str
	while (fmt[i] != 0 && i < MAX_PRINTF_LEN - 1) {

		if (fmt[i] == '%') {

			i++;
			if (fmt[i] == 0) {
				//lo que le sigue al % es el final de la cadena
				str[j] = fmt[i];
				break;

			} else if (fmt[i] == '%') {

				str[j] = fmt[i];
				j++;
				i++;

			} else {
				// hay que procesar el siguiente caracter y actuar acorde


				switch (fmt[i]) {
				case 's': {
					//lo que se desea es imprimir unca cadena
					char* arg = va_arg(ap, char*);
					int k = 0;

					//k: posicion en el argumento

					while (arg[k] != 0) {
						str[j] = arg[k];
						j++;
						k++;
					}

					i++;
					break;
				}

				case 'i': {

					int arg = va_arg(ap, int);

					char* number = intToChar(arg);

					int k = 0;

					//k: posicion en el argumento

					while (number[k] != 0) {
						str[j] = number[k];
						j++;
						k++;
					}

					i++;
					break;

				}

				case 'c': {

					char arg = (char)va_arg(ap, int);

					str[j] = arg;
					j++;
					i++;
					break;

				}
				}



			}

		} else if (fmt[i] != 0) {
			str[j] = fmt[i];
			j++;
			i++;
		} else {
			str[j] = fmt[i];
			break;
		}

	}

	//va_end(ap);

	sys_write(fd, str, j);

}

void fprintf(FD fd, char* fmt, ...) {

	va_list ap;
	va_start(ap, fmt);

	vfprintf(fd, fmt, ap);

	va_end(ap);

}

void printf(char* fmt, ...) {

	va_list ap;
	va_start(ap, fmt);

	vfprintf(FD_STDOUT, fmt, ap);

	va_end(ap);

}

void putchar(char c) {

	sys_write(FD_STDOUT, &c, 1);
}

int strlen(char* str) {
	int size;
	for (size = 0; *str != '\0' ; str++) {
		size++;
	}

	return size;
}

int getchar() {

	static char buffer[2] = {0};

	char read = sys_read(FD_STDOUT, buffer, 1);

	if (read == EOF) {
		return EOF;
	}

	return (int) buffer[0];
}

int scanf(char* c, int len) {

	char read = sys_read(FD_STDOUT, c, len);

	return read;
}


int strcmp(const char* s1, const char* s2) {

	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}

	return *s1 - *s2;
}


// Verificado
char* strcpy(char* src, char* dest) {

	while (*src != 0) {
		*dest = *src;
		src++;
		dest++;
	}

	*dest = 0;

	return dest;
}


//Anda todo.. lo que no pude probar es sys_rtc_time y el putchar  lo demas anda!
void printTime() {

	int horas, minutos, segundos;

	sys_rtc_time(&horas, &minutos, &segundos);

	printf("El tiempo actual es: %i:%i:%i\n", BCD_to_DEC(horas), BCD_to_DEC(minutos), BCD_to_DEC(segundos));

}

//Verificado
char* intToChar(int number) {

	int i = 0;
	int j = 0;
	int cnt = 0;

	char* c = malloc(10);

	if (number < 0) {
		number = -number;
		c[i++] = '-';
	}

	while (number >= 10 ) {
		int dig = number % 10;
		number /= 10;
		c[i++] = dig + '0';
		cnt++;
	}
	c[i] = number + '0';

	while (cnt >= j) {
		char aux;
		aux = c[cnt];
		c[cnt--] = c[j];
		c[j++] = aux;
	}

	return c;

}

int BCD_to_DEC(int bcdval) {
	int  decval, temp;
	temp = (int)(bcdval / 16);
	decval = bcdval - 16 * temp;

	return decval;
}
