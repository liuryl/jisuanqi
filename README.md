# jisuanqi
使用windows的qt是发布程序需要在qt的命令行工具中输入windeployqt+需要release的.exe的地址，在qt终端中运行
因为qt中使用release发布的程序未包含程序所需的库文件


#如何在开发模式下直接执行Debug的.exe文件
系统属性-高级设置-环境变量
系统变量-path-添加文件夹（qt-qt版本号-mingw-bin）
无法连接到库的时候：
在qt的tools中找到mingw-bin
配置到最前边!
![iShot_2023-04-13_22 28 35](https://user-images.githubusercontent.com/63986390/231791573-4a5a9efd-34d6-4b53-8452-8abac1f1f431.gif)
