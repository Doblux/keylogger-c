#include <linux/input.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input-event-codes.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("uso: ./%s /dev/input/<event_teclado>", argv[0]);
        exit(-1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error al abrir el dispositivo");
        return 1;
    }

    struct input_event ie;
    // value 1 = presionado, 0 = soltado, 2 = repetición

    const char *key_names[] = {
        [KEY_ESC] = "[ESC]", [KEY_1] = "1", [KEY_2] = "2", [KEY_3] = "3", [KEY_4] = "4",
        [KEY_5] = "5", [KEY_6] = "6", [KEY_7] = "7", [KEY_8] = "8", [KEY_9] = "9", [KEY_0] = "0",
        [KEY_MINUS] = "-", [KEY_EQUAL] = "=", [KEY_BACKSPACE] = "Borrar1", [KEY_TAB] = "\t",
        [KEY_W] = "W", [KEY_E] = "E", [KEY_R] = "R", [KEY_T] = "T", [KEY_Y] = "Y", [KEY_U] = "U",
        [KEY_I] = "I", [KEY_O] = "O", [KEY_P] = "P", 
        [KEY_LEFTBRACE] = "[", [KEY_RIGHTBRACE] = "]", [KEY_ENTER] = "\n", [KEY_LEFTCTRL] = "Ctrl_Izq",
        [KEY_A] = "A", [KEY_S] = "S", [KEY_D] = "D", [KEY_F] = "F", [KEY_G] = "G", 
        [KEY_H] = "H",  [KEY_J] = "J", [KEY_K] = "K", [KEY_L] = "L", [KEY_SEMICOLON] = "Ñ", [KEY_APOSTROPHE] = "´",
        [KEY_GRAVE] = "º", [KEY_LEFTSHIFT] = "[shift_izq]", [KEY_BACKSLASH] = "\\", 
        [KEY_Z] = "Z", [KEY_X] = "X", [KEY_C] = "C", [KEY_V] = "V", [KEY_B] = "B", [KEY_N] = "N", [KEY_M] = "M",
        [KEY_COMMA] = ",", [KEY_DOT] = ".", [KEY_SLASH] = "/", [KEY_RIGHTSHIFT] = "[shift_derecho]", [KEY_SPACE] = " ",
        [KEY_F1] = "[F1]", [KEY_F2] = "[F2]", [KEY_F3] = "[F3]", [KEY_F4] = "[F4]", [KEY_F5] = "[F5]",
        [KEY_F6] = "[F6]", [KEY_F7] = "[F7]", [KEY_F8] = "[F8]", [KEY_F9] = "[F9]", [KEY_F10] = "[F10]",
        [KEY_KP7] = "7", [KEY_KP8] = "8", [KEY_KP9] = "9", [KEY_KP4] = "4", [KEY_KP5] = "5", [KEY_KP6] = "6",
        [KEY_KP1] = "1", [KEY_KP2] = "2", [KEY_KP3] = "3", [KEY_KP0] = "0",
    };


    while (1)
    {
        read(fd, &ie, sizeof(ie));
        if (ie.type != EV_KEY)
            continue;
        if (ie.value != 1)
            continue;

        printf(key_names[ie.code]);
        // ¡IMPORTANTE! Forzar la salida a la terminal
        fflush(stdout);
    }

    close(fd);
    return 0;
}