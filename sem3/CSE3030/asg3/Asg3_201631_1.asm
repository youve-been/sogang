TITLE Assembly Homework 2-1

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
var1 BYTE "65", 0
sep DWORD 7h

.code
main PROC
	mov ecx, LENGTHOF var1 - 1
	mov esi, 0
	mov ebx, 0
	mov eax, 0
L1:
	mul sep
	mov bl, var1[esi]
	sub bl, 30h
	add eax, ebx
	inc esi
	loop L1

	call DUMPREGS
main ENDP
END main