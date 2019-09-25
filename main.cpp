#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <sstream>
#define PI 3.14159265

using namespace std;

int main()
{
    fstream arq; 												 // variável de manipulação de arquivos
    string texto; 												// string utilizada para varrer o arquivo e contar a quantidade de linhas
	string texto_x = "\0", texto_y = "\0", texto_z = "\0"; 	    // strings auxiliares para conversão de string para inteiro
    char letra;// caracter de varredura do arquivo
	char letra_x, letra_y, letra_z; // caracter de concatenação
    unsigned int linha = 0; // recebe a quantidade de linhas do arquivo
	unsigned int i = 0;  // indice
    arq.open("attitude_exam.log"); //abertura do arquivo
   
    /* Verificação de abertura do arquivo*/
    if(!arq.is_open()) 
    {
        cout<<"Erro na abertura do arquivo";
        arq.clear();
    }
    
	/* Contagem de linhas do arquivo */
    while(!arq.eof())
    {
        getline(arq, texto);
        linha++;
    }
	
    double theta[linha - 1]; // Vetor de angulos theta
    double phi[linha-1]; // Vetor de ângulos phi 
    double x, y, z; // Variáveis que recebem as coordenadas

    arq.close(); 

    arq.open("attitude_exam.log");

    while(arq.get(letra)) // Varredura geral do arquivo
    {
        if(letra == ' ')  // Se encontrar um espaço em branco
        {
            while(letra_x != ' ') // Enquanto não encontrar espaço em branco
            {
                arq.get(letra_x); // Armazena os caracteres até encontrar um 'espaço'
                texto_x = texto_x + letra_x; //Concatenação de caracteres em strings
                stringstream teste_x(texto_x); // Conversão de string para inteiro
                teste_x >> x; // Armazenamento do valor inteiro convertido em x
            }
            letra_x = '\0'; // Reiniciar caracter com terminardor
            texto_x = "\0"; // Reniciar string com terminador

            while(letra_y != ' ')
            {
                arq.get(letra_y);
                texto_y = texto_y + letra_y;
                stringstream teste_y(texto_y);
                teste_y >> y;
            }
            letra_y = '\0';
            texto_y = "\0";

            while(letra_z != '\n') // Enquanto não pular para a próxima linha
            {
                arq.get(letra_z);
                texto_z = texto_z + letra_z;
                stringstream teste_z(texto_z);
                teste_z >> z;
            }
            letra_z = '\0';
            texto_z = "\0";

            phi[i] = atan (y/z)*(180/PI); // Cálculo do angulo phi (roll)
            theta[i]= atan(-x/(sqrt(pow(y,2)+pow(z,2))))*(180/PI); // Cálculo do ângulo theta (pitch)
            i++;
        }
    }

    ofstream fout("angulos.log"); // Criação do arquivo de saída
	/* Escrita em arquivo dos vetores de phi e theta */
   
    for(i = 0; i < linha - 1; i++) 
    {
        fout << phi[i] << "; " << theta[i] << endl;
    }

    return 0;
}
