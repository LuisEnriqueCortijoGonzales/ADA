#include "ejercicio1.h"
#include "ejercicio2.h"
#include "ejercicio3.h"

int main() {
    //funciones manuales de los ejercicios (como se ingresarian los datos como pide el ejercicio)
    ejercicio1();
    ejercicio2();
    ejercicio3();

    //experimentacion del informe (con datos aleatorios que se saltan el ingreso manual creado y llenan automaticamente)
    experimentar1(8);
    cout<<"pregunta 1 lista"<<endl;
    experimentarGreedy2(8);
    cout<<"pregunta 2 lista"<<endl;
    experimentarDP3(3);
    cout<<"pregunta 3 lista"<<endl;


    return 0;
}
