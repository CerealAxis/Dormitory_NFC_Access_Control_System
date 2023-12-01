#  Dormitory_NFC_Access_Control_System
## 基于Arduino搭建的宿舍NFC门禁系统

### 目录
1. [开发原因](#开发原因)
2. [所需硬件](#所需硬件)
    1. 必备硬件
    2. 选配硬件
    3. 推荐购买的工具
3. [主体接线图](#主体接线图)
    - Arduino UNO引脚说明图
    - SG90舵机的接线
    - RC522的接线
4. [软件和代码部分](#软件和代码部分)
5. [电源问题](#电源问题)
6. [成品图](#成品图)


### 开发原因

宿舍被分到老宿舍，没门禁系统，只能用钥匙（忘带钥匙的痛你们知道嘛）！恰好高中的时候有接触Arduino这类单片机的开发，于是乎决定对宿舍大门进行微改造，加上一套基于Arduino开发的NFC门禁系统。

### 所需硬件
#### 2.1 必备硬件
1. Arduino UNO开发板✖1（理由：成本便宜，一块板就十多块钱，且拓展性极强。没有必要买意大利原板，国产的也能用）

2. 杜邦线 （公对公 母对母的建议都准备些，用于连接线路）

3. SG90舵机 90-180度范围（别杠为什么不用15KG及以上的舵机，问就是一个字，贵！而且经过实测，sg90这款9g的舵机能够满足我的需求，最后就选用了这款（3块钱的舵机真香！））

4. RC522射频模块（一定要选已经焊接好排针的，会省事很多。建议买商家配好的配件，可以省得去其他店铺再购买一张白卡）

#### 2.2 选配硬件
1. 0.96寸 4针OLED显示屏（一开始代码里面是有包括屏幕显示的代码的，显示屏也买回来了，但是最后真正使用的时候感觉加个屏幕很鸡肋，就移除了这个。如果需要可以在我的代码上简单修改就可以支持使用了）
#### 2.3 推荐购买的工具
1. 热熔胶枪（方便固定线路）
2. 长的排插（用于供电）

### 主体接线图
#### Arduino UNO引脚说明图
[![引脚说明](https://pic.imgdb.cn/item/6569de45c458853aef9dc919.jpg "引脚说明")](https://pic.imgdb.cn/item/6569de45c458853aef9dc919.jpg "引脚说明")

以上是UNO板上各个引脚名字的说明，下面详细介绍舵机和NFC模块的接线。

#### SG90舵机的接线
舵机上的黑线——UNO板上的GND口

红色——主板上的5V口

黄色线——主板上数字8对应的接口

#### RC522的接线
RC522——UNO板

3.3V——3.3V

RST——数字9对应的接口

GND——GND

MISO——数字12对应的接口

MOSI——数字11对应的接口

SCK——数字13对应的接口

SDA——数字10对应的接口

### 软件和代码部分
首先先安装好官方的Arduino IDE(可前往官网：https://www.arduino.cc/en/software 自行下载)

首次使用Arduino IDE的同学需要先安装这几个库，步骤如下：

打开工具，找到里面的管理库

[![打开工具](https://pic.imgdb.cn/item/6569e7dfc458853aefcd5dc5.jpg "打开工具")](https://pic.imgdb.cn/item/6569e7dfc458853aefcd5dc5.jpg "打开工具")

搜索并安装MFRC522库（如下图所示，版本选最新即可）

[![MFRC](https://pic.imgdb.cn/item/6569e8a6c458853aefd0f72f.jpg "MFRC")](https://pic.imgdb.cn/item/6569e8a6c458853aefd0f72f.jpg "MFRC")

搜索并安装SSD1306库（如下图所示）

[![SSD1306](https://pic.imgdb.cn/item/6569e91dc458853aefd31966.jpg "SSD1306")](https://pic.imgdb.cn/item/6569e91dc458853aefd31966.jpg "SSD1306")

下载好后，下载仓库内的NFC.ino文件（在NFC文件夹里面），然后用Arduino IDE打开，最后将Arduino开发板连接到电脑上，点击上传即可。

[![上传](https://pic.imgdb.cn/item/6569e99bc458853aefd5b70d.jpg "上传")](https://pic.imgdb.cn/item/6569e99bc458853aefd5b70d.jpg "上传")

**怎么将自己的校园卡或者门禁卡添加到程序中呢？**

上传程序后，打开串口监视器

[![串口监视器](https://pic.imgdb.cn/item/6569ea67c458853aefd94f25.jpg "串口监视器")](https://pic.imgdb.cn/item/6569ea67c458853aefd94f25.jpg "串口监视器")

然后会显示一串十六位进制的UID（例如22B3A455）
在将其拆分成四组数（22 B3 A4 55），然后修改此处的代码

[![代码](https://pic.imgdb.cn/item/6569ebd1c458853aefdfe3a7.jpg "代码")](https://pic.imgdb.cn/item/6569ebd1c458853aefdfe3a7.jpg "代码")
把红色框内的两位数字改成你前面所拆分的四组数（0x不变），即可添加你的门禁卡了

### 电源问题
我是采用Arduino UNO板上自带的Type B口接上适配器进行供电的，老铁们可以自行选择。

### 成品图

[![成品图](	 https://pic.imgdb.cn/item/6569ecfdc458853aefe54209.jpg "成品图")](	 https://pic.imgdb.cn/item/6569ecfdc458853aefe54209.jpg "成品图")