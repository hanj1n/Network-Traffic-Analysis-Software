# 网络流量分析软件
（基于QT和WINPCAP的低配版wireshark）

### 1. 开发环境

基于Windows10环境

GUI界面选择qt 5.11，功能接口选择winpcap

winpcap官方中文文档：www.ferrisxu.com/WinPcap/html/index.html

### 2. 实现功能

①具有可视化界面（GUI）；

②能够将报文在网络层IPv4、IPv6、ARP和传输层UDP、TCP逐字段展开；

③具有简单的过滤器设计功能；

④统计数据并表格显示（如统计IPv4报文、IPv6报文、UDP报文、TCP报文、ARP报文等），其中，IPv4和IPv6以饼图统计、TCP、UDP和ARP以柱状图显示；

⑤采集到的数据，可另存为一个pac文件，并能被自己的软件所读取和展示；

⑥该软件运行时，不影响机器正常使用

⑦复杂过滤器的设计

⑧后台加载数据包内容的功能

⑨界面是否显示搜索筛选栏的功能

### 3. 效果图

![image-20210115195952553](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20210115195952553.png)

![image-20210115200023127](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20210115200023127.png)

![image-20210115200008262](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20210115200008262.png)

