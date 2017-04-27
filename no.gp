set term jpeg
set output "mics2714-function.jpg"

#set logscale xz
m = 0.9886
a = 7.3
#a = 6.266
f(x) = a * x**m 
# Plot

set grid lw 1
set grid ytics mytics
set grid xtics mytics

set logscale x

set xlabel "ppm NO2"

set logscale y
set yrange [0.1:1000]
set xrange [0.01:100]
set xtics
set ytics


plot [0.01:10] f(x) title 'MIC52714 function -  x**m' with lines linestyle 1;
#     g(x) notitle with lines linestyle 2

pause mouse close
