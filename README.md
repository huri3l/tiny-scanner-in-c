# Scanner TINY em C
Implementação de um Scanner em C para a linguagem TINY, trabalho prático de analisador léxico para a matéria de Compiladores.

## Ambiente
O Scanner foi codificado e testado em Linux.

## Utilização
Para testar o código, existem dois arquivos de entrada, **tiny_ok.txt** e **tiny_error.txt**. Caso queira, pode modificar os arquivos para validar diversos tipos de entrada.

Após preparar o código a ser analisado, basta utilizar o comando `gcc scanner.c -o scanner` para compilar o código e `./scanner < tiny_error.txt > tiny_error_out.txt` para rodar o programa.
Se preferir, pode substituir `tiny_error.txt` pelo `tiny_ok.txt`. Se preferir, pode utilizar o comando `./scanner < tiny_error.txt >> tiny_error_out.txt`
