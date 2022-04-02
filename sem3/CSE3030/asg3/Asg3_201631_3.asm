TITLE Assembly Homework 2-3

.386
.MODEL flat, stdcall

INCLUDE irvine32.inc

.data
Input1 BYTE "Type_A_String: ", 0
Input2 BYTE "A_Word_for_Search: ", 0
Output1 BYTE "Found", 0
Output2 BYTE "Not found", 0
Output3 BYTE "Changed : ", 0
quitStr BYTE "Bye!", 0
inputStr BYTE 45 DUP(0)
key BYTE 45 DUP(0)
newStr BYTE 41 DUP(0)
foundFlag DWORD 0
checkStart DWORD 0
checkEnd DWORD 0

.code
main PROC
L1:
	mov foundFlag, 0
	mov edx, OFFSET Input1
	call WriteString
	mov edx, OFFSET inputStr
	mov ecx, SIZEOF inputStr-1
	call ReadString
	jz quit
	mov eax, 0
	mov ebx, 0
	mov bl, inputStr[40]
	cmp eax, ebx
	jne L1


L2:
	mov edx, OFFSET Input2
	call WriteString
	mov edx, OFFSET key
	mov ecx, SIZEOF key -1
	call ReadString
	jz quit
	mov eax, 0
	mov ebx, 0
	mov bl, key[40]
	cmp eax, ebx
	jne L1
	call search
	call output
	
endL1:	
	call CRLF
	loop L1

quit:
	mov edx, OFFSET quitStr
	call WriteString
	exit
main ENDP


output PROC
	mov edx, 0h
	cmp foundFlag, edx
	je notfound

found:
	call change
	mov edx, OFFSET Output1
	call WriteString
	call CRLF
	mov edx, OFFSET Output3
	call WriteString
	mov edx, OFFSET newStr
	call WriteString
	jmp quit

notfound:
	mov edx, OFFSET Output2
	call WriteString
	call CRLF
	mov edx, OFFSET Output3
	call WriteString
	mov edx, OFFSET inputStr
	call WriteString

quit:
	ret
output ENDP


search PROC
	mov ecx, SIZEOF inputStr - 1
	mov edx, 0
	mov ebx, 0
	mov esi, 0
	mov edi, 0
L1:
	mov bl, inputStr[esi]
	mov dl, key[edi]
	cmp ebx, edx
	jne endL1
	mov checkStart, esi

L2:
	inc esi
	inc edi
	mov bl, inputStr[esi]
	mov dl, key[edi]
	mov eax, 0h
	cmp edx, eax
	je endKey
	cmp ebx, edx
	jne endL1
	je endL2

endKey:
	mov eax, 20h
	cmp ebx, eax
	je found
	mov eax, 0h
	cmp ebx, eax
	je found
	jne endL1

endL2:
	loop L2

endL1:
	mov edi, 0
	inc esi
	cmp edi, ebx
	je notfound
	loop L1

notfound:
	ret

found:
	mov checkEnd, esi
	inc foundFlag
	ret
search ENDP


change PROC
	mov ecx, SIZEOF inputStr - 1
	mov esi, 0
	mov edi, 0
	mov ebx, 0
L1:
	cmp esi, checkStart
	jb copy
	cmp esi, checkEnd
	jae copy
	jmp endL1

copy:
	mov bl, inputStr[esi]
	mov newStr[edi], bl
	inc edi
	mov edx, 0
	cmp edx, ebx
	je quit

endL1:
	inc esi
	loop L1

quit:
	ret
change ENDP
END main