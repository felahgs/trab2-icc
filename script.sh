

#//www.ibm.com/developerworks/aix/library/au-gnuplot/
# Script para teste de desenpenho das funções de multiplicação de matriz de matmult

# Cria tabela com duas colunas representando tamanho da matriz e valor do grupo testado

#likwid-perfctr -C 1 -g $1  -f ./cgSolver -i 10 -n $2 -k 7 -o asdf -p .5
generate_table()
{
 
 likwid="likwid-perfctr -C 3 -g $1 -m -f" 
 filter="grep '$2' | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4"
 cg_solver_v1="$5"
 cg_solver_v2="$6"
 
 #echo "$likwid" "$cg_solver_v1" "$filter"
 #echo "$likwid" "$cg_solver_v2" "$filter"
 #echo "v1" "$1"
 #evol "$likwid" "$cg_solver_v1"

 echo Resolvendo "$1" de tamanho "$3" para versao antiga
 outputv1="$(eval "$likwid" "$cg_solver_v1")"
 echo Resolvendo "$1" de tamanho "$3" para versao nova
 outputv2="$(eval "$likwid" "$cg_solver_v2")"

# echo "$outputv1" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f $4 | sed -n 1p >> tables/v1-op1_"$1".dat
 #echo "$outputv1" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f $4 | sed -n 2p >> tables/v1-op2_"$1".dat
 #echo "$outputv2" | grep "$2" | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4 | sed -n 3p >> tables/v2-op1_"$1".dat
 #echo "$outputv2" | grep "$2" | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4 | sed -n 4p >> tables/v2-op2_"$1".dat

 echo -ne "$3 " >> tables/v1_op1_"$1".dat
 echo "$outputv1" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f $4 | sed -n 1p >> tables/v1_op1_"$1".dat
 echo -ne "$3 " >> tables/v1_op2_"$1".dat
 echo "$outputv1" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f $4 | sed -n 2p >> tables/v1_op2_"$1".dat
 echo -ne "$3 " >> tables/v2_op1_"$1".dat
 echo "$outputv2" | grep "$2" | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4 | sed -n 1p >> tables/v2_op1_"$1".dat
 echo -ne "$3 " >> tables/v2_op2_"$1".dat
 echo "$outputv2" | grep "$2" | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4 | sed -n 2p >> tables/v2_op2_"$1".dat

 echo
 #echo "$outputv1" | grep "$2" | grep -v "AVX" | tr -s ' ' | cut -d ' ' -f $4 
 #echo "$outputv2" | grep "$2" | grep -v 'AVX' | tr -s ' ' | cut -d ' ' -f $4 

 tempov1=$(echo "$outputv1" | grep Tempo)
 tempov2=$(echo "$outputv2" | grep Tempo)

 if [ $7 = 1 ]
 then
    
    #echo "$tempov1"
    #echo "$tempov2"

    echo -ne "$3 " >> tables/v1_op1_tempo.dat
    echo "$tempov1" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 1p >> tables/v1_op1_tempo.dat
    echo -ne "$3 " >> tables/v1_op2_tempo.dat
    echo "$tempov1" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 2p >> tables/v1_op2_tempo.dat
    echo -ne "$3 " >> tables/v2_op1_tempo.dat
    echo "$tempov2" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 1p >> tables/v2_op1_tempo.dat
    echo -ne "$3 "  >> tables/v2_op2_tempo.dat
    echo "$tempov2" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 2p >> tables/v2_op2_tempo.dat


# echo -ne "$3 "
#echo "$tempov1" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 1p
#echo -ne "$3 " 
#echo "$tempov1" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 2p
#echo -ne "$3 " 
#echo "$tempov2" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 1p
#echo -ne "$3 "  
#echo "$tempov2" | tr -s ' ' | cut -d ' ' -f 4 | sed -n 2p 

 fi
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
[ -e tables/v1_op1_L2CACHE.dat ] && rm tables/*.dat
#rm tables/*.dat

# groups=(60 120)
groups=(32 64 128 256 512 1000 2000)

eval "export PATH=/home/soft/likwid/bin:/home/soft/likwid/sbin:$PATH"
eval "export LD_LIBRARY_PATH=/home/soft/likwid/lib:$LD_LIBRARY_PATH"

#  eval "$cg_solver"
for i in "${groups[@]}"
 do
    # echo $i
    cg_solver_v1="./ver/0.1_original/cgSolver -i 10 -n $i -k 7 -o output/v1_$i.txt -p .5"
    cg_solver_v2="./cgSolver -i 10 -n $i -k 7 -o output/v2_$i.txt -p .5"
    generate_table L2CACHE "miss rate" $i 6 "$cg_solver_v1" "$cg_solver_v2" 1
    generate_table "L3" "L3 bandwidth" $i 6 "$cg_solver_v1" "$cg_solver_v2" 0
    generate_table FLOPS_DP "DP MFLOP/s" $i 5 "$cg_solver_v1" "$cg_solver_v2" 0
 done

#   generate_table L2CACHE "L2 miss rate" $i 6
#   generate_table "L3" "L3 bandwidth" $i 6
#   generate_table FLOPS_DP "DP MFLOP/s" $i 5   generate_table FLOPS_DP "DP MFLOP/s" $i 5
