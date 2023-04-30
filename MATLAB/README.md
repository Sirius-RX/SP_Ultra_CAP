# SP_Ultra_CAP

### 目录内容

此文件夹用以存放Simulink仿真文件

### 文件简介

buck_boost.slx：电路buck工作模式时的仿真文件

buck_boost_mix.slx：电路buck-boost工作模式时的仿真文件

### 文件使用环境

Matlab 2023a

### 文件使用方法

文件主要是用来验证设计合理性和调整PID参数，PID参数调整方法如下：

1.  先将系统中输出的变量调整至由一个PID环决定；
2.  选中Simulink库中的PID模型并点开；
3.  打开后点击自动调节栏目中的调节按钮（注意调节方式选择基于频率相应）；
4.  配置好对应的参数之后点击调节，具体参数的含义及其配置方式可以参考Matlab官方教程，链接如下：[Design PID Controller Using Plant Frequency Response Near Bandwidth - MATLAB & Simulink - MathWorks 中国](https://ww2.mathworks.cn/help/slcontrol/ug/design-pid-controller-using-plant-frequency-response-near-bandwidth.html)；
5.  在上述自动调整器输出的结果上微调，直至达到自己认为的理想情况。