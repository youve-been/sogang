TITLE Assembly Homework 3

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
INCLUDE hw3.inc
count DWORD ?

.code
main PROC
	mov eax, X
	mov ecx, Y
	dec ecx
L1:   ;X to the power of Y
	mov count, ecx
	mov ecx, X
	dec ecx
	mov edx, eax
L2:
	add eax, edx
	loop L2
	mov ecx, count
	loop L1
	mov ebx, Y
	mov ecx, X
	dec ecx
L3:   ;Y to the power of X
	mov count, ecx
	mov ecx, Y
	dec ecx
	mov edx, ebx
L4:
	add ebx, edx
	loop L4
	mov ecx, count
	loop L3
	call DumpRegs
main ENDP
END main