/////////////////////////////////////////////////////////////////////////////////// 
//                                                                               //
//  Memória Descritiva relativa ao projecto computacional de Mecânica Analítica  //
//	         		2º Semestre 2017/2018  - Junho de 2018	              		 //
//	     				  Diogo Ribeiro (nº 187311)            	                 //
//                   Prof. João Seixas e Prof. Hugo Terças                       //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

Comentários aos Ficheiros:

___________________________________________________________________________________

Pasta /code : Contém os ficheiros de código em C++ : 

fpu_rb.cpp  - Ficheiro com o código referente à simulação da cadeia de FPU
sao_rb.cpp  - Ficheiro com o código referente à simulação de um único oscilador não harmónico

Pasta /data : Contém os ficheiros de dados de cada simulação (correr código)

Pasta /gnuplot_scipt : Contém os scripts de gnuplot para gerar os gráficos

___________________________________________________________________________________

Na pasta main os seguintes comandos podem ser utilizados:

COMPILAR  : $> make

CORRER FPU: $> make run_fpu
CORRER SAO: $> make run_sao

PLOT MODOS FPU: $> make plot_modes
PLOT ANIME FPU: $> make plot_all

PLOT PHASE SPACE SAO : $> make plot_sao

LIMPAR PASTA : $> make clean
REMOVER TXT's: $> make remove

Nota: O código encontra-se comentado, sendo necessário, aquando das alterações dos parâmetros das
	  simulações, alterar também as respectivas variáveis dos scripts de gnuplot para 
	  gerar os gráficos.









