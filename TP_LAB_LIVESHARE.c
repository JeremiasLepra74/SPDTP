#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cliente
{
    char nombre[50];
    int num_cuenta, pass, estado, maxMov;
    float saldo;
};

int numero_client;
int mostrarMenu();
void Deposito(int numero_client, struct cliente clientes[10]);
void Extraccion(int numero_client, struct cliente clientes[10]);
void ConsultarSaldo(int numero_client, struct cliente clientes[10]);
void Transferencia(int numero_client, struct cliente clientes[10]);

// cliente 1

int main()
{
    struct cliente clientes[10];
    strcpy(clientes[0].nombre, "juan");
    clientes[0].num_cuenta = 1;
    clientes[0].pass = 123456;
    clientes[0].saldo = 100;
    clientes[0].estado = 1;
    clientes[0].maxMov = 0;

    // cliente 2
    strcpy(clientes[1].nombre, "carlitos");
    clientes[1].num_cuenta = 2;
    clientes[1].pass = 123457;
    clientes[1].saldo = 200;
    clientes[1].estado = 1;
    clientes[1].maxMov = 0;

    // cliente 3
    strcpy(clientes[2].nombre, "la momia");
    clientes[2].num_cuenta = 3;
    clientes[2].pass = 123458;
    clientes[2].saldo = 300;
    clientes[2].estado = 1;
    clientes[2].maxMov = 0;

    int lee_cuenta, lee_pass, inicio_sesion, intento, opcion, numero_client, apagar, aux_intento;
    apagar = 0;
do
{
    // lectura y verificacion de usuario
    do
    {
        printf("Ingrese su numero de cuenta:\n");
        scanf("%d", &lee_cuenta);
    } while (lee_cuenta < 0 || lee_cuenta > 11);
    for (int i = 0; i < 10; i++)
    {
        if (lee_cuenta == clientes[i].num_cuenta)
        {
            do
            {
                printf("Ingrese su contrase%ca:\n", 164);
                scanf("%d", &lee_pass);
            } while (lee_pass < 9999 || lee_pass > 999999);

            intento = 1;

            if (lee_pass == clientes[i].pass)
            {
                inicio_sesion = 1;
                numero_client = i;
                clientes[numero_client].maxMov = 1;
                break;
            }
            else
            {
                 
                while (intento <= 2)
                {

                    printf("Ingrese su contrase%ca:\n", 164);
                    scanf("%d", &lee_pass);

                    if (lee_pass == clientes[i].pass)
                    {
                        inicio_sesion = 1;
                        // el problema del inicio esta aca, caundo iaguala a 3
                    }
                    intento++;

                    if (intento == 3) // cuando es igual a 3 el estado es 0
                    {
                        printf("Cuenta bloqueada, comuniquese con la entidad bancaria\n");
                        clientes[numero_client].estado = 0;
                    }
                }
            }
        }
    }

    while (inicio_sesion == 1 && clientes[numero_client].estado == 1)
    {
            int opc1;
            printf("Numero de movimientos hechos: %i \n", clientes[numero_client].maxMov - 1); // corregir ya que se acumula
            opc1 = mostrarMenu();
            if (clientes[numero_client].maxMov >= 10)
            {
                printf("Supero la cantida de movimientos posibles. Inicie sesion de vuelta \n");
                inicio_sesion = 0;
                /*clientes[numero_client].estado = 0;*/
            }

            switch (opc1)
            {
            case 1:
                Deposito(numero_client, clientes);
                break;
            case 2:
                Extraccion(numero_client, clientes);
                break;
            case 3:
                ConsultarSaldo(numero_client, clientes);
                break;
            case 4:
                Transferencia(numero_client, clientes);
                break;
            case 5:
                // mostrar cant de operaciones realiszadas
                break;
            case 6:
                inicio_sesion = 0;
                
                break;
            default:
                break;
            }
        }
        
} while (apagar == 0);
        return 0;
    
}
// TODOS LOS RESULTADOS DE LAS FUNCIONES TERMINAN EN UN LOOP INFINITO, los calculos los hace correctamente.

// Función para realizar un depósito
void Deposito(int numero_client, struct cliente clientes[])
{
    float saldo_funcion;
    int contador;
    contador = 0;
    do
    {
        printf("Ingrese la cantidad de dinero que desea depositar\n");
        scanf(" %f", &saldo_funcion);
        if (saldo_funcion <= 0)
        {
            printf("No puede ingresar 0 pesos o numeros negativos.\n");
            printf("Ingresar 0 si desea salir\n");
            scanf("%d", &saldo_funcion);
        }
        if (saldo_funcion > 0)
        {
            clientes[numero_client].saldo = clientes[numero_client].saldo + saldo_funcion;
            printf("Deposito: %f\n"), saldo_funcion;
            printf("Saldo actul: %.2f \n", clientes[numero_client].saldo);
            contador++;
            clientes[numero_client].maxMov = clientes[numero_client].maxMov + contador;
        }

    } while (saldo_funcion < 0);
}

// Función para realizar una extracción
void Extraccion(int numero_client, struct cliente clientes[]){
    float monto_extraccion;
    int contador;
    contador = 0;
    printf("Ingrese la cantidad de dinero que desea extrar\n");
    scanf("%f", &monto_extraccion);

    if (clientes[numero_client].saldo >= monto_extraccion)
    {
        clientes[numero_client].saldo = clientes[numero_client].saldo - monto_extraccion;
        printf("Extraccion: $%.2f \n", monto_extraccion);
        printf("Saldo actul: %.2f \n", clientes[numero_client].saldo);
        contador++;
        clientes[numero_client].maxMov = clientes[numero_client].maxMov + contador;
    }
    else if (clientes[numero_client].saldo <= 0 || clientes[numero_client].saldo < monto_extraccion)
    {
        printf("No posee dinero en su cuenta o quiere retirar un monto mayor al disponible \n");
    }
}

// Función para consultar saldo
void ConsultarSaldo(int numero_client, struct cliente clientes[10])
{
    int contador;
    contador = 0;
    printf("Su saldo es %.2f\n", clientes[numero_client].saldo);
    contador++;
    clientes[numero_client].maxMov = clientes[numero_client].maxMov + contador;
}

// Función para realizar una transferencia
void Transferencia(int numero_client, struct cliente clientes[10])
{
    int encontrado;
    encontrado = 0;
    printf("Su saldo es %.2f\n", clientes[numero_client].saldo);
    int destino;
    float monto_tf;
    do
    {
        printf("Ingrese el numero de cuenta a la que desea realizar la transferencia\n");
        scanf("%d", &destino);
        if (destino < 0 || destino > 10)
        {
            printf("No se puede ingresar un numero negativo o mayor a 10 \n");
        }
    } while (destino < 0 || destino > 10);

    for (int i = 0; i < 10; i++)
    {

        if (destino == clientes[i].num_cuenta)
        {
            do
            {
                printf("Ingrese la cantidad de dinero que desea transferir\n");
                scanf("%f", &monto_tf);
                if (monto_tf > clientes[numero_client].saldo || monto_tf <= 0)
                {
                    printf("El monto supera el saldo disponible o el monto a transferir es 0. Reingreselo \n");
                }

            } while (monto_tf > clientes[numero_client].saldo);
            clientes[i].saldo = clientes[i].saldo + monto_tf;                         // aumenta saldo de la cuenta que recibe
            clientes[numero_client].saldo = clientes[numero_client].saldo - monto_tf; // disminuye saldo a la cuenta que envia
            i = 10;
            encontrado = 1;
        }
    }

   /* if (encontrado == 0) // este if me parece que no hace falta,
    {                    // el while (destino < 0 || destino > 10); acota la busqueda a los perfiles precargados
        printf("Cuenta no encontrada \n");
    }*/
}
// Función para mostrar el menú de opciones
int mostrarMenu()
{
    int opcion;
    do
    {
        printf("1. Realizar un Deposito.\n");
        printf("2. Realizar una Extraccion.\n");
        printf("3. Consultar el Saldo de la Cuenta.\n");
        printf("4. Realizar una Transferencia entre Cuentas.\n");
        printf("5. Mostrar cantidad de Operaciones Realizadas y Saldo Actual.\n");
        printf("6. Salir de la Sesion.\n");
        printf("Ingrese una opcion:\n");
        scanf("%d", &opcion);
    } while (opcion > 7 || opcion < 0);
    return opcion;
}

/* prueba para confirmar si los datos fueron correctamente guardados en el array
printf("%s\n", clientes[0].nombre);     // %s para imprimir una cadena de caracteres
printf("%d\n", clientes[0].num_cuenta); // %d para imprimir un entero
printf("%d\n", clientes[0].contrasea);  // %d para imprimir un entero
printf("%f\n", clientes[0].saldo); NO
printf("%d\n", clientes[0].estado); // %d para imprimir un entero */
