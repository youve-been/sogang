TITLE Assembly Homework 2-2

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
Input1 BYTE "Enter a Multiplier : ", 0
Input2 BYTE "Enter a Multilicand : ", 0
Output1 BYTE "Produce : ", 0
Output2 BYTE "Bye!", 0
numStr BYTE 9 DUP(0)
ZERO DWORD 0
Int1 DWORD ?
Int2 DWORD ?

.code
main PROC
L1:									; loop for input and output
	mov edx, OFFSET Input1
	call WriteString				; display Input1(multiplier) string
	mov edx, OFFSET numStr
	mov ecx, SIZEOF numStr - 1
	call ReadString					; read input string of first number
	jz quit							; end loop if input is empty
	call StrToInt					; change input string into hex number
	mov Int1, eax					; put first input number into Int1
	mov edx, OFFSET Input2
	call WriteString				; display Input2(multiplicand) string
	mov edx, OFFSET numStr
	mov ecx, SIZEOF numStr - 1
	call ReadString					; read input string of second number
	call StrToInt					; change input string into hex number
	mov Int2, eax					; put second input number into Int2
	call Multip					; call multiplying procedure
	mov edx, OFFSET Output1
	call WriteString				; display Output1(produce) string
	call WriteHex					; display the product of two numbers in hex
	call CRLF						; start at new line = <enter>

	;temporary
	;mov eax, Int1
	;call WriteHex
	;call CRLF
	;mov eax, Int2
	;call WriteHex
	;call CRLF
	loop L1							; end of loop L1
quit:								; started when loop L1 is ended
	mov edx, OFFSET Output2
	call WriteString				; display Output2(bye) string
main ENDP


StrToInt PROC						; procedure that changes string into hex int
	mov ecx, LENGTHOF numStr - 1	; set loop counter to size of string numStr
	mov esi, 0						; set array index to zero
	mov ebx, 0						; initialize ebx regs to zero
	mov eax, 0						; initialize eax regs to zero

L1:									; loop for changing each element of string into hex int
	mov edx, 10h					; set edx to 10h (multiplier)
	mov bl, numStr[esi]				; set bl regs to [esi]th element of numStr
	cmp ZERO, ebx					; compare ebx regs with zero
	je quitloop						; end loop if ebx regs is zero 
	mul edx							; multiply multiplier
	mov edx, 41h					; set dex to 41h for compare
	cmp ebx, edx					; compare input element with 41h
	jae alpha						; jump to alpha if the input element is an alphabet
	sub ebx, 30h					; make ebx character into int
	add eax, ebx					; add ebx regs to eax regs
	jmp endL1

alpha:								; calculation for hex digits represented by alphabets
	sub ebx, 41h
	add ebx, 10d
	add eax, ebx

endL1:
	inc esi							; increase array index
	loop L1							; end of loop L1

quitloop:							; start when loop L1 ended
	ret								; return to the main procedure
StrToInt ENDP


Multip PROC							; procedure that multiplies Int1 by Int2
	mov ebx, Int1
	mov eax, 0h
	mov edx, 2h
	mov ecx, Int2
	
L1:
	cmp ecx, edx
	jae evenCalc
	cmp ecx, ZERO
	je endL1
	jmp oddCalc

evenCalc:
	shl ebx, 1
	add eax, ebx
	add ecx, -1
	shr ebx, 1
	jmp endL1

oddCalc:
	add eax, ebx

endL1:
	loop L1

quitloop:
	ret
Multip ENDP
END main