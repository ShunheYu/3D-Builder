; Listing generated by Microsoft (R) Optimizing Compiler Version 19.23.28106.4 

	TITLE	J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRT
INCLUDELIB OLDNAMES

EXTRN	__imp_?staticMetaObject@QMainWindow@@2UQMetaObject@@B:BYTE
CONST	SEGMENT
?qt_meta_stringdata_Builder@@3Uqt_meta_stringdata_Builder_t@@B DD 0ffffffffH ; qt_meta_stringdata_Builder
	DD	07H
	DD	00H
	DD	010H
	DB	042H
	DB	075H
	DB	069H
	DB	06cH
	DB	064H
	DB	065H
	DB	072H
	DB	00H
?qt_meta_data_Builder@@3QBIB DD 08H			; qt_meta_data_Builder
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
	DD	00H
CONST	ENDS
PUBLIC	??_H@YGXPAXIIP6EPAX0@Z@Z			; `vector constructor iterator'
PUBLIC	?metaObject@Builder@@UBEPBUQMetaObject@@XZ	; Builder::metaObject
PUBLIC	?qt_metacast@Builder@@UAEPAXPBD@Z		; Builder::qt_metacast
PUBLIC	?qt_metacall@Builder@@UAEHW4Call@QMetaObject@@HPAPAX@Z ; Builder::qt_metacall
PUBLIC	?qt_static_metacall@Builder@@CAXPAVQObject@@W4Call@QMetaObject@@HPAPAX@Z ; Builder::qt_static_metacall
PUBLIC	?staticMetaObject@Builder@@2UQMetaObject@@B	; Builder::staticMetaObject
EXTRN	__imp_?dynamicMetaObject@QObjectData@@QBEPAUQMetaObject@@XZ:PROC
EXTRN	__imp_?qt_metacast@QMainWindow@@UAEPAXPBD@Z:PROC
EXTRN	__imp_?qt_metacall@QMainWindow@@UAEHW4Call@QMetaObject@@HPAPAX@Z:PROC
CRT$XCU	SEGMENT
??staticMetaObject$initializer$@Builder@@2P6AXXZA@@3P6AXXZA DD FLAT:??__E?staticMetaObject@Builder@@2UQMetaObject@@B@@YAXXZ ; ??staticMetaObject$initializer$@Builder@@2P6AXXZA@@3P6AXXZA
CRT$XCU	ENDS
_DATA	SEGMENT
?staticMetaObject@Builder@@2UQMetaObject@@B DB 4 DUP(00H) ; Builder::staticMetaObject
	DD	FLAT:?qt_meta_stringdata_Builder@@3Uqt_meta_stringdata_Builder_t@@B
	DD	FLAT:?qt_meta_data_Builder@@3QBIB
	DD	FLAT:?qt_static_metacall@Builder@@CAXPAVQObject@@W4Call@QMetaObject@@HPAPAX@Z
	DD	00H
	DD	00H
_DATA	ENDS
; Function compile flags: /Ogtp
;	COMDAT ??__E?staticMetaObject@Builder@@2UQMetaObject@@B@@YAXXZ
text$di	SEGMENT
??__E?staticMetaObject@Builder@@2UQMetaObject@@B@@YAXXZ PROC ; `dynamic initializer for 'Builder::staticMetaObject'', COMDAT
; File J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
; Line 66
	mov	eax, DWORD PTR __imp_?staticMetaObject@QMainWindow@@2UQMetaObject@@B
	mov	DWORD PTR ?staticMetaObject@Builder@@2UQMetaObject@@B, eax
; Line 71
	ret	0
??__E?staticMetaObject@Builder@@2UQMetaObject@@B@@YAXXZ ENDP ; `dynamic initializer for 'Builder::staticMetaObject''
text$di	ENDS
; Function compile flags: /Ogtp
;	COMDAT ?qt_static_metacall@Builder@@CAXPAVQObject@@W4Call@QMetaObject@@HPAPAX@Z
_TEXT	SEGMENT
__o$ = 8						; size = 4
__c$ = 12						; size = 4
__id$ = 16						; size = 4
__a$ = 20						; size = 4
?qt_static_metacall@Builder@@CAXPAVQObject@@W4Call@QMetaObject@@HPAPAX@Z PROC ; Builder::qt_static_metacall, COMDAT
; File J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
; Line 63
	ret	0
?qt_static_metacall@Builder@@CAXPAVQObject@@W4Call@QMetaObject@@HPAPAX@Z ENDP ; Builder::qt_static_metacall
_TEXT	ENDS
; Function compile flags: /Ogtp
;	COMDAT ?qt_metacall@Builder@@UAEHW4Call@QMetaObject@@HPAPAX@Z
_TEXT	SEGMENT
__c$ = 8						; size = 4
__id$ = 12						; size = 4
__a$ = 16						; size = 4
?qt_metacall@Builder@@UAEHW4Call@QMetaObject@@HPAPAX@Z PROC ; Builder::qt_metacall, COMDAT
; _this$ = ecx
; File J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
; Line 89
	push	ebp
	mov	ebp, esp
; Line 92
	pop	ebp
; Line 90
	jmp	DWORD PTR __imp_?qt_metacall@QMainWindow@@UAEHW4Call@QMetaObject@@HPAPAX@Z
?qt_metacall@Builder@@UAEHW4Call@QMetaObject@@HPAPAX@Z ENDP ; Builder::qt_metacall
_TEXT	ENDS
; Function compile flags: /Ogtp
;	COMDAT ?qt_metacast@Builder@@UAEPAXPBD@Z
_TEXT	SEGMENT
__clname$ = 8						; size = 4
?qt_metacast@Builder@@UAEPAXPBD@Z PROC			; Builder::qt_metacast, COMDAT
; _this$ = ecx
; File J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
; Line 81
	push	ebp
	mov	ebp, esp
	push	esi
; Line 82
	mov	esi, DWORD PTR __clname$[ebp]
	push	edi
	mov	edi, ecx
	test	esi, esi
	jne	SHORT $LN2@qt_metacas
	pop	edi
	xor	eax, eax
; Line 86
	pop	esi
	pop	ebp
	ret	4
$LN2@qt_metacas:
; Line 83
	mov	eax, OFFSET ?qt_meta_stringdata_Builder@@3Uqt_meta_stringdata_Builder_t@@B+16
	mov	ecx, esi
	npad	3
$LL5@qt_metacas:
	mov	dl, BYTE PTR [ecx]
	cmp	dl, BYTE PTR [eax]
	jne	SHORT $LN6@qt_metacas
	test	dl, dl
	je	SHORT $LN7@qt_metacas
	mov	dl, BYTE PTR [ecx+1]
	cmp	dl, BYTE PTR [eax+1]
	jne	SHORT $LN6@qt_metacas
	add	ecx, 2
	add	eax, 2
	test	dl, dl
	jne	SHORT $LL5@qt_metacas
$LN7@qt_metacas:
	xor	eax, eax
	jmp	SHORT $LN8@qt_metacas
$LN6@qt_metacas:
	sbb	eax, eax
	or	eax, 1
$LN8@qt_metacas:
	test	eax, eax
	jne	SHORT $LN3@qt_metacas
; Line 84
	mov	eax, edi
	pop	edi
; Line 86
	pop	esi
	pop	ebp
	ret	4
$LN3@qt_metacas:
; Line 85
	push	esi
	mov	ecx, edi
	call	DWORD PTR __imp_?qt_metacast@QMainWindow@@UAEPAXPBD@Z
	pop	edi
; Line 86
	pop	esi
	pop	ebp
	ret	4
?qt_metacast@Builder@@UAEPAXPBD@Z ENDP			; Builder::qt_metacast
_TEXT	ENDS
; Function compile flags: /Ogtp
;	COMDAT ?metaObject@Builder@@UBEPBUQMetaObject@@XZ
_TEXT	SEGMENT
?metaObject@Builder@@UBEPBUQMetaObject@@XZ PROC		; Builder::metaObject, COMDAT
; _this$ = ecx
; File J:\for_linux_file\work\3D-Builder\3D-Builder\Release\moc\moc_Builder.cpp
; Line 77
	mov	ecx, DWORD PTR [ecx+4]
	cmp	DWORD PTR [ecx+24], 0
	je	SHORT $LN3@metaObject
	jmp	DWORD PTR __imp_?dynamicMetaObject@QObjectData@@QBEPAUQMetaObject@@XZ
$LN3@metaObject:
	mov	eax, OFFSET ?staticMetaObject@Builder@@2UQMetaObject@@B ; Builder::staticMetaObject
; Line 78
	ret	0
?metaObject@Builder@@UBEPBUQMetaObject@@XZ ENDP		; Builder::metaObject
_TEXT	ENDS
; Function compile flags: /Ogtp
;	COMDAT ??_H@YGXPAXIIP6EPAX0@Z@Z
_TEXT	SEGMENT
___t$ = 8						; size = 4
___s$ = 12						; size = 4
___n$ = 16						; size = 4
___f$ = 20						; size = 4
??_H@YGXPAXIIP6EPAX0@Z@Z PROC				; `vector constructor iterator', COMDAT
	push	ebp
	mov	ebp, esp
	push	esi
	mov	esi, DWORD PTR ___n$[ebp]
	test	esi, esi
	je	SHORT $LN6@vector
	push	ebx
	mov	ebx, DWORD PTR ___f$[ebp]
	push	edi
	mov	edi, DWORD PTR ___t$[ebp]
$LL2@vector:
	mov	ecx, edi
	call	ebx
	add	edi, DWORD PTR ___s$[ebp]
	sub	esi, 1
	jne	SHORT $LL2@vector
	pop	edi
	pop	ebx
$LN6@vector:
	pop	esi
	pop	ebp
	ret	16					; 00000010H
??_H@YGXPAXIIP6EPAX0@Z@Z ENDP				; `vector constructor iterator'
_TEXT	ENDS
END