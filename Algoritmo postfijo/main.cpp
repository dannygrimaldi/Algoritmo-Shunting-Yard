//
//  main.cpp
//  Algoritmo postfijo
//
//  Created by Daniel Hernández Grimaldi on 10/30/20.
//  Copyright © 2020 Daniel Hernández Grimaldi. All rights reserved.
//

#include <iostream>
#include <map>
using namespace std;



class cNodo
{
    char c;
    int num,prec;

public:
    cNodo *sig;
    cNodo(char c)
    {
        this->c = c;
        this->prec = precedencia();

        sig=NULL;
    }
    cNodo(int num)
    {
        this->num = num;
        this->prec = precedencia();

        sig=NULL;
    }


    int precedencia(){
        int c=getData();
if(c=='('||c==')'||c=='^'||c=='*'||c=='/'||c=='+'||c=='-'){
    if(c=='('||c==')'){return 0;}
    if(c=='^'){return 4;}
    if(c=='*'||c=='/'){return 3;}
    if(c=='+'||c=='-'){return 2;}
        }
            else{
                return 1;
            }
        return false;
    }

    void imp(){
        if(prec==1){
            cout<<num<<' ';
            
        }
       else
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

    void endn(int Ainsertar){
        if (inicio==NULL)
            inicio = new cNodo(Ainsertar);
        else
        {
            cNodo *aux=inicio;
            while(aux->sig!=NULL){
                aux=aux->sig;
            }
            aux->sig = new cNodo(Ainsertar);
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

   bool leer(){
       char cadena[100];
       cout<<"Ingrese la operación infija: ";
       cin>>cadena;
       fflush(stdin);
       int j=0;
       for(int i = 0; cadena[i]; i++){
           end(cadena[i]);
           if(cadena[i]=='('){
               j++;
           }
           if(cadena[i]==')'){
               j--;
           }
        }
       if(j!=0){
           cout<<"Error de sintaxis"<<endl;
           return false;
       }
       else{
           return true;
       }
           
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
        //token.leer();
        if(token.leer()==true){
            algoritmo();
            out.imprimirExit();
        }
        else{
            exit (0);
        }
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
                int a,i=0;char cadena[i];
                cadena[i]=aux->getData();
                while(aux->sig!=NULL&&aux->sig->getPrec()==1){
                      aux=aux->sig;
                            i++;
                    cadena[i]=aux->getData();}
                
                       a=atoi(cadena);
                        out.endn(a);
                         cadena[i]=NULL;
                
           // out.end(aux->getData());
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
                    out.end(stak.inicio->getData());   ///
                    x=true;
                }
            if(stak.inicio->sig!=NULL&&stak.inicio->sig->getPrec()==aux->getPrec())
                    {  if(x==true)
                        {
                            stak.DelFront();
                            out.end(stak.inicio->getData());
                            stak.DelFront();
                        }
                        
                        stak.front(aux->getData());   ///
                        
                        
                    }

                    else
                    {
                            if(x==true){
                            stak.DelFront();}
                            stak.front(aux->getData()); ///
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
