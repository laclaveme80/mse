/*
    configuracao do editor de texto, é necessario
    compilar novamente para aplicar as mudancas
*/
static const unsigned int bold = 0; // true = 1, false = 0;
static const unsigned int theme = 3; // default: none
/*themes = {
    nightdark  // 3
    mc         // 2
    none       // 1
}*/
// define os atalhos
#define EXIT ('q' & 0x1f) // ctrl + q
#define SAVE ('s' & 0x1f) // ctrl + s
