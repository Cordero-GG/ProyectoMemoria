/*
* Principal.cpp
 *
 *  Created on: 1 oct. 2018
 *      Author: Albert Acevedo
 *      Seccion: 2
 *      Cedula: 26.710.983
 */

#include <iostream>
#include <cstdlib>
using namespace std;

typedef float* apunt;
apunt p1,p2;
char *p3;
void Calculadora(apunt x,apunt y, char z);
void Potencia(apunt x,apunt y);

int main(){
    p1 = new float;
    p2 = new float;
    p3 = new char;
    do{
        *p1=*p2=*p3=NULL;
        system("CLS");
        cout<<endl;
        cout<<"				------------"<<endl;
        cout<<"				-Bienvenido-"<<endl;
        cout<<"				------------"<<endl;
        cout<<"\nDesea '+'.Sumar '-'.Restar '*'.Multiplicar '/'.Dividir '^'. Elevar Potencia: ";
        cin>>*p3;
        if(*p3=='+' || *p3=='-' || *p3=='*' || *p3=='/'){
            cout<<"\nIngrese Numero 1: ";
            cin>>*p1;
            cout<<"Ingrese Numero 2: ";
            cin>>*p2;
            Calculadora(p1,p2,*p3);
        }
        else if(*p3=='^'){
            cout<<"\nIngrese Base: ";
            cin>>*p1;
            cout<<"Ingrese Potencia: ";
            cin>>*p2;
            Potencia(p1,p2);
        }
        cout<<"\n\nDesea Continuar (1.Si 2.No): ";
        cin>>*p2;
    }while(*p2==1);
    delete p1;
    delete p2;
    delete p3;
    return 0;
}

void Calculadora(apunt x,apunt y, char z){
    switch(z){
    case '+': *x+=*y;;
        break;
    case '-': *x-=*y;
        break;
    case '*': *x*=*y;
        break;
    case '/': *x/=*y;
        break;
    }
    cout<<"\nSu resultado es: "<<*x;
}

void Potencia(apunt x,apunt y){
    apunt aux1,aux2,i,j;
    aux1=new float;
    aux2=new float;
    i=new float;
    j=new float;
    *aux2=*aux1=*x;
    if(*y>0){
        for(*i=1;*i<*y;*i+=1){
            for(*j=1;*j<*x;*j+=1){
                *aux2+=*aux1;
            }
            *aux1=*aux2;
        }
    }
    else if(*y==0){
        *aux1=1;
    }
    else if(*y<0){
        *y=-1**y;
        for(*i=1;*i<*y;*i+=1){
            for(*j=1;*j<*x;*j+=1){
                *aux2+=*aux1;
            }
            *aux1=*aux2;
        }
        *aux1=1/ *aux1;
    }
    cout<<"\nSu resultado es: "<<*aux1;
    delete aux1;
    delete aux2;
}
