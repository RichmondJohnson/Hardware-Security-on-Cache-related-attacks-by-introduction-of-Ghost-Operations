	.text
	.file	"InputFiles/_TP4_circles/./circles.ll"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$0, -4(%ebp)
	movl	$.L.str, (%esp)
	calll	printf
	leal	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.L.str.1, (%esp)
	calll	__isoc99_scanf
	movss	-16(%ebp), %xmm0        # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, (%esp)
	calll	cir
	fstps	-8(%ebp)
	movss	-16(%ebp), %xmm0        # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, (%esp)
	calll	area
	fstps	-12(%ebp)
	movss	-8(%ebp), %xmm0         # xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, 4(%esp)
	movl	$.L.str.2, (%esp)
	calll	printf
	movss	-12(%ebp), %xmm0        # xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, 4(%esp)
	movl	$.L.str.3, (%esp)
	calll	printf
	cvttss2si	-12(%ebp), %eax
	addl	$40, %esp
	popl	%ebp
	retl
.Lfunc_end0:
	.size	main, .Lfunc_end0-main

	.section	.rodata.cst8,"aM",@progbits,8
	.align	8
.LCPI1_0:
	.quad	4618756669842359583     # double 6.2800000000000002
	.text
	.globl	cir
	.align	16, 0x90
	.type	cir,@function
cir:                                    # @cir
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movss	8(%ebp), %xmm0          # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -4(%ebp)
	movss	-4(%ebp), %xmm0         # xmm0 = mem[0],zero,zero,zero
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LCPI1_0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%ebp)
	flds	-8(%ebp)
	addl	$8, %esp
	popl	%ebp
	retl
.Lfunc_end1:
	.size	cir, .Lfunc_end1-cir

	.section	.rodata.cst8,"aM",@progbits,8
	.align	8
.LCPI2_0:
	.quad	4623260269469730079     # double 12.56
	.text
	.globl	area
	.align	16, 0x90
	.type	area,@function
area:                                   # @area
# BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movss	8(%ebp), %xmm0          # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -4(%ebp)
	movss	%xmm0, (%esp)
	calll	cir
	fstps	-16(%ebp)
	movss	-16(%ebp), %xmm0        # xmm0 = mem[0],zero,zero,zero
	movss	%xmm0, -12(%ebp)
	mulss	%xmm0, %xmm0
	cvtss2sd	%xmm0, %xmm0
	divsd	.LCPI2_0, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -8(%ebp)
	flds	-8(%ebp)
	addl	$24, %esp
	popl	%ebp
	retl
.Lfunc_end2:
	.size	area, .Lfunc_end2-area

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Enter r : "
	.size	.L.str, 11

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%f"
	.size	.L.str.1, 3

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"Circumference is : %f\n"
	.size	.L.str.2, 23

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"Area is : %f\n"
	.size	.L.str.3, 14


	.ident	"clang version 3.8.1 (tags/RELEASE_381/final)"
	.section	".note.GNU-stack","",@progbits
