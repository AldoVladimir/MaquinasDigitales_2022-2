#include <iostream>

using namespace std;

string my_string="Hello world!";
string my_string_2="Good bye world!";
uint8_t my_var=5;
uint8_t *p= &my_var;

//int my_func(int a);

uint8_t * my_func(uint8_t *a){
    return a+0x02;
}

int main(){

    cout<<my_string+my_string_2<<endl;
    cout<<p<<endl;
    cout<<my_func(p)<<endl;

    return 25;
}




//Class
    //public
    //private

//Libreria
    //.h

//Class : LM--- Fotoresist
    //Public: 
        //volt2temp(){
        //    return V*f;
        //}
