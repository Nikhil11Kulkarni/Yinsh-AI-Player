# Yinsh-AI-Player
Yinsh Player based on AI with the adversarial search algorithm (mini-max and alpha beta pruning), which arise in sequential deterministic adversarial situations.

How to Run on Windows:
1. Set up server:
python server.py 10000 -ip 127.0.0.1 -n 5 -NC 2 -TL 150 -LOG server.log

2. Set Client1:
python client.py 127.0.0.1 10000 RandomPlayer.py -mode GUI

3.Set Client:
python client.py 127.0.0.1 10000 RandomPlayer.py
