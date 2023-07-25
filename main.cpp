// Libreria usuario
#include "libreria.hpp"

// Verificar sistema operativo
#ifdef _WIN32
#include <cstdlib>
#else
#include <unistd.h>
#endif

using namespace std;

int main()
{   SetConsoleOutputCP(CP_UTF8);
    LimpiarConsola(); 
    //Guardar valores en el struct
    AsignarValoresStruct();
    // LLamamos al menu inicial de login
    MenuPrimario();
    return 0;
}