# Compilador Minimo C
    Este eh um projeto para disciplina de compiladores do curso de Ciencias da computação


# Programas

- Bison 
- Flex
- as
- gcc 

# Instruções
Para compilação do compilador e compilação do codigo minimo

```bash 
$ make
$ ./Cmin < entrada.c
```



# Requistos

- [x] -1: Cálculo de expressões com parênteses e números constantes (adição, subtração e multiplicação);
    - ex1: return 5 + 3 * 4;
    - ex2: return 5 * 3 - 4;
    - ex3: return (5 + (3 * 4));
    - ex2: return 5 + (4 – 2) * (5 - 1);

- [x] -2: Declaração de variáveis inteiras;
    - ex1: int x; int y;
    - ex2: int soma; int contador_1;

- [x] -3: Uso de variáveis – atribuição e cálculo em expressões (declaração antes do uso);
    - ex1: x = 10; y = x; z = z + t -1;
    - ex2: x = (10 + 2) - 1; y = (x + (2 - z)); return z + (t -1);

- [x] -4: Uso de operadores relacionais básicos (==, >, >=, <, <=, !=);
    - ex: return 2 == x; return x >= 10; return x != y;

- [x] -5: Estrutura condicional com bloco (uso aninhado deve ser permitido);
    - ex: if(x >= 6) { x = 1;} if (x != y) {z = 10; return z;}

- [x] -6: Estrutura condicional com else (uso aninhado deve ser permitido);
    - ex: if(nota >= 6) { x = 10;} else { if ( nota >=5 ) {x = 6;} else { x = 0; } }

- [x] - 7:  Laço de repetição while com bloco;
    - ex: x=1; soma=0; while(x!=10){ soma=soma+x; x = x+1;} return soma;

- [x] - 8:  Atribuir e declara muilti variaveis
    - ex: int a = 10, b = 32;

- [x] - 9: Comparação com && e ||
    - ex: nota >= 6 && nota <= 6 ;