#!/usr/bin/gnuplot -c
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera grafico para FLOPS_DP
set terminal png
set output 'FLOPS_DP.png'
set autoscale
set ylabel "FLOPS_DP (MFlops/s)"
set xlabel "N (bytes)"

plot "tables/matptr_FLOPS_DP.dat" using 1:2 with lines title "matptr", \
     "tables/matcol_FLOPS_DP.dat" using 1:2 with lines title "matcol", \
     "tables/matrow_FLOPS_DP.dat" using 1:2 with lines title "matrow"
     
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera gráfico para L3

set terminal png
set output 'L3.png'
set autoscale
set ylabel "Memory bandwidth [MBytes/s]"
set xlabel "N (bytes)"


plot "tables/matptr_L3.dat" using 1:2 with lines title "matptr", \
     "tables/matcol_L3.dat" using 1:2 with lines title "matcol", \
     "tables/matrow_L3.dat" using 1:2 with lines title "matrow"
   

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera gráfico para L2CACHE

set terminal png
set output 'L2CACHE.png'
set autoscale
set ylabel "Data cache miss ratio"
set xlabel "N (bytes)"

plot "tables/matptr_L2CACHE.dat" using 1:2 with lines title "matptr", \
     "tables/matcol_L2CACHE.dat" using 1:2 with lines title "matcol", \
     "tables/matrow_L2CACHE.dat" using 1:2 with lines title "matrow"