
#include <libc.h>


//DEBERIAMOS PONERLE COMANDOS.C O ALGO ASI, NO LE MODIFIQUE EL NOMBRE POR SI ALGUNO ESTABA TOCANDO EL ARCHIVO

void command_echo(char * in) {

	printf(in);

}


void command_time() {
	

	printf("\n");
	printf("Mostrando la hora");
	printTime();
}
void command_settime(int hours, int minutes, int seconds) {

	printf("\n");
	if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
		printf("Horario invalido.");
	}
	printf("Seteando la hora");
}
void command_backcolor(int color) {

	printf("\n");
	/*if(color invalido){
		return;
		}
	*/

	//CREO -HABRIA QUE PREGUNTAR- que tendriamos que definir nuestras propias syscalls
	//para poder llamar a las funciones de kernel que permiten cambiar colores

	//por ejemplo nose la interrupcion 55 recibe un parametro que es el numero de color y llama a la funcion set_bkg_color
	printf("Color cambiado");

}
void command_fontcolor(int color) {

	printf("\n");
	/*if(color invalido){
		return;
		}
	*/

	//idem fc anterior
	printf("Color cambiado");

}
void command_exit() {

	printf("\n");
	printf("Saliendo..");

}

void command_restart() {


}


void command_clean() {

	//idem colores, llamar a la funcion clear_screen de kernel

}
void command_refresh() {

	//idem idem idem idem idem, llama a refresh de kernel

}