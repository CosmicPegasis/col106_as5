for i in {1..50};
do
    python3 siddhartha_tester.py >> /dev/null
    ./e++ a.txt >> /dev/null
    python3 run_stack_machine.py targ.txt 500
    python3 run_stack_machine.py expecTarg.txt 500
    done
