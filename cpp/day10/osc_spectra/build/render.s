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
	.file	"/root/Bela/projects/osc_spectra/build/render.bc"
	.globl	_Z12advancePhaseff
	.p2align	3
	.type	_Z12advancePhaseff,%function
_Z12advancePhaseff:                     @ @_Z12advancePhaseff
	.fnstart
@ BB#0:
	vcvt.f64.f32	d16, s1
	movw	r0, :lower16:.L_MergedGlobals
	movt	r0, :upper16:.L_MergedGlobals
	vldr	d17, .LCPI0_0
	vldr	s2, [r0, #24]
	vmul.f64	d16, d16, d17
	vcvt.f64.f32	d18, s2
	vmul.f64	d16, d16, d18
	vcvt.f64.f32	d18, s0
	vadd.f64	d16, d16, d18
	vcvt.f32.f64	s0, d16
	vcvt.f64.f32	d16, s0
	vcmpe.f64	d16, d17
	vmrs	APSR_nzcv, fpscr
	vldr	d18, .LCPI0_1
	vadd.f64	d18, d16, d18
	vcvt.f32.f64	s2, d18
	vmovgt.f32	s0, s2
	bx	lr
	.p2align	3
@ BB#1:
.LCPI0_0:
	.long	1413754136              @ double 6.2831853071795862
	.long	1075388923
.LCPI0_1:
	.long	1413754136              @ double -6.2831853071795862
	.long	3222872571
.Lfunc_end0:
	.size	_Z12advancePhaseff, .Lfunc_end0-_Z12advancePhaseff
	.fnend

	.globl	setup
	.p2align	2
	.type	setup,%function
setup:                                  @ @setup
	.fnstart
@ BB#0:
	vmov.f32	d1, #1.000000e+00
	vldr	s0, [r0, #32]
	movw	r0, :lower16:.L_MergedGlobals
	movt	r0, :upper16:.L_MergedGlobals
	vdiv.f32	s0, s2, s0
	vstr	s0, [r0, #24]
	mov	r0, #1
	bx	lr
.Lfunc_end1:
	.size	setup, .Lfunc_end1-setup
	.fnend

	.globl	render
	.p2align	3
	.type	render,%function
render:                                 @ @render
	.fnstart
@ BB#0:
	.save	{r4, r5, r6, r7, r8, r10, r11, lr}
	push	{r4, r5, r6, r7, r8, r10, r11, lr}
	.setfp	r11, sp, #24
	add	r11, sp, #24
	.vsave	{d8, d9, d10, d11, d12, d13, d14, d15}
	vpush	{d8, d9, d10, d11, d12, d13, d14, d15}
	ldr	r8, [r0, #20]
	cmp	r8, #0
	beq	.LBB2_3
@ BB#1:                                 @ %.lr.ph
	ldr	r1, [r0, #4]
	vmov.i32	d10, #0x0
	ldr	r0, [r0, #28]
	movw	r4, :lower16:.L_MergedGlobals
	add	r5, r1, #4
	vldr	d8, .LCPI2_0
	vldr	d9, .LCPI2_1
	mov	r7, #0
	vldr	d11, .LCPI2_2
	lsl	r6, r0, #2
	movt	r4, :upper16:.L_MergedGlobals
.LBB2_2:                                @ =>This Inner Loop Header: Depth=1
	vldr	s2, [r4]
	vmov.f32	d15, #1.000000e+00
	vldr	s4, [r4, #24]
	vcvt.f64.f32	d16, s2
	vmul.f64	d16, d16, d8
	vcvt.f64.f32	d17, s4
	vmul.f64	d16, d16, d17
	vldr	s0, [r4, #8]
	vldr	s24, [r4, #4]
	vcvt.f64.f32	d18, s0
	vadd.f64	d16, d16, d18
	vcvt.f32.f64	s2, d16
	vcvt.f64.f32	d16, s2
	vcmpe.f64	d16, d8
	vmrs	APSR_nzcv, fpscr
	vadd.f64	d18, d16, d9
	vcvt.f32.f64	s4, d18
	vmovgt.f32	s2, s4
	vstr	s2, [r4, #8]
	vldr	s2, [r4, #12]
	vldr	s4, [r4, #20]
	vcvt.f64.f32	d16, s2
	vmul.f64	d16, d16, d8
	vmul.f64	d16, d16, d17
	vcvt.f64.f32	d17, s4
	vcmpe.f64	d17, d11
	vadd.f64	d16, d16, d17
	vmrs	APSR_nzcv, fpscr
	vcvt.f32.f64	s28, d16
	vcvt.f64.f32	d16, s28
	vcmpe.f64	d16, d8
	vadd.f64	d18, d16, d9
	vmovgt.f32	s30, s20
	vmrs	APSR_nzcv, fpscr
	vcvt.f32.f64	s2, d18
	vldr	s26, [r4, #16]
	vmovgt.f32	s28, s2
	bl	sinf
                                        @ kill: %S0<def> %S0<kill> %D0<def>
	vmul.f32	d17, d15, d13
	add	r7, r7, #1
	vmul.f32	d16, d0, d12
	vstr	s28, [r4, #20]
	cmp	r7, r8
	vadd.f32	d0, d17, d16
	vstr	s0, [r5, #-4]
	vstr	s0, [r5]
	add	r5, r5, r6
	blo	.LBB2_2
.LBB2_3:                                @ %._crit_edge
	vpop	{d8, d9, d10, d11, d12, d13, d14, d15}
	pop	{r4, r5, r6, r7, r8, r10, r11, pc}
	.p2align	3
@ BB#4:
.LCPI2_0:
	.long	1413754136              @ double 6.2831853071795862
	.long	1075388923
.LCPI2_1:
	.long	1413754136              @ double -6.2831853071795862
	.long	3222872571
.LCPI2_2:
	.long	1413754136              @ double 3.1415926535897931
	.long	1074340347
.Lfunc_end2:
	.size	render, .Lfunc_end2-render
	.fnend

	.globl	cleanup
	.p2align	2
	.type	cleanup,%function
cleanup:                                @ @cleanup
	.fnstart
@ BB#0:
	bx	lr
.Lfunc_end3:
	.size	cleanup, .Lfunc_end3-cleanup
	.fnend

	.type	.L_MergedGlobals,%object @ @_MergedGlobals
	.data
	.p2align	4
.L_MergedGlobals:
	.long	1130102784              @ float 220
	.long	1045220557              @ float 0.200000003
	.long	0                       @ float 0
	.long	1111752704              @ float 49
	.long	1028443341              @ float 0.0500000007
	.long	0                       @ float 0
	.long	0                       @ float 0
	.size	.L_MergedGlobals, 28


	.globl	freq_sine
freq_sine = .L_MergedGlobals
	.size	freq_sine, 4
	.globl	amp_sine
amp_sine = .L_MergedGlobals+4
	.size	amp_sine, 4
	.globl	phase_sine
phase_sine = .L_MergedGlobals+8
	.size	phase_sine, 4
	.globl	freq_square
freq_square = .L_MergedGlobals+12
	.size	freq_square, 4
	.globl	amp_square
amp_square = .L_MergedGlobals+16
	.size	amp_square, 4
	.globl	phase_square
phase_square = .L_MergedGlobals+20
	.size	phase_square, 4
	.globl	invSrate
invSrate = .L_MergedGlobals+24
	.size	invSrate, 4
	.ident	"clang version 3.9.1-9 (tags/RELEASE_391/rc2)"
	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 2	@ Tag_ABI_optimization_goals
