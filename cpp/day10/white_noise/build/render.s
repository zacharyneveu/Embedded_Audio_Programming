	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.cpu	cortex-a8
	.eabi_attribute	6, 10	@ Tag_CPU_arch
	.eabi_attribute	7, 65	@ Tag_CPU_arch_profile
	.eabi_attribute	8, 1	@ Tag_ARM_ISA_use
	.eabi_attribute	9, 2	@ Tag_THUMB_ISA_use
	.fpu	neon
	.eabi_attribute	17, 1	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 2	@ Tag_ABI_FP_denormal
	.eabi_attribute	23, 1	@ Tag_ABI_FP_number_model
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	28, 1	@ Tag_ABI_VFP_args
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	18, 4	@ Tag_ABI_PCS_wchar_t
	.eabi_attribute	26, 2	@ Tag_ABI_enum_size
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.eabi_attribute	68, 1	@ Tag_Virtualization_use
	.file	"/root/Bela/projects/white_noise/build/render.bc"
	.globl	setup
	.p2align	2
	.type	setup,%function
setup:                                  @ @setup
	.fnstart
@ BB#0:
	.save	{r11, lr}
	push	{r11, lr}
	.setfp	r11, sp
	mov	r11, sp
	vldr	s0, [r0, #32]
	movw	r0, :lower16:scope
	movt	r0, :upper16:scope
	mov	r1, #1
	bl	_ZN5Scope5setupEjf
	mov	r0, #1
	pop	{r11, pc}
.Lfunc_end0:
	.size	setup, .Lfunc_end0-setup
	.fnend

	.globl	render
	.p2align	2
	.type	render,%function
render:                                 @ @render
	.fnstart
@ BB#0:
	.save	{r4, r5, r6, r7, r11, lr}
	push	{r4, r5, r6, r7, r11, lr}
	.setfp	r11, sp, #16
	add	r11, sp, #16
	.vsave	{d8, d9, d10}
	vpush	{d8, d9, d10}
	mov	r4, r0
	ldr	r0, [r4, #20]
	cmp	r0, #0
	beq	.LBB1_3
@ BB#1:                                 @ %.lr.ph
	vmov.f32	d9, #-1.000000e+00
	movw	r5, :lower16:scope
	movw	r7, :lower16:amp
	vldr	s16, .LCPI1_0
	mov	r6, #0
	movt	r5, :upper16:scope
	movt	r7, :upper16:amp
.LBB1_2:                                @ =>This Inner Loop Header: Depth=1
	bl	rand
	vmov	s0, r0
	mov	r0, r5
	vcvt.f32.s32	d16, d0
	vmul.f32	d16, d16, d8
	vadd.f32	d10, d16, d9
	vcvt.f64.f32	d16, s20
	vmov	r2, r3, d16
	bl	_ZN5Scope3logEdz
	ldr	r1, [r4, #28]
	vldr	s0, [r7]
	ldr	r0, [r4, #4]
	mul	r1, r1, r6
	vmul.f32	d0, d10, d0
	add	r6, r6, #1
	add	r0, r0, r1, lsl #2
	vstr	s0, [r0]
	vldr	s0, [r7]
	vmul.f32	d0, d0, d10
	vstr	s0, [r0, #4]
	ldr	r0, [r4, #20]
	cmp	r6, r0
	blo	.LBB1_2
.LBB1_3:                                @ %._crit_edge
	vpop	{d8, d9, d10}
	pop	{r4, r5, r6, r7, r11, pc}
	.p2align	2
@ BB#4:
.LCPI1_0:
	.long	813694976               @ float 9.31322574E-10
.Lfunc_end1:
	.size	render, .Lfunc_end1-render
	.fnend

	.globl	cleanup
	.p2align	2
	.type	cleanup,%function
cleanup:                                @ @cleanup
	.fnstart
@ BB#0:
	bx	lr
.Lfunc_end2:
	.size	cleanup, .Lfunc_end2-cleanup
	.fnend

	.section	.text.startup,"ax",%progbits
	.p2align	2
	.type	_GLOBAL__sub_I_render.ii,%function
_GLOBAL__sub_I_render.ii:               @ @_GLOBAL__sub_I_render.ii
	.fnstart
@ BB#0:
	.save	{r4, r10, r11, lr}
	push	{r4, r10, r11, lr}
	.setfp	r11, sp, #8
	add	r11, sp, #8
	movw	r4, :lower16:scope
	movt	r4, :upper16:scope
	mov	r0, r4
	bl	_ZN5ScopeC1Ev
	movw	r0, :lower16:_ZN5ScopeD1Ev
	movw	r2, :lower16:__dso_handle
	movt	r0, :upper16:_ZN5ScopeD1Ev
	movt	r2, :upper16:__dso_handle
	mov	r1, r4
	pop	{r4, r10, r11, lr}
	b	__cxa_atexit
.Lfunc_end3:
	.size	_GLOBAL__sub_I_render.ii, .Lfunc_end3-_GLOBAL__sub_I_render.ii
	.fnend

	.type	amp,%object             @ @amp
	.data
	.globl	amp
	.p2align	2
amp:
	.long	1028443341              @ float 0.0500000007
	.size	amp, 4

	.type	scope,%object           @ @scope
	.bss
	.globl	scope
	.p2align	2
scope:
	.zero	212
	.size	scope, 212

	.section	.init_array,"aw",%init_array
	.p2align	2
	.long	_GLOBAL__sub_I_render.ii(target1)

	.ident	"clang version 3.9.1-9 (tags/RELEASE_391/rc2)"
	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 2	@ Tag_ABI_optimization_goals
