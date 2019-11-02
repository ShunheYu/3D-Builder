# 3D-Builder

## 编译说明：

在VS中的项目属性中修改VC++包含目录和库目录，将第三方库和Qt库路径设置正确

## 第三方库说明：

- include下assimp库：可导入大量3D模型和导出数种主流模型文件的库
- lib下assimp-*文件：assimp库对应的动态链接库，必须添加到程序根目录
- lib下zlib.dll文件：assimp库使用到的压缩库，必须添加到程序根目录