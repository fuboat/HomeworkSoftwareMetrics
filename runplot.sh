#!/bin/bash

aflfile="$1"
moptfile="$2"
outputfile="$3"

echo "afl file = '$1', mopt file = '$2', output file = '$3'. Right? Press any key to continue."

read -r

(

cat <<_EOF_
set terminal png truecolor enhanced size 800,400 butt

set output '$outputfile'

# set xdata time
# set timefmt '%s'
set format x "%g"
# set format x "%b %d\n%H:%M"
set tics font 'small'
unset mxtics
unset mytics

set grid xtics linetype 0 linecolor rgb '#e0e0e0'
set grid ytics linetype 0 linecolor rgb '#e0e0e0'
set border linecolor rgb '#50c0f0'
set tics textcolor rgb '#000000'
set key outside

set autoscale xfixmin
set autoscale xfixmax

stats '$moptfile' using 1 nooutput
first_x_mopt = STATS_min
stats '$aflfile' using 1 nooutput
first_x_afl = STATS_min
set xrange [0:STATS_max - first_x_afl]
plot '$moptfile' using (\$1-first_x_mopt):(\$7*65536/100) with lines title 'MOpt edges' linecolor rgb '#c000f0' linewidth 3,\
     '$aflfile'  using (\$1-first_x_afl):(\$7*65536/100) with lines title 'AFL edges' linecolor rgb '#0090ff' linewidth 3;

_EOF_

) | gnuplot 