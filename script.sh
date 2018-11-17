#//www.ibm.com/developerworks/aix/library/au-gnuplot/
# Script para teste de desenpenho das funções de multiplicação de matriz de matmult

# Cria tabela com duas colunas representando tamanho da matriz e valor do grupo testado
#likwid-perfctr -C 1 -g $1  -f ./cgSolver -i 10 -n $2 -k 7 -o asdf -p .5
generate_table()
{

 likwid="likwid-perfctr -C 1 -g $1  -f"
 filter="| grep '$2' | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4"
 cg_solver_v1="$5"
 cg_solver_v2="$6"

 #echo "$likwid" "$cg_solver_v1" "$filter"
 #echo "$likwid" "$cg_solver_v2" "$filter"

 eval "$likwid" "$cg_solver_v1"

 # tr -s ' '       --- comprimir todos os empaçamentos em apenas um character
 # cut -d ' ' -f 6 --- utilizar expaços como delimitador e retornar palavra na posição 6
 # sed -n 1p       --- rotorna a linha escolhida pelo numero que antecede p
#  likwid-perfctr -C 1 -g L2CACHE  -f 
#  ./cgSolver -i 400 -n 60 -k 3 -o asdf -p .5 
#  | grep "L2 miss rate" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 6


#  results=$(echo "$likwid_test" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f "$4")
# likwid-perfctr -C 1 -g L2CACHE  -f ./cgSolver -i 400 -n 60 -k 3 -o asdf -p .5 | grep "L2 miss rate" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 6
# likwid-perfctr -C 1 -g L3  -f ./cgSolver -i 400 -n 60 -k 3 -o asdf -p .5 | grep "L3 bandwidth"| grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 6
# likwid-perfctr -C 1 -g FLOPS_DP  -f ./cgSolver -i 400 -n 60 -k 3 -o asdf -p .5 | grep "DP MFLOP/s" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 5

#  eval $5 | grep "residuo" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 4
#  eval $6 | grep "residuo" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f 4
#  echo "$tam" $(echo "$results" | sed -n 1p) >> tables/matptr_"$1".dat
#  echo "$tam" $(echo "$results" | sed -n 2p) >> tables/matrow_"$1".dat
#  echo "$tam" $(echo "$results" | sed -n 3p) >> tables/matcol_"$1".dat

}

# Execução do script
###
[ -e tables/matcol_L3.dat ] && rm tables/*.dat
#rm tables/*.dat

# groups=(60 120)
groups=(60)

eval "export PATH=/usr/local/bin:/usr/local/sbin:$PATH"
eval "export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH"

#  eval "$cg_solver"
for i in "${groups[@]}"
 do
    # echo $i
    cg_solver_v1="./ver/0.1_original/cgSolver -i 400 -n $i -k 3 -o output/v1_$i.txt -p .5"
    cg_solver_v2="./cgSolver -i 400 -n $i -k 3 -o output/v2_$i.txt -p .5"
    generate_table L2CACHE "L2 miss rate" $i 6 "$cg_solver_v1" "$cg_solver_v2" 0
    # generate_table "L3" "L3 bandwidth" $i 6 "$cgSolver_v1" "$cg_solver_v2"
    # generate_table FLOPS_DP "DP MFLOP/s" $i 5 "$cgSolver_v1" "$cg_solver_v2"
 done

#   generate_table L2CACHE "L2 miss rate" $i 6
#   generate_table "L3" "L3 bandwidth" $i 6
#   generate_table FLOPS_DP "DP MFLOP/s" $i 5   generate_table FLOPS_DP "DP MFLOP/s" $i 5:uu

likwid-perfctr -C 1 -g L3 -m -f ./cgSolver -i 400 -n 60 -k 3 -o testlik -p .5
likwid-perfctr -C 1 -g L3 -m -f