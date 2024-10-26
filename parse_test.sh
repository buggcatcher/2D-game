#!/bin/bash
# dai i permessi necessari con chmod +x parse_test.sh prima di fare ./parse_test.sh
# parse_test.sh, so_long e /maps devono essere sullo stesso livello

MAPS_DIR="./maps"

maps=("aaaaaa.ber" "ber.bertoldo" "char.ber" "door.ber" "file.txt" "rect.ber" "walls.ber" "ber" "cep.ber" "door2.ber" "empty.ber" "line_empty.ber" "nosudo.ber" "unreach.ber")

success_count=0
total_maps=${#maps[@]} 

run_with_timeout() {
    map_name=$1
    timeout 0.1 ./so_long "$MAPS_DIR/$map_name" > output.log 2>&1
    if [[ $? -eq 124 ]]; then
        echo -e "❌ \e[31mERRORE: Il programma e' stato eseguito con $map_name\e[0m"
    else
        echo -e "✅ \e[32m$(cat output.log)\e[0m"
        ((success_count++))
    fi
}

# scommenta per vedere le mappe
for map in "${maps[@]}"; do
    echo "./so_long $map"
    #cat "$MAPS_DIR/$map"
    #echo ""
    run_with_timeout "$map"
    echo ""
done

if [[ $success_count -eq $total_maps ]]; then
    echo "Bravo, tutte le mappe invalide restituiscono errore."
else
    echo "Male, non hai gestito correttamente tutti i casi."
fi

