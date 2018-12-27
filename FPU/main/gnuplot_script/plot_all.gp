#This is the relative path to the data files
#It is a relative path, meaning it has the form:
#	"location/where/script/is/run/"."data"

path_to_directory = 'data/'

#iteration counter and number
j  = 0
nt = 9900

#Problem variables (number of springs , amplitude and number of normal modes)
ns = 32
amp = 1.2;
k = 4
time_max = 1000

#Animation cycle
while ( j < nt ) {
reset

#Plot 1 - positions
set term x11 0 size 900,500 position 50,50

set xrange[-2:ns+2]
set yrange[-amp:amp]
set grid

plot path_to_directory."pos_data.txt" i j u 2:3 w lp lw 1.5 

#Plot 2 - Mode Energy
set term x11 1 size 400,400 position 1050,50

set xrange[0:time_max]
set yrange[0:8]
set grid

plot for[mode=2:k+1:1] path_to_directory.'ene_data.txt' every ::::j u 1:mode w l t sprintf("Mode : %d", mode-1 )
j = j + 1
pause 0.01

} 
