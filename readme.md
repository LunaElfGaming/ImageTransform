 ## 仿射变换

项目transform对图片*Lena.bmp*分别做了平移变换、放缩变换和旋转变换，其中放缩变换和旋转变换分别用最近邻插值和双线性插值输出了不同的结果。程序依赖3.4.1版本opencv，项目内已包含依赖的执行文件，需要链接器的附加依赖项opencv_world341d.lib。 

#### 程序流程

主程序在读取图片后分别调用了三个函数，分别是translation平移变换、expansion放缩变换、rotation旋转变换。

1. 平移变换具体为x方向正向移动30、y方向正向移动60，具体变换见于函数*trans1，*具体效果如下：

![catch1](https://github.com/LunaElfGaming/ImageTransform/raw/master/catch1.PNG)

​	结果保存于*translation.png*，若导入原图在文档中看不出平移效果而采用了程序结果的截图。

2. 放缩变换为将图片放大1.5倍，由于灰度插值需要的是逆变换，trans_inv是将图片缩小1.5倍到原图的逆变换。在*expansion*函数中，对图像res采用最近邻插值处理，所有像素的灰度值都用逆变换后的原图像素灰度来赋值。res2采用双线性插值，从公式中简化出的具体步骤为：$若逆变换后的像素点坐标为(x+u,y+v)，其中x,y为整数，u,v为小数，则灰度值取:\\(1-u)*(1-v)*g_{x,y}+(1-u)*v*g{x,y+1}+u*(1-v)*g_{x+1,y}+u*v*g_{x,y}$

   处理结果分别如下：

   ![expansion1](https://github.com/LunaElfGaming/ImageTransform/raw/master/transform/expansion1.png)
   ![expansion2](https://github.com/LunaElfGaming/ImageTransform/raw/master/transform/expansion2.png)

   明显能够看出，采用最近邻插值的第一张图马赛克非常明显，而双线性插值的图二则很平滑。

3. 旋转变换对应于rotation，将图片顺时针旋转30°，为了保证图片完整，实际处理中是先旋转30°后向右平移了100距离，所以逆变换是向左平移100，再逆时针旋转到正确位置。

   关于灰度插值不再赘述，具体结果如下：

   

   ![rotation1](https://github.com/LunaElfGaming/ImageTransform/raw/master/transform/rotation1.png)

   ![rotation2](https://github.com/LunaElfGaming/ImageTransform/raw/master/transform/rotation2.png)

   可以从头发或身体等色差比较明显的边界看出，双线性插值达到了一种类似对前一张图做抗锯齿的效果。

#### 程序运行

程序每次执行都会重新保存五张处理结果图，同时为了直观观看会打开五个窗口，从Test1到Test5，分别是平移、放缩+最近邻、放缩+双线性、旋转+最近邻、旋转+双线性的结果。按键盘任意键，所有窗口关闭并且程序结束执行。

