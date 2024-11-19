#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;


enum eDir { PARAR = 0, IZQUIERDA = 1, ARRIBA_IZQUIERDA = 2, ABAJO_IZQUIERDA = 3, DERECHA = 4, ARRIBA_DERECHA = 5, ABAJO_DERECHA = 6 };


class cPelota {
private:
    int x, y; 
    int xOriginal, yOriginal; 
    eDir direccion; 
public:
    cPelota(int posX, int posY) {
        xOriginal = posX;
        yOriginal = posY;
        x = posX; 
        y = posY;
        direccion = PARAR;
    }

    void Reiniciar() {
        x = xOriginal; 
        y = yOriginal;
        direccion = PARAR;
    }

    void cambiarDireccion(eDir d) {
        direccion = d;
    }

    void direccionAleatoria() {
        direccion = (eDir)((rand() % 6) + 1);
    }

    inline int obtenerX() { return x; }
    inline int obtenerY() { return y; }
    inline eDir obtenerDireccion() { return direccion; }

    void Mover() {
        switch (direccion) {
            case PARAR: break;
            case IZQUIERDA: x--; break;
            case DERECHA: x++; break;
            case ARRIBA_IZQUIERDA: x--; y--; break;
            case ABAJO_IZQUIERDA: x--; y++; break;
            case ARRIBA_DERECHA: x++; y--; break;
            case ABAJO_DERECHA: x++; y++; break;
            default: break;
        }
    }

    friend ostream& operator<<(ostream& o, const cPelota& c) {
        o << "Pelota [" << c.x << "," << c.y << "] Direccion: " << c.direccion;
        return o;
    }
};


class cPaleta {
private:
    int x, y; 
    int xOriginal, yOriginal; 
public:
    cPaleta() { x = y = 0; }

    cPaleta(int posX, int posY) {
        xOriginal = posX;
        yOriginal = posY;
        x = posX;
        y = posY;
    }

    inline void Reiniciar() { x = xOriginal; y = yOriginal; }
    inline int obtenerX() { return x; }
    inline int obtenerY() { return y; }
    inline void moverArriba() { y--; }
    inline void moverAbajo() { y++; }

    friend ostream& operator<<(ostream& o, const cPaleta& c) {
        o << "Paleta [" << c.x << "," << c.y << "]";
        return o;
    }
};


class cAdminJuego {
private:
    int ancho, alto; 
    int puntuacion1, puntuacion2;
    char arriba1, abajo1, arriba2, abajo2;
    bool salir; 
    cPelota* pelota; 
    cPaleta* jugador1; 
    cPaleta* jugador2; 
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

public:
    cAdminJuego(int w, int h) {
        srand(time(NULL));
        salir = false;
        arriba1 = 'w'; abajo1 = 's';
        arriba2 = 'i'; abajo2 = 'k';
        puntuacion1 = puntuacion2 = 0;
        ancho = w;
        alto = h;
        pelota = new cPelota(w / 2, h / 2);
        jugador1 = new cPaleta(1, h / 2 - 3);
        jugador2 = new cPaleta(w - 2, h / 2 - 3);
    }

    ~cAdminJuego() {
        delete pelota;
        delete jugador1;
        delete jugador2;
    }

    void aumentarPuntuacion(cPaleta* jugador) {
        if (jugador == jugador1) puntuacion1++;
        else if (jugador == jugador2) puntuacion2++;
        
        pelota->Reiniciar();
        jugador1->Reiniciar();
        jugador2->Reiniciar();
    }

    void limpiarPantalla() {
        COORD cursorPosicion = { 0, 0 };
        SetConsoleCursorPosition(consola, cursorPosicion);
    }

    void Dibujar() {
        limpiarPantalla(); 

        for (int i = 0; i < ancho + 2; i++) cout << char(206);
        cout << endl;

        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho; j++) {
                int pelotaX = pelota->obtenerX();
                int pelotaY = pelota->obtenerY();
                int jugador1X = jugador1->obtenerX();
                int jugador2X = jugador2->obtenerX();
                int jugador1Y = jugador1->obtenerY();
                int jugador2Y = jugador2->obtenerY();

                if (j == 0) cout << char(206);

                if (pelotaX == j && pelotaY == i)
                    cout << "O"; 
                else if (jugador1X == j && (jugador1Y <= i && i < jugador1Y + 4))
                    cout << char(219); 
                else if (jugador2X == j && (jugador2Y <= i && i < jugador2Y + 4))
                    cout << char(219); 
                else
                    cout << " ";

                if (j == ancho - 1) cout << char(206);
            }
            cout << endl;
        }

        for (int i = 0; i < ancho + 2; i++) cout << char(206);
        cout << endl;

        cout << "Puntuacion 1: " << puntuacion1 << endl << "Puntuacion 2: " << puntuacion2 << endl;
    }

    void Entrada() {
        pelota->Mover();

        int jugador1Y = jugador1->obtenerY();
        int jugador2Y = jugador2->obtenerY();

        if (_kbhit()) {
            char teclaActual = _getch();
            if (teclaActual == arriba1 && jugador1Y > 0)
                jugador1->moverArriba();
            if (teclaActual == abajo1 && jugador1Y + 4 < alto)
                jugador1->moverAbajo();
            if (teclaActual == arriba2 && jugador2Y > 0)
                jugador2->moverArriba();
            if (teclaActual == abajo2 && jugador2Y + 4 < alto)
                jugador2->moverAbajo();
            if (pelota->obtenerDireccion() == PARAR)
                pelota->direccionAleatoria();
            if (teclaActual == 'q')
                salir = true;
        }
        

    }

    void Logica() {
        int pelotaX = pelota->obtenerX();
        int pelotaY = pelota->obtenerY();
        int jugador1X = jugador1->obtenerX();
        int jugador2X = jugador2->obtenerX();
        int jugador1Y = jugador1->obtenerY();
        int jugador2Y = jugador2->obtenerY();

        
        for (int i = 0; i < 4; i++) {
            if (pelotaX == jugador1X + 1 && pelotaY == jugador1Y + i)
                pelota->cambiarDireccion((eDir)((rand() % 3) + 4));
            if (pelotaX == jugador2X - 1 && pelotaY == jugador2Y + i)
                pelota->cambiarDireccion((eDir)((rand() % 3) + 1));
        }

        
        if (pelotaY == alto - 1)
            pelota->cambiarDireccion(pelota->obtenerDireccion() == ABAJO_DERECHA ? ARRIBA_DERECHA : ARRIBA_IZQUIERDA);
        if (pelotaY == 0)
            pelota->cambiarDireccion(pelota->obtenerDireccion() == ARRIBA_DERECHA ? ABAJO_DERECHA : ABAJO_IZQUIERDA);

        
        if (pelotaX == ancho - 1) aumentarPuntuacion(jugador1);
        if (pelotaX == 0) aumentarPuntuacion(jugador2);
    }

    void Ejecutar() {
        while (!salir) {
            Dibujar();
            Entrada();
            Logica();
            Sleep(12);
        }
    }
};

void OcultarCursor() {
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;  
    info.dwSize = 1;
    SetConsoleCursorInfo(consola, &info);
}

int main() {
    OcultarCursor();
    cAdminJuego juego(40, 20);
    juego.Ejecutar();
    return 0;
}

