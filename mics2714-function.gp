set term jpeg
set output "mics2714-function.jpg"

#set logscale xz
#a = 6.266
f(x) = a * x**m 
# Plot

set grid lw 1
set grid ytics mytics
set grid xtics mytics

set logscale x

set xlabel "ppm NO2"

set logscale y
set yrange [0.01:1000]
set xrange [0.01:1000]
set xtics
set ytics

m = 0.9886
a = 7.3


m1 = 2.35
a1 = 500


f1(x) = a1 * x**m1 

plot [0.01:100] f(x) title 'MIC52714 function -  x**m model II' with lines linestyle 1, f1(x) title 'MIC52714 function -  x**m model I' with lines linestyle 3;
#     g(x) notitle with lines linestyle 2

pause mouse close
