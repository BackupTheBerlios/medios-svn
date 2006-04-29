	.if (1)

;**********************************************************************
;*		 (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 1996 				  *
;*																	  *
;*		Interrupt Vector Assignments for 'C54x						  *
;* 
;* Note that not all interupt names will apply to any given target.
;* This serves only as a multi-purpose example across the C54x family.
;* Consult the TI DSP Reference manual to determine which interrupts 
;*   apply to a given target.
;**********************************************************************
	.title "Interrupt Vectors w/ RTDX for C54X"
	.tab	4
	.file	"vectors.asm"
	.mmregs

	.sect	".vectors"
	.def RS_V, SINTR_V, _VECSTART
	.ref _c_int00
	.ref _dummyISR
_VECSTART:
RS_V:				; Hardware Reset Vector
SINTR_V:			; Software Reset Vector
	; Note: no need to push XPC here - reset clears XPC
	.if ((__far_mode) & ($isdefed("_BIOSHWINEAR") = 0))
	FBD		_c_int00			; Branch to MainLine.
	.else
	BD		_c_int00			; Branch to MainLine.
	.endif
	STM		#0100h, SP			; initialize Stack Pointer

	.def NMI_V, SINT16_V
NMI_V:				; Non-maskable interrupt Vector
SINT16_V:			; Software Interrupt #16 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT17_V
SINT17_V:			; Software Interrupt #17 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT18_V
SINT18_V:			; Software Interrupt #18 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT19_V
SINT19_V:			; Software Interrupt #19 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT20_V
SINT20_V:			; Software Interrupt #20 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT21_V
SINT21_V:			; Software Interrupt #21 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT22_V
SINT22_V:			; Software Interrupt #22 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT23_V
SINT23_V:			; Software Interrupt #23 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT24_V
SINT24_V:			; Software Interrupt #24 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT25_V
SINT25_V:			; Software Interrupt #25 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT26_V
SINT26_V:			; Software Interrupt #26 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT27_V
SINT27_V:			; Software Interrupt #27 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT28_V
SINT28_V:			; Software Interrupt #28 Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT29_V,MTRAP_V
SINT29_V:			; Software Interrupt #29 Vector (reserved)
MTRAP_V:			; Message TRAP Vector
	B		_dummyISR
	NOP
	NOP

	.def SINT30_V,ATRAP_V
;;	.ref ATRAP_H
SINT30_V:			; Software Interrupt #30 Vector (reserved)
ATRAP_V:			; Analysis TRAP Vector
	.if ((__far_mode) & ($isdefed("_BIOSHWINEAR") = 0))
	; ATRAP ISR MUST be on same page as RTDX Monitor because 
	; this SWI trap can only NEAR return, so saving XPC on stack 
	; would only corrupt it as there is no FRET from the ATRAP 
	; handler which would pop the XPC off the stack.
	;PSHM	XPC					; do NOT save XPC
	FBD		ATRAP_V				; far branch anyway in case ISR mis-located
	.else
	BD		ATRAP_V 			; Delayed branch to handler
	.endif
	PSHM	ST0					; save Status before branch
	SSBX	CPL 				; switch to stack-based addressing

	.def INT0_V,SINT0_V
INT0_V:				; External User Interrupt #0 Vector
SINT0_V:			; Software Interrupt #0 Vector
	B		_dummyISR
	NOP
	NOP

	.def INT1_V,SINT1_V
INT1_V:				; External User Interrupt #1 Vector
SINT1_V:			; Software Interrupt #1 Vector
	B		_dummyISR
	NOP
	NOP

	.def INT2_V,SINT2_V
INT2_V:				; External User Interrupt #2 Vector
SINT2_V:			; Software Interrupt #2 Vector
	B		_dummyISR
	NOP
	NOP

	.def TINT_V,SINT3_V
;;	.ref _TimerISR
TINT_V:				; Internal Timer Interrupt Vector
SINT3_V:			; Software Interrupt #3 Vector
	; Note: do NOT set CPL bit here.
	; Instead, let C interrupt handler first save current ST0
	; and we'll set CPL inside function after save.  If we 
	; change CPL here it won't get restored properly.
	B		TINT_V
	NOP
	NOP

	.def RINT0_V,BRINT0_V,SINT4_V
RINT0_V:			; Serial Port 0 Receive Interrupt Vector
BRINT0_V:			; Buffered Serial Port 0 Receive Interrupt Vector
SINT4_V:			; Software Interrupt #4 Vector
	B		_dummyISR
	NOP
	NOP

;;	.ref _writeISR
	.def XINT0_V,BXINT0_V,SINT5_V
XINT0_V:			; Serial Port 0 Transmit Interrupt Vector
BXINT0_V:			; Buffered Serial Port Transmit Interrupt Vector
SINT5_V:			; Software Interrupt #5 Vector
	B		_dummyISR
	NOP
	NOP

	.def RINT1_V,TRINT_V,SINT6_V
RINT1_V:			; Serial Port 1 Receive Interrupt Vector
TRINT_V:			; TDM Serial Port Receive Interrupt
SINT6_V:			; Software Interrupt #6 Vector
	B		_dummyISR
	NOP
	NOP

	.def XINT1_V,TXINT_V,SINT7_V
XINT1_V:			; Serial Port 1 Transmit Interrupt Vector
TXINT_V:			; TDM Serial Port Transmit Interrupt
SINT7_V:			; Software Interrupt #7 Vector
	B		_dummyISR
	NOP
	NOP

	.def INT3_V,SINT8_V
INT3_V:				; External User Interrupt #3 Vector
SINT8_V:			; Software Interrupt #8 Vector
	B		_dummyISR    
	NOP
	NOP

	.def HPINT_V,SINT9_V
HPINT_V:			; HPI Interrupt Vector
SINT9_V:			; Software Interrupt #9 Vector
	B		_dummyISR
	NOP
	NOP

	.def BRINT1_V,SINT10_V
BRINT1_V:			; Buffered Serial Port 1 Receive Interrupt Vector
SINT10_V:			; Software Interrupt #10 Vector
	B		_dummyISR
	NOP
	NOP

	.def BXINT1_V,SINT11_V
BXINT1_V:			; Buffered Serial Port 1 Transmit Interrupt Vector
SINT11_V:			; Software Interrupt #11 Vector
	B		_dummyISR
	NOP
	NOP

	.def RESERVED_V
RESERVED_V:			; Reserved Interrupt Vectors
	B		_dummyISR
	NOP
	NOP
	
	.else
	
;**********************************************************************
;*		 (C) COPYRIGHT TEXAS INSTRUMENTS, INC. 1996 				  *
;*																	  *
;*		Interrupt Vector Assignments for 'C54x						  *
;* 
;* Note that not all interupt names will apply to any given target.
;* This serves only as a multi-purpose example across the C54x family.
;* Consult the TI DSP Reference manual to determine which interrupts 
;*   apply to a given target.
;**********************************************************************
	.title "Interrupt Vectors w/ RTDX for C54X"
	.tab	4
	.file	"vectors.asm"
	.mmregs

	.sect	".vectors"
	.def RS_V, SINTR_V
	.ref _c_int00
RS_V:				; Hardware Reset Vector
SINTR_V:			; Software Reset Vector
	; Note: no need to push XPC here - reset clears XPC
	.if ((__far_mode) & ($isdefed("_BIOSHWINEAR") = 0))
	FBD		_c_int00			; Branch to MainLine.
	.else
	BD		_c_int00			; Branch to MainLine.
	.endif
;	STM		#06f00h, SP			; initialize Stack Pointer
	STM		#0100h, SP			; initialize Stack Pointer

	.def NMI_V, SINT16_V
NMI_V:				; Non-maskable interrupt Vector
SINT16_V:			; Software Interrupt #16 Vector
	B		$
	NOP
	NOP

	.endif

	.end

