# SP_Ultra_CAP

### 目录

[SP\_Ultra\_CAP](#sp_ultra_cap)

    - [目录](#目录)
        - [项目所属：河北工业大学\_山海Mas战队	Sirius\_P](#项目所属河北工业大学_山海mas战队sirius_p)
    - [最后更新时间：2023.4.29](#最后更新时间2023429)
    - [文件目录](#文件目录)
    - [简介](#简介)
            - [测试视频：【Robomaster超级电容功能展示（默剧）（最高集成度\&较低成本）】](#测试视频robomaster超级电容功能展示默剧最高集成度较低成本)
            - [外设一览：](#外设一览)
            - [以下为渲染预览图，使用渲染软件keyshot](#以下为渲染预览图使用渲染软件keyshot)
            - [实物焊接图（因为喷了三防漆可能有点影响观感）](#实物焊接图因为喷了三防漆可能有点影响观感)
            - [**项目方案优点**](#项目方案优点)
            - [**项目方案缺点**](#项目方案缺点)
    - [硬件框图](#硬件框图)
    - [软件框图](#软件框图)

### 项目所属：河北工业大学_山海Mas战队	Sirius_P

​	我们是于2022年成立，2023年第一次参赛的新战队，还请各位大佬们多多指教。

### 最后更新时间：2023.4.29

### 文件目录

│  LICENSE

│  README.md

│  文件目录.txt

│  生成文件目录.bat

│  

├─Doc

│      代码控制框图.drawio.html

│      设计电源拓扑.drawio.html

│ 

├─HARDWARE

│  ├─CAP_Group

│  │      CAP_Group.PcbDoc

│  │      CAP_Group.pdf

│  │      CAP_Group.PrjPcb

│  │      CAP_Group.SchDoc

│  │      README.md

│  │ 

│  └─Ultra_CAP_Ctrl

│          Digital.SchDoc

│          Power.SchDoc

│          README.md

│          Ultra_CAP.PcbDoc

│          Ultra_CAP.pdf

│          Ultra_CAP.PrjPcb

│       

├─MATLAB

│      buck_boost.slx

│      buck_boost_mix.slx

│      README.md

│

└─SOFTWARE
        README.md

### 简介

##### 	测试视频：[【Robomaster超级电容功能展示（默剧）（最高集成度&较低成本）】](https://www.bilibili.com/video/BV1DM4y127du/?share_source=copy_web&vd_source=c66b5cf402383e929f3b27696605cd3c) 

​	该项目用作于Robomaster电容管理，使用单板在7.62cm* 7.62cm*2.5cm（高度主要是有个EC11旋钮有点小高）的超小体积下实现了集成度较高的双向buckboost控制。

##### 	外设一览：

-   IPS屏幕接口
-   EC11旋钮
-   蜂鸣器
-   RGB灯（三路PWM控制）
-   两路FDCAN通信
-   ICM42605陀螺仪

##### 	以下为渲染预览图，使用渲染软件keyshot

​	![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/pxy_ultracap.28.png)

​	![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/pxy_ultracap.29.png)

##### 	实物焊接图（因为喷了三防漆可能有点影响观感）

​	![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/Ultra_CAP_front.jpg)

​	![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/Ultra_CAP_back.jpg)

##### **项目方案优点**	

1.  工作模式能在buck、buck-boost、boost三种不同的工作拓扑之间进行无感切换，使得电路工作效率最大化；
2.  超高集成度，在保证体积的前提下，集成了诸多外设及其电调中心板的功能，使得底盘只需要两个pcb即可实现所有功能，节省了底盘的安装空间；
3.  超多外设使得开发板的功能能在后续工程的推进可以增加更多的功能；
4.  6层板设计，叠层结构：电源-模拟地（包括电源地）-电源-信号-数字地-信号，设计时正面器件只有功率与模拟器件，背面器件只有数字器件，使得pcb设计中所有的地回路均为最短且具有两个完整的参考地平面。两个地之间使用了一个680R@100MHz/4A的磁珠进行单点连接；
5.  在同类方案中最低的成本：电流采样运放使用NCS210RMUTAG（全新2.8774yuan一片，云汉芯城2023.1.19报价，现在好像涨了），电压跟随运放使用NCS20282FCTTAG（两路运放，全新4.61yuan一片，e络盟2023.1.17报价），桥驱使用ADP3110AKCPZ-RL（全新3.43yuan一片，e络盟2023.1.17报价），MOS使用国产HYG025N06LS1C2（60V/170A 全新4.11yuan一片，立创2023.4.29报价），电感使用国产TMPC1707HP-100MG-D（10uH/16.5A/11.8mΩ 全新7.1yuan一片，立创2023.4.29报价）。上述都是buckboost实现的核心组件，也是各大学校最堆料的一些组件，选型仅供参考，报价均按1个购买价格计算，并非梯度价格；
6.  极高的控制频率：PWM控制频率200k，让你体验几乎瞬时的功率响应，实现方式请移步SOFTWARE readme；
7.  拥有众多保护功能，包括不限于：输入过压保护，输入掉压保护，输出过流保护，输出过压保护等；
8.  *这一块板子没有经过任何迭代，初版即为最终版。

##### 	**项目方案缺点**

1.  电流采样使用了采样滤波电路，导致电流采样放大后的电压有线性误差，每个板子需要单独校准电流参数；

### 硬件框图

**使用drawio绘制，HTML请移步Doc文件夹**

![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/设计电源拓扑.png)

### 软件框图

**使用drawio绘制，HTML请移步Doc文件夹**

软件框图是当时给自己提供代码功能设计思路用的，实际实现的方式可能与框图中有些不一样（PS：因为框图是写代码之间先画的，所以肯定会和实现差比较多，因为我是懒狗就还没更新，等后续有时间了再更新一下）

![](https://raw.githubusercontent.com/Sirius-RX/blogimg/main/img/代码控制框图.png)

### 

