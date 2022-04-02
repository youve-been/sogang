TITLE Assembly Homework 3-2

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

Get_frequencies PROTO, 
	pTarget:PTR BYTE,
	pTable:PTR DWORD

.data
target BYTE "12345678910", 0
Comma BYTE "  ", 0
freqTable DWORD 256 DUP(0)
tableSize DWORD 128	

.code
main PROC
	invoke Get_frequencies, ADDR target, ADDR freqTable
	mov esi, OFFSET freqTable
	mov ecx, tableSize
	mov ebx, 0

L1:
	mov eax, ebx
	call WriteInt
	mov edx, OFFSET Comma
	call WriteString
	mov eax, [esi]
	call WriteInt
	call CRLF
	add esi, 4
	inc ebx
	loop L1
	exit
main ENDP

Get_frequencies PROC,
	pTarget:PTR BYTE,
	pTable:PTR DWORD
	mov esi, pTarget
	
L1:
	mov ebx, 0
	mov eax, [esi]
	mov bl, al
	cmp bl, 0
	je quit

	mov edi, pTable
	mov edx, 1
	imul ebx, 4
	add edi, ebx
	add [edi], edx
	mov eax, [edi]
	inc esi
	jmp L1

quit:
	ret
Get_frequencies ENDP

END main