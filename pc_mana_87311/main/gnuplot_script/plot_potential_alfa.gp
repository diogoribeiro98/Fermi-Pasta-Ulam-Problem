
#Plot - Energy Function
set terminal postscript eps enhanced color font 'Helvetica,10'
set output "potential_a.eps"
set size 0.6,0.5

set title 'Potential wells as a function of {/Symbol a} parameter'
set xlabel 'Displacement'
set ylabel 'Potential'

set xrange[-3:2]
set yrange[-3:3]

dalfa = 0.1
beta = 0

#set xrange[-4.2:2.2]
set yrange[-1:2.5]
set grid
set key outside

plot for[i=0:10:1] 0.5*x*x + 0.3*(dalfa*i)*x*x*x + 0.25*beta*x*x*x*x title (sprintf('{/Symbol a} = %.1f' ,dalfa*i )) lw 2.5


