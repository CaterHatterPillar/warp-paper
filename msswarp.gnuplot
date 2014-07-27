# msswarp.gnuplot

f(x) = mean_basic
t(x) = mean_tile

# Retrieve data need during plot:
plot 'dat/BASICWARPFLOAT.mss'
mss_min_basic = GPVAL_DATA_Y_MIN
mss_max_basic = GPVAL_DATA_Y_MAX
plot 'dat/TILEWARPFLOAT.mss'
mss_min_tile = GPVAL_DATA_Y_MIN
mss_max_tile = GPVAL_DATA_Y_MAX

reset
set terminal latex
set output "msswarp.tex"
unset key
unset xtics
set ytics nomirror

#set ylabel "Time (ms)" rotate by 0 offset -2

set style line 1 lt rgb "#000000" lw 2 pt 1
set style line 2 lt rgb "#000000" lw 2 pt 6
set style line 3 lt rgb "#000000" lw 2 pt 2
set style line 4 lt rgb "#000000" lw 2 pt 9

fit f( x ) 'dat/BASICWARPFLOAT.mss' u 0:1 via mean_basic
stdd_basic = sqrt( FIT_WSSR / ( FIT_NDF + 1 ) )

fit t( x ) 'dat/TILEWARPFLOAT.mss' u 0:1 via mean_tile
stdd_tile = sqrt( FIT_WSSR / ( FIT_NDF + 1 ) )

#set label 1 "Basic" at 0,mean_basic left offset -8,0
#set label 2 "Tile" at 0,mean_tile left offset -8,0
plot mean_basic w l lt rgb "black"      ,\
	mean_basic+stdd_basic w l ls 2	,\
	mean_basic-stdd_basic w l ls 2  ,\
	mean_basic w l ls 2             ,\
	'dat/BASICWARPFLOAT.mss' u 0:(abs($1-mean_basic) < stdd_basic ? $1 : 1/0) w p pt 7 lt rgb "#000000" ps 1 ,\
	mean_tile w l lt rgb "black", mean_tile+stdd_tile w l ls 1 ,\
	mean_tile-stdd_tile w l ls 1 ,\
	mean_tile w l ls 1 ,\
	'dat/TILEWARPFLOAT.mss' u 0:(abs($1-mean_tile) < stdd_tile ? $1 : 1/0) w p pt 7 lt rgb "#000000" ps 1
