TITLE Assembly Homework 4

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
	INCLUDE hw4.inc

.code
main PROC
	mov ecx, SIZEOF source
	mov esi, 0
	mov edi, SIZEOF source
	dec edi
	dec edi
L1:
	mov al, source[edi]
	mov target[esi], al
	inc esi
	dec edi
	loop L1
	mov edx, OFFSET target
	call WriteString
main ENDP
END main