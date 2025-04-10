#!/bin/bash
export LC_ALL=C

# For tester;
# ./run.sh |tee -a run.log| run ./main.app | tee -a runtime.log
# rm *.log
# rm *.DAT

generate_random_string() {
    local length=$1
    tr -dc 'A-Z' < /dev/urandom | head -c $length
}

generate_random_price() {
    awk -v min=20 -v max=80 'BEGIN{srand(); printf "%.2f", min+rand()*(max-min)}'
}

echo 1
echo 15

for i in {1..15}; do
    book_id=$(generate_random_string 6)
    book_name=$(generate_random_string 12)
    author=$(generate_random_string 8)
    price=$(generate_random_price)

    echo "$book_id"
    echo "$book_name"
    echo "$author"
    echo "$price"
done
echo "\n"
echo 2
echo "\n"
# 使用最后一个生成的 book_id
echo "3"
echo "$book_id"
echo "\n"
echo 0