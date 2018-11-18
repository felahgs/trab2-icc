ii#!/usr/bin/gnuplot -c
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera grafico para Tempo
set terminal png
set output 'plots/tempo.png'
set logscale xy 2
set autoscale
set ylabel "sec"
set xlabel "N (size)"

plot "tables/v1_op1_tempo.dat" using 1:2 with lines title "v1-iteração", \
     "tables/v1_op2_tempo.dat" using 1:2 with lines title "v1-residuo", \
     "tables/v2_op1_tempo.dat" using 1:2 with lines title "v2-iteração",  \
     "tables/v2_op2_tempo.dat" using 1:2 with lines title "v2-residuo"
     
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera grafico para FLOPS_DP
set terminal png
set output 'plots/FLOPS_DP.png'
set logscale xy 2
set autoscale
set ylabel "FLOPS_DP (MFlops/s)"
set xlabel "N (size)"

plot "tables/v1_op1_FLOPS_DP.dat" using 1:2 with lines title "v1-iteração", \
     "tables/v1_op2_FLOPS_DP.dat" using 1:2 with lines title "v1-residuo", \
     "tables/v2_op1_FLOPS_DP.dat" using 1:2 with lines title "v2-iteração",  \
     "tables/v2_op2_FLOPS_DP.dat" using 1:2 with lines title "v2-residuo"
     
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera gráfico para L3

set terminal png
set output 'plots/L3.png'
set logscale xy 2
set autoscale
set ylabel "Memory bandwidth [MBytes/s]"
set xlabel "N (size)"


plot "tables/v1_op1_L3.dat" using 1:2 with lines title "v1-iteração", \
     "tables/v1_op2_L3.dat" using 1:2 with lines title "v1-residuo", \
     "tables/v2_op1_L3.dat" using 1:2 with lines title "v2-iteração",  \
     "tables/v2_op2_L3.dat" using 1:2 with lines title "v2-residuo"
   

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# Gera gráfico para L2CACHE

set terminal png
set output 'plots/L2CACHE.png'
set logscale xy 2
set autoscale
set ylabel "Data cache miss ratio"
set xlabel "N (size)"

plot "tables/v1_op1_L2CACHE.dat" using 1:2 with lines title "v1-iteração", \
     "tables/v1_op2_L2CACHE.dat" using 1:2 with lines title "v1-residuo", \
     "tables/v2_op1_L2CACHE.dat" using 1:2 with lines title "v2-iteração",  \
     "tables/v2_op2_L2CACHE.dat" using 1:2 with lines title "v2-residuo"
