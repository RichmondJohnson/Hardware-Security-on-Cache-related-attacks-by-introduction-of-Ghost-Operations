	.text
	.file	"InputFiles/_TP5_access/./access.ll"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$36, %esp
	movl	$0, -8(%ebp)

	movl	$4252, -28(%ebp)
	movl	$9721, -16(%ebp)        # imm = 0x25F9

	movl	$2455, -32(%ebp)
	movl	$0, -20(%ebp)

	movl	$8237, -36(%ebp)
	movl	$5, -24(%ebp)

	movl	$676, -40(%ebp)
	leal	-12(%ebp), %esi
	.align	16, 0x90
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movl	$.L.str, (%esp)
	calll	printf
	movl	%esi, 4(%esp)
	movl	$.L.str.1, (%esp)
	calll	__isoc99_scanf
	movl	-12(%ebp), %eax
	cmpl	-16(%ebp), %eax
	je	.LBB0_4
# BB#2:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	$.L.str.2, (%esp)
	calll	printf
	movl	-20(%ebp), %eax
	incl	%eax
	movl	%eax, -20(%ebp)
	cmpl	-24(%ebp), %eax
	jne	.LBB0_1
# BB#3:
	movl	$.L.str.3, (%esp)
	calll	printf
	movl	$-1, -8(%ebp)

	movl	$2563, -44(%ebp)
	jmp	.LBB0_5
.LBB0_4:
	movl	$.L.str.4, (%esp)
	calll	printf
	movl	$0, -8(%ebp)

	movl	$1591, -48(%ebp)
.LBB0_5:
	movl	-8(%ebp), %eax
	addl	$36, %esp
	popl	%esi
	popl	%ebp
	retl
.Lfunc_end0:
	.size	main, .Lfunc_end0-main

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Enter passkey : "
	.size	.L.str, 17

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%d"
	.size	.L.str.1, 3

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"Access Denied\n"
	.size	.L.str.2, 15

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"Disabled Access\nExiting\n"
	.size	.L.str.3, 25

	.type	.L.str.4,@object        # @.str.4
.L.str.4:
	.asciz	"Access Granted\n"
	.size	.L.str.4, 16


	.ident	"clang version 3.8.1 (tags/RELEASE_381/final)"
	.section	".note.GNU-stack","",@progbits
