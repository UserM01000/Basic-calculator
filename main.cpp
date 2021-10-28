#include <windows.h>
#include <bits/stdc++.h>

#define ID_LABEL 100
#define ID_BTNSALIR 101
#define ID_EDIT1 102
#define ID_EDIT2 103
#define ID_COMBOBOX 104
#define ID_RESOLVER 105
#define Contact 106


LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstanciaActual,HINSTANCE hInstanciaPrevia,LPSTR lpCmdLinea,int nCmdShow){

    HWND ventana; //manejador de ventana
    MSG mensaje; //intermediario para comunicar los mensajes de la aplicacion    WNDCLASSEX clase;
    WNDCLASSEX clase; //estructura que contienen un conjunto de elementos que caracterizan a una ventana

    clase.cbSize = sizeof(WNDCLASSEX); //tamaño de la clase es igual al tamaño de la estructura    clase.cbClsExtra = 0;
    clase.cbClsExtra = 0; //El número de bytes adicionales para asignar (El sistema inicializa los bytes a cero.)
    clase.style = CS_HREDRAW | CS_VREDRAW;  //se puede dibujar horizontalmente y verticalmente
    clase.lpfnWndProc = ProcediementoVentana;

    /* lpfnWndProc:
    Es la responsable de todo lo relativo al aspecto y al comportamiento de una ventana.
    Puntero a una función de este tipo, esa función es la que se encargará de procesar
    todos los mensajes para esa clase de ventana. Cuando registremos nuestra clase de
    ventana, tendremos que asignar a ese miembro el puntero a nuestro procedimiento de ventana.*/
    clase.hInstance = hInstanciaActual;
    clase.hIcon = LoadIcon(NULL,0);//Identificador de icono
    clase.hIconSm =LoadIcon(NULL,IDI_INFORMATION);//Elegimos que icono queremos
    clase.hCursor = LoadCursor(NULL,IDC_ARROW);//Identificador de cursor, elegimos la forma en que se mostrará
    clase.lpszClassName = "IdentificadorVentana"; //este es el identificador para pasarlo a CreateWindowsEx();
    clase.hbrBackground =CreateSolidBrush( RGB(233,240,252)); //color de la ventana

    if(!RegisterClassEx(&clase)){ //si no esta registrada la clase
        MessageBox( NULL,"No se pudo ejecutar la aplicacion","Error",MB_ICONERROR);
        return EXIT_FAILURE;
    }

    //WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU (para que no se maximice)
    ventana = CreateWindowEx(0,"IdentificadorVentana","Calculadora Basica",WS_OVERLAPPEDWINDOW |WS_SYSMENU,
                             400,80,560,630,HWND_DESKTOP,NULL,hInstanciaActual,NULL);

    CreateWindowW(L"Static",L"Ingrese un numero",WS_BORDER|WS_VISIBLE|WS_CHILD|SS_NOTIFY,90,100,150,20,ventana,(HMENU)ID_LABEL,hInstanciaActual,NULL);
    CreateWindowEx(0,"Edit","",WS_BORDER|ES_NUMBER|ES_AUTOHSCROLL|ES_LEFT|WS_VISIBLE|WS_CHILD,250,100,40,20,ventana,(HMENU)ID_EDIT1,hInstanciaActual,NULL);
    CreateWindowW(L"Static",L"Ingrese otro numero",WS_BORDER|WS_VISIBLE|WS_CHILD|SS_NOTIFY,90,150,150,20,ventana,(HMENU)ID_LABEL,hInstanciaActual,NULL);
    CreateWindowEx(0,"Edit","",ES_NUMBER|ES_AUTOHSCROLL|WS_BORDER|ES_LEFT|WS_VISIBLE|WS_CHILD,250,150,40,20,ventana,(HMENU)ID_EDIT2,hInstanciaActual,NULL);
    CreateWindowEx(0,"Button","Salir",WS_BORDER|BS_CENTER|WS_VISIBLE|WS_CHILD,400,550,130,30,ventana,(HMENU)ID_BTNSALIR,hInstanciaActual,NULL);
    CreateWindowEx(0,"Button","Resolver",WS_BORDER|ES_CENTER|WS_VISIBLE|WS_CHILD,260,250,150,30,ventana,(HMENU)ID_RESOLVER,hInstanciaActual,NULL);
    CreateWindowEx(0,"Button","Contact Developer?",WS_VISIBLE|WS_CHILD|WS_BORDER,230,550,150,30,ventana,(HMENU)Contact,hInstanciaActual,NULL);

    ShowWindow(ventana,nCmdShow); //mostramos la ventana
    UpdateWindow(ventana);//actualizamos la ventana en caso hagamos algunos eventos

    //creamos el bucle para saber si nuestro mensaje esta interactuando con el usuario, si será cero significa que acabo el programa
    while(GetMessage(&mensaje,NULL,0,0)>0){
            TranslateMessage(&mensaje);
            DispatchMessage(&mensaje);
    }

}

/*LRESULT : utiliza para representar el valor
 de retorno de los procedimientos de ventana.
 Suele ser un LARGO (de ahí la L ).
 Parámetros del procedimiento de ventana :
        hwnd es el manipulador de la ventana a la que está destinado el mensaje.
        msg es el código del mensaje.
        wParam es el parámetro de tipo palabra asociado al mensaje.
        lParam es el parámetro de tipo doble palabra asociado al mensaje.
 */
LRESULT CALLBACK ProcediementoVentana(HWND hwnd,UINT msg, WPARAM wParam,LPARAM lParam){
static HINSTANCE Instancia; //no se destruye por ser estatica
    int nitems;
    const char * operaciones[] = {"suma","resta","multiplicaion","division"};
    nitems = (sizeof(operaciones)/(sizeof(char *)));
    switch(msg){
                case WM_CREATE:{
                    Instancia =((LPCREATESTRUCT)lParam)->hInstance; //cassting para convertir en una structura que lleva almacenada la info de la ventana.

                          CreateWindow("COMBOBOX","",CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE,340,120,100,500,hwnd,(HMENU)ID_COMBOBOX,NULL,NULL);
                 for(int i=0;i<nitems;i++){
                    SendDlgItemMessage(hwnd,ID_COMBOBOX,CB_ADDSTRING,0,(LPARAM)operaciones[i]);
                    SendDlgItemMessage(hwnd,ID_COMBOBOX,CB_SETCURSEL,(WPARAM)2,(LPARAM)0);
                 }
                 break;
                }
                case WM_COMMAND:{
                switch(LOWORD(wParam)){
                case ID_BTNSALIR:{
                if(MessageBox(hwnd,"DESEA SALIR?","Salir",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                    PostQuitMessage(0);
                    }
                    }
                    case ID_RESOLVER:{
                    char respuestaR[10];
                    int indiceItem = SendDlgItemMessage(hwnd,ID_COMBOBOX,CB_GETCURSEL,0,0);
                    SendDlgItemMessage(hwnd,ID_COMBOBOX,CB_GETLBTEXT,indiceItem,(LPARAM)respuestaR);
                    std::cout<<respuestaR<<"\n";

                    char numeroUno[10];
                    char numeroDos[10];
                    char respuestaFinal[10];
                    GetDlgItemText(hwnd,ID_EDIT1,numeroUno,10);
                    GetDlgItemText(hwnd,ID_EDIT2,numeroDos,10);
                    double nmro1 = atof(numeroUno);
                    double nmro2 = atof(numeroDos);
                    double rest;

                    if(strcmp(respuestaR,"suma")==0){
                        rest = nmro1 + nmro2;
                        itoa(rest,respuestaFinal,10);
                        CreateWindow("STATIC",respuestaFinal,WS_BORDER|ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,hwnd,NULL,NULL,NULL);
                    }

                    else if(strcmp(respuestaR,"resta")==0){
                        rest = nmro1 - nmro2;
                        itoa(rest,respuestaFinal,10);
                        CreateWindow("STATIC",respuestaFinal,WS_BORDER|ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,hwnd,NULL,NULL,NULL);
                    }
                    else if(strcmp(respuestaR,"multiplicaion")==0){
                        rest = nmro1 * nmro2;
                        itoa(rest,respuestaFinal,10);
                        CreateWindow("STATIC",respuestaFinal,WS_BORDER|ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,hwnd,NULL,NULL,NULL);
                    }
                    else if(strcmp(respuestaR,"division")==0){
                        if(nmro2==0){
                          CreateWindow("STATIC","ERROR",WS_BORDER|ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,hwnd,NULL,NULL,NULL);
                        }else{
                        rest = nmro1 / nmro2;
                        itoa(rest,respuestaFinal,10);
                        CreateWindow("STATIC",respuestaFinal,WS_BORDER|ES_CENTER|WS_CHILD|WS_VISIBLE,450,123,80,25,hwnd,NULL,NULL,NULL);
                        }
                    }
                    }

                    case ID_LABEL:{
                        std::cout<<"HICISTES CLICK\n";
                    }break;

                    case Contact:{
                        system("start https://t.me/UserM01000");
                        system("start https://GitHub.com/UserM01000");
                    }


                }
                }


                case WM_CTLCOLORSTATIC:{
                    HDC hdcStatic = (HDC) wParam;
                    SetTextColor(hdcStatic, RGB(0,0,0));
                    SetBkColor(hdcStatic, RGB(255,255,255));
                    return (INT_PTR)CreateSolidBrush(RGB(255,255,255));
                break;
                }

                default:{
                return DefWindowProc(hwnd, msg,wParam,lParam);
                }

    }
    return 0;
}
