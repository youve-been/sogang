TITLE Assembly Homework 2

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
INCLUDE hw2.inc

.code
main PROC
	mov ebx, 1   ;fib(n-1)
	mov edx, 1   ;fib(n-2)
	mov ecx, fib
	sub ecx, 2
L1:
	mov eax, 0
	add eax, ebx
	add eax, edx
	mov edx, ebx
	mov ebx, eax
	loop L1
	call DumpRegs
main ENDP
END main