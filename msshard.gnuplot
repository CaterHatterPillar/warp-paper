# msshard.gnuplot

# Function declarations:
f( x ) = mean_basic
t( x ) = mean_tile

# Retrieve data need during plot:
plot 'BASICHARDFLOAT.mss'
mss_min_basic = GPVAL_DATA_Y_MIN
mss_max_basic = GPVAL_DATA_Y_MAX
plot 'TILEHARDFLOAT.mss'
mss_min_tile = GPVAL_DATA_Y_MIN
mss_max_tile = GPVAL_DATA_Y_MAX

# Configuration and output-settings:
reset
set terminal latex
set title "Execution Time - Hardware Acceleration"
set output "msshard.tex"
set yrange [0:0.8]
unset key

set ylabel "Time (ms)" offset -2

# Utility:
set style line 1 lt rgb "#A00000" lw 2 pt 1
set style line 2 lt rgb "#00A000" lw 2 pt 6
set style line 3 lt rgb "#5060D0" lw 2 pt 2
set style line 4 lt rgb "#F25900" lw 2 pt 9

# Plotting Source:
fit f( x ) 'BASICHARDFLOAT.mss' u 0:1 via mean_basic
stdd_basic = sqrt( FIT_WSSR / ( FIT_NDF + 1 ) )

fit t( x ) 'TILEHARDFLOAT.mss' u 0:1 via mean_tile
stdd_tile = sqrt( FIT_WSSR / ( FIT_NDF + 1 ) )

set label 1 "Basic" at 0,mean_basic left offset -8,0
set label 2 "Tile" at 0,mean_tile left offset -8,0
plot 'BASICHARDFLOAT.mss' u 0:(abs($1-mean_basic) < stdd_basic ? $1 : 1/0) w p pt 7 lt rgb "#00A000" ps 1	,\
	'TILEHARDFLOAT.mss' u 0:(abs($1-mean_tile) < stdd_tile ? $1 : 1/0) w p pt 7 lt rgb "#A00000" ps 1