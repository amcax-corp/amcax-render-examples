# AMCAXRenderSample

AMCAXRender SDK 示例程序

## 运行注意事项
1. 该示例程序生成的可执行程序，对应的createEntityFromJson示例程序，需要resources文件下的prism.json文件复制到可执行程序目录下。
2. VisltPseudoColor、VisltPseudoColorClip和VisltPseudoColorSlicer需要resources文件下的meshtally.vtk复制到可执行程序目录下。
3. VisltVolume和VisltVolumeSlicer需要resources文件下的FullHead.mhd和FullHead.raw.gz文件复制到可执行程序目录下。
## 依赖库
### QT6
1. 已测试版本号为6.5.3
## 内源依赖库
1. AMCAXKernel和AMCAXRender，需要下载对应的模块SDK。
## 打开终端
1. 在每个模块的示例代码的文件目录下，运行终端
2. 参考配置命令
```powershell
cmake -B ./build/ `
    -DAMCAX_DIR="D:/code/2024/project/AMCAXRenderSample1/Packages/AMCAXKernel" `
    -DAMCAXRender_PATH="D:/code/2024/project/AMCAXRenderSample1/Packages/AMCAXRender" `
    -DCMAKE_PREFIX_PATH="D:/install/QT/6.5.3/msvc2019_64/"
```
参考编译命令
```powershell
    cmake --build ./build/ --config Release -j8
```

