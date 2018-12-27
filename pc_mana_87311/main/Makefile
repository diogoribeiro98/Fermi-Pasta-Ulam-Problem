CODE = code/
DATA = data/
GNUPLOT = gnuplot_script/

all: program1 program2

program1: $(CODE)fpu_rb.cpp 
	g++ $(CODE)fpu_rb.cpp -o fpu_rb 

program2: $(CODE)sao_rb.cpp
	g++ $(CODE)sao_rb.cpp -o sao_rb 

run_fpu:
	./fpu_rb

run_sao:
	./sao_rb

plot_all:
	gnuplot $(GNUPLOT)plot_all.gp

plot_modes:
	gnuplot $(GNUPLOT)plot_modes.gp

plot_sao:
	gnuplot $(GNUPLOT)plot_sao.gp

remove:
	rm -f $(DATA)*.txt

clean:
	rm fpu_rb sao_rb