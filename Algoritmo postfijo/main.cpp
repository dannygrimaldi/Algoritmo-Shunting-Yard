//
//  main.cpp
//  Algoritmo postfijo
//
//  Created by Daniel Hernández Grimaldi on 10/30/20.
//  Copyright © 2020 Daniel Hernández Grimaldi. All rights reserved.
//

#include <iostream>
using namespace std;



class cNodo
{
    char c;
    int prec;

public:
    cNodo *sig;
    cNodo(char c)
    {
        this->c = c;
        this->prec = precedencia();
        
        sig = NULL;
    }
    
    int precedencia(){
        int c=getData();
        switch(c){
        case '(': break;
        case ')': break;
        case '^':       return 4; break;
        case '*':       return 3; break;
        case '/':       return 3; break;
        case '+':       return 2; break;
        case '-':       return 2; break;
            default: return 1;
        }
        return false;
    }
    
    void imp(){
        cout<<c<<' ';
    }

    void imprimir()
    {
        cout << "el valor de c: " << c;
        cout<<" prec: "<< prec<<endl;
        cout << "sig: " << sig << endl;
    }
    friend class cListaLigada;
    
    int getData(){          // interfaz de clase
    return c;
    }
    cNodo* getSig(){
    return sig;
    }
    int getPrec(){
        return prec;
    }
};

class cListaLigada
{

public:
    cNodo *inicio;
cListaLigada(){
    inicio = NULL;
}
    
    void insertarEnLa3Pos(char charAinsertar)
    {
        cNodo *aux = new cNodo('u');
        cNodo *aux1;
        aux1 = inicio->sig->sig->sig;
        aux->sig = aux1;
        inicio->sig->sig->sig = aux;
    }

    void borrarPrimer()
    {
        cNodo * aux = inicio;
        inicio = inicio->sig;
        aux->sig = NULL;
    }

    void insAlprinc(char charAinsertar)
    {
        if (inicio == NULL)
            inicio = new cNodo(charAinsertar);
        else
        {
            cNodo *aux = new cNodo(charAinsertar);
            aux->sig = inicio;
            inicio = aux;
        }
    }
    void insAlfinal(char charAinsertar)
    {
        if (inicio == NULL)
            inicio = new cNodo(charAinsertar);
        else
        {
            cNodo *aux;
                aux=inicio;
            while(aux->sig!=NULL){
                aux=aux->sig;
            }
            aux->sig = new cNodo(charAinsertar);
        }
    }
    void crearNodosDePrueba()
    {
        inicio = new cNodo('5');
        inicio->sig = new cNodo('-');
        inicio->sig->sig = new cNodo('6');
        inicio->sig->sig->sig = new cNodo('d');
        
    }
    
    void imprimirExit(){
        cNodo * aux=inicio;
        while(aux!=NULL){
            aux->imp();
            aux=aux->sig;
            
        }
        cout<<endl;
        
    }
    
   void leer(){
       char cadena[100];
       cout<<"ingrese el string: ";
       cin>>cadena;
       fflush(stdin);
        int i;
         for(i = 0; cadena[i]; i++)
             insAlfinal(cadena[i]);
      //printf("%s\n", cadena);
    }
    
    void imprimirLista()
      {
          cNodo * aux=inicio;
          while(aux!=NULL){
              aux->imprimir();
              aux=aux->sig;
          }
    }
    
};

class shunting{
    
    cListaLigada token;
    cListaLigada stak;
    cListaLigada salida;
    public:
    
    shunting(){
        
    }

public:
    
    
    void resolver(){
        token.leer();
        algoritmo();
        salida.imprimirExit();
    }
    
    
    void algoritmo(){
        cNodo * aux = token.inicio;
        while(aux!=NULL){
            
if(aux->getPrec()==1){
                salida.insAlfinal(aux->getData());
            }
    
            else {
                    if (stak.inicio!=NULL) {
                        if (stak.inicio->getPrec()>=aux->getPrec()) {
                            salida.insAlfinal(stak.inicio->getData());
                            stak.borrarPrimer();
                            stak.insAlprinc(aux->getData());
                        } else if ((stak.inicio->getPrec()<aux->getPrec())) {
                            stak.insAlprinc(aux->getData());
                        }
                    } else {
                        stak.insAlprinc(aux->getData());
                    }
                }
            aux=aux->sig;
            
        }
        cNodo* aux1=stak.inicio;
        while(aux1!=NULL){
            salida.insAlfinal(aux1->getData());
            aux1=aux1->sig;
            }
        
           
        }
            
};


int main()
{
   
    shunting problema;
    problema.resolver();
    cout << "hello world" << endl;
    
    return 0;
}
