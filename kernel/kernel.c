/*
void test(){

}
*/

void main() {

    /*----------------------*/
    // Clear

    volatile unsigned short *video = (volatile unsigned short*)0xB8000;

    for (int i = 0; i < 80 * 25; i++) {
        video[i] = 0x0700 | ' ';
    }
    
    /*----------------------*/
    // Display message

    *video = (volatile unsigned short*)0xB8000;

    const char *str = "Welcome to OuranOS!";

    for (int i = 0; str[i] != '\0' && (0 + i) < 80 * 25; i++) {
        video[1 + i] = 0x0700 | str[i];
    }
    
    /*----------------------*/
    // Test

    //test();
    
    while (1) {}
}