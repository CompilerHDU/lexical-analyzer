# SysY compiler.
	.text
	.data
	.align	4
	.globl	n
	.type	n, @object
	.size	n, 4
n:
	.long	0
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%c"
	.text
	.globl	Merge
	.type	Merge, @function
Merge:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$112, %esp
	movl	16(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -12(%ebp)
	movl	20(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	movl	%eax, -16(%ebp)
	movl	$0, %eax
	movl	%eax, -100(%ebp)
	movl	$0, %eax
	movl	%eax, -104(%ebp)
.L0:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L1
	jmp		.L2
.L1:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	8(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-100(%ebp), %eax
	popl	%ebx
	movl	%ebx, -20(%ebp,%eax,4)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L0
.L2:
.L3:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L4
	jmp		.L5
.L4:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	8(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-104(%ebp), %eax
	popl	%ebx
	movl	%ebx, -60(%ebp,%eax,4)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
	jmp		.L3
.L5:
	movl	$0, %eax
	movl	%eax, -100(%ebp)
	movl	$0, %eax
	movl	%eax, -104(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -108(%ebp)
.L6:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setne	%al
	jne		.L9
	jmp		.L8
	pushl	%eax
.L9:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setne	%al
	jne		.L7
	jmp		.L8
	popl	%ebx
	andl	%eax, %ebx
	setne	%al
.L7:
.L10:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L11
	jmp		.L12
.L11:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L13
.L12:
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
.L13:
	jmp		.L6
.L8:
.L14:
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L15
	jmp		.L16
.L15:
	movl	-100(%ebp), %eax
	movl	-20(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-100(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -100(%ebp)
	jmp		.L14
.L16:
.L17:
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L18
	jmp		.L19
.L18:
	movl	-104(%ebp), %eax
	movl	-60(%ebp,%eax,4), %eax
	pushl	%eax
	movl	-108(%ebp), %eax
	popl	%ebx
	movl	%ebx, 8(%ebp,%eax,4)
	movl	-108(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -108(%ebp)
	movl	-104(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -104(%ebp)
	jmp		.L17
.L19:
	movl	$0, %eax
	jmp		.LRET_Merge
.LRET_Merge:
	addl	$112, %esp
	popl	%ebp
	ret
	.globl	MergeSort
	.type	MergeSort, @function
MergeSort:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
.L20:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L21
	jmp		.L22
.L21:
	movl	12(%ebp), %eax
	pushl	%eax
	movl	16(%ebp), %eax
	popl	%ebx
	addl	%ebx, %eax
	pushl	%eax
	movl	$2, %eax
	movl	%eax, %ebx
	popl	%eax
	cltd
	idivl	%ebx
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -16(%ebp)
	movl	16(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	pushl	%eax
	movl	8(%ebp), %eax
	pushl	%eax
	call	Merge
	addl	$16, %esp
	movl	%eax, -16(%ebp)
.L22:
	movl	$0, %eax
	jmp		.LRET_MergeSort
.LRET_MergeSort:
	addl	$20, %esp
	popl	%ebp
	ret
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$60, %esp
	movl	$10, %eax
	movl	%eax, n
	movl	$4, %eax
	pushl	%eax
	movl	$0, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$3, %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$9, %eax
	pushl	%eax
	movl	$2, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$2, %eax
	pushl	%eax
	movl	$3, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$0, %eax
	pushl	%eax
	movl	$4, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$1, %eax
	pushl	%eax
	movl	$5, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$6, %eax
	pushl	%eax
	movl	$6, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$5, %eax
	pushl	%eax
	movl	$7, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$7, %eax
	pushl	%eax
	movl	$8, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$8, %eax
	pushl	%eax
	movl	$9, %eax
	popl	%ebx
	movl	%ebx, -12(%ebp,%eax,4)
	movl	$0, %eax
	movl	%eax, -52(%ebp)
	movl	n, %eax
	pushl	%eax
	movl	$1, %eax
	movl	%eax, %ebx
	popl	%eax
	subl	%ebx, %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	-12(%ebp), %eax
	pushl	%eax
	call	MergeSort
	addl	$12, %esp
	movl	%eax, -52(%ebp)
.L23:
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	n, %eax
	popl	%ebx
	cmpl	%eax, %ebx
	setl	%al
	jl		.L24
	jmp		.L25
.L24:
	movl	-52(%ebp), %eax
	movl	-12(%ebp,%eax,4), %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	$.LC0, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	movl	$10, %eax
	movl	%eax, -56(%ebp)
	movl	-56(%ebp), %eax
	pushl	%eax
	movl	$.LC1, %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	movl	-52(%ebp), %eax
	pushl	%eax
	movl	$1, %eax
	popl	%ebx
	addl	%ebx, %eax
	movl	%eax, -52(%ebp)
	jmp		.L23
.L25:
	movl	$0, %eax
	jmp		.LRET_main
.LRET_main:
	addl	$60, %esp
	popl	%ebp
	ret
