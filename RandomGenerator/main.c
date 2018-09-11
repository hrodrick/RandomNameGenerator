#include <stdio.h>
#include <stdlib.h>                                                                                                                                                                                                                                //By Rodrigo Soria
#include <time.h>
#include <windows.h>
#include <string.h>


typedef struct
{
    short int vocals;              /// Un maximo de DOS vocales

    short int consonants;          /// Un maximo de TRES consonantes sólo si la primera fue Sufija y la segunda intermedia.
    /// Caso contrario el máximo es DOS.

    short int wasUsed;             /// Contador interno que determina la cantidad de veces que una letra es usada continuamente.
    //-0 : no.
    //-1.
    //-2 : Deberá obligar a que una nueva y diferente letra sea elegida y se reiniciará el contador.
    short int Continuas;           /// Un maximo de DOS seguidas.


} Cantidades;


typedef struct
{

    short int wasEnd;                     /// Si es la ultima letra. Se coloca un espacio para separarla del apellido.
    //-0 : no is a end letter.
    //-1 : colocará un espacio.

    short int wasvocal;                 ///A, E, I, O, U.
    short int wasconsonant;               ///Q, W, R, T, Y, P, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M.
    short int wasintermediate;          /// Si puede ir antes de otra consonante, De acuerdo a la letra se definirá la siguiente.
    short int wascontinua;                /// Si es una R o una T o una S o una H o una K.
    short int wasSufija;                /// Si después de una vocal la letra es una R, S, X, N, M, D, G.

    short int wasprevioustovocal;       /// Si despues de ella debe ir si o si una vocal.
    short int wasprevioustoconsonant;     /// Si en el caso de ir dos vocales seguidas, o, sea necesario, seguirá una consonante.

    char letra;                         /// Debe de representar a una letra ya usada.

} Letra;


///GENERA NUMEROS ALEATORIOS ENTRE INICIO Y LIMITE INCLUSIVE.
int AleatNumber(int inicio, int Limite);

///GENERA LETRAS ALEATORIAS EN MINUSCULA;
char AleatLetterMin(void);

///GENERA NOMBRES DE FORMA ALEATORIA DE HASTA 1, 2 o 3 NOMBRES.
void AleatName(char Nombre[], int Dim);

//Inicializa los tipos de letra.
void inicLetras(Letra * LETT );
//Inicializa las cantidades.
void inicCantidades(Cantidades * CANTS);
//CAMBIA MINUSCULAS POR MAYUSCULAS.
char toUpper(char minuscula);

//REVISA LETRAS PARA DETERMINAR SU TIPO.
int letra_Is(char tipoDe_Ltra[], char letra , short int DimTipo_Letra);

//FUNCIONES DE COLOCACION DE LETRAS.
void Primera_letra(Letra * actuals, char vocals[], char consonants[], short int DimV, short int DimC);



int main()
{
    srand(time(NULL));
    int i = 0;
    int c = 0;
    int Dim = 20;
    char nombre[Dim];
    while(i < 50)
    {
    Dim = AleatNumber(4, 10);
    printf("\n");
    AleatName(nombre, Dim);
    while(c < Dim)
    {
        printf("%c",nombre[c]);
        c++;
    }
    c = 0;
    i++;
    }

    return 0;
}

int AleatNumber(int inicio, int limite)
{
    int numeroAleatorio;
    if(inicio < limite)
    {
        numeroAleatorio = (rand()%(limite - inicio + 1))+inicio;
    }
    else
    {
        printf("\nERROR: \nEl valor de inicio debe ser menor al limite.\n");
        system("pause");
    }
    return numeroAleatorio;
}

char AleatLetterMin(void)
{
    char letras[] = {'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    int cantidad = strlen(letras);

    unsigned short int pos;
    pos = AleatNumber(0, cantidad-2); ///Los ultimos 2 pertenecen a un caracter de escape.

    return letras[pos];
}

void AleatName(char Nombre[], int Dim)
{
    /// VARIABLES DE CONTROL:

    short int tomada = 0;
    short int Mayus = 0;
    int i = 0;
    int prob = 0;
    Cantidades cants;
    inicCantidades(&cants);
    short int controlSufija = 0;

    /// LETRAS A USAR EN SU RESPECTIVA CATEGORIA

    char vocals[5] = {'a','e','i','o','u'};
    int DimVocales = 5;
    char consonants[20] = {'w','r','t','y','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'};
    int DimConsonantes = 20;
    char intermediates[12] = {'g','s','d','r','t','p','f','l','c','b','m','n'};
    int DimIntermedias = 12;
    char Continuas[5] = {'r','t','s', 'h','k'};
    int DimContinuas = 5;
    char Sufijas[7] = {'r', 's', 'x', 'n', 'm', 'd', 'g'};
    int DimSufijas = 7;
    Letra actual;
    Letra previous;
    inicLetras(&previous);

    ///PROCEDIMIENTO DE SELECCION DE LETRA
    while(i < Dim)
    {
        do
        {
            inicLetras(&actual);
            tomada = 0;
            ///Toma de primera letra.
            if(Mayus == 0)
            {
                Primera_letra(&actual, vocals, consonants, DimVocales, DimConsonantes);
                tomada = 1;
            }


            ///Toma de letras obligatorias
            if( !tomada && previous.wasprevioustovocal)
            {
                actual.letra = vocals[AleatNumber(0, DimVocales-1)];
                actual.wasvocal = 1;
                tomada = 1;
            }
            else
            {
                if( !tomada && previous.wasprevioustoconsonant)
                {
                    actual.letra = consonants[AleatNumber(0, DimConsonantes-1)];
                    actual.wasconsonant = 1;
                    tomada = 1;
                }
            }
            ///Toma de letras random.
            if (!tomada)
            {
                prob = AleatNumber(0, 100);
                if(prob < 30)
                {
                    actual.letra = vocals[AleatNumber(0, DimVocales-1)];
                    actual.wasvocal = 1;
                    if(previous.wasvocal) actual.wasprevioustoconsonant = 1;
                    tomada = 1;
                }
                else
                {
                    if(prob >= 30)
                    {
                        if(previous.wasvocal && prob < 80)
                        {
                            actual.letra = Sufijas[AleatNumber(0, DimSufijas-1)];
                            actual.wasSufija = 1;
                        }
                        else
                        {
                            if(previous.wasintermediate)
                            {
                                actual.letra = Continuas[AleatNumber(0, DimContinuas-1)];
                                actual.wascontinua = 1;
                                actual.wasprevioustovocal = 1;
                            }
                            else
                            {
                                if(previous.wascontinua && cants.Continuas == 1 && (previous.letra != 'h' || previous.letra != 'k'))
                                {
                                    actual.letra = Continuas[AleatNumber(0, DimContinuas-1)];
                                    actual.wascontinua = 1;
                                    actual.wasprevioustovocal = 1;
                                }else
                                {
                                    actual.letra = consonants[AleatNumber(0, DimConsonantes-1)];
                                }
                            }
                        }
                    }
                    actual.wasconsonant = 1;
                    tomada = 1;
                }
            }

            if(previous.letra != actual.letra)
            {
                cants.wasUsed = 0;
            }

            if((actual.letra == 'r' && previous.letra == 'r') || (actual.letra == 't' && previous.letra == 't') || (previous.letra == 'c' && actual.letra == 'h'))
            {
                cants.wasUsed = 0;
                actual.wasprevioustovocal = 1;
            }
        } /// Elige una nueva letra si es que hay 2 iguales que no sean "rr" o "tt".
        while(cants.wasUsed >= 1 && !tomada);  // fin de ciclo
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///Establecer informacion de letra.
        //Anulacion de contrarios y suma de valores.
        if(actual.wasvocal == 1)
        {
            cants.vocals++;
            actual.wasconsonant = 0;
            actual.wascontinua = 0;
            actual.wasintermediate = 0;
            actual.wasSufija = 0;
            cants.consonants = 0;
            cants.Continuas = 0;
        }
        else
        {
            cants.consonants++;
            actual.wasvocal = 0;
            cants.vocals = 0;
        }
        //Modificacion de variables de control internas.
        if(previous.wasvocal && letra_Is(Sufijas, actual.letra, DimSufijas))
        {
            actual.wasSufija = 1;
        }
        else
        {
            if(previous.wasSufija && letra_Is(intermediates, actual.letra, DimIntermedias))
            {
                actual.wasintermediate = 1;
                controlSufija = 1;
            }
            else
            {
                if(letra_Is(consonants, actual.letra, DimConsonantes)) actual.wasprevioustovocal = 1;
            }
        }

        if(controlSufija == 1 && previous.wasintermediate && letra_Is(Continuas, actual.letra, DimContinuas))
        {
            actual.wascontinua = 1;
            cants.Continuas = 0;
            controlSufija = 0;
            actual.wasprevioustovocal = 1;
        }


        ///AL SER LA TERCERA CONSONANTE SEGUIDA, SI NO ES CONTINUA, ES VOCAL SI O SI.
        if(cants.consonants >= 3) actual.wasprevioustovocal = 1;
        if(cants.Continuas >= 2) actual.wasprevioustovocal = 1;
        if(cants.vocals >= 2) actual.wasprevioustoconsonant = 1;



        ///COLOCACION DE LETRA.
        previous = actual;
        Nombre[i] = actual.letra;
        cants.wasUsed++;

        if(Mayus == 0)
        {
            Mayus++;
            Nombre[i] = toUpper(actual.letra);
        }

        i++;
    }
}

void inicLetras(Letra * LETT )
{
    (*LETT).wasconsonant = 0;
    (*LETT).wascontinua = 0;
    (*LETT).wasEnd = 0;
    (*LETT).wasintermediate = 0;
    (*LETT).wasprevioustoconsonant = 0;
    (*LETT).wasprevioustovocal = 0;
    (*LETT).wasvocal = 0;
    (*LETT).letra = 0;
    (*LETT).wasSufija = 0;

}

void inicCantidades(Cantidades * CANTS)
{
    CANTS->consonants = 0;
    CANTS->vocals = 0;
    CANTS->wasUsed = 0;
    CANTS->Continuas = 0;
}

char toUpper(char minuscula)
{
    char mayus = minuscula - 32;

    return mayus;
}


void Primera_letra(Letra * actuals, char vocals[], char consonants[], short int DimV, short int DimC)
{
    int prob = AleatNumber(0,30);
    if(prob >= 15)
    {
        /// VOCAL
        actuals->letra = vocals[AleatNumber(0, DimV-1)];
        actuals->wasvocal = 1;

    }
    else
    {
        /// CONSONANT
        actuals->letra = consonants[AleatNumber(0, DimC-1)];
        actuals->wasconsonant = 1;
    }

}

int letra_Is(char tipoDe_Ltra[], char letra , short int DimTipo_Letra)
{
    int rta = 0;
    int i = 0;
    for(i = 0; i < DimTipo_Letra && rta != 1; i++)
    {
        if(letra == tipoDe_Ltra[i])
        {
            rta = 1;
        }

    }
    return rta;
}

