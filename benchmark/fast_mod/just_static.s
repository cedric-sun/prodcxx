	.file	"just_static.cc"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"     run: "
.LC2:
	.string	"       %: "
.LC3:
	.string	" "
.LC5:
	.string	"s"
.LC6:
	.string	"     mod: "
.LC7:
	.string	"fast_mod: "
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1892:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$1000000000, %r15d
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	leaq	_ZSt4cout(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	23(%rsp), %r12
.L10:
	movl	$10, %edx
	leaq	.LC1(%rip), %rsi
	movq	%rbp, %rdi
	xorl	%ebx, %ebx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	movq	%r12, %rsi
	movb	$10, 23(%rsp)
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	xorl	%ecx, %ecx
	movq	%rax, %r8
	.p2align 4,,10
	.p2align 3
.L2:
	movl	%r15d, %esi
	movl	%ecx, %eax
	xorl	%edx, %edx
	subl	%ecx, %esi
	addl	$1, %ecx
	divl	%esi
	addl	%edx, %ebx
	cmpl	$1000000000, %ecx
	jne	.L2
	movq	%r8, 8(%rsp)
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	movl	$10, %edx
	leaq	.LC2(%rip), %rsi
	movq	%rbp, %rdi
	movq	%rax, (%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	%ebx, %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r14
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	(%rsp), %rcx
	movq	8(%rsp), %r8
	pxor	%xmm0, %xmm0
	cmpq	%rcx, %r8
	jge	.L3
	subq	%r8, %rcx
	pxor	%xmm0, %xmm0
	movabsq	$2361183241434822607, %rax
	shrq	$3, %rcx
	mulq	%rcx
	shrq	$4, %rdx
	cvtsi2sdq	%rdx, %xmm0
	divsd	.LC4(%rip), %xmm0
.L3:
	movq	%r14, %rdi
	xorl	%ebx, %ebx
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC5(%rip), %rsi
	movq	%rax, %r14
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r14, %rdi
	movl	$1, %edx
	movq	%r12, %rsi
	movb	$10, 23(%rsp)
	xorl	%r14d, %r14d
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	movq	%rax, %r9
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%ebx, %eax
	movl	%r15d, %ecx
	subl	%ebx, %ecx
	cltd
	addl	$1, %ebx
	idivl	%ecx
	addl	%edx, %r14d
	cmpl	$1000000000, %ebx
	jne	.L4
	movq	%r9, 8(%rsp)
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	movl	$10, %edx
	leaq	.LC6(%rip), %rsi
	movq	%rbp, %rdi
	movq	%rax, (%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %r14
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	(%rsp), %rcx
	movq	8(%rsp), %r9
	pxor	%xmm0, %xmm0
	cmpq	%r9, %rcx
	jle	.L5
	subq	%r9, %rcx
	pxor	%xmm0, %xmm0
	movabsq	$2361183241434822607, %rax
	shrq	$3, %rcx
	mulq	%rcx
	shrq	$4, %rdx
	cvtsi2sdq	%rdx, %xmm0
	divsd	.LC4(%rip), %xmm0
.L5:
	movq	%r14, %rdi
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC5(%rip), %rsi
	movq	%rax, %r14
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$1, %edx
	movq	%r14, %rdi
	movq	%r12, %rsi
	movb	$10, 23(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	xorl	%edx, %edx
	movq	%rax, %r14
	.p2align 4,,10
	.p2align 3
.L6:
	addl	%edx, %r8d
	addl	$1, %ecx
	subl	$1, %ebx
	je	.L20
.L8:
	movl	%ecx, %edx
	cmpl	%ecx, %ebx
	jg	.L6
	movl	%ecx, %eax
	addl	$1, %ecx
	cltd
	idivl	%ebx
	addl	%edx, %r8d
	subl	$1, %ebx
	jne	.L8
.L20:
	movl	%r8d, (%rsp)
	call	_ZNSt6chrono3_V212steady_clock3nowEv@PLT
	movl	$10, %edx
	leaq	.LC7(%rip), %rsi
	movq	%rbp, %rdi
	movq	%rax, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	(%rsp), %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, (%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	%rbx, %r14
	movq	(%rsp), %rdi
	pxor	%xmm0, %xmm0
	jge	.L9
	subq	%r14, %rbx
	pxor	%xmm0, %xmm0
	movabsq	$2361183241434822607, %rax
	shrq	$3, %rbx
	mulq	%rbx
	shrq	$4, %rdx
	cvtsi2sdq	%rdx, %xmm0
	divsd	.LC4(%rip), %xmm0
.L9:
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC5(%rip), %rsi
	addq	$1, %r13
	movq	%rax, %rbx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$1, %edx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	movb	$10, 23(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	$4, %r13
	jne	.L10
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L21
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L21:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1892:
	.size	main, .-main
	.p2align 4
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2428:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE2428:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC4:
	.long	0
	.long	1093567616
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
