Task: To implement 2 phase locking with Wound-Wait:

Algorithm:
Assume that Ti requests a variable held by Tj. The following table summarizes the actions taken for wait-die and wound-wait scheme:

Ti is younger than Tj       Ti dies          Ti waits

Ti is older than Tj         Ti waits         Tj aborts



How to run the code:

Command: g++ -o woundAndwait ww.cpp -std=c++11

./woundAndwait < input

Allow wait only if waiting process is younger. 

Here timestamps decrease in any chain of waiting process, so cycles are again impossible. So deadlocks are avoided.
