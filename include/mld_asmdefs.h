#ifndef MLD_INCLUDE_ASMDEFS_H
#define MLD_INCLUDE_ASMDEFS_H

#define ENTRY_ALIGN(name, alignment)	\
	.global	name;			\
	.type name, %function;		\
	.align	alignment;		\
	name:

#define ENTRY(name)	ENTRY_ALIGN(name, 6)

#define END(name) \
	.size	name, (. - name)

#define L(l) .L ## l

#endif // MLD_INCLUDE_ASMDEFS_H
