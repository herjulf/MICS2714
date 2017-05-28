set terminal jpeg
#set output "chrge.svg"
#set size 1.0,.5
set format x "%y%m%d\n%H:%M"
#set format x "%H:%M"
set timefmt "%Y-%m-%d %H:%M:%S"
#set timefmt "%y%m%d %H:%M"
set yrange [ 00.00 : 5 ] noreverse nowriteback
set ytics 1
#set ticscale 5 1
#set time 
set  xdata time
# time range must be in same format as data file
#set xrange ["2008-11-17 08:00":"2008-11-17 22:18"]
#set xrange ["2010-08-26 20:00":"2010-08-28 14:00"]
#set xrange ["0-13:00:00":"0-14:00:00"]

set title "NO2 Response Using\nMICS2714 Sensor RLOAD=10k\nLocation Hagundagan Uppsala/SWEDEN";

set ylabel "Voltage/PPM/Temp"
float = 2.5



#define MIC2714_M  0.9986
#define MIC2714_A  0.163
m = 0.9986
a = 0.163


no2convec = 1.9125
no2convwho = 1.88

plot "h19.dat" using 1:($3) title "NO2 Voltage" with line, \
"h19.dat" using 1:(a*(((5-$3)/$3))**m) title "NO2 PPM" with line, \
"h19.dat" using 1:(a*(((5-$3)/$3))**m)*no2convec title "NO2 ug/m**3" with line;
#float title  "RS/R0=1 (Air)" with line 0; 

#charge title "Charge-thresh" with line 3 0

#pause -1;
