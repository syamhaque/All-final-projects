	.ORIG x4000
	
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0

; output label1 to console
LOOP	LEA R0, Label1
	TRAP x22
	AND R1, R1, #0
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0 

; get number input
	TRAP x23
	ADD R1, R1, R0

; convert the ascii to number
	ADD R1, R1, #-15
	ADD R1, R1, #-15
	ADD R1, R1, #-15
	ADD R1, R1, #-3

; check if input is 0
	BRz FINISH

; output label2 to console
	LEA R0, Label2
	TRAP x22

; get letter input
	TRAP x23
	ADD R2, R2, R0

; convert the ascii lower case to upper case
	ADD R2, R2, #-15
	ADD R2, R2, #-15
	ADD R2, R2, #-2

; output label 3
	LEA R0, Label3
	TRAP x22

; output uppercase letters 
COUNTER AND R0, R0, #0
	ADD R0, R0, R2
	TRAP x21
	ADD R1, R1, #-1
	BRp COUNTER

	LEA R0, Label5
	TRAP x22

	BR LOOP

FINISH	LEA R0, Label4
	TRAP x22
	TRAP x25

Label1 .STRINGZ "Enter a number between 0 and 8 (0 to exit):"
Label2 .STRINGZ "Enter a lowercase letter:"
Label3 .STRINGZ "The output is: "
Label4 .STRINGZ "Bye"
Label5 .STRINGZ "\n"
	.END