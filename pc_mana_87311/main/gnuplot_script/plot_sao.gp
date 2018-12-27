#This is the relative path to the data files
#It is a relative path, meaning it has the form:
#	"location/where/script/is/run/"."data"

path_to_directory = 'data/'

#Plot - Phase space
set term x11 0 size 600,350 position 50,50 persist

set title 'Phase space {/Symbol a} = 1.4 , {/Symbol b} = 0.3' 
set xlabel 'Displacement' 
set ylabel 'Momenta' 

set style line 1 lt 8 lw 0.01 pt 3 ps 0.1 lc rgb '#00000000'

set xrange[-5:1.2]
set yrange[-3:3]
set grid 
unset key

plot path_to_directory."pointcare_map.txt" u 2:3 w d lc 8 notitle

#----- For LaTeX output -----#

#set terminal postscript eps enhanced color font 'Helvetica,10'
#set output "pointcare.eps"
#set size 0.5,0.5