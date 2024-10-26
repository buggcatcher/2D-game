#!/bin/bash
# dai i permessi necessari con chmod +x leak_test.sh prima di fare ./leak_test.sh
# leak_test.sh, so_long e /maps devono essere sullo stesso livello

MAPS_DIR="./maps"
maps=("leak1.ber" "leak2.ber" "leak3.ber" "leak4.ber")
no_leak_count=0

run_valgrind_check() {
    map_name=$1
    valgrind --leak-check=full --show-leak-kinds=all ./so_long "$MAPS_DIR/$map_name" > output.log 2>&1

    definitely_lost=$(grep -c "definitely lost:" output.log)
    indirectly_lost=$(grep -c "indirectly lost:" output.log)
    possibly_lost=$(grep -c "possibly lost:" output.log)
    still_reachable=$(grep -c "still reachable:" output.log)

    if [[ $definitely_lost -eq 0 && $indirectly_lost -eq 0 && $possibly_lost -eq 0 && $still_reachable -eq 0 ]]; then
        echo -e "\e[32mNo leaks are possible in $map_name\e[0m"
        ((no_leak_count++))
    else
        grep "definitely lost:" output.log | grep -v "0 bytes" | sed 's/==[0-9]*==//' | awk '{print "\033[31m    " $0 "\033[0m"}'
        grep "indirectly lost:" output.log | grep -v "0 bytes" | sed 's/==[0-9]*==//' | awk '{print "\033[31m    " $0 "\033[0m"}'
        grep "possibly lost:" output.log | grep -v "0 bytes" | sed 's/==[0-9]*==//' | awk '{print "\033[31m    " $0 "\033[0m"}'
        grep "still reachable:" output.log | grep -v "0 bytes" | sed 's/==[0-9]*==//' | awk '{print "\033[31m    " $0 "\033[0m"}'
    fi
}

for map in "${maps[@]}"; do
    echo "Running valgrind check on $MAPS_DIR/$map"
    run_valgrind_check "$map"
    echo ""
done

if [[ $no_leak_count -eq ${#maps[@]} ]]; then
    echo -e "\e[32mBravo! Non sono possibili perdite di memoria.\e[0m"
else
    echo -e "\e[31mMale, non hai liberato correttamente la memoria\e[0m"
fi
