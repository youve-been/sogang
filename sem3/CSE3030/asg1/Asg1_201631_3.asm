TITLE Assembly Homework 3-3

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
Menu1 BYTE "x AND y", 0
Menu2 BYTE "x OR y", 0
Menu3 BYTE "NOT x", 0
Menu4 BYTE "x XOR y", 0
Menu5 BYTE "5. Exit program", 0
Input1 BYTE "Choose Calculation Mode : ", 0
InputX BYTE "Enter x : ", 0
InputY BYTE "Enter y : ", 0
Output1 BYTE "Result of ", 0
Output2 BYTE "Do you want to change the mode(Y/N)? : ", 0
Colon BYTE " : ", 0
Dot BYTE ". ", 0
Choice DWORD ?
Answer DWORD 0

CaseTable DWORD 1
	DWORD AND_op
	EntrySize = ($ - CaseTable)
	DWORD 2
	DWORD OR_op
	DWORD 3
	DWORD NOT_op
	DWORD 4
	DWORD XOR_op
nEntries  = ($ - CaseTable) / EntrySize

.code
main PROC
Menu:
	call PrintMenu
Input:
	mov edx, OFFSET Input1
	call WriteString
	call ReadInt
	cmp eax, 0
	jbe Input
	cmp eax, 5
	je quit
	ja Input
	mov Choice, eax

L0:
	mov eax, Choice
	mov ebx, OFFSET CaseTable
	mov ecx, nEntries

L1:
	cmp eax, [ebx]
	jne L2
	call NEAR PTR [ebx+4]
	jmp L3
L2:
	add ebx, EntrySize
	loop L1

L3:
	mov edx, OFFSET Output2
	call WriteString
	call ReadChar
	call CRLF
	cmp al, 59h
	je Menu
	cmp al, 79h
	je Menu
	cmp al, 6Eh
	je L0
	cmp al, 4Eh
	je L0
	jmp L3

quit:
	exit
main ENDP

AND_op PROC
	mov edx, OFFSET InputX
	call WriteString
	call ReadHex
	mov Answer, eax
	mov edx, OFFSET InputY
	call WriteString
	call ReadHex
	and Answer, eax
	call PrintOutput
	ret
AND_op ENDP

OR_op PROC
	mov edx, OFFSET InputX
	call WriteString
	call ReadHex
	mov Answer, eax
	mov edx, OFFSET InputY
	call WriteString
	call ReadHex
	or Answer, eax
	call PrintOutput
	ret
OR_op ENDP

NOT_op PROC
	mov edx, OFFSET InputX
	call WriteString
	call ReadHex
	mov Answer, eax
	not Answer
	call PrintOutput
	ret
NOT_op ENDP

XOR_op PROC
	mov edx, OFFSET InputX
	call WriteString
	call ReadHex
	mov Answer, eax
	mov edx, OFFSET InputY
	call WriteString
	call ReadHex
	xor Answer, eax
	call PrintOutput
	ret
XOR_op ENDP

PrintMenu PROC
	mov eax, 0
	mov ecx, 4
L1:
	inc eax
	call WriteDec
	mov edx, OFFSET Dot
	call WriteString
	cmp eax, 1
	jne _menu2
	mov edx, OFFSET Menu1
	jmp print
_menu2:
	cmp eax, 2
	jne _menu3
	mov edx, OFFSET Menu2
	jmp print
_menu3:
	cmp eax, 3
	jne _menu4
	mov edx, OFFSET Menu3
	jmp print
_menu4:
	mov edx, OFFSET Menu4
print:
	call WriteString
	call CRLF
	loop L1

	mov edx, OFFSET Menu5
	call WriteString
	call CRLF
	call CRLF
	call CRLF
	ret
PrintMenu ENDP

PrintOutput PROC
	mov eax, Choice
	mov edx, OFFSET Output1
	call WriteString
	cmp eax, 1
	jne _menu2
	mov edx, OFFSET Menu1
	jmp print
_menu2:
	cmp eax, 2
	jne _menu3
	mov edx, OFFSET Menu2
	jmp print
_menu3:
	cmp eax, 3
	jne _menu4
	mov edx, OFFSET Menu3
	jmp print
_menu4:
	mov edx, OFFSET Menu4
print:
	call WriteString
	mov edx, OFFSET Colon
	call WriteString
	mov eax, Answer
	call WriteHex
	call CRLF
	call CRLF
	call CRLF
	ret
PrintOutput ENDP

END main