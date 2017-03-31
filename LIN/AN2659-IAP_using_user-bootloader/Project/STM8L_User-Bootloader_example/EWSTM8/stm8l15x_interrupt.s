/**************************************************
 *
 * System initialization code for the STM8 IAR Compiler.
 *
 * Copyright 2010 IAR Systems AB.
 *
 * $Revision: 1413 $
 *
 ***************************************************
 *
 * To add your own interrupt handler to the table,
 * give it the label _interrupt_N, where N is the
 * offset from the RESET vector.  Your label will
 * override the corresponding weak label declaration
 * on the unhandled_exception function.
 *
 **************************************************/

        MODULE   ?interrupt

        SECTION __DEFAULT_CODE_SECTION__:CODE

declare_label MACRO
        PUBWEAK _interrupt_\1
_interrupt_\1:
        ENDM

unhandled_exception:

        declare_label 1
        declare_label 2
        declare_label 3
        declare_label 4
        declare_label 5
        declare_label 6
        declare_label 7
        declare_label 8
        declare_label 9
        declare_label 10
        declare_label 11
        declare_label 12
        declare_label 13
        declare_label 14
        declare_label 15
        declare_label 16
        declare_label 17
        declare_label 18
        declare_label 19
        declare_label 20
        declare_label 21
        declare_label 22
        declare_label 23
        declare_label 24
        declare_label 25
        declare_label 26
        declare_label 27
        declare_label 28
        declare_label 29
        declare_label 30
        declare_label 31

        NOP                                   ;; put a breakpoint here
        JRA    unhandled_exception


/*
 * The interrupt vector table.
 */


        SECTION `.intvec`:CONST

define_vector MACRO
        DC8     0x82
        DC24    _interrupt_\1
        ENDM

        PUBLIC  __intvec
        EXTERN   __iar_program_start
        


__intvec:
        DC8     0x82
        DC24    __iar_program_start          ;; RESET    0x8000
        DC8     0x82
        DC24    0x9004
        DC8     0x82
        DC24    0x9008
        DC8     0x82
        DC24    0x900C
        DC8     0x82
        DC24    0x9010
        DC8     0x82
        DC24    0x9014
        DC8     0x82
        DC24    0x9018
        DC8     0x82
        DC24    0x901C
        DC8     0x82
        DC24    0x9020
        DC8     0x82
        DC24    0x9024
        DC8     0x82
        DC24    0x9028
        DC8     0x82
        DC24    0x902C
        DC8     0x82
        DC24    0x9030
        DC8     0x82
        DC24    0x9034
        DC8     0x82
        DC24    0x9038
        DC8     0x82
        DC24    0x903C
        DC8     0x82
        DC24    0x9040
        DC8     0x82
        DC24    0x9044
        DC8     0x82
        DC24    0x9048
        DC8     0x82
        DC24    0x904C
        DC8     0x82
        DC24    0x9050
        DC8     0x82
        DC24    0x9054
        DC8     0x82
        DC24    0x9058
        DC8     0x82
        DC24    0x905C
        DC8     0x82
        DC24    0x9060
        DC8     0x82
        DC24    0x9064
        DC8     0x82
        DC24    0x9068
        DC8     0x82
        DC24    0x906C
        DC8     0x82
        DC24    0x9070
        DC8     0x82
        DC24    0x9074
        DC8     0x82
        DC24    0x9078
        DC8     0x82
        DC24    0x907C

        END
