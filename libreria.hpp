#ifndef LIBRERIA_HPP
#define LIBRERIA_HPP
// Librerias utilizadas
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
// Estructura Inicio de sesion
struct inicioSesion
{
    string Usuario;
    string contrasena;
};

// Estructura de comidas
struct menuComidas
{
    string nombreComida;
    float precioUnitario;
    int popularidad;
    float cantidadVentas;
};
// Variables
// Medir cantidad de comidas
extern size_t numElementos;
// Inicio sesion
extern string contrasenaInsertada;
extern string usuarioInsertado;
// Nombre del archivo y fecha
extern string nombreFinal;
extern string fecha;
// Variables globales para menus
extern bool key;
extern int eleccion;
extern int resultadoPopularidad;
extern float totalDiario;
extern float total;

// Vectores para guardar lo que se vende (por index)
extern vector<int> productosVendidos;
extern vector<int> cantidadVendida;
extern vector<float> totalProducto;
/*Funciones*/
void LimpiarConsola();
void EsperarEnter();
// Asignar valores a struct
void AsignarValoresStruct();
void ComprobarFecha();
void ComprobarArchivoDia();
void ComprobarArchivoPopular();

// Menu Inicio de sesion
void MenuPrimario();
void PreguntarDato();
bool Login(string, string);
void MostrarComida();
// Menu central
void MenuSecundario();
void VenderProducto();
float CalculoTotal(int idProducto, int cantidadProducto);
void ImpresionTicket(vector<int> nombre, vector<int> cantidad);
void AgregarTicketArchivo();

void PreguntarNombreVentas();

// Reinicia los vectores de conteo
void LimpiarProductos();
// Verifica que exista archivo ventas
bool VerificarExistenciaArchivo(string nombreFinal);
void ImprimirVentasDiarias(string nombreFinal);
// Menu Productos mas vendidos
void CargarValoresPopularidad();
void GuardarProductosPopulares(int id, int unidades);
void CalculoProductoMasVendido();
void CompararPopularidad();
void GuardarArchivoPopularidad(vector<int> idsMaximos, int valorMaximo);
// Reinicia valor de popularidad al guardar
void ReiniciarPopularidad();
void ImprimirDatos();

#endif