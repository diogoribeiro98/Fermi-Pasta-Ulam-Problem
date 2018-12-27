
#Plot - Energy Function
set terminal postscript eps enhanced color font 'Helvetica,10'
set output "potential_b.eps"
set size 0.6,0.5

set title 'Potential wells as a function of {/Symbol b} parameter and constant {/Symbol a}'
set xlabel 'Displacement'
set ylabel 'Potential'

alfa = 1.4
dbeta = 0.05

set xrange[-5.2:2.2]
set yrange[-1:2.5]
set grid
set key outside box

plot for[i=0:10:1] 0.5*x*x + 0.3*alfa*x*x*x + 0.25*(dbeta*i)*x*x*x*x title (sprintf('{/Symbol b} = %.1f' ,dbeta*i )) lw 2.5 , 0.5*x*x + 0.3*alfa*x*x*x + 0.25*(5)*x*x*x*x title (sprintf('{/Symbol b} = %.1f' ,5 )) lw 2.5 
