   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
   3                     ; Optimizer V4.2.4 - 18 Dec 2007
  35                     ; 14 @far @interrupt void NonHandledInterrupt (void)
  35                     ; 15 {
  36                     .text:	section	.text,new
  37  0000               f_NonHandledInterrupt:
  42                     ; 19 	return;
  45  0000 80            	iret	
  51                     .const:	section	.text
  52  0000               __vectab:
  53  0000 82            	dc.b	130
  55  0001 00            	dc.b	page(__stext)
  56  0002 0000          	dc.w	__stext
  57  0004 82            	dc.b	130
  58  0005 00            	dc.b	page(_UserISR_IRQ+4)
  59  0006 9004          	dc.w	_UserISR_IRQ+4
  60  0008 82            	dc.b	130
  61  0009 00            	dc.b	page(_UserISR_IRQ+8)
  62  000a 9008          	dc.w	_UserISR_IRQ+8
  63  000c 82            	dc.b	130
  64  000d 00            	dc.b	page(_UserISR_IRQ+12)
  65  000e 900c          	dc.w	_UserISR_IRQ+12
  66  0010 82            	dc.b	130
  67  0011 00            	dc.b	page(_UserISR_IRQ+16)
  68  0012 9010          	dc.w	_UserISR_IRQ+16
  69  0014 82            	dc.b	130
  70  0015 00            	dc.b	page(_UserISR_IRQ+20)
  71  0016 9014          	dc.w	_UserISR_IRQ+20
  72  0018 82            	dc.b	130
  73  0019 00            	dc.b	page(_UserISR_IRQ+24)
  74  001a 9018          	dc.w	_UserISR_IRQ+24
  75  001c 82            	dc.b	130
  76  001d 00            	dc.b	page(_UserISR_IRQ+28)
  77  001e 901c          	dc.w	_UserISR_IRQ+28
  78  0020 82            	dc.b	130
  79  0021 00            	dc.b	page(_UserISR_IRQ+32)
  80  0022 9020          	dc.w	_UserISR_IRQ+32
  81  0024 82            	dc.b	130
  82  0025 00            	dc.b	page(_UserISR_IRQ+36)
  83  0026 9024          	dc.w	_UserISR_IRQ+36
  84  0028 82            	dc.b	130
  85  0029 00            	dc.b	page(_UserISR_IRQ+40)
  86  002a 9028          	dc.w	_UserISR_IRQ+40
  87  002c 82            	dc.b	130
  88  002d 00            	dc.b	page(_UserISR_IRQ+44)
  89  002e 902c          	dc.w	_UserISR_IRQ+44
  90  0030 82            	dc.b	130
  91  0031 00            	dc.b	page(_UserISR_IRQ+48)
  92  0032 9030          	dc.w	_UserISR_IRQ+48
  93  0034 82            	dc.b	130
  94  0035 00            	dc.b	page(_UserISR_IRQ+52)
  95  0036 9034          	dc.w	_UserISR_IRQ+52
  96  0038 82            	dc.b	130
  97  0039 00            	dc.b	page(_UserISR_IRQ+56)
  98  003a 9038          	dc.w	_UserISR_IRQ+56
  99  003c 82            	dc.b	130
 100  003d 00            	dc.b	page(_UserISR_IRQ+60)
 101  003e 903c          	dc.w	_UserISR_IRQ+60
 102  0040 82            	dc.b	130
 103  0041 00            	dc.b	page(_UserISR_IRQ+64)
 104  0042 9040          	dc.w	_UserISR_IRQ+64
 105  0044 82            	dc.b	130
 106  0045 00            	dc.b	page(_UserISR_IRQ+68)
 107  0046 9044          	dc.w	_UserISR_IRQ+68
 108  0048 82            	dc.b	130
 109  0049 00            	dc.b	page(_UserISR_IRQ+72)
 110  004a 9048          	dc.w	_UserISR_IRQ+72
 111  004c 82            	dc.b	130
 112  004d 00            	dc.b	page(_UserISR_IRQ+76)
 113  004e 904c          	dc.w	_UserISR_IRQ+76
 114  0050 82            	dc.b	130
 115  0051 00            	dc.b	page(_UserISR_IRQ+80)
 116  0052 9050          	dc.w	_UserISR_IRQ+80
 117  0054 82            	dc.b	130
 118  0055 00            	dc.b	page(_UserISR_IRQ+84)
 119  0056 9054          	dc.w	_UserISR_IRQ+84
 120  0058 82            	dc.b	130
 121  0059 00            	dc.b	page(_UserISR_IRQ+88)
 122  005a 9058          	dc.w	_UserISR_IRQ+88
 123  005c 82            	dc.b	130
 124  005d 00            	dc.b	page(_UserISR_IRQ+92)
 125  005e 905c          	dc.w	_UserISR_IRQ+92
 126  0060 82            	dc.b	130
 127  0061 00            	dc.b	page(_UserISR_IRQ+96)
 128  0062 9060          	dc.w	_UserISR_IRQ+96
 129  0064 82            	dc.b	130
 130  0065 00            	dc.b	page(_UserISR_IRQ+100)
 131  0066 9064          	dc.w	_UserISR_IRQ+100
 132  0068 82            	dc.b	130
 133  0069 00            	dc.b	page(_UserISR_IRQ+104)
 134  006a 9068          	dc.w	_UserISR_IRQ+104
 135  006c 82            	dc.b	130
 136  006d 00            	dc.b	page(_UserISR_IRQ+108)
 137  006e 906c          	dc.w	_UserISR_IRQ+108
 138  0070 82            	dc.b	130
 139  0071 00            	dc.b	page(_UserISR_IRQ+112)
 140  0072 9070          	dc.w	_UserISR_IRQ+112
 141  0074 82            	dc.b	130
 142  0075 00            	dc.b	page(_UserISR_IRQ+116)
 143  0076 9074          	dc.w	_UserISR_IRQ+116
 144  0078 82            	dc.b	130
 145  0079 00            	dc.b	page(_UserISR_IRQ+120)
 146  007a 9078          	dc.w	_UserISR_IRQ+120
 147  007c 82            	dc.b	130
 148  007d 00            	dc.b	page(_UserISR_IRQ+124)
 149  007e 907c          	dc.w	_UserISR_IRQ+124
 212                     	xdef	__vectab
 213                     	xref	__stext
 214                     	xdef	f_NonHandledInterrupt
 233                     	end
