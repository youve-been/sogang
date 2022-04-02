TITLE Assembly Homework 1

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
INCLUDE hw1.inc

.code
main PROC
	mov eax, 0
	mov edi, OFFSET array1
	mov ecx, LENGTHOF array1
	dec ecx
L1:
	mov ebx, 0
	add ebx, [edi+4]
	sub ebx, [edi]
	add eax, ebx
	add edi, TYPE array1
	loop L1
	call DumpRegs
main ENDP
END main