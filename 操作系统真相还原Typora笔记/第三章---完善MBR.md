## 第三章---完善MBR

​	在上一章节通过BIOS中断来实现打印字符串，现在尝试绕过BIOS来直接显示字符串，这是为了应对进入保护模式后不能使用BIOS中断做准备

​	可以这样做的原理是因为显卡的内存已经编排好了CPU能够寻址的范围之内，当CPU操作这部分内存是，实际上是直接和显卡打交道。显卡拿到数据处理之后，显示器最终会按照要求显示数据。内存中显存映射的地址范围如下：

| C000 | C7FFF | 32KB | 显示适配器BIOS         |
| :--: | ----- | ---- | ---------------------- |
| B800 | BFFFF | 32KB | 用于文本模式显示适配器 |
| B000 | B7FFF | 32KB | 用于黑白显示适配器     |
| A000 | AFFFF | 64KB | 用于彩色显示适配器     |

显示器上**每个字符占俩字节，低字节是字符ASCLL码，高字节是用来控制颜色**。高字节低四位是字符前景色，即字符颜色（I位表示是否高亮），高字节高四位是字符背景色（K位控制是否闪烁），所以向显卡的对应内存操作是也应按如下格式：

![1737861570424](C:\Users\nihao\AppData\Roaming\Typora\typora-user-images\1737861570424.png)

RGB配色的效果：

|  R   |  G   |  B   | I=0  |  I=1   |
| :--: | :--: | :--: | :--: | :----: |
|  0   |  0   |  0   |  黑  |  h灰   |
|  0   |  0   |  1   |  蓝  |  浅蓝  |
|  0   |  1   |  0   |  绿  |  浅绿  |
|  0   |  1   |  1   |  青  |  浅青  |
|  1   |  0   |  0   |  红  |  浅红  |
|  1   |  0   |  1   | 品红 | 浅品红 |
|  1   |  1   |  0   |  棕  |   黄   |
|  1   |  1   |  1   |  白  |  亮白  |

##### p110代码mbr.S剖析

**1.代码功能**

​	不使用BIOS中断的显示字符串功能，直接使用显卡在内存中的映射来显示字符

2.**实现原理**

​	显卡将自己的内存编排在了CPU可以寻址的范围之内，CPU可寻址范围中有一块区域是显卡的显存。通过对这块内存区域进行特定操作，可以让显示器显示内容

3.**代码逻辑**

​	A.清屏

​	B.显示字符

4.**如何实现**

A.指定vasart=0x7c00，告诉编译器吧程序的起始地址编译为0x7c00；

B.查询并调用BIOS中断来进行清屏（与显卡打交道实现）；

C.指定段基地址，用gs=0xb800，b800是由于显卡内存在内存中的位置决定。gs是随意选择的，也可以gs，也可以选择es，因为我们用（段基址：偏移）的形式访问显卡内存，并用规定的格式向0xb800开始的位置移入字符与颜色设定：

D.死循环；填入MBR规定510字节大小剩下的的0；固定 结尾俩字节0x55，0xaa

5.**代码**

mbr3.S文件代码

                                        ;主引导程序
                                        
                                        ;LOADER_BASE_ADDR equ 0xA000
                                        ;LOADER_START_SECTOR equ 0x2
                                        ;---------------------------------------------
SECTION MBR vstart=0x7c00
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov fs,ax
    mov sp,0x7c00
    mov ax,0xb800
    mov gs,ax
                                        ;清屏
                                        ;利用0x06号功能上卷全部行，则清屏
                                        ;
                                        ;INT x  功能号0x06 上卷窗口

                                        ;输入
                                        ;AH功能号0x06
                                        ;AL=上卷行数 如果为0表示全部
                                        ;BH=上卷行属性
                                        ;(CL,CH)=窗口左上角的(X,Y)位置
                                        ;(DL,DH)=窗口右下角(X,Y)位置
                                        ;无返回值
    
    mov ax,0600h
    mov bx,0700h
    mov cx,0                            ;左上角(0,0)
    mov dx,184fh                        ;右下角(80,25)
                                        ;VGA文本模式中一行只能容纳80个字符，共25行
                                        ;下标从0开始，所以0x18=24，0x4f=79
    int 10h                             ;int 10h
    
                                        ;输出背景色绿色，前景色红色，跳动的字符串"1 MBR"
    mov byte [gs:0x00],'1'   
    mov byte [gs:0x01],0xA4           ;A表示绿色背景色闪烁，4表示前景色为红色
    
    mov byte [gs:0x02],' ' 
    mov byte [gs:0x03],0xA4
    
    mov byte [gs:0x04],'M' 
    mov byte [gs:0x05],0xA4 
    
    mov byte [gs:0x06],'B'
    mov byte [gs:0x07],0xA4
    
    jmp $                               ;通过死循环让程序悬停
    
    times 510-($-$$) db 0
    db 0x55,0xaa  
虚拟机中汇编所需指令：

nasm -o /home/qiji-9923/bochs/mbr /home/qiji-9923/bochs/mbr3.S

dd if=/home/qiji-9923/bochs/mbr of=/home/qiji-9923/bochs/hd60M.img bs=512 count=1 conv=notrunc

bin/bochs -f bochsrc.disk

成功示意图：

![1738313178489](C:\Users\nihao\AppData\Roaming\Typora\typora-user-images\1738313178489.png)

##### MBR要加载到loader

**6.其他代码详解看书p111**

MBR只有510B，能做的事情非常少，所以我们用它把操作系统的loader加载到指定位置，然后跳转到loader执行，loader由于大小可以比MBR大得多，所以做的多。MBR要加载到loader就要借助磁盘，通过in与out指令与磁盘暴露在外的寄存器交互，用法如下：

​			**in指令用于从端口中读取数据，其一般形式是：**

​			**(1)in al,dx;**

​			**(2)in ax,dx。**

​			**其中al和ax用来存储从端口获取的数据，dx是指端口号**

**这是固定的用法，只要用in指令，源操作数（端口号）必须是dx，而目的操作数是用al还是ax取决于dx端口指代的寄存器是8位宽度还是16位**

​			**out指令用于往端口中写数据，其一般形式是：**

​			**(1)out dx,al;**

​			**(2)out dx,ax;**

​			**(3)out立即数,al;**

​			**(4)out立即数,ax。**

​	**注意：这和in指令相反，in指令的源操作数是端口号，而out指令中的目的操作数是端口号**



磁盘端口对应寄存器用途：



![1738316906652](C:\Users\nihao\AppData\Roaming\Typora\typora-user-images\1738316906652.png)

其中Status与Device寄存器比较复杂，他们的结构含义如下：

![1738317678198](C:\Users\nihao\AppData\Roaming\Typora\typora-user-images\1738317678198.png)

**（1）先选择通道，往该通道的sector count寄存器中写入待操作的扇区数。**

**(2)往该通道上的三个LBA寄存器写入扇区起始地址的低24位（分三次写，低八位中八位高八位）**

**(3)往dedvice寄存器中写入LBA地址的24~27位，并置第六位为1，使其为LBA模式，设置第四位选择操作的硬盘（master硬盘或slave硬盘）**

**(4)往该通道上的command寄存器写入操作命令（读入命令）**

**(5)读取该通道上的status寄存器，判断硬盘工作是否完成**

**(6)如果以上步骤是读取硬盘，进入下一个步骤否则完工**

**(7)将硬盘数据读出**

再写一个mbr程序，实现从磁盘中加载我们的loader

p131剖析mbr3-1.S

**1.代码功能**

​	从磁盘中加载操作系统的loader，该loader由我们自己写入磁盘

2.**实现原理**

​	目前的计算机已经将对磁盘的各种操作简化成了对磁盘暴露在外的寄存器的操作，这些操作需要通过in与out指令

3.**代码逻辑**

​	A.清屏

​	B.通过对内存特定区域的操作显示字符

​	C.从磁盘特定区域读取特定大小的数据到待定内存位置中

4.**如何实现**

A.include boot.inc  这里面定义了loader在磁盘中的位置（我们将其写入磁盘2号扇区），与loader加载进入内存后将要存放的位置（在第二章的内存布局图中找一个靠前的可用位置就行了，本代码用的是0x900）

B.定义vstart=0x7c00 调用BIOS中断清屏，对待定内存区域放入数据来显示字符

C.按照与磁盘打交道的7个步骤来完成从磁盘取出数据存放到内存指定区域（这七个步骤就是用in与out操作特定通道的寄存器）

D.跳转到内存中的loader位置执行

E.填充MBR要求的510字节剩下的0，定义MBR要求的标准结尾0x55，0xaa

5.**代码**

                                        ;主引导程序
                                        ;LOADER_BASE_ADDR equ 0xA000
                                        ;LOADER_START_SECTOR equ 0x2
                                        ;-------------------------------
%include"boot.inc"                                      
SECTION MBR vstart=0x7c00
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    mov fs,ax
    mov sp,0x7c00
    mov ax,0xb800
    mov gs,ax
                                        ;清屏
                                        ;利用0x06号功能上卷全部行，则清屏
                                        ;INT x  功能号0x06 上卷窗口
                                        ;输入
                                        ;AH功能号0x06
                                        ;AL=上卷行数 如果为0表示全部
                                        ;BH=上卷行属性
                                        ;(CL,CH)=窗口左上角的(X,Y)位置
                                        ;(DL,DH)=窗口右下角(X,Y)位置
                                        ;无返回值
    mov ax,0600h
    mov bx,0700h
    mov cx,0                            ;左上角(0,0)
    mov dx,184fh                        ;右下角(80,25)
                                        ;VGA文本模式中一行只能容纳80个字符，共25行
                                        ;下标从0开始，所以0x18=24，0x4f=79
    int 10h                             ;int 10h
                                        ;输出背景色绿色，前景色红色，跳动的字符串"1 MBR"
    mov byte [gs:0x00],'1'   
    mov byte [gs:0x01],0xA4           ;A表示绿色背景色闪烁，4表示前景色为红色
    
    mov byte [gs:0x02],' ' 
    mov byte [gs:0x03],0xA4
    
    mov byte [gs:0x04],'M' 
    mov byte [gs:0x05],0xA4 
    
    mov byte [gs:0x06],'B'
    mov byte [gs:0x07],0xA4
    
    mov eax,LOADER_START_SECTOR          ;起始扇区1ba地址
    mov bx,LOADER_BASE_ADDR              ;写入的地址
    mov cx,1                             ;带读入的扇区数
    call rd_disk_m_16                    ;以下读程序的起始部分(一个扇区)
    
    jmp LOADER_BASE_ADDR
                                         ;功能：读取硬盘n个扇区
rd_disk_m_16                            
                                        ;eax=LBA扇区号
                                        ;ebx=将数据写入的内存地址
                                        ;ecx=读入的扇区数
    mov esi,eax                         ;备份eax
    mov di,cx                           ;备份cx
                                        ;读写硬盘
                                        ;先选择特定通道寄存器设置要读取的扇区数
    mov dx,0x1f2                                   
    mov al,cl
    out dx,al                           ;读取的扇区数

    mov eax,esi                         ;恢复ax
                                        ;第二步：在特定通道寄存器中放入要读取扇区的地址，将LBA地址存入0x1f3~0x1f6
                                        ;LBA地址7~0位写入端口0x1f3
    mov dx,0x1f3
    out dx,al
                                        ;LBA地址15~8位写入端口0x1f4
    mov cl,8
    shr eax,cl          ;把eax右移八位,高八位补0,实现中八位变低八位
    mov dx,0x1f4
    out dx,al
                                        ;LBA地址23~16位写入端口0x1f5
    shr eax,cl
    mov dx,0x1f5
    out dx,al
    
    shr eax,cl
    and al,0x0f                         ;lba第24~27位
    or al,0xe0                          ;设置7~4位为1110,表示lba模式
    mov dx,0x1f6
    out dx,al
    
                                        ;第三步向0x1f7端口写入读命令,0x20
    mov dx,0x1f7
    mov al,0x20
    out dx,al
                                        ;第四步,检测硬盘状态
.not_ready:                        
                                        ;同一端口，写时表示写入命令字，读时表示读入硬盘状态
    nop                                 ;nop停滞一下为了等待硬盘是否准备好
    in al,dx
    and al,0x88                         ;第四位为1表示硬盘控制器已准备好数据传输，第七位为1表示硬盘忙
    cmp al,0x08                         
    jnz .not_ready                      ;若未准备好，继续等   

                                        ;第五步，从0x1f0端口读数据
    mov ax,di                           ;di当中存储的是要读取的扇区数
    mov dx,256                          ;每个扇区512字节，一次读取俩个字节所以一个扇区就要读256次，与扇区数相乘就得到总读取次数
    mul dx                              ;8位乘法与16位乘法看书p133，16位乘法会改变dx的值
    mov cx,ax                           ;得到了要读取的总次数然后将这个数字放入cx中
    mov dx,0x1f0
.go_on_read:
    in ax,dx
    mov [bx],ax                         ;没有表明则bx默认配[ds：bx]
    add bx,2
    loop .go_on_read
    ret

    times 510-($-$$) db 0
    db 0x55,0xaa
所需要用到的loader.S

%include"boot.inc"
section loader vstart=LOADER_BASE_ADDR
                                    ;输出背景色绿色，前景色红色，跳动的字符串"1 MBR"
mov byte [gs:0x00],'2' 
mov byte [gs:0x01],0xA4             ;A表示绿色背景色闪烁，4表示前景色为红色
    
mov byte [gs:0x02],' ' 
mov byte [gs:0x03],0xA4
    
mov byte [gs:0x04],'L' 
mov byte [gs:0x05],0xA4
    
mov byte [gs:0x06],'O'
mov byte [gs:0x07],0xA4

mov byte [gs:0x08],'A' 
mov byte [gs:0x09],0xA4
    
mov byte [gs:0x0a],'D' 
mov byte [gs:0x0b],0xA4
    
mov byte [gs:0x0c],'E' 
mov byte [gs:0x0d],0xA4
    
mov byte [gs:0x0e],'R'
mov byte [gs:0x0f],0xA4

jmp $                               ;用死循环使程序悬停

虚拟机中的命令：

nasm -o /home/qiji-9923/bochs/mbr /home/qiji-9923/bochs/chapter_3/mbs3-1.S -I /home/qiji-9923/bochs/chapter_3/include/
dd if=/home/qiji-9923/bochs/mbr of=/home/qiji-9923/bochs/hd60M.img bs=512 count=1 conv=notrunc
nasm -o /home/qiji-9923/bochs/loader /home/qiji-9923/bochs/chapter_3/loader.S -I /home/qiji-9923/bochs/chapter_3/include/
dd if=/home/qiji-9923/bochs/loader of=/home/qiji-9923/bochs/hd60M.img bs=512 count=1 conv=notrunc seek=2
执行
bin/bochs -f bochsrc.disk

