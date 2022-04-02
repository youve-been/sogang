TITLE Assembly Homework 3-1

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
INCLUDE hw3.inc
Input1 BYTE "Before sort : ", 0
Comma BYTE ", ", 0
Output1 BYTE "After sort : ", 0
Output2 BYTE "Bye!", 0

.code
main PROC
	mov edx, OFFSET Input1
	call WriteString
	call PrintArray
	mov ebx, 0
	call Sort			; sort odd index
	mov ebx, TYPE ArrData
	call Sort			; sort even index

	mov edx, OFFSET Output1
	call WriteString
	call PrintArray

	mov edx, OFFSET Output2
	call WriteString
	exit
main ENDP

PrintArray PROC
	mov ecx, Lendata
	dec ecx
	mov esi, 0
	mov edx, OFFSET Comma
L1:
	mov eax, ArrData[esi]
	call WriteHex
	call WriteString
	add esi, TYPE ArrData
	loop L1

	mov eax, ArrData[esi]
	call WriteHex
	call CRLF
	ret 
PrintArray ENDP

Sort PROC
	LOCAL Index:DWORD				; size of Arrdata * 2

	mov Index, TYPE ArrData
	add Index, TYPE ArrData
	mov ecx, LenData
	dec ecx
	cmp ebx, 0
	je _next
_minus:
	dec ecx
	dec ecx
_next:
	
L1:
	push ecx
	mov ecx, LenData
	dec ecx
	cmp ebx, 0
	je next
minus:
	dec ecx
	dec ecx
next:
	mov esi, 0
	add esi, ebx
L2:
	mov edi, esi
	add edi, Index
	mov eax, ArrData[esi]
	mov edx, ArrData[edi]
	shr eax, 16
	shr edx, 16
	cmp ebx, 0
	jne _even

_odd:
	call OddComp
	jmp cont

_even:
	call EvenComp
	
cont:
	add esi, Index
	dec ecx
	loop L2
	pop ecx
	dec ecx
	loop L1

	ret
Sort ENDP

OddComp PROC
	cmp al, dl
	ja swap
	jb quit
	je equal

swap:
	mov eax, ArrData[esi]
	mov edx, ArrData[edi]
	mov ArrData[esi], edx
	mov ArrData[edi], eax
	jmp quit

equal:
	mov eax, ArrData[esi]
	mov edx, ArrData[edi]
	cmp al, dl
	jb swap
	jae quit

quit:
	ret
OddComp ENDP

EvenComp PROC
	cmp al, dl
	jb swap
	ja quit
	je equal

swap:
	mov eax, ArrData[esi]
	mov edx, ArrData[edi]
	mov ArrData[esi], edx
	mov ArrData[edi], eax
	jmp quit

equal:
	mov eax, ArrData[esi]
	mov edx, ArrData[edi]
	cmp al, dl
	ja swap
	jbe quit

quit:
	ret
EvenComp ENDP
END main