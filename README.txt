Passos para compilar os programas usando o gcc no teminal linux

    Abra o terminal;

    Abra (/navegue até) o diretório "trabalho-APA-01" no terminal;

    Entre com o bloco seguinte no terminal;
    (se copiar linha a linha, então copie tudo exceto as linhas com '---' e a última linha em branco)
    (se copiar o bloco então, copie tudo, incluindo a última linha em branco, exceto as linhas com '---')
--------------------
mkdir objects
mkdir bin
gcc src/heapsort.c -o objects/heapsort.o -c
gcc src/ordenacaoMetodoCaixas.c -o objects/ordenacaoMetodoCaixas.o -c
gcc src/tests.c -o objects/tests.o -c
gcc src/util.c -o objects/util.o -c
gcc src/mainTempoCpuCaixas.c -o objects/mainTempoCpuCaixas.o -c
gcc src/mainTempoCpuHeapsort.c -o objects/mainTempoCpuHeapsort.o -c
cd objects
gcc -o ../bin/tempoCpuCaixas mainTempoCpuCaixas.o heapsort.o ordenacaoMetodoCaixas.o tests.o util.o
gcc -o ../bin/tempoCpuHeapsort mainTempoCpuHeapsort.o heapsort.o ordenacaoMetodoCaixas.o tests.o util.o
cd ..

--------------------

    Execute os programas no diretório bin/ com
./bin/tempoCpuCaixas
    E/Ou
./bin/tempoCpuHeapsort