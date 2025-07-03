void _start() {
    volatile char *video = (volatile char*)0xB8000;
    video[0] = 'O'; video[1] = 0x07;  // Affiche 'O'
    video[2] = 'K'; video[3] = 0x07;  // Affiche 'K'

    while (1) {
        // Boucle infinie pour éviter de quitter le programme
    }
}