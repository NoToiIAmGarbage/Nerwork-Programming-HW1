#!/bin/bash

make 

SERVER_SESSION="np_demo_server"
CLIENT_SESSION="np_demo_client"

if [ -n "`tmux ls | grep $SERVER_SESSION`" ]; then
  tmux kill-session -t $SERVER_SESSION
fi

if [ -n "`tmux ls | grep $CLIENT_SESSION`" ]; then
  tmux kill-session -t $CLIENT_SESSION
fi

IP=$1
PORT=$2
SLEEP_TIME=0.1

# Create the server
tmux new-session -d -s $SERVER_SESSION
tmux set remain-on-exit on

tmux send-keys -t $SERVER_SESSION "./server $PORT" ENTER

# Create the clients
tmux new-session -d -s $CLIENT_SESSION
tmux set remain-on-exit on

tmux select-pane -t 0
tmux split-window -h

sleep 2.5

# Start testing
echo -e "\nconnection & exit test...\c"
if [ -f "connection_test.txt" ]; then
  rm connection_test.txt
fi
for i in $(seq 0 1)
do
    tmux send-keys -t ${i} "./client $IP $PORT >> user${i}.txt" Enter
    sleep $SLEEP_TIME

    # No difference with connection.txt is correct
    diff user${i}.txt ./connection.txt -b -B -y --suppress-common-lines >> connection_test.txt
    rm user${i}.txt
done

for i in $(seq 0 1)
do
    # You must ensure that your server is running after the connection closeing 
    tmux send-keys -t ${i} "exit" Enter          
    sleep $SLEEP_TIME
done

# If there's difference between your client output and connection.txt, the difference will be printed:
if [ -s connection_test.txt ]; then
  echo " Wrong"
  cat connection_test.txt
else
  echo " Success"
  rm connection_test.txt
fi

# Delete the executable files
rm server
rm client

# If you want to see how your program is running on tmux,
# you can comment out these two commands and just use
# "tmux attach -t np_demo_server" or "tmux attach -t np_demo_client"
# to check server and client respectively
tmux kill-session -t $SERVER_SESSION
tmux kill-session -t $CLIENT_SESSION
