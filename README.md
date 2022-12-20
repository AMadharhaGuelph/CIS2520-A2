# Student Information
Name: **Ankush Madharha** \
ID: **1172859** \
Assignment Number: **#2** 

# Execution
The program uses a single makefile to compile both questions into executable files.
## Run the `make` command:
```
make
```
Expected Output:
```
gcc  -Wall -std=c99 -pedantic q1.c -o q1
gcc  -Wall -std=c99 -pedantic q2.c -o q2
```

## Execute Q1:
```
./q1 "initialCars.txt"
```

## Execute Q2:
```
./q2 "12+"
```

**Note:** To ensure correct execution, surround the command line arguments in quotations shown above. This is especially important for Q2, as the multiplication symbol (*) can be treated differently depending on the operating system.

# Sample Output
## Q1:
### Menu:
```
1: Add a new car to the available-for-rent list,
2: Add a returned car to the available-for-rent list,
3: Add a returned car to the repair list,
4: Transfer a car from the repair list to the available-for-rent list,
5: Rent the first available car,
6: Print all the lists,
7: quit.
```
### Code 1
```
Enter Plate Number: JGSL-123
Enter Milage: 1234
Added car JGSL-123 to available-for-rent list.
```
### Code 2
```
Enter Plate Number: FJFD-453
Enter Milage: 30000
Returned rented car FJFD-453. Milage cost $2733.35
```
### Code 3
```
Enter Plate Number: TIAA-031
Enter Milage: 10000
Returned rented car TIAA-031. Milage cost $1851.85
```
### Code 4
```
Enter Plate Number: LAKS-294
Moved car LAKS-294 from repair list to avilable-for-rent list.
```
### Code 5
```
Enter Expected Return Date: 220101  
Rented First Available Car: BSNA-350
```
### Code 6
```
Cars Available For Rent:
Plate Number: BSNA-350 | Milage: 99
Plate Number: AMLL-508 | Milage: 2911
Plate Number: BZZZ-063 | Milage: 32131
Plate Number: BPNW-999 | Milage: 34712
Plate Number: ABCD-123 | Milage: 91294

Cars Rented:
Plate Number: TIAA-031 | Milage: 5321 | Expected Return Date: 210120
Plate Number: CJAK-483 | Milage: 3293 | Expected Return Date: 220125
Plate Number: DJDS-812 | Milage: 384 | Expected Return Date: 220508
Plate Number: FJFD-453 | Milage: 23111 | Expected Return Date: 220601
Plate Number: FJDS-224 | Milage: 58322 | Expected Return Date: 221214

Cars in Repair:
Plate Number: POAS-091 | Milage: 39822
Plate Number: UAJS-394 | Milage: 29328
Plate Number: FIAT-352 | Milage: 1922
Plate Number: LAKS-294 | Milage: 91882
Plate Number: UFIN-626 | Milage: 6125
```
### Code 7
```
Total Income: $0.00
```
**Note:** Output may differ depending on output. Sample output given shows the corresponding output for correct input.

## Q2:
```
./q2 "12+53-*"
Answer: 6.00
```