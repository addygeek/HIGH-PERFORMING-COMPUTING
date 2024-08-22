
set terminal dumb size 80, 24
set title 'Monte Carlo Simulation of π'
set xlabel 'x'
set ylabel 'y'
set xrange [-1:1]
set yrange [-1:1]
set size square
plot 'points.dat' with points pt 1 lc rgb 'blue' title 'Points'
