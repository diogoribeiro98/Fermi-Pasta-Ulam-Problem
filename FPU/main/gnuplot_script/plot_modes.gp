#This is the relative path to the data files
#It is a relative path, meaning it has the form:
#	"location/where/script/is/run/"."data"

path_to_directory = 'data/'


#Problem variables (max time and number of modes)
time_max = 1000
k = 5

#Plot - Mode Energy
set term x11 1 size 500,500 position 50,50 persist background rgb 'black'

set xlabel 'ylabel' tc rgb 'white'
set ylabel 'xlabel' tc rgb 'white'
set border lc rgb 'white'
set key tc rgb 'white'

set xrange[0:time_max]
set yrange[0:15]
set grid lc rgb 'white'

plot for[mode=2:k+1:1] path_to_directory.'ene_data.txt' u 1:mode w d t sprintf("Mode : %d", mode-1 )

reset

#----- For LaTeX output -----#

#Plot - Mode Energy eps
#set terminal postscript eps enhanced color font 'Helvetica,10'
#set output "mode_energy.eps"
#set size 0.6,0.5

#set title 'Normal mode Energies'
#set xlabel 'time (s)'
#set ylabel 'Energy'

#set xrange[0:time_max]
#set yrange[0:7]
#set grid
#set key box at 880000,6.5

#set linestyle 1 lw 0.05

#plot for[mode=0:k:1] path_to_directory.'ene_data.txt' u 1: w l lw 0.01 t sprintf("Mode : %d", k )
