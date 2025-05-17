./generation_test_RMQ.sh
./runner.sh

for (( i = 1; i <= 5; i++));
do
    cd TEST
    ./generation_test_RMQ
    cd ..
    ./runner
    echo 
    sleep 1
done
