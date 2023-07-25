#include "libreria.hpp"
//USUARIO CON VALORES QUEMADOS//
inicioSesion empleado[3] = {
    { "default1", "1234" },
    { "default2", "5678" },
    { "default3", "9012" }
};
  //COMIDAS//
menuComidas comida[10];
//Variables
//Medir cantidad de comidas
size_t numElementos = sizeof(comida) / sizeof(comida[0]);
//Inicio sesion
string contrasenaInsertada;
string usuarioInsertado;
//Nombre del archivo y fecha
string nombreFinal;
string fecha;

//Variables globales para menus
bool key =false;
int eleccion;
int resultadoPopularidad;
float totalDiario = 0;
float total =0;
//Vectores para guardar lo que se vende (por index)
vector<int> productosVendidos;
vector<int>cantidadVendida;
vector<float> totalProducto;
vector<int> posicionValorPopular;
vector<int> cantidadProductoPopular;

void LimpiarConsola() {
    //Verifica sistema para limpiar consola
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");  
    #endif
}
void EsperarEnter(){
    cin.ignore(); 
    cin.get(); 
}
void AsignarValoresStruct(){
    //Abrir archivo
    ifstream archivoStruct("Menu.txt");
    if(archivoStruct.is_open()){
        //Definir linea
        string linea;
        int i = 0;
        while (getline(archivoStruct, linea) && i < 10) {
                // Leer línea
                stringstream ss(linea);
                //Definir Valores de nombre y precio
                string nombre;
                float precioQuemado;

                // Extraer los valores separados por coma
                getline(ss, nombre, ',');
                ss >> precioQuemado;

                // Asignar los valores a la estructura
                comida[i] = {nombre, precioQuemado, 0, 0};

                i++;
        }
        //Cerrar archivo
        archivoStruct.close();
         ComprobarFecha();
    }
    else{
        cout << "Problema de lectura de archivo menu, cerrando.. :(" << endl;
        EsperarEnter();
        return;
    }

}
void  ComprobarFecha(){
    time_t now = time(0);
    tm * time = localtime(&now);
    fecha = to_string(time->tm_mday)+"-"+to_string(time->tm_mon+1)+"-"+to_string(time->tm_year + 1900);
    
    ComprobarArchivoDia();
}
void ComprobarArchivoDia() {
    ifstream archivoDiario(fecha + ".txt", ios::in);
    if (archivoDiario.good()) {
        
        archivoDiario.close(); // Cierra el archivo después de la comprobación
    }
    else {
        ofstream nuevoArchivo(fecha + ".txt");
        if (nuevoArchivo.good()) {
            nuevoArchivo.close();
        } else {
            cout << "No se pudo crear el archivo" << endl;
            EsperarEnter();
            LimpiarConsola();
        }
    }
    ComprobarArchivoPopular();
}
void ComprobarArchivoPopular(){
    ifstream archivoDiario("ProductosPopulares.txt", ios::in);
    if (archivoDiario.good()) {
        
        archivoDiario.close(); // Cierra el archivo después de la comprobación
    }
    else {
        ofstream nuevoArchivo("ProductosPopulares.txt");
        if (nuevoArchivo.good()) {
            nuevoArchivo.close();
        } else {
            cout << "No se pudo crear el archivo" << endl;
            EsperarEnter();
            LimpiarConsola();
        }
    }
}
void MenuPrimario(){
   
    do{
        cout<<"---------------Sabor Casero----------------"<<endl;
        cout<<"| 1. Mostrar menu                         |"<<endl;
        cout<<"| 2. Iniciar Sesión                       |"<<endl;
        cout<<"| 3. Salir                                |"<<endl;
        cout<<"-------------------------------------------"<<endl;
        cin>>eleccion;
        LimpiarConsola();
        switch(eleccion){
            case 1: 
                MostrarComida();
                break;
            case 2:
                PreguntarDato();
                break;
            case 3:
                cout<<"SALIENDO....."<<endl;
                exit(-1);
                break;
            default:
            key = false;
        }
       
        
   }
   while(key == false);
}
void PreguntarDato(){
    do{
        cout<<"---------------Sabor Casero----------------"<<endl;
        cout<<"Inserte nombre de usuario"<<endl;
        cin>>usuarioInsertado;
        cout<<"Inserte contraseña"<<endl;
        cin>>contrasenaInsertada;
        
        LimpiarConsola();
    }
    while( Login(usuarioInsertado, contrasenaInsertada) == false);
    MenuSecundario();
    LimpiarConsola();

}
bool Login(string,string){
    bool sesionCorrecto = false;
    for(int i = 0; i<3; i++){
        if(empleado[i].Usuario == usuarioInsertado && empleado[i].contrasena == contrasenaInsertada){
            sesionCorrecto = true;
        }
        
    }
    return sesionCorrecto;
};
void MenuSecundario(){
    LimpiarConsola();
    do{
        cout<<"---------------Sabor Casero----------------------"<<endl;
        cout<<"| 1.Mostrar menu                                |"<<endl;
        cout<<"| 2.Mostrar ticket de compra                    |"<<endl;
        cout<<"| 3.Leer ventas diarias                         |"<<endl;
        cout<<"| 4.Leer comida mas popular                     |"<<endl;
        cout<<"| 5.Cerrar sesión                               |"<<endl;
        cout<<"-------------------------------------------------"<<endl;
        cin>>eleccion;
        LimpiarConsola();
        switch(eleccion){
            case 1: 
                MostrarComida();
            break;
            case 2:
                VenderProducto();
            break;
            case 3:
                PreguntarNombreVentas();
            break;
            case 4:
               ImprimirDatos();
            break;
            case 5:
                cout<<"CERRANDO SESION..."<<endl;
                LimpiarConsola();
                MenuPrimario();
                break;
            default:
                key = false;
        }
        
    }
        
        
    while(key == false);
}
void MostrarComida() {
    cout << "-------------------------MENÚ--------------------------" <<endl;
    cout << "|   Código   |   Nombre Producto   |   Precio         |" <<endl;
    cout << "-------------------------------------------------------" <<endl;
    //Iteramos cada valor del struct de comidas
    for (int j = 0; j < numElementos; j++) {
        cout << "|    " <<setw(2) <<left << j + 1 << "      |    " <<setw(16) <<left << comida[j].nombreComida << " |    $" <<setw(9) <<right <<fixed <<setprecision(2) << comida[j].precioUnitario << "    |" <<endl;
    }
    cout << "-------------------------------------------------------" <<endl;
    EsperarEnter();
    LimpiarConsola();
}
void VenderProducto(){
  //Variables locales para verificar el producto y cantidad    
  int idProducto =0;
  int cantidadProducto=1;
  string continuarTicket;
  
  do{
        LimpiarConsola();
        cout << "---------------------------------IMPRESION-TICKET------------------------------" << endl;
        for (int i = 0; i < 4; i++) {
            for (int j = i; j < numElementos; j += 4) {
                cout << setw(3) <<"["<< j+1 << "]" << setw(12) << left << comida[j].nombreComida << " $" << setw(5) << right << fixed << setprecision(2) << comida[j].precioUnitario << "   ";
            }
            cout << endl;
        }
        
        cout << "-------------------------------------------------------------------------------" << endl;
        cout<<endl;
        cout <<"Inserte identificador de producto(1-"<<numElementos<<")"<<endl;
        cin  >>idProducto;
        //Resta 1 para ajustar el index
        idProducto -= 1;
        if (idProducto < 0 || idProducto > numElementos-1) {
            cout << "Producto no valido" << endl;
            EsperarEnter(); 
            continue; 
        }
        cout<<"Seleccionó: "<<comida[idProducto].nombreComida<<" ("
        <<comida[idProducto].precioUnitario<<"$)"<<endl;
        
        cout<<"Inserte cantidad de unidades"<<endl;
        cin>>cantidadProducto;
          if (cantidadProducto <1) {
            cout << "Cantidad invalida" << endl;
            EsperarEnter();
            continue; 
        }
        cout<<"Total:"<<CalculoTotal(idProducto,cantidadProducto)<<"$"<<endl;
        cout<<"¿Desea insertar mas productos (y/n)?"<<endl;
        cin>>continuarTicket;
        if(continuarTicket =="Y" || continuarTicket =="Y"){
             LimpiarConsola();
             key = false;
        }
        else if(continuarTicket =="n" || continuarTicket == "N"){
            LimpiarConsola();
            ImpresionTicket(productosVendidos, cantidadVendida);
            MenuSecundario();
        }
        else{
            LimpiarConsola();
            key = false;
        }
    }
  while(key == false);
}
float CalculoTotal(int idProducto, int cantidadProducto){
    //Variables para guardar al vector
    int numeroProductos = cantidadProducto;
    int tipoProducto = idProducto;
    productosVendidos.push_back(tipoProducto);
    cantidadVendida.push_back(cantidadProducto);
    comida[tipoProducto].cantidadVentas = ((comida[tipoProducto].precioUnitario)*numeroProductos);
    
    comida[tipoProducto].popularidad += numeroProductos;
    
    total += ((comida[tipoProducto].precioUnitario)*numeroProductos);
    return total;
}

void ImpresionTicket(vector<int> , vector<int>){
    cout << "---------------------TICKET------------------------------------------" << endl;
    cout << "| Producto           | Precio   | Unidades | Total por productos    |" << endl;
    cout << "|-------------------------------------------------------------------|" << endl;

    for (int j = 0; j < productosVendidos.size(); j++) {
        
    
        cout << "| " << setw(19) << left << comida[productosVendidos[j]].nombreComida
             << "| $" << setw(8) << right << fixed << setprecision(2) << comida[productosVendidos[j]].precioUnitario
             << "| " << setw(8) << right << cantidadVendida[j]
             << " | $" << setw(20) << right << fixed << setprecision(2) << comida[productosVendidos[j]].cantidadVentas << "  |" << endl;
    }
    cout <<" -------------------------------------------------------------------|"<<endl;
    cout << "| Total final:       | $" << setw(8) << right << fixed << setprecision(2) <<"  "<< total << "                               |" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    
    AgregarTicketArchivo();
    EsperarEnter();
    MenuSecundario();
}
void AgregarTicketArchivo(){
    ofstream archivo(fecha +".txt", ios::app);
    if (archivo.is_open()) {
        //Guardamos identificador
        archivo<<"ticket"<<endl;
        for (int j = 0; j < productosVendidos.size(); j++) {
        archivo << productosVendidos[j]<<","
              << cantidadVendida[j]<<","
              << comida[productosVendidos[j]].cantidadVentas << endl;
        }
        archivo<<"?"<<total<<"?"<<endl;
        archivo<<"***"<<endl;
        
        archivo.close();
        cout << "Archivo actualizado exitosamente"<< endl;
         EsperarEnter();
          LimpiarProductos();
        CargarValoresPopularidad();
        ReiniciarPopularidad(); // Reiniciar popularidad después de cargar los datos
        LimpiarConsola();
       
    
       
        
        
    } 
    else {
        cout << "No se pudo guardar" << endl;
        EsperarEnter();
        LimpiarConsola();
        
    }
    
}
void LimpiarProductos(){
    //Guardar valores para el corte de caja//
   
    //Limpiar valores ya guardados
    cantidadVendida.clear();
    productosVendidos.clear();
    totalProducto.clear();
    totalDiario = 0;
    for(int k =0; k<numElementos-1; k++){
        comida[k].cantidadVentas = 0;
        
    }
    total = 0;
   
}

void PreguntarNombreVentas(){

 string continuar;
    do{
     
     cout<<"Inserte nombre del archivo:"<<endl;
     cin>>nombreFinal;
     nombreFinal = nombreFinal + ".txt";
     if (VerificarExistenciaArchivo(nombreFinal) == true) {
        cout<<"Acceso verificado.."<<endl;
        LimpiarConsola();
        ImprimirVentasDiarias(nombreFinal);        
     }
     else{
        cout<<"No existe un archivo con ese nombre"<<endl;
        cout<<"¿Reintentar?(y/n)"<<endl;
        cin>>continuar;
        LimpiarConsola();
        if(continuar =="y"){
             key = false;    
             LimpiarConsola();
        }
        if(continuar == "n"){
          MenuSecundario();
        }
        
     }   
    }
    while(key == false);
}
bool VerificarExistenciaArchivo(string nombreFinal) {
    ifstream archivo(nombreFinal);
    return archivo.good(); // Devuelve true si el archivo existe
}
void ImprimirVentasDiarias(string nombreFinal){
    LimpiarConsola();
      //Abrir archivo
    ifstream archivo(nombreFinal);
    if(archivo.is_open()){
        //Definir linea
        bool nuevoTicket = false;
        string linea;
        string totalRecibo;
        float totalGlobal = 0.0; 
        int j = 0;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string idStr;
            string unidadesStr;
            string totalStr;
            
            if(linea.substr(0, 6) == "ticket") {
            nuevoTicket = true;
             cout << "---------------------TICKET------------------------------------------" << endl;
             cout << "| Producto           | Precio   | Unidades | Total por productos    |" << endl;
             cout << "|-------------------------------------------------------------------|" << endl;

            } 
            else if(linea.substr(0,3)=="***"){
                nuevoTicket = true;
                cout<<"---------------------------------------------------------------------"<<endl;
                cout<<""<<endl;
            }
           else if (linea.substr(0, 1) == "?") {
                   size_t primerPos = 1; // Comenzar en la posición después del primer símbolo "?"
                   size_t segundoPos = linea.find("?", primerPos); // Buscar el segundo símbolo "?"
                    //Comprobamos que no sea una posicion invalida
                    if (segundoPos != string::npos) {
                        // Extraer el valor entre primerPos y segundoPos
                        float valorEntreSimbolos = stof(linea.substr(primerPos, segundoPos - primerPos));
                        
                        // Ahora tienes el valor entre los símbolos "?" en la variable valorEntreSimbolos
                        cout <<"|-------------------------------------------------------------------|"<<endl;
                        cout <<"| Total ticket:       | $" << setw(8) << right << fixed << setprecision(2) <<"  "<< valorEntreSimbolos << "                              |" << endl;
                        //Aumentar total global del dia
                        totalGlobal += valorEntreSimbolos; 
                     
                    }

                
            }
            
            else if (nuevoTicket){
            getline(ss, idStr, ',');
            getline(ss, unidadesStr, ',');
            getline(ss, totalStr, ',');

            int id = stoi(idStr);
            int unidades = stoi(unidadesStr);
            float total = stof(totalStr);
            cout << "| " << setw(19) << left << comida[id].nombreComida
             << "| $" << setw(8) << right << fixed << setprecision(2) << comida[id].precioUnitario
             << "| " << setw(8) << right << unidades
             << " | $" << setw(20) << right << fixed << setprecision(2) <<total<< "  |" << endl;
            }
       
        
           
        }
         cout <<"---------------------------------------------------------------------"<<endl;
         cout <<"| Total del dia:       | $" << setw(8) << right << fixed << setprecision(2) <<"  "<< totalGlobal<<setw(30)<< "   |"<<endl;
         cout <<"---------------------------------------------------------------------"<<endl;
        //Cerrar archivo
        archivo.close();
        EsperarEnter();
        LimpiarConsola();
        MenuSecundario();
    }
    else{
        cout << "Problema de lectura de archivo" << endl;
        EsperarEnter();
        MenuSecundario();
    }
    
}
void CargarValoresPopularidad(){
    ifstream archivo(fecha +".txt");
    if(archivo.is_open()){
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string caracterId;
            string caracterCantidad;
            if (linea.substr(0, 6) == "ticket" || linea.substr(0, 3) == "***" || linea.substr(0, 1) == "?") {
                continue;
            }
            getline(ss, caracterId, ',');
            getline(ss, caracterCantidad, ',');
            int id = stoi(caracterId);
            int unidades = stoi(caracterCantidad);
            GuardarProductosPopulares(id, unidades);
        }
        archivo.close();
        CalculoProductoMasVendido();
       
    }
    else{
        cout << "Problema de lectura de archivo" << endl;
        EsperarEnter();
        MenuSecundario();
    }
    
}
void GuardarProductosPopulares(int id, int unidades){
  posicionValorPopular.push_back(id);
  cantidadProductoPopular.push_back(unidades);
}
void CalculoProductoMasVendido(){
    ReiniciarPopularidad();
        for (int j = 0; j < posicionValorPopular.size(); j++) {
            int id = posicionValorPopular[j];
            int unidades = cantidadProductoPopular[j];
            comida[id].popularidad += unidades; 
    }
    comida[9].popularidad = comida[9].popularidad/2;
    posicionValorPopular.clear();
    cantidadProductoPopular.clear();
    CompararPopularidad();
}
void CompararPopularidad() {
 
  int valorMaximo = 0;
    vector<int> idsMaximos;    
    // Encuentra el valor máximo de popularidad
        for (int i = 0; i < numElementos; i++) {
            if (comida[i].popularidad > valorMaximo) {
                valorMaximo = comida[i].popularidad;
                idsMaximos.clear();
                idsMaximos.push_back(i);
            } else if (comida[i].popularidad == valorMaximo) {
                idsMaximos.push_back(i);
            }
        }
   
    GuardarArchivoPopularidad(idsMaximos, valorMaximo);
    ReiniciarPopularidad();
}
void GuardarArchivoPopularidad(vector<int> idsMaximos, int valorMaximo) {
    ifstream archivoLectura("ProductosPopulares.txt");
    ofstream archivoTemporal("Temporal.txt");
    if (archivoLectura.is_open() && archivoTemporal.is_open()) {
        string linea;
        bool fechaEncontrada = false;
        while (getline(archivoLectura, linea)) {
            stringstream ss(linea);
            string idValor, fechaLinea;
            getline(ss, idValor, '?');
            getline(ss, fechaLinea, '?');
            
            if (fecha == fechaLinea) {
                fechaEncontrada = true;
                archivoTemporal << idsMaximos[0] << "," << valorMaximo << "?" << fecha << "?" << endl;
                 ReiniciarPopularidad();
                 
            } else {
                archivoTemporal << linea << endl;
                 ReiniciarPopularidad();
                 // Escribe la línea existente tal cual
            }
        }
        
        // Agrega la nueva línea si la fecha no fue encontrada
        if (!fechaEncontrada) {
            archivoTemporal << idsMaximos[0] << "," << valorMaximo << "?" << fecha << "?" << endl;
             ReiniciarPopularidad();
            
        }
        
        archivoLectura.close();
        archivoTemporal.close();
        remove("ProductosPopulares.txt");
        rename("Temporal.txt", "ProductosPopulares.txt");
        idsMaximos.clear();
        valorMaximo = 0;
        ReiniciarPopularidad();
        MenuSecundario();
      
       
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void ReiniciarPopularidad(){
    for(int i=0; i<numElementos-1; i++){
        comida[i].popularidad = 0;
    }
}
void ImprimirDatos() {
    LimpiarConsola();
    ifstream archivo("ProductosPopulares.txt");
    if (archivo.is_open()) {
        string linea;
        cout << "                       PRODUCTOS MAS VENDIDOS                        " << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "| Producto                |  Cantidad                  | Fecha       |" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string idStr;
            string cantidad;
            string fechaVenta;
            getline(ss, idStr, ',');           // Obtener el ID hasta la coma
            getline(ss, cantidad, '?');        // Obtener la cantidad entre la coma y el signo de interrogación
            getline(ss, fechaVenta, '?');      // Obtener la fecha entre los dos signos de interrogación

            int id = stoi(idStr);              // Convertir el ID a entero si es necesario
            int unidades = stoi(cantidad);      // Convertir la cantidad a entero si es necesario

            cout << "| " << setw(24) << left << comida[id].nombreComida << "|  " << setw(18) << left << unidades << "        | " << fechaVenta << "   |" << endl;
        }
        cout << "----------------------------------------------------------------------" << endl;
        archivo.close();
        EsperarEnter();
        LimpiarConsola();
        MenuSecundario();
    } else {
        cout << "Problema de lectura de archivo" << endl;
        // Resto del código en caso de error
    }
}