int main(){
    int resultado = 0;
    int a = 10;
    int b = 15;

    while (a >= 0 && b >= 0){
        if( b > a) {
            resultado = resultado +  2;
            b = b - resultado;
        }else{
            resultado = resultado -  1;
            a = a + resultado;
        }
        a = a - b;
    }

    return resultado;
    
}