
#include <syscalls.h>
#include <video.h>

#include <keyboard.h>

#define EOF 	-1

extern char keyboard_kbuffer[KEYBOARD_BUFFER_SIZE];
extern int keyboard_rpos;
extern int keyboard_wpos;
extern bool keyboard_buffer_loop;

void sys_write(int fd, char* s, int len) {

	uint16_t colorbk;

	switch (fd) {
	case FD_STDOUT:
		video_write_string(s);
		break;

	case FD_STDERR:

		colorbk = video_get_color();

		video_set_color(COLOR_RED, COLOR_BLACK);

		video_write_line(s);

		video_set_full_color(colorbk);
		break;


	}



}
//aseguramos que len no sea mayor al tamaño maximo del buffer
//aseguramos el buen manejo del flag de loop 

int sys_read(int fd, char* s, int len) {

	int read = 0;
	bool eof = FALSE;

	char c;

	while (read < len && !eof) {

		while (keyboard_rpos == keyboard_wpos && keyboard_buffer_loop == FALSE) {

		}

		c = keyboard_kbuffer[keyboard_rpos];

		if (c == '\n') {

			eof = TRUE;

		} else {

			s[read] = c;


			read++;

		}


		keyboard_rpos++;

		if (keyboard_rpos == KEYBOARD_BUFFER_SIZE - 1) {
			keyboard_buffer_loop = FALSE;
			keyboard_rpos = 0;
		}

	}

	if (eof) {
		return EOF; //ojo con esto, sys read SIEMPRE deberia retornar la cantidad de caracteres que leyo, 
					//sin importar la condicion de corte eso deberia analizarlo el receptor del buffer.
	}

	return read;
}

