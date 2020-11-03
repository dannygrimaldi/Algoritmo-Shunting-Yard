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

        sig=NULL;
    }

    int precedencia(){
        int c=getData();
        switch(c){
        case '(':       break;
        case ')':       break;
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

    int getData(){
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

    void DelFront()
    {
        cNodo * aux = inicio;
        inicio=aux->sig;
        aux=nullptr;
    }

    void front(char charAinsertar)
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

    void end(char charAinsertar){
        if (inicio==NULL)
            inicio = new cNodo(charAinsertar);
        else
        {
            cNodo *aux=inicio;
            while(aux->sig!=NULL){
                aux=aux->sig;
            }
            aux->sig = new cNodo(charAinsertar);
        }
    }

    void imprimirExit(){
       cout<<"Notación Polaca inversa: ";
        cNodo * aux=inicio;
        while(aux!=NULL){
            aux->imp();
            aux=aux->sig;

        }
        cout<<endl;

    }

   void leer(){
       char cadena[100];
       cout<<"Ingrese la operación infija: ";
       cin>>cadena;
       fflush(stdin);
         for(int i = 0; cadena[i]; i++)
             end(cadena[i]);
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
    cListaLigada out;
    public:

    shunting(){

    }

public:

    void resolver(){
        token.leer();
        algoritmo();
        out.imprimirExit();

    }


    void algoritmo(){
        cNodo * aux = token.inicio;
        while(aux!=NULL){
            //stak.imprimirExit();
            //out.imprimirExit();

    if(aux->getData()==')'){
        cNodo* aux1=stak.inicio;
           while(aux1!=NULL&&aux1->getData()!='('){
                out.end(aux1->getData());
                //if(stak.inicio->getData()=='(')
                stak.DelFront();
                aux1=aux1->sig;
                //stak.imprimirExit();
                //out.imprimirExit();
           }
            if(stak.inicio->getData()=='(')
            stak.DelFront();
            }


            else if(aux->getPrec()==1){
            out.end(aux->getData());
            }
    else
    {
        if (stak.inicio!=NULL)
        {
            if (stak.inicio->getPrec()>=aux->getPrec())
            {
                bool x=false;
                if(aux->getData()!='(')
                {
                    out.end(stak.inicio->getData());
                    x=true;
                }
            if(stak.inicio->sig!=NULL&&stak.inicio->sig->getPrec()==aux->getPrec())
                    {  if(x==true)
                        {
                            stak.DelFront();
                            out.end(stak.inicio->getData());
                            stak.DelFront();
                        }
                        
                        stak.front(aux->getData());
                        
                        
                    }

                    else
                    {
                            if(x==true){
                            stak.DelFront();}
                            stak.front(aux->getData());
                    }
            }
            else
            {
            stak.front(aux->getData());
            }
        }
        else
        {
        stak.front(aux->getData());
        }
    }
        aux=aux->sig;
        }

        cNodo* aux1=stak.inicio;
        while(aux1!=NULL){
            if(aux1->getData()!='(')
            out.end(aux1->getData());
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
