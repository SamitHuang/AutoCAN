   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Generator V4.2.4 - 19 Dec 2007
   3                     ; Optimizer V4.2.4 - 18 Dec 2007
   5                     .const:	section	.text
   6  0000               _MainUserApplication:
   7  0000 9000          	dc.w	-28672
   8                     	bsct
   9  0000               _RoutinesInRAM:
  10  0000 00            	dc.b	0
  53                     ; 80 void main(void){
  55                     .text:	section	.text,new
  56  0000               _main:
  60                     ; 81   sim();               // disable interrupts 
  63  0000 9b            	sim	
  65                     ; 83   RoutinesInRAM = 0;
  68  0001 3f00          	clr	_RoutinesInRAM
  69                     ; 86   GPIOD->DDR &= ~0x04; 	  // PD2 as Input 
  71  0003 72155011      	bres	20497,#2
  72                     ; 87 	GPIOD->CR1 |= 0x04; 		// PD2 as Pull Up
  74  0007 72145012      	bset	20498,#2
  75                     ; 88 	GPIOD->CR2 &= ~0x04;	  // no external interrupt
  77  000b 72155013      	bres	20499,#2
  78                     ; 91 	if( (GPIOD->IDR & 0x04) == 0x04 ) 
  80  000f 7205501025    	btjf	20496,#2,L12
  81                     ; 94     if((*((u8 FAR*)MainUserApplication)==0x82) || (*((u8 FAR*)MainUserApplication)==0xAC))
  83  0014 bc009000      	ldf	a,36864
  84  0018 a182          	cp	a,#130
  85  001a 2704          	jreq	L52
  87  001c a1ac          	cp	a,#172
  88  001e 2619          	jrne	L12
  89  0020               L52:
  90                     ; 97 			GPIOD->ODR=0x00;
  92  0020 725f500f      	clr	20495
  93                     ; 98 			GPIOD->DDR=0x00;
  95  0024 725f5011      	clr	20497
  96                     ; 99 			GPIOD->CR1=0x00;
  98  0028 725f5012      	clr	20498
  99                     ; 100 			GPIOD->CR2=0x00;			
 101  002c 725f5013      	clr	20499
 102                     ; 103  _asm("LDW X,  SP ");
 105  0030 96            	ldw	X,SP
 107                     ; 104  _asm("LD  A,  $FF");
 110  0031 b6ff          	ld	A,$FF
 112                     ; 105  _asm("LD  XL, A  ");
 115  0033 97            	ld	XL,A
 117                     ; 106  _asm("LDW SP, X  ");
 120  0034 94            	ldw	SP,X
 122                     ; 107  _asm("JPF $9000");
 125  0035 ac009000      	jpf	$9000
 127  0039               L12:
 128                     ; 129 	GPIOD->ODR=0x00;
 130  0039 725f500f      	clr	20495
 131                     ; 130 	GPIOD->DDR=0x00;
 133  003d 725f5011      	clr	20497
 134                     ; 131 	GPIOD->CR1=0x00;
 136  0041 725f5012      	clr	20498
 137                     ; 132 	GPIOD->CR2=0x00;
 139  0045 725f5013      	clr	20499
 140                     ; 135   CLK->CKDIVR = 0x00;
 142  0049 725f50c6      	clr	20678
 143                     ; 138   protocol_init();
 145  004d cd0000        	call	_protocol_init
 147                     ; 141   if(!Master_ident(IDENT))  
 149  0050 a67f          	ld	a,#127
 150  0052 cd0000        	call	_Master_ident
 152  0055 4d            	tnz	a
 153  0056 2611          	jrne	L72
 154                     ; 143 		Transmit(NACK);
 156  0058 a61f          	ld	a,#31
 157  005a cd0000        	call	_Transmit
 159                     ; 145     DeInitBootloader();     // then set back all microcontroller changes to reset values
 161  005d cd0000        	call	_DeInitBootloader
 163                     ; 148  _asm("LDW X,  SP ");
 166  0060 96            	ldw	X,SP
 168                     ; 149  _asm("LD  A,  $FF");
 171  0061 b6ff          	ld	A,$FF
 173                     ; 150  _asm("LD  XL, A  ");
 176  0063 97            	ld	XL,A
 178                     ; 151  _asm("LDW SP, X  ");
 181  0064 94            	ldw	SP,X
 183                     ; 152  _asm("JPF $9000");
 186  0065 ac009000      	jpf	$9000
 188  0069               L72:
 189                     ; 171   _fctcpy('F');
 191  0069 a646          	ld	a,#70
 192  006b cd0000        	call	__fctcpy
 194                     ; 178   RoutinesInRAM = 1;
 196  006e 35010000      	mov	_RoutinesInRAM,#1
 197                     ; 179   unlock_PROG();
 199  0072 cd0000        	call	_unlock_PROG
 201                     ; 180 	unlock_DATA();
 203  0075 cd0000        	call	_unlock_DATA
 205                     ; 182   Transmit(ACK);
 207  0078 a679          	ld	a,#121
 208  007a cd0000        	call	_Transmit
 210  007d               L13:
 211                     ; 186     ProcessCommands();
 213  007d cd0000        	call	_ProcessCommands
 215                     ; 189     DeInitBootloader();
 217  0080 cd0000        	call	_DeInitBootloader
 219                     ; 192     GoAddress();
 221  0083 92cd84        	call	[_GoAddress.w]
 224  0086 20f5          	jra	L13
 284                     ; 197 void ProcessCommands(void){
 285                     .text:	section	.text,new
 286  0000               _ProcessCommands:
 288  0000 5203          	subw	sp,#3
 289       00000003      OFST:	set	3
 292  0002               L37:
 293                     ; 203 		wait = 8;
 295  0002 a608          	ld	a,#8
 296  0004 6b02          	ld	(OFST-1,sp),a
 297  0006               L101:
 298                     ; 205 			wait --;
 300  0006 0a02          	dec	(OFST-1,sp)
 301                     ; 204 		while(wait)
 303  0008 26fc          	jrne	L101
 304                     ; 207     ReceivedData = DataBuffer;
 306  000a ae0002        	ldw	x,#_DataBuffer
 307                     ; 210     if(!Receive(ReceivedData++))
 309  000d 5c            	incw	x
 310  000e bf00          	ldw	_ReceivedData,x
 311  0010 5a            	decw	x
 312  0011 cd0000        	call	_Receive
 314  0014 4d            	tnz	a
 315  0015 2738          	jreq	L57
 316                     ; 211       continue;
 318                     ; 214     if(!Receive(ReceivedData++))
 320  0017 be00          	ldw	x,_ReceivedData
 321  0019 5c            	incw	x
 322  001a bf00          	ldw	_ReceivedData,x
 323  001c 5a            	decw	x
 324  001d cd0000        	call	_Receive
 326  0020 4d            	tnz	a
 327  0021 272c          	jreq	L57
 328                     ; 215       continue;
 330                     ; 218     if(DataBuffer[N_COMMAND] != (u8)(~DataBuffer[N_NEG_COMMAND]))
 332  0023 b603          	ld	a,_DataBuffer+1
 333  0025 43            	cpl	a
 334  0026 b102          	cp	a,_DataBuffer
 335  0028 2707          	jreq	L311
 336                     ; 220       Transmit(NACK);
 338  002a a61f          	ld	a,#31
 339  002c cd0000        	call	_Transmit
 341                     ; 221       continue;
 343  002f 201e          	jra	L57
 344  0031               L311:
 345                     ; 225     Transmit(ACK);
 347  0031 a679          	ld	a,#121
 348  0033 cd0000        	call	_Transmit
 350                     ; 226 		cmd=DataBuffer[0];
 352  0036 b602          	ld	a,_DataBuffer
 353  0038 6b01          	ld	(OFST-2,sp),a
 354                     ; 227     switch(cmd)
 357                     ; 232       case (WM_Command): result = WM_Command_Process(); break;
 358  003a 270e          	jreq	L53
 359  003c a011          	sub	a,#17
 360  003e 271c          	jreq	L73
 361  0040 a010          	sub	a,#16
 362  0042 271d          	jreq	L14
 363  0044 a010          	sub	a,#16
 364  0046 271e          	jreq	L34
 365  0048 2005          	jra	L57
 366  004a               L53:
 367                     ; 229       case (GT_Command): result = GT_Command_Process(); break;
 369  004a cd0000        	call	_GT_Command_Process
 371  004d               LC001:
 372  004d 6b03          	ld	(OFST+0,sp),a
 374  004f               L57:
 375                     ; 234   }while( (!result) || (cmd != GO_Command) ); //until GO command received
 377  004f 7b03          	ld	a,(OFST+0,sp)
 378  0051 27af          	jreq	L37
 380  0053 7b01          	ld	a,(OFST-2,sp)
 381  0055 a121          	cp	a,#33
 382  0057 26a9          	jrne	L37
 383                     ; 235 }//ProcessCommands
 386  0059 5b03          	addw	sp,#3
 387  005b 81            	ret	
 388  005c               L73:
 389                     ; 230       case (RM_Command): result = RM_Command_Process(); break;
 391  005c cd0000        	call	_RM_Command_Process
 395  005f 20ec          	jp	LC001
 396  0061               L14:
 397                     ; 231       case (GO_Command): result = GO_Command_Process(); break;
 399  0061 cd0000        	call	_GO_Command_Process
 403  0064 20e7          	jp	LC001
 404  0066               L34:
 405                     ; 232       case (WM_Command): result = WM_Command_Process(); break;
 407  0066 cd0000        	call	_WM_Command_Process
 411  0069 20e2          	jp	LC001
 435                     ; 237 u8 GT_Command_Process(void){
 436                     .text:	section	.text,new
 437  0000               _GT_Command_Process:
 441                     ; 239   Transmit(Num_GT_Command);
 443  0000 a605          	ld	a,#5
 444  0002 cd0000        	call	_Transmit
 446                     ; 242   Transmit(Version_Number);
 448  0005 a610          	ld	a,#16
 449  0007 cd0000        	call	_Transmit
 451                     ; 245   Transmit(GT_Command);
 453  000a 4f            	clr	a
 454  000b cd0000        	call	_Transmit
 456                     ; 248   Transmit(RM_Command);
 458  000e a611          	ld	a,#17
 459  0010 cd0000        	call	_Transmit
 461                     ; 251   Transmit(GO_Command);
 463  0013 a621          	ld	a,#33
 464  0015 cd0000        	call	_Transmit
 466                     ; 254   Transmit(WM_Command);
 468  0018 a631          	ld	a,#49
 469  001a cd0000        	call	_Transmit
 471                     ; 257   Transmit(EM_Command);
 473  001d a643          	ld	a,#67
 474  001f cd0000        	call	_Transmit
 476                     ; 260   Transmit(ACK);
 478  0022 a679          	ld	a,#121
 479  0024 cd0000        	call	_Transmit
 481                     ; 262   return 1;
 483  0027 a601          	ld	a,#1
 486  0029 81            	ret	
 543                     ; 265 u8 RM_Command_Process(void){
 544                     .text:	section	.text,new
 545  0000               _RM_Command_Process:
 547  0000 5205          	subw	sp,#5
 548       00000005      OFST:	set	5
 551                     ; 270   if(!ReceiveAddress())
 553  0002 cd0000        	call	_ReceiveAddress
 555  0005 4d            	tnz	a
 556                     ; 272     Transmit(NACK);// if not valid - NACK
 558                     ; 273     return 0;
 560  0006 2718          	jreq	LC002
 561                     ; 277   DataAddress = *(u8 FAR**)(&DataBuffer[N_ADDR_3]);
 563  0008 b605          	ld	a,_DataBuffer+3
 564  000a 6b02          	ld	(OFST-3,sp),a
 565  000c b606          	ld	a,_DataBuffer+4
 566  000e 6b03          	ld	(OFST-2,sp),a
 567  0010 b607          	ld	a,_DataBuffer+5
 568  0012 6b04          	ld	(OFST-1,sp),a
 569                     ; 280   if(!ReceiveCount(0xFF, 1))
 571  0014 ae0001        	ldw	x,#1
 572  0017 a6ff          	ld	a,#255
 573  0019 95            	ld	xh,a
 574  001a cd0000        	call	_ReceiveCount
 576  001d 4d            	tnz	a
 577  001e 2609          	jrne	L161
 578                     ; 282     Transmit(NACK);// if not valid - NACK
 581                     ; 283     return 0;
 583  0020               LC002:
 585  0020 a61f          	ld	a,#31
 586  0022 cd0000        	call	_Transmit
 588  0025 4f            	clr	a
 590  0026               L411:
 592  0026 5b05          	addw	sp,#5
 593  0028 81            	ret	
 594  0029               L161:
 595                     ; 287   Checksum = 0;
 597  0029 0f01          	clr	(OFST-4,sp)
 598                     ; 288   for(i=0; i<=DataBuffer[N_DATACOUNT]; i++)
 600  002b 0f05          	clr	(OFST+0,sp)
 602  002d 2027          	jra	L761
 603  002f               L361:
 604                     ; 290     Checksum ^= DataAddress[i];
 606  002f 7b02          	ld	a,(OFST-3,sp)
 607  0031 b700          	ld	c_x,a
 608  0033 1e03          	ldw	x,(OFST-2,sp)
 609  0035 bf01          	ldw	c_x+1,x
 610  0037 7b05          	ld	a,(OFST+0,sp)
 611  0039 905f          	clrw	y
 612  003b 9097          	ld	yl,a
 613  003d 93            	ldw	x,y
 614  003e 92af0000      	ldf	a,([c_x.e],x)
 615  0042 1801          	xor	a,(OFST-4,sp)
 616  0044 6b01          	ld	(OFST-4,sp),a
 617                     ; 291     Transmit(DataAddress[i]);
 619  0046 7b05          	ld	a,(OFST+0,sp)
 620  0048 905f          	clrw	y
 621  004a 9097          	ld	yl,a
 622  004c 93            	ldw	x,y
 623  004d 92af0000      	ldf	a,([c_x.e],x)
 624  0051 cd0000        	call	_Transmit
 626                     ; 288   for(i=0; i<=DataBuffer[N_DATACOUNT]; i++)
 628  0054 0c05          	inc	(OFST+0,sp)
 629  0056               L761:
 632  0056 7b05          	ld	a,(OFST+0,sp)
 633  0058 b109          	cp	a,_DataBuffer+7
 634  005a 23d3          	jrule	L361
 635                     ; 293   return 1;
 637  005c a601          	ld	a,#1
 639  005e 20c6          	jra	L411
 686                     ; 296 u8 GO_Command_Process(void){
 687                     .text:	section	.text,new
 688  0000               _GO_Command_Process:
 690  0000 5206          	subw	sp,#6
 691       00000006      OFST:	set	6
 694                     ; 300   if(!ReceiveAddress())
 696  0002 cd0000        	call	_ReceiveAddress
 698  0005 4d            	tnz	a
 699  0006 2608          	jrne	L512
 700                     ; 302     Transmit(NACK);// if not valid - NACK
 702  0008 a61f          	ld	a,#31
 703  000a cd0000        	call	_Transmit
 705                     ; 303     return 0;
 707  000d 4f            	clr	a
 709  000e 200e          	jra	L421
 710  0010               L512:
 711                     ; 306   Address32 = *(u32*)(&DataBuffer[N_ADDR_3]);
 713  0010 be07          	ldw	x,_DataBuffer+5
 714  0012 1f03          	ldw	(OFST-3,sp),x
 715  0014 be05          	ldw	x,_DataBuffer+3
 716  0016 1f01          	ldw	(OFST-5,sp),x
 717                     ; 307 	Address16 = (u16)(Address32 >> 8);
 719  0018 1e02          	ldw	x,(OFST-4,sp)
 720                     ; 308   GoAddress = (TFunction)Address16;
 722  001a bf84          	ldw	_GoAddress,x
 723                     ; 309   return 1;
 725  001c a601          	ld	a,#1
 727  001e               L421:
 729  001e 5b06          	addw	sp,#6
 730  0020 81            	ret	
 816                     ; 312 u8 WM_Command_Process(void){
 817                     .text:	section	.text,new
 818  0000               _WM_Command_Process:
 820  0000 5209          	subw	sp,#9
 821       00000009      OFST:	set	9
 824                     ; 318   int ierror = 0;
 826  0002 5f            	clrw	x
 827  0003 1f07          	ldw	(OFST-2,sp),x
 828                     ; 321   if(!ReceiveAddress())
 830  0005 cd0000        	call	_ReceiveAddress
 832  0008 4d            	tnz	a
 833                     ; 323     Transmit(NACK);// if not valid - NACK
 835                     ; 324     return 0;
 837  0009 2716          	jreq	LC003
 838                     ; 328   DataAddress = *(u8 FAR**)(&DataBuffer[N_ADDR_3]);
 840  000b b605          	ld	a,_DataBuffer+3
 841  000d 6b01          	ld	(OFST-8,sp),a
 842  000f b606          	ld	a,_DataBuffer+4
 843  0011 6b02          	ld	(OFST-7,sp),a
 844  0013 b607          	ld	a,_DataBuffer+5
 845  0015 6b03          	ld	(OFST-6,sp),a
 846                     ; 331    if(!ReceiveCount(BLOCK_SIZE-1, 0))
 848  0017 5f            	clrw	x
 849  0018 a63f          	ld	a,#63
 850  001a 95            	ld	xh,a
 851  001b cd0000        	call	_ReceiveCount
 853  001e 4d            	tnz	a
 854  001f 2609          	jrne	L362
 855                     ; 333     Transmit(NACK);// if not valid - NACK
 858                     ; 334     return 0;
 860  0021               LC003:
 864  0021 a61f          	ld	a,#31
 865  0023 cd0000        	call	_Transmit
 869  0026 4f            	clr	a
 871  0027               L451:
 873  0027 5b09          	addw	sp,#9
 874  0029 81            	ret	
 875  002a               L362:
 876                     ; 338   DataCount = DataBuffer[N_DATACOUNT]; // init count
 878  002a b609          	ld	a,_DataBuffer+7
 879  002c 6b06          	ld	(OFST-3,sp),a
 880                     ; 339   Checksum = DataCount;                //init checksum
 882  002e 6b05          	ld	(OFST-4,sp),a
 883                     ; 340   for(i=0; i<=DataCount; i++)
 885  0030 0f09          	clr	(OFST+0,sp)
 887  0032 201b          	jra	L172
 888  0034               L562:
 889                     ; 342     if(!Receive(&DataBuffer[i]))
 891  0034 ab02          	add	a,#_DataBuffer
 892  0036 5f            	clrw	x
 893  0037 97            	ld	xl,a
 894  0038 cd0000        	call	_Receive
 896  003b 4d            	tnz	a
 897  003c 2605          	jrne	L572
 898                     ; 344       ierror = 1;
 900  003e ae0001        	ldw	x,#1
 901  0041 1f07          	ldw	(OFST-2,sp),x
 902  0043               L572:
 903                     ; 347     Checksum ^= DataBuffer[i];
 905  0043 7b09          	ld	a,(OFST+0,sp)
 906  0045 5f            	clrw	x
 907  0046 97            	ld	xl,a
 908  0047 7b05          	ld	a,(OFST-4,sp)
 909  0049 e802          	xor	a,(_DataBuffer,x)
 910  004b 6b05          	ld	(OFST-4,sp),a
 911                     ; 340   for(i=0; i<=DataCount; i++)
 913  004d 0c09          	inc	(OFST+0,sp)
 914  004f               L172:
 917  004f 7b09          	ld	a,(OFST+0,sp)
 918  0051 1106          	cp	a,(OFST-3,sp)
 919  0053 23df          	jrule	L562
 920                     ; 351   if(!Receive(&ChecksumByte))
 922  0055 96            	ldw	x,sp
 923  0056 1c0004        	addw	x,#OFST-5
 924  0059 cd0000        	call	_Receive
 926  005c 4d            	tnz	a
 927  005d 2605          	jrne	L772
 928                     ; 353 		ierror = 1;
 930  005f ae0001        	ldw	x,#1
 931  0062 1f07          	ldw	(OFST-2,sp),x
 932  0064               L772:
 933                     ; 356   if(ChecksumByte != Checksum)
 935  0064 7b04          	ld	a,(OFST-5,sp)
 936  0066 1105          	cp	a,(OFST-4,sp)
 937  0068 2705          	jreq	L103
 938                     ; 358     ierror = 1;
 940  006a ae0001        	ldw	x,#1
 941  006d 1f07          	ldw	(OFST-2,sp),x
 942  006f               L103:
 943                     ; 361   if (ierror == 1)
 945  006f 1e07          	ldw	x,(OFST-2,sp)
 946  0071 a30001        	cpw	x,#1
 947                     ; 363     Transmit(NACK); //send error
 949                     ; 364     return 0;    
 951  0074 27ab          	jreq	LC003
 952                     ; 368   if (!WriteBuffer(DataAddress, DataCount+1))
 954  0076 7b06          	ld	a,(OFST-3,sp)
 955  0078 4c            	inc	a
 956  0079 88            	push	a
 957  007a 7b02          	ld	a,(OFST-7,sp)
 958  007c b700          	ld	c_x,a
 959  007e 1e03          	ldw	x,(OFST-6,sp)
 960  0080 cd0000        	call	_WriteBuffer
 962  0083 5b01          	addw	sp,#1
 963  0085 4d            	tnz	a
 964                     ; 370     Transmit(NACK); //send error
 966                     ; 371     return 0;    
 968  0086 2799          	jreq	LC003
 969                     ; 374   Transmit(ACK);
 971  0088 a679          	ld	a,#121
 972  008a cd0000        	call	_Transmit
 974                     ; 375   return 1;
 976  008d a601          	ld	a,#1
 978  008f 2096          	jra	L451
1012                     	switch	.const
1013  0002               L061:
1014  0002 00008000      	dc.l	32768
1015  0006               L261:
1016  0006 00028000      	dc.l	163840
1017  000a               L461:
1018  000a 00004000      	dc.l	16384
1019  000e               L661:
1020  000e 00004400      	dc.l	17408
1021  0012               L071:
1022  0012 00000400      	dc.l	1024
1023  0016               L271:
1024  0016 00004800      	dc.l	18432
1025  001a               L471:
1026  001a 0000480b      	dc.l	18443
1027                     ; 378 u8 CheckAddress(u32 DataAddress){
1028                     .text:	section	.text,new
1029  0000               _CheckAddress:
1031       00000000      OFST:	set	0
1034                     ; 380   if ((DataAddress >= FLASH_START) && (DataAddress <= FLASH_END))
1036  0000 96            	ldw	x,sp
1037  0001 1c0003        	addw	x,#OFST+3
1038  0004 cd0000        	call	c_ltor
1040  0007 ae0002        	ldw	x,#L061
1041  000a cd0000        	call	c_lcmp
1043  000d 2512          	jrult	L523
1045  000f 96            	ldw	x,sp
1046  0010 1c0003        	addw	x,#OFST+3
1047  0013 cd0000        	call	c_ltor
1049  0016 ae0006        	ldw	x,#L261
1050  0019 cd0000        	call	c_lcmp
1052  001c 2403          	jruge	L523
1053                     ; 381     return 1;
1055  001e a601          	ld	a,#1
1058  0020 81            	ret	
1059  0021               L523:
1060                     ; 384     if ((DataAddress >= EEPROM_START) && (DataAddress <= EEPROM_END))
1062  0021 96            	ldw	x,sp
1063  0022 1c0003        	addw	x,#OFST+3
1064  0025 cd0000        	call	c_ltor
1066  0028 ae000a        	ldw	x,#L461
1067  002b cd0000        	call	c_lcmp
1069  002e 2512          	jrult	L133
1071  0030 96            	ldw	x,sp
1072  0031 1c0003        	addw	x,#OFST+3
1073  0034 cd0000        	call	c_ltor
1075  0037 ae000e        	ldw	x,#L661
1076  003a cd0000        	call	c_lcmp
1078  003d 2403          	jruge	L133
1079                     ; 385       return 1;
1081  003f a601          	ld	a,#1
1084  0041 81            	ret	
1085  0042               L133:
1086                     ; 388       if ((DataAddress >= RAM_START) && (DataAddress <= RAM_END))
1089  0042 96            	ldw	x,sp
1090  0043 1c0003        	addw	x,#OFST+3
1091  0046 cd0000        	call	c_ltor
1093  0049 ae0012        	ldw	x,#L071
1094  004c cd0000        	call	c_lcmp
1096  004f 2403          	jruge	L533
1097                     ; 389         return 1;
1099  0051 a601          	ld	a,#1
1102  0053 81            	ret	
1103  0054               L533:
1104                     ; 392         if ((DataAddress >= OPTION_START) && (DataAddress <= OPTION_END))
1106  0054 96            	ldw	x,sp
1107  0055 1c0003        	addw	x,#OFST+3
1108  0058 cd0000        	call	c_ltor
1110  005b ae0016        	ldw	x,#L271
1111  005e cd0000        	call	c_lcmp
1113  0061 2512          	jrult	L723
1115  0063 96            	ldw	x,sp
1116  0064 1c0003        	addw	x,#OFST+3
1117  0067 cd0000        	call	c_ltor
1119  006a ae001a        	ldw	x,#L471
1120  006d cd0000        	call	c_lcmp
1122  0070 2403          	jruge	L723
1123                     ; 393           return 1;
1125  0072 a601          	ld	a,#1
1128  0074 81            	ret	
1129  0075               L723:
1130                     ; 394   return 0;
1132  0075 4f            	clr	a
1135  0076 81            	ret	
1191                     ; 397 u8 WriteBuffer(u8 FAR* DataAddress, u8 DataCount){
1192                     .text:	section	.text,new
1193  0000               _WriteBuffer:
1195  0000 89            	pushw	x
1196  0001 3b0000        	push	c_x
1197  0004 88            	push	a
1198       00000001      OFST:	set	1
1201                     ; 401   if (((u32)DataAddress >= FLASH_START) && (((u32)DataAddress + DataCount - 1) <= FLASH_END))
1203  0005 3f00          	clr	c_lreg
1204  0007 450001        	mov	c_lreg+1,c_x
1205  000a bf02          	ldw	c_lreg+2,x
1206  000c ae0002        	ldw	x,#L061
1207  000f cd0000        	call	c_lcmp
1209  0012 2524          	jrult	L173
1211  0014 3f00          	clr	c_lreg
1212  0016 7b02          	ld	a,(OFST+1,sp)
1213  0018 b701          	ld	c_lreg+1,a
1214  001a 7b03          	ld	a,(OFST+2,sp)
1215  001c b702          	ld	c_lreg+2,a
1216  001e 7b04          	ld	a,(OFST+3,sp)
1217  0020 b703          	ld	c_lreg+3,a
1218  0022 7b07          	ld	a,(OFST+6,sp)
1219  0024 cd0000        	call	c_ladc
1221  0027 a601          	ld	a,#1
1222  0029 cd0000        	call	c_lsbc
1224  002c ae0006        	ldw	x,#L261
1225  002f cd0000        	call	c_lcmp
1227  0032 2404          	jruge	L173
1228                     ; 402     return WriteBufferFlash(DataAddress, DataCount, FLASH_MEMTYPE_PROG);
1230  0034 4b00          	push	#0
1233  0036 2038          	jp	LC004
1234  0038               L173:
1235                     ; 405   if (((u32)DataAddress >= EEPROM_START) && (((u32)DataAddress + DataCount - 1) <= EEPROM_END))
1237  0038 3f00          	clr	c_lreg
1238  003a 7b02          	ld	a,(OFST+1,sp)
1239  003c b701          	ld	c_lreg+1,a
1240  003e 7b03          	ld	a,(OFST+2,sp)
1241  0040 b702          	ld	c_lreg+2,a
1242  0042 7b04          	ld	a,(OFST+3,sp)
1243  0044 b703          	ld	c_lreg+3,a
1244  0046 ae000a        	ldw	x,#L461
1245  0049 cd0000        	call	c_lcmp
1247  004c 2532          	jrult	L373
1249  004e 3f00          	clr	c_lreg
1250  0050 7b02          	ld	a,(OFST+1,sp)
1251  0052 b701          	ld	c_lreg+1,a
1252  0054 7b03          	ld	a,(OFST+2,sp)
1253  0056 b702          	ld	c_lreg+2,a
1254  0058 7b04          	ld	a,(OFST+3,sp)
1255  005a b703          	ld	c_lreg+3,a
1256  005c 7b07          	ld	a,(OFST+6,sp)
1257  005e cd0000        	call	c_ladc
1259  0061 a601          	ld	a,#1
1260  0063 cd0000        	call	c_lsbc
1262  0066 ae000e        	ldw	x,#L661
1263  0069 cd0000        	call	c_lcmp
1265  006c 2412          	jruge	L373
1266                     ; 406     return WriteBufferFlash(DataAddress, DataCount, FLASH_MEMTYPE_DATA);
1268  006e 4b01          	push	#1
1270  0070               LC004:
1271  0070 7b08          	ld	a,(OFST+7,sp)
1272  0072 88            	push	a
1273  0073 7b04          	ld	a,(OFST+3,sp)
1274  0075 b700          	ld	c_x,a
1275  0077 1e05          	ldw	x,(OFST+4,sp)
1276  0079 cd0000        	call	_WriteBufferFlash
1277  007c 85            	popw	x
1279  007d               L012:
1281  007d 5b04          	addw	sp,#4
1282  007f 81            	ret	
1283  0080               L373:
1284                     ; 409   if (((u32)DataAddress >= RAM_START) && (((u32)DataAddress + DataCount - 1) <= RAM_END))
1287  0080 3f00          	clr	c_lreg
1288  0082 7b02          	ld	a,(OFST+1,sp)
1289  0084 b701          	ld	c_lreg+1,a
1290  0086 7b03          	ld	a,(OFST+2,sp)
1291  0088 b702          	ld	c_lreg+2,a
1292  008a 7b04          	ld	a,(OFST+3,sp)
1293  008c b703          	ld	c_lreg+3,a
1294  008e 7b07          	ld	a,(OFST+6,sp)
1295  0090 cd0000        	call	c_ladc
1297  0093 a601          	ld	a,#1
1298  0095 cd0000        	call	c_lsbc
1300  0098 ae0012        	ldw	x,#L071
1301  009b cd0000        	call	c_lcmp
1303  009e 242d          	jruge	L573
1304                     ; 411     for(i=0; i<DataCount; i++)
1306  00a0 0f01          	clr	(OFST+0,sp)
1308  00a2 2021          	jra	L304
1309  00a4               L773:
1310                     ; 412       DataAddress[i] = DataBuffer[i];
1312  00a4 5f            	clrw	x
1313  00a5 97            	ld	xl,a
1314  00a6 e602          	ld	a,(_DataBuffer,x)
1315  00a8 88            	push	a
1316  00a9 7b03          	ld	a,(OFST+2,sp)
1317  00ab b700          	ld	c_x,a
1318  00ad 1e04          	ldw	x,(OFST+3,sp)
1319  00af 84            	pop	a
1320  00b0 41            	exg	a,xl
1321  00b1 1b01          	add	a,(OFST+0,sp)
1322  00b3 41            	exg	a,xl
1323  00b4 2407          	jrnc	L402
1324  00b6 1c0100        	addw	x,#256
1325  00b9 2402          	jrnc	L402
1326  00bb 3c00          	inc	c_x
1327  00bd               L402:
1328  00bd bf01          	ldw	c_x+1,x
1329  00bf 92bd0000      	ldf	[c_x.e],a
1330                     ; 411     for(i=0; i<DataCount; i++)
1332  00c3 0c01          	inc	(OFST+0,sp)
1333  00c5               L304:
1336  00c5 7b01          	ld	a,(OFST+0,sp)
1337  00c7 1107          	cp	a,(OFST+6,sp)
1338  00c9 25d9          	jrult	L773
1339                     ; 413     return 1;
1341  00cb 2060          	jp	LC005
1342  00cd               L573:
1343                     ; 417   if (((u32)DataAddress >= OPTION_START) && (((u32)DataAddress + DataCount - 1) <= OPTION_END))
1345  00cd 3f00          	clr	c_lreg
1346  00cf 7b02          	ld	a,(OFST+1,sp)
1347  00d1 b701          	ld	c_lreg+1,a
1348  00d3 7b03          	ld	a,(OFST+2,sp)
1349  00d5 b702          	ld	c_lreg+2,a
1350  00d7 7b04          	ld	a,(OFST+3,sp)
1351  00d9 b703          	ld	c_lreg+3,a
1352  00db ae0016        	ldw	x,#L271
1353  00de cd0000        	call	c_lcmp
1355  00e1 254f          	jrult	L704
1357  00e3 3f00          	clr	c_lreg
1358  00e5 7b02          	ld	a,(OFST+1,sp)
1359  00e7 b701          	ld	c_lreg+1,a
1360  00e9 7b03          	ld	a,(OFST+2,sp)
1361  00eb b702          	ld	c_lreg+2,a
1362  00ed 7b04          	ld	a,(OFST+3,sp)
1363  00ef b703          	ld	c_lreg+3,a
1364  00f1 7b07          	ld	a,(OFST+6,sp)
1365  00f3 cd0000        	call	c_ladc
1367  00f6 a601          	ld	a,#1
1368  00f8 cd0000        	call	c_lsbc
1370  00fb ae001a        	ldw	x,#L471
1371  00fe cd0000        	call	c_lcmp
1373  0101 242f          	jruge	L704
1374                     ; 419     for(i=0; i<DataCount; i++)
1376  0103 0f01          	clr	(OFST+0,sp)
1378  0105 2020          	jra	L514
1379  0107               L114:
1380                     ; 421        FLASH_ProgramOptionByte((u32)(&DataAddress[i]), DataBuffer[i]);
1382  0107 5f            	clrw	x
1383  0108 97            	ld	xl,a
1384  0109 e602          	ld	a,(_DataBuffer,x)
1385  010b 88            	push	a
1386  010c 3f00          	clr	c_lreg
1387  010e 7b03          	ld	a,(OFST+2,sp)
1388  0110 b701          	ld	c_lreg+1,a
1389  0112 7b04          	ld	a,(OFST+3,sp)
1390  0114 b702          	ld	c_lreg+2,a
1391  0116 7b05          	ld	a,(OFST+4,sp)
1392  0118 b703          	ld	c_lreg+3,a
1393  011a 7b02          	ld	a,(OFST+1,sp)
1394  011c cd0000        	call	c_ladc
1396  011f be02          	ldw	x,c_lreg+2
1397  0121 cd0000        	call	_FLASH_ProgramOptionByte
1399  0124 84            	pop	a
1400                     ; 419     for(i=0; i<DataCount; i++)
1402  0125 0c01          	inc	(OFST+0,sp)
1403  0127               L514:
1406  0127 7b01          	ld	a,(OFST+0,sp)
1407  0129 1107          	cp	a,(OFST+6,sp)
1408  012b 25da          	jrult	L114
1409                     ; 423     return 1;
1411  012d               LC005:
1413  012d a601          	ld	a,#1
1415  012f cc007d        	jra	L012
1416  0132               L704:
1417                     ; 427   return 0;
1419  0132 4f            	clr	a
1421  0133 cc007d        	jra	L012
1525                     ; 430 u8 WriteBufferFlash(u8 FAR* DataAddress, u8 DataCount, FLASH_MemType_TypeDef MemType){
1526                     .text:	section	.text,new
1527  0000               _WriteBufferFlash:
1529  0000 89            	pushw	x
1530  0001 3b0000        	push	c_x
1531  0004 520a          	subw	sp,#10
1532       0000000a      OFST:	set	10
1535                     ; 431   u32 Address = (u32) DataAddress;
1537  0006 3f00          	clr	c_lreg
1538  0008 450001        	mov	c_lreg+1,c_x
1539  000b bf02          	ldw	c_lreg+2,x
1540  000d 96            	ldw	x,sp
1541  000e 1c0007        	addw	x,#OFST-3
1542  0011 cd0000        	call	c_rtol
1544                     ; 432   u8 * DataPointer = DataBuffer;
1546  0014 ae0002        	ldw	x,#_DataBuffer
1547  0017 1f05          	ldw	(OFST-5,sp),x
1548                     ; 435   if(MemType == FLASH_MEMTYPE_PROG)
1550  0019 7b11          	ld	a,(OFST+7,sp)
1551  001b 2605          	jrne	L374
1552                     ; 436     Offset = FLASH_START;
1554  001d ae8000        	ldw	x,#32768
1556  0020 2003          	jp	LC006
1557  0022               L374:
1558                     ; 438     Offset = EEPROM_START;
1560  0022 ae4000        	ldw	x,#16384
1561  0025               LC006:
1562  0025 1f03          	ldw	(OFST-7,sp),x
1563  0027 5f            	clrw	x
1564  0028 1f01          	ldw	(OFST-9,sp),x
1565  002a 201d          	jra	L105
1566  002c               L774:
1567                     ; 442     *((PointerAttr u8*) Address) = *DataPointer;
1569  002c 1e05          	ldw	x,(OFST-5,sp)
1570  002e f6            	ld	a,(x)
1571  002f 1e09          	ldw	x,(OFST-1,sp)
1572  0031 f7            	ld	(x),a
1574  0032               L115:
1575                     ; 443 		while( (FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS)) == 0);
1577  0032 c6505f        	ld	a,20575
1578  0035 a505          	bcp	a,#5
1579  0037 27f9          	jreq	L115
1580                     ; 444 		Address++;
1582  0039 96            	ldw	x,sp
1583  003a 1c0007        	addw	x,#OFST-3
1584  003d a601          	ld	a,#1
1585  003f cd0000        	call	c_lgadc
1587                     ; 445     DataPointer++;
1589  0042 1e05          	ldw	x,(OFST-5,sp)
1590  0044 5c            	incw	x
1591  0045 1f05          	ldw	(OFST-5,sp),x
1592                     ; 446     DataCount--;
1594  0047 0a10          	dec	(OFST+6,sp)
1595  0049               L105:
1596                     ; 440   while((Address % 4) && (DataCount))
1598  0049 7b0a          	ld	a,(OFST+0,sp)
1599  004b a503          	bcp	a,#3
1600  004d 276f          	jreq	L125
1602  004f 0d10          	tnz	(OFST+6,sp)
1603  0051 26d9          	jrne	L774
1604  0053 2069          	jra	L125
1605  0055               L715:
1606                     ; 451 		FLASH->CR2 |= (u8)0x40;
1608  0055 721c505b      	bset	20571,#6
1609                     ; 452 		FLASH->NCR2 &= (u8)~0x40;
1611  0059 721d505c      	bres	20572,#6
1612                     ; 453 		*((PointerAttr u8*)Address) = (u8)*DataPointer  ; 	 /* Write one byte - from lowest address*/
1614  005d 1e05          	ldw	x,(OFST-5,sp)
1615  005f f6            	ld	a,(x)
1616  0060 1e09          	ldw	x,(OFST-1,sp)
1617  0062 f7            	ld	(x),a
1618                     ; 454 		*((PointerAttr u8*)(Address + 1)) = *(DataPointer + 1); /* Write one byte*/
1620  0063 96            	ldw	x,sp
1621  0064 1c0007        	addw	x,#OFST-3
1622  0067 cd0000        	call	c_ltor
1624  006a a601          	ld	a,#1
1625  006c cd0000        	call	c_ladc
1627  006f be02          	ldw	x,c_lreg+2
1628  0071 1605          	ldw	y,(OFST-5,sp)
1629  0073 90e601        	ld	a,(1,y)
1630  0076 f7            	ld	(x),a
1631                     ; 455 		*((PointerAttr u8*)(Address + 2)) = *(DataPointer + 2); /* Write one byte*/
1633  0077 96            	ldw	x,sp
1634  0078 1c0007        	addw	x,#OFST-3
1635  007b cd0000        	call	c_ltor
1637  007e a602          	ld	a,#2
1638  0080 cd0000        	call	c_ladc
1640  0083 be02          	ldw	x,c_lreg+2
1641  0085 1605          	ldw	y,(OFST-5,sp)
1642  0087 90e602        	ld	a,(2,y)
1643  008a f7            	ld	(x),a
1644                     ; 456 		*((PointerAttr u8*)(Address + 3)) = *(DataPointer + 3); /* Write one byte - from higher address*/
1646  008b 96            	ldw	x,sp
1647  008c 1c0007        	addw	x,#OFST-3
1648  008f cd0000        	call	c_ltor
1650  0092 a603          	ld	a,#3
1651  0094 cd0000        	call	c_ladc
1653  0097 be02          	ldw	x,c_lreg+2
1654  0099 1605          	ldw	y,(OFST-5,sp)
1655  009b 90e603        	ld	a,(3,y)
1656  009e f7            	ld	(x),a
1658  009f               L135:
1659                     ; 457     while( (FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS)) == 0);
1661  009f c6505f        	ld	a,20575
1662  00a2 a505          	bcp	a,#5
1663  00a4 27f9          	jreq	L135
1664                     ; 458 		Address    += 4;
1666  00a6 96            	ldw	x,sp
1667  00a7 1c0007        	addw	x,#OFST-3
1668  00aa a604          	ld	a,#4
1669  00ac cd0000        	call	c_lgadc
1671                     ; 459     DataPointer+= 4;
1673  00af 1e05          	ldw	x,(OFST-5,sp)
1674  00b1 1c0004        	addw	x,#4
1675  00b4 1f05          	ldw	(OFST-5,sp),x
1676                     ; 460     DataCount  -= 4;
1678  00b6 7b10          	ld	a,(OFST+6,sp)
1679  00b8 a004          	sub	a,#4
1680  00ba 6b10          	ld	(OFST+6,sp),a
1681  00bc 7b0a          	ld	a,(OFST+0,sp)
1682  00be               L125:
1683                     ; 449 	while((Address % BLOCK_BYTES) && (DataCount >= 4))
1685  00be a53f          	bcp	a,#63
1686  00c0 273e          	jreq	L145
1688  00c2 7b10          	ld	a,(OFST+6,sp)
1689  00c4 a104          	cp	a,#4
1690  00c6 248d          	jruge	L715
1691  00c8 2036          	jra	L145
1692  00ca               L735:
1693                     ; 465     Mem_ProgramBlock((Address - Offset)/BLOCK_BYTES, MemType, DataPointer);
1695  00ca 1e05          	ldw	x,(OFST-5,sp)
1696  00cc 89            	pushw	x
1697  00cd 7b13          	ld	a,(OFST+9,sp)
1698  00cf 88            	push	a
1699  00d0 96            	ldw	x,sp
1700  00d1 1c000a        	addw	x,#OFST+0
1701  00d4 cd0000        	call	c_ltor
1703  00d7 96            	ldw	x,sp
1704  00d8 1c0004        	addw	x,#OFST-6
1705  00db cd0000        	call	c_lsub
1707  00de a606          	ld	a,#6
1708  00e0 cd0000        	call	c_lursh
1710  00e3 be02          	ldw	x,c_lreg+2
1711  00e5 cd0000        	call	_Mem_ProgramBlock
1713  00e8 5b03          	addw	sp,#3
1714                     ; 466     Address    += BLOCK_BYTES;
1716  00ea 96            	ldw	x,sp
1717  00eb 1c0007        	addw	x,#OFST-3
1718  00ee a640          	ld	a,#64
1719  00f0 cd0000        	call	c_lgadc
1721                     ; 467     DataPointer+= BLOCK_BYTES;    
1723  00f3 1e05          	ldw	x,(OFST-5,sp)
1724  00f5 1c0040        	addw	x,#64
1725  00f8 1f05          	ldw	(OFST-5,sp),x
1726                     ; 468     DataCount  -= BLOCK_BYTES;
1728  00fa 7b10          	ld	a,(OFST+6,sp)
1729  00fc a040          	sub	a,#64
1730  00fe 6b10          	ld	(OFST+6,sp),a
1731  0100               L145:
1732                     ; 463   while(DataCount >= BLOCK_BYTES)
1734  0100 7b10          	ld	a,(OFST+6,sp)
1735  0102 a140          	cp	a,#64
1736  0104 24c4          	jruge	L735
1738  0106 2067          	jra	L745
1739  0108               L545:
1740                     ; 474 		FLASH->CR2 |= (u8)0x40;
1742  0108 721c505b      	bset	20571,#6
1743                     ; 475 		FLASH->NCR2 &= (u8)~0x40;
1745  010c 721d505c      	bres	20572,#6
1746                     ; 476 		*((PointerAttr u8*)Address) = (u8)*DataPointer  ; 	 /* Write one byte - from lowest address*/
1748  0110 1e05          	ldw	x,(OFST-5,sp)
1749  0112 f6            	ld	a,(x)
1750  0113 1e09          	ldw	x,(OFST-1,sp)
1751  0115 f7            	ld	(x),a
1752                     ; 477 		*((PointerAttr u8*)(Address + 1)) = *(DataPointer + 1); /* Write one byte*/
1754  0116 96            	ldw	x,sp
1755  0117 1c0007        	addw	x,#OFST-3
1756  011a cd0000        	call	c_ltor
1758  011d a601          	ld	a,#1
1759  011f cd0000        	call	c_ladc
1761  0122 be02          	ldw	x,c_lreg+2
1762  0124 1605          	ldw	y,(OFST-5,sp)
1763  0126 90e601        	ld	a,(1,y)
1764  0129 f7            	ld	(x),a
1765                     ; 478 		*((PointerAttr u8*)(Address + 2)) = *(DataPointer + 2); /* Write one byte*/
1767  012a 96            	ldw	x,sp
1768  012b 1c0007        	addw	x,#OFST-3
1769  012e cd0000        	call	c_ltor
1771  0131 a602          	ld	a,#2
1772  0133 cd0000        	call	c_ladc
1774  0136 be02          	ldw	x,c_lreg+2
1775  0138 1605          	ldw	y,(OFST-5,sp)
1776  013a 90e602        	ld	a,(2,y)
1777  013d f7            	ld	(x),a
1778                     ; 479 		*((PointerAttr u8*)(Address + 3)) = *(DataPointer + 3); /* Write one byte - from higher address*/
1780  013e 96            	ldw	x,sp
1781  013f 1c0007        	addw	x,#OFST-3
1782  0142 cd0000        	call	c_ltor
1784  0145 a603          	ld	a,#3
1785  0147 cd0000        	call	c_ladc
1787  014a be02          	ldw	x,c_lreg+2
1788  014c 1605          	ldw	y,(OFST-5,sp)
1789  014e 90e603        	ld	a,(3,y)
1790  0151 f7            	ld	(x),a
1792  0152               L755:
1793                     ; 480     while( (FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS)) == 0);
1795  0152 c6505f        	ld	a,20575
1796  0155 a505          	bcp	a,#5
1797  0157 27f9          	jreq	L755
1798                     ; 481 		Address    += 4;
1800  0159 96            	ldw	x,sp
1801  015a 1c0007        	addw	x,#OFST-3
1802  015d a604          	ld	a,#4
1803  015f cd0000        	call	c_lgadc
1805                     ; 482     DataPointer+= 4;
1807  0162 1e05          	ldw	x,(OFST-5,sp)
1808  0164 1c0004        	addw	x,#4
1809  0167 1f05          	ldw	(OFST-5,sp),x
1810                     ; 483     DataCount  -= 4;
1812  0169 7b10          	ld	a,(OFST+6,sp)
1813  016b a004          	sub	a,#4
1814  016d 6b10          	ld	(OFST+6,sp),a
1815  016f               L745:
1816                     ; 472   while(DataCount >= 4)
1818  016f a104          	cp	a,#4
1819  0171 2495          	jruge	L545
1821  0173 201d          	jra	L565
1822  0175               L365:
1823                     ; 489     *((PointerAttr u8*) Address) = *DataPointer;
1825  0175 1e05          	ldw	x,(OFST-5,sp)
1826  0177 f6            	ld	a,(x)
1827  0178 1e09          	ldw	x,(OFST-1,sp)
1828  017a f7            	ld	(x),a
1830  017b               L575:
1831                     ; 490     while( (FLASH->IAPSR & (FLASH_IAPSR_EOP | FLASH_IAPSR_WR_PG_DIS)) == 0);
1833  017b c6505f        	ld	a,20575
1834  017e a505          	bcp	a,#5
1835  0180 27f9          	jreq	L575
1836                     ; 491 		Address++;
1838  0182 96            	ldw	x,sp
1839  0183 1c0007        	addw	x,#OFST-3
1840  0186 a601          	ld	a,#1
1841  0188 cd0000        	call	c_lgadc
1843                     ; 492     DataPointer++;
1845  018b 1e05          	ldw	x,(OFST-5,sp)
1846  018d 5c            	incw	x
1847  018e 1f05          	ldw	(OFST-5,sp),x
1848                     ; 493     DataCount--;
1850  0190 0a10          	dec	(OFST+6,sp)
1851  0192               L565:
1852                     ; 487   while(DataCount)
1854  0192 7b10          	ld	a,(OFST+6,sp)
1855  0194 26df          	jrne	L365
1856                     ; 496   return 1;
1858  0196 4c            	inc	a
1861  0197 5b0d          	addw	sp,#13
1862  0199 81            	ret	
1886                     ; 499 void DeInitBootloader(void){
1887                     .text:	section	.text,new
1888  0000               _DeInitBootloader:
1892                     ; 500   if(RoutinesInRAM)
1894  0000 b600          	ld	a,_RoutinesInRAM
1895  0002 2708          	jreq	L116
1896                     ; 503     FLASH->IAPSR = ~0x02;
1898  0004 35fd505f      	mov	20575,#253
1899                     ; 505     FLASH->IAPSR = ~0x08;
1901  0008 35f7505f      	mov	20575,#247
1902  000c               L116:
1903                     ; 509 	I2C->CR1 = 0x00;
1905  000c 725f5210      	clr	21008
1906                     ; 510   I2C->CR2 = 0x00;
1908  0010 725f5211      	clr	21009
1909                     ; 511   I2C->FREQR = 0x00;
1911  0014 725f5212      	clr	21010
1912                     ; 512   I2C->OARL = 0x00;
1914  0018 725f5213      	clr	21011
1915                     ; 513   I2C->OARH = 0x00;
1917  001c 725f5214      	clr	21012
1918                     ; 514   I2C->ITR = 0x00;
1920  0020 725f521a      	clr	21018
1921                     ; 515   I2C->CCRL = 0x00;
1923  0024 725f521b      	clr	21019
1924                     ; 516   I2C->CCRH = 0x00;
1926  0028 725f521c      	clr	21020
1927                     ; 517   I2C->TRISER = 0x02;
1929  002c 3502521d      	mov	21021,#2
1930                     ; 519 }//DeInitBootloader
1933  0030 81            	ret	
1968                     ; 521 void protocol_init (void) {
1969                     .text:	section	.text,new
1970  0000               _protocol_init:
1972  0000 5204          	subw	sp,#4
1973       00000004      OFST:	set	4
1976                     ; 553 		u32 BaudRate_Mantissa, BaudRate_Mantissa100 = 0;	
1978  0002 5f            	clrw	x
1979  0003 1f03          	ldw	(OFST-1,sp),x
1980  0005 1f01          	ldw	(OFST-3,sp),x
1981                     ; 558     GPIOD->CR1 |= (u8)0x40;
1983  0007 721c5012      	bset	20498,#6
1984                     ; 559 		GPIOC->CR1 |= (u8)0x02;		
1986  000b 7212500d      	bset	20493,#1
1987                     ; 562 		UART1->CR1 &= (u8)(~0x20); 
1989  000f 721b5234      	bres	21044,#5
1990                     ; 565     UART1->CR1 |= (u8)  0x14;
1992  0013 c65234        	ld	a,21044
1993  0016 aa14          	or	a,#20
1994  0018 c75234        	ld	21044,a
1995                     ; 568 		UART1->CR2 |= (u8)  0x0C;
1997  001b c65235        	ld	a,21045
1998  001e aa0c          	or	a,#12
1999  0020 c75235        	ld	21045,a
2000                     ; 571     UART1->BRR2 = 0x02;
2002  0023 35025233      	mov	21043,#2
2003                     ; 572 		UART1->BRR1 = 0x68;
2005  0027 35685232      	mov	21042,#104
2006                     ; 622 }
2009  002b 5b04          	addw	sp,#4
2010  002d 81            	ret	
2053                     ; 624 void Transmit(u8 Data){
2054                     .text:	section	.text,new
2055  0000               _Transmit:
2057  0000 88            	push	a
2058  0001 88            	push	a
2059       00000001      OFST:	set	1
2062                     ; 655 	sr = UART1->SR;
2064  0002               L356:
2065                     ; 656   while(!(sr & 0x80/*TxNE*/)) sr = UART1->SR;
2068  0002 c65230        	ld	a,21040
2069  0005 6b01          	ld	(OFST+0,sp),a
2072  0007 2af9          	jrpl	L356
2073                     ; 658    UART1->DR = Data;
2075  0009 7b02          	ld	a,(OFST+1,sp)
2076  000b c75231        	ld	21041,a
2077                     ; 660   sr = UART1->SR;
2079  000e               L366:
2080                     ; 661   while(!(sr & 0x40/*TxNE*/)) sr = UART1->SR;
2083  000e c65230        	ld	a,21040
2084  0011 6b01          	ld	(OFST+0,sp),a
2087  0013 a540          	bcp	a,#64
2088  0015 27f7          	jreq	L366
2089                     ; 683 }//Transmit
2092  0017 85            	popw	x
2093  0018 81            	ret	
2138                     ; 685 u8 Receive(u8* ReceivedData){
2139                     .text:	section	.text,new
2140  0000               _Receive:
2142  0000 89            	pushw	x
2143  0001 88            	push	a
2144       00000001      OFST:	set	1
2147                     ; 740 	sr = UART1->SR;
2149  0002               L517:
2150                     ; 741   while(!(sr & 0x20 /*RXNE*/)) sr = UART1->SR ;
2153  0002 c65230        	ld	a,21040
2154  0005 6b01          	ld	(OFST+0,sp),a
2157  0007 a520          	bcp	a,#32
2158  0009 27f7          	jreq	L517
2159                     ; 743 	if((sr & 0x08/*OR*/)||(sr & 0x01/*PE*/))
2161  000b a508          	bcp	a,#8
2162  000d 2604          	jrne	L727
2164  000f a501          	bcp	a,#1
2165  0011 270e          	jreq	L527
2166  0013               L727:
2167                     ; 746     *ReceivedData = UART1->DR ;
2169  0013 1e02          	ldw	x,(OFST+1,sp)
2170  0015 c65231        	ld	a,21041
2171  0018 f7            	ld	(x),a
2172                     ; 748     Transmit(NACK);
2174  0019 a61f          	ld	a,#31
2175  001b cd0000        	call	_Transmit
2177                     ; 750     return 0;
2179  001e 4f            	clr	a
2181  001f 2008          	jra	L032
2182  0021               L527:
2183                     ; 753   *ReceivedData = UART1->DR;
2185  0021 1e02          	ldw	x,(OFST+1,sp)
2186  0023 c65231        	ld	a,21041
2187  0026 f7            	ld	(x),a
2188                     ; 755   return 1;
2190  0027 a601          	ld	a,#1
2192  0029               L032:
2194  0029 5b03          	addw	sp,#3
2195  002b 81            	ret	
2239                     ; 800 u8 Master_ident(u8 IDENT_byte){
2240                     .text:	section	.text,new
2241  0000               _Master_ident:
2243  0000 88            	push	a
2244  0001 88            	push	a
2245       00000001      OFST:	set	1
2248                     ; 802 	Receive(&master_ident);
2250  0002 96            	ldw	x,sp
2251  0003 5c            	incw	x
2252  0004 cd0000        	call	_Receive
2254                     ; 803   if (master_ident == IDENT_byte) 
2256  0007 7b01          	ld	a,(OFST+0,sp)
2257  0009 1102          	cp	a,(OFST+1,sp)
2258  000b 2604          	jrne	L357
2259                     ; 805 		return 1;	
2261  000d a601          	ld	a,#1
2263  000f 2001          	jra	L632
2264  0011               L357:
2265                     ; 807 	return 0;
2267  0011 4f            	clr	a
2269  0012               L632:
2271  0012 85            	popw	x
2272  0013 81            	ret	
2309                     ; 810 u8 ReceiveAddress(void){
2310                     .text:	section	.text,new
2311  0000               _ReceiveAddress:
2313  0000 88            	push	a
2314       00000001      OFST:	set	1
2317                     ; 811   u8 result = 1;
2319  0001 a601          	ld	a,#1
2320  0003 6b01          	ld	(OFST+0,sp),a
2321                     ; 814   if(!Receive(ReceivedData++))
2323  0005 be00          	ldw	x,_ReceivedData
2324  0007 5c            	incw	x
2325  0008 bf00          	ldw	_ReceivedData,x
2326  000a 5a            	decw	x
2327  000b cd0000        	call	_Receive
2329  000e 4d            	tnz	a
2330  000f 2602          	jrne	L377
2331                     ; 815     result = 0;
2333  0011 6b01          	ld	(OFST+0,sp),a
2334  0013               L377:
2335                     ; 816   if(!Receive(ReceivedData++))
2337  0013 be00          	ldw	x,_ReceivedData
2338  0015 5c            	incw	x
2339  0016 bf00          	ldw	_ReceivedData,x
2340  0018 5a            	decw	x
2341  0019 cd0000        	call	_Receive
2343  001c 4d            	tnz	a
2344  001d 2602          	jrne	L577
2345                     ; 817     result = 0;
2347  001f 6b01          	ld	(OFST+0,sp),a
2348  0021               L577:
2349                     ; 818   if(!Receive(ReceivedData++))
2351  0021 be00          	ldw	x,_ReceivedData
2352  0023 5c            	incw	x
2353  0024 bf00          	ldw	_ReceivedData,x
2354  0026 5a            	decw	x
2355  0027 cd0000        	call	_Receive
2357  002a 4d            	tnz	a
2358  002b 2602          	jrne	L777
2359                     ; 819     result = 0;
2361  002d 6b01          	ld	(OFST+0,sp),a
2362  002f               L777:
2363                     ; 820   if(!Receive(ReceivedData++))
2365  002f be00          	ldw	x,_ReceivedData
2366  0031 5c            	incw	x
2367  0032 bf00          	ldw	_ReceivedData,x
2368  0034 5a            	decw	x
2369  0035 cd0000        	call	_Receive
2371  0038 4d            	tnz	a
2372  0039 2602          	jrne	L1001
2373                     ; 821     result = 0;
2375  003b 6b01          	ld	(OFST+0,sp),a
2376  003d               L1001:
2377                     ; 824   if(!Receive(ReceivedData++))
2379  003d be00          	ldw	x,_ReceivedData
2380  003f 5c            	incw	x
2381  0040 bf00          	ldw	_ReceivedData,x
2382  0042 5a            	decw	x
2383  0043 cd0000        	call	_Receive
2385  0046 4d            	tnz	a
2386  0047 2602          	jrne	L3001
2387                     ; 825     result = 0;
2389  0049 6b01          	ld	(OFST+0,sp),a
2390  004b               L3001:
2391                     ; 828   if(*(--ReceivedData) ^ *(--ReceivedData) ^ *(--ReceivedData) ^ *(--ReceivedData) ^ *(--ReceivedData))
2393  004b be00          	ldw	x,_ReceivedData
2394  004d 5a            	decw	x
2395  004e f6            	ld	a,(x)
2396  004f 5a            	decw	x
2397  0050 f8            	xor	a,(x)
2398  0051 5a            	decw	x
2399  0052 f8            	xor	a,(x)
2400  0053 5a            	decw	x
2401  0054 f8            	xor	a,(x)
2402  0055 5a            	decw	x
2403  0056 f8            	xor	a,(x)
2404  0057 2702          	jreq	L5001
2405                     ; 829     result = 0;
2407  0059 0f01          	clr	(OFST+0,sp)
2408  005b               L5001:
2409                     ; 831   ReceivedData += 5;
2411  005b 1c0005        	addw	x,#5
2412  005e bf00          	ldw	_ReceivedData,x
2413                     ; 838   if (!result)
2415  0060 7b01          	ld	a,(OFST+0,sp)
2416  0062 2603          	jrne	L7001
2417                     ; 839     return 0;
2421  0064 5b01          	addw	sp,#1
2422  0066 81            	ret	
2423  0067               L7001:
2424                     ; 842   Transmit(ACK);
2426  0067 a679          	ld	a,#121
2427  0069 cd0000        	call	_Transmit
2429                     ; 843   return 1;
2431  006c a601          	ld	a,#1
2434  006e 5b01          	addw	sp,#1
2435  0070 81            	ret	
2511                     ; 846 u8 ReceiveCount(u8 max, u8 enablechecksum){
2512                     .text:	section	.text,new
2513  0000               _ReceiveCount:
2515  0000 89            	pushw	x
2516  0001 88            	push	a
2517       00000001      OFST:	set	1
2520                     ; 847   bool result = 1;
2522  0002 a601          	ld	a,#1
2523  0004 6b01          	ld	(OFST+0,sp),a
2524                     ; 850   if(!Receive(ReceivedData))
2526  0006 be00          	ldw	x,_ReceivedData
2527  0008 cd0000        	call	_Receive
2529  000b 4d            	tnz	a
2530  000c 2602          	jrne	L7401
2531                     ; 851     result = 0;
2533  000e 6b01          	ld	(OFST+0,sp),a
2534  0010               L7401:
2535                     ; 854   if(!((*ReceivedData++) <= max))
2537  0010 be00          	ldw	x,_ReceivedData
2538  0012 5c            	incw	x
2539  0013 bf00          	ldw	_ReceivedData,x
2540  0015 5a            	decw	x
2541  0016 f6            	ld	a,(x)
2542  0017 1102          	cp	a,(OFST+1,sp)
2543  0019 2302          	jrule	L1501
2544                     ; 855     result = 0;
2546  001b 0f01          	clr	(OFST+0,sp)
2547  001d               L1501:
2548                     ; 859   if (enablechecksum)
2550  001d 7b03          	ld	a,(OFST+2,sp)
2551  001f 271e          	jreq	L3501
2552                     ; 862     if(!Receive(ReceivedData++))
2554  0021 be00          	ldw	x,_ReceivedData
2555  0023 5c            	incw	x
2556  0024 bf00          	ldw	_ReceivedData,x
2557  0026 5a            	decw	x
2558  0027 cd0000        	call	_Receive
2560  002a 4d            	tnz	a
2561  002b 2602          	jrne	L5501
2562                     ; 863       result = 0;
2564  002d 6b01          	ld	(OFST+0,sp),a
2565  002f               L5501:
2566                     ; 866     if((*(--ReceivedData) ^ *(--ReceivedData)) != 0xFF)
2568  002f be00          	ldw	x,_ReceivedData
2569  0031 5a            	decw	x
2570  0032 f6            	ld	a,(x)
2571  0033 5a            	decw	x
2572  0034 f8            	xor	a,(x)
2573  0035 4c            	inc	a
2574  0036 2702          	jreq	L7501
2575                     ; 867       result = 0;
2577  0038 0f01          	clr	(OFST+0,sp)
2578  003a               L7501:
2579                     ; 869     ReceivedData += 2;
2581  003a 1c0002        	addw	x,#2
2582  003d bf00          	ldw	_ReceivedData,x
2583  003f               L3501:
2584                     ; 873   if (enablechecksum)
2586  003f 7b03          	ld	a,(OFST+2,sp)
2587  0041 2705          	jreq	L1601
2588                     ; 874     Transmit(ACK);
2590  0043 a679          	ld	a,#121
2591  0045 cd0000        	call	_Transmit
2593  0048               L1601:
2594                     ; 876   return result;
2596  0048 7b01          	ld	a,(OFST+0,sp)
2599  004a 5b03          	addw	sp,#3
2600  004c 81            	ret	
2623                     ; 879 void unlock_PROG(void){
2624                     .text:	section	.text,new
2625  0000               _unlock_PROG:
2629                     ; 881   FLASH->PUKR = 0x56;
2631  0000 35565062      	mov	20578,#86
2632                     ; 882   FLASH->PUKR = 0xAE;
2634  0004 35ae5062      	mov	20578,#174
2635                     ; 883   }
2638  0008 81            	ret	
2661                     ; 885 void unlock_DATA(void) {
2662                     .text:	section	.text,new
2663  0000               _unlock_DATA:
2667                     ; 887 	FLASH->DUKR = 0xAE; /* Warning: keys are reversed on data memory !!! */
2669  0000 35ae5064      	mov	20580,#174
2670                     ; 888   FLASH->DUKR = 0x56;
2672  0004 35565064      	mov	20580,#86
2673                     ; 889 }
2676  0008 81            	ret	
2757                     ; 901 void Mem_ProgramBlock(u16 BlockNum, FLASH_MemType_TypeDef MemType, u8 *Buffer)
2757                     ; 902 #endif /*_RAISONANCE_*/
2757                     ; 903 {
2758                     .FLASH_CODE:	section	.text,new
2759  0000               _Mem_ProgramBlock:
2761  0000 89            	pushw	x
2762  0001 5208          	subw	sp,#8
2763       00000008      OFST:	set	8
2766                     ; 904     u16 Count = 0;
2768                     ; 905     u32 StartAddress = 0;
2770  0003 96            	ldw	x,sp
2771  0004 1c0003        	addw	x,#OFST-5
2772  0007 cd0000        	call	c_ltor
2774                     ; 906     u16 timeout = (u16)0x6000;
2776  000a ae6000        	ldw	x,#24576
2777  000d 1f01          	ldw	(OFST-7,sp),x
2778                     ; 909     if (MemType == FLASH_MEMTYPE_PROG)
2780  000f 7b0d          	ld	a,(OFST+5,sp)
2781  0011 2605          	jrne	L5411
2782                     ; 911         StartAddress = FLASH_START;
2784  0013 ae8000        	ldw	x,#32768
2786  0016 2003          	jra	L7411
2787  0018               L5411:
2788                     ; 915         StartAddress = EEPROM_START;
2790  0018 ae4000        	ldw	x,#16384
2791  001b               L7411:
2792  001b 1f05          	ldw	(OFST-3,sp),x
2793  001d 5f            	clrw	x
2794  001e 1f03          	ldw	(OFST-5,sp),x
2795                     ; 919     StartAddress = StartAddress + ((u32)BlockNum * BLOCK_SIZE);
2797  0020 1e09          	ldw	x,(OFST+1,sp)
2798  0022 a640          	ld	a,#64
2799  0024 cd0000        	call	c_cmulx
2801  0027 96            	ldw	x,sp
2802  0028 1c0003        	addw	x,#OFST-5
2803  002b cd0000        	call	c_lgadd
2805                     ; 922     FLASH->CR2 |= (u8)0x01;
2807  002e 7210505b      	bset	20571,#0
2808                     ; 923     FLASH->NCR2 &= (u8)~0x01;
2810  0032 7211505c      	bres	20572,#0
2811                     ; 926     for (Count = 0; Count < BLOCK_SIZE; Count++)
2813  0036 5f            	clrw	x
2814  0037 1f07          	ldw	(OFST-1,sp),x
2815  0039               L1511:
2816                     ; 928         *((PointerAttr u8*)StartAddress + Count) = ((u8)(Buffer[Count]));
2818  0039 1e0e          	ldw	x,(OFST+6,sp)
2819  003b 72fb07        	addw	x,(OFST-1,sp)
2820  003e f6            	ld	a,(x)
2821  003f 1e05          	ldw	x,(OFST-3,sp)
2822  0041 72fb07        	addw	x,(OFST-1,sp)
2823  0044 f7            	ld	(x),a
2824                     ; 926     for (Count = 0; Count < BLOCK_SIZE; Count++)
2826  0045 1e07          	ldw	x,(OFST-1,sp)
2827  0047 5c            	incw	x
2828  0048 1f07          	ldw	(OFST-1,sp),x
2831  004a a30040        	cpw	x,#64
2832  004d 25ea          	jrult	L1511
2833                     ; 932     if (MemType == FLASH_MEMTYPE_DATA)
2835  004f 7b0d          	ld	a,(OFST+5,sp)
2836  0051 4a            	dec	a
2837  0052 2610          	jrne	L7511
2839  0054 2005          	jra	L3611
2840  0056               L1611:
2841                     ; 937             timeout--;
2843  0056 1e01          	ldw	x,(OFST-7,sp)
2844  0058 5a            	decw	x
2845  0059 1f01          	ldw	(OFST-7,sp),x
2846  005b               L3611:
2847                     ; 935         while ((FLASH->IAPSR & 0x40) != 0x00 || (timeout == 0x00))
2849  005b 720c505ff6    	btjt	20575,#6,L1611
2851  0060 1e01          	ldw	x,(OFST-7,sp)
2852  0062 27f2          	jreq	L1611
2853  0064               L7511:
2854                     ; 941 }
2857  0064 5b0a          	addw	sp,#10
2858  0066 81            	ret	
2911                     ; 947 void FLASH_ProgramOptionByte(u16 Address, u8 Data){
2912                     .text:	section	.text,new
2913  0000               _FLASH_ProgramOptionByte:
2915  0000 89            	pushw	x
2916  0001 88            	push	a
2917       00000001      OFST:	set	1
2920                     ; 950   FLASH->CR2 |= (u8)0x80;
2922  0002 721e505b      	bset	20571,#7
2923                     ; 951   FLASH->NCR2 &= (u8)(~0x80);
2925  0006 721f505c      	bres	20572,#7
2926                     ; 954   *((NEAR u8*)Address) = Data;
2928  000a 7b06          	ld	a,(OFST+5,sp)
2929  000c 1e02          	ldw	x,(OFST+1,sp)
2930  000e f7            	ld	(x),a
2931                     ; 955   *((NEAR u8*)(Address + 1)) = (u8)(~Data);
2933  000f 43            	cpl	a
2934  0010 e701          	ld	(1,x),a
2935                     ; 958 	  flash_iapsr = FLASH->IAPSR ;
2937  0012               L5121:
2938                     ; 959 		while (!(flash_iapsr & 0x41)) flash_iapsr = FLASH->IAPSR ;
2941  0012 c6505f        	ld	a,20575
2942  0015 6b01          	ld	(OFST+0,sp),a
2945  0017 a541          	bcp	a,#65
2946  0019 27f7          	jreq	L5121
2947                     ; 966   FLASH->CR2 &= (u8)(~0x80);
2949  001b 721f505b      	bres	20571,#7
2950                     ; 967   FLASH->NCR2 |= (u8)0x80;
2952  001f 721e505c      	bset	20572,#7
2953                     ; 968 }
2956  0023 5b03          	addw	sp,#3
2957  0025 81            	ret	
2960                     	switch	.const
2961  001e               L5221_HSIDivFactor:
2962  001e 01            	dc.b	1
2963  001f 02            	dc.b	2
2964  0020 04            	dc.b	4
2965  0021 08            	dc.b	8
3025                     ; 971 u32 CLK_GetClockFreq(void)
3025                     ; 972 {
3026                     .text:	section	.text,new
3027  0000               _CLK_GetClockFreq:
3029  0000 520d          	subw	sp,#13
3030       0000000d      OFST:	set	13
3033                     ; 973 	uc8 HSIDivFactor[4] = {1, 2, 4, 8}; /* Holds the different HSI Dividor factors */
3035  0002 96            	ldw	x,sp
3036  0003 1c0005        	addw	x,#OFST-8
3037  0006 90ae001e      	ldw	y,#L5221_HSIDivFactor
3038  000a a604          	ld	a,#4
3039  000c cd0000        	call	c_xymvx
3041                     ; 974 	u32 clockfrequency = 0;
3043  000f 96            	ldw	x,sp
3044  0010 1c0009        	addw	x,#OFST-4
3045  0013 cd0000        	call	c_ltor
3047                     ; 975 	u8 tmp = 0, presc = 0;
3051                     ; 976 	tmp = (u8)(CLK->CKDIVR & 0x18);
3053  0016 c650c6        	ld	a,20678
3054  0019 a418          	and	a,#24
3055                     ; 977 	tmp = (u8)(tmp >> 3);
3057  001b 44            	srl	a
3058  001c 44            	srl	a
3059  001d 44            	srl	a
3060  001e 6b0d          	ld	(OFST+0,sp),a
3061                     ; 978 	presc = HSIDivFactor[tmp];
3063  0020 96            	ldw	x,sp
3064  0021 1c0005        	addw	x,#OFST-8
3065  0024 9f            	ld	a,xl
3066  0025 5e            	swapw	x
3067  0026 1b0d          	add	a,(OFST+0,sp)
3068  0028 2401          	jrnc	L003
3069  002a 5c            	incw	x
3070  002b               L003:
3071  002b 02            	rlwa	x,a
3072  002c f6            	ld	a,(x)
3073  002d 6b0d          	ld	(OFST+0,sp),a
3074                     ; 979 	clockfrequency = 16000000 / presc;
3076  002f b703          	ld	c_lreg+3,a
3077  0031 3f02          	clr	c_lreg+2
3078  0033 3f01          	clr	c_lreg+1
3079  0035 3f00          	clr	c_lreg
3080  0037 96            	ldw	x,sp
3081  0038 5c            	incw	x
3082  0039 cd0000        	call	c_rtol
3084  003c ae2400        	ldw	x,#9216
3085  003f bf02          	ldw	c_lreg+2,x
3086  0041 ae00f4        	ldw	x,#244
3087  0044 bf00          	ldw	c_lreg,x
3088  0046 96            	ldw	x,sp
3089  0047 5c            	incw	x
3090  0048 cd0000        	call	c_ldiv
3092  004b 96            	ldw	x,sp
3093  004c 1c0009        	addw	x,#OFST-4
3094  004f cd0000        	call	c_rtol
3096                     ; 980 	return((u32)clockfrequency);
3098  0052 96            	ldw	x,sp
3099  0053 1c0009        	addw	x,#OFST-4
3100  0056 cd0000        	call	c_ltor
3104  0059 5b0d          	addw	sp,#13
3105  005b 81            	ret	
3172                     	xdef	_CheckAddress
3173                     	xdef	_CLK_GetClockFreq
3174                     	xdef	_Mem_ProgramBlock
3175                     	xdef	_FLASH_ProgramOptionByte
3176                     	xdef	_unlock_DATA
3177                     	xdef	_unlock_PROG
3178                     	xdef	_ReceiveCount
3179                     	xdef	_ReceiveAddress
3180                     	xdef	_Receive
3181                     	xdef	_Transmit
3182                     	xdef	_Master_ident
3183                     	xdef	_protocol_init
3184                     	xdef	_DeInitBootloader
3185                     	xdef	_WriteBufferFlash
3186                     	xdef	_WriteBuffer
3187                     	xdef	_GO_Command_Process
3188                     	xdef	_WM_Command_Process
3189                     	xdef	_RM_Command_Process
3190                     	xdef	_GT_Command_Process
3191                     	xdef	_ProcessCommands
3192                     	xdef	_main
3193                     	xref	__fctcpy
3194                     	xdef	_RoutinesInRAM
3195                     	switch	.ubsct
3196  0000               _ReceivedData:
3197  0000 0000          	ds.b	2
3198                     	xdef	_ReceivedData
3199  0002               _DataBuffer:
3200  0002 000000000000  	ds.b	130
3201                     	xdef	_DataBuffer
3202  0084               _GoAddress:
3203  0084 0000          	ds.b	2
3204                     	xdef	_GoAddress
3205                     	xdef	_MainUserApplication
3206                     	xref.b	c_lreg
3207                     	xref.b	c_x
3227                     	xref	c_ldiv
3228                     	xref	c_xymvx
3229                     	xref	c_lgadd
3230                     	xref	c_cmulx
3231                     	xref	c_lursh
3232                     	xref	c_lsub
3233                     	xref	c_lgadc
3234                     	xref	c_rtol
3235                     	xref	c_lsbc
3236                     	xref	c_ladc
3237                     	xref	c_lcmp
3238                     	xref	c_ltor
3239                     	end
